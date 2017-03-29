########################################################################
#
#	File:			EmRPC.pm
#
#	Purpose:		Low-level functions for using RPC with the Palm OS
#					Emulator.
#
#	Description:	This file contains base functions for using RPC:
#
#					OpenConnection
#						Opens a socket to the Emulator
#
#					CloseConnection
#						Closes the socket
#
#					DoRPC
#						Full-service RPC packet sending and receiving,
#						including marshalling and unmarshalling of
#						parameters.
#
#					ReadBlock
#						Read up to 256 bytes from the remote device's
#						memory.
#
#					WriteBlock
#						Write up to 256 bytes to the remote device's
#						memory.
#
#					ReadString
#						Read a C string from the remote device's memory.
#
#					PrintString
#						Debugging utility.  Prints a Perl string
#						(block of arbitrary data) as a hex dump.
#
########################################################################

package EmRPC;

use vars qw(@ISA @EXPORT);

use Exporter;
$VERSION = 1.00;
@ISA = qw(Exporter);

@EXPORT = qw(
	OpenConnection CloseConnection
	DoRPC
	ReadBlock WriteBlock
	ReadString PrintString
);

use IO::Socket;
use IO::File;

use constant slkSocketDebugger		=>	0;	# Debugger Socket
use constant slkSocketConsole		=>	1;	# Console Socket
use constant slkSocketRemoteUI		=>	2;	# Remote UI Socket
use constant slkSocketDLP			=>	3;	# Desktop Link Socket
use constant slkSocketFirstDynamic	=>	4;	# first dynamic socket ID
use constant slkSocketPoserRPC		=> 14;

use constant slkPktTypeSystem		=>	0;	# System packets
use constant slkPktTypeUnused1		=>	1;	# used to be: Connection Manager packets
use constant slkPktTypePAD			=>	2;	# PAD Protocol packets
use constant slkPktTypeLoopBackTest	=>	3;	# Loop-back test packets


########################################################################
#
#	FUNCTION:		OpenConnection
#
#	DESCRIPTION:	Open a socket-based connection to Poser.
#
#	PARAMETERS:		Either "[<host>][:[<port>]]" (defaults are localhost and
#					6415) to connect to an IPv4 socket, or a filename (with
#					at least one "/") to open a file (eg a device file), or
#					"@<fd>" to reopen an existing fd.
#
#					"#<socket>" can be added to any of these, and causes the
#					given SLK socket to be used instead of slkSocketPoserRPC.
#
#					The older form with two parameters, (<port> <host>), is
#					equivalent to "<host>:<port>".
#
#	RETURNED:		Nothing. Dies if fail to connect.
#
########################################################################

sub OpenConnection
{
	# Are we already connected?
	return if defined $sock;

	# Rewrite the old two parameter (<port> <host>) form as <host>:<port>
	local ($_) = join ":", reverse @_;
	$_ = ":$_" unless /\D/;  # Handle two parameters with <host> omitted

	my $sname = (s/#(.*)//)? $1 : "PoserRPC";
	$sname = "slkSocket\u$sname" unless $sname =~ /slkSocket/;
	$sock_slkSocket = eval $sname;
	die "invalid SLK socket '$sname'\n" if $sock_slkSocket =~ /\D/;

	if (/^@(\d+)/)
	{
		my $fd = $1;
		$sock = new_from_fd IO::Handle ($fd, "r+")
			or die "cannot reopen fd $fd: $!\n";
	}
	elsif (m"/")
	{
		$sock = new IO::File ($_, O_RDWR)
			or die "cannot open $_: $!\n";
	}
	else
	{
		my ($remote, $port) = split /:/, $_;
		$remote = "localhost" unless $remote;
		$port = 6415 unless $port;

		$sock = new IO::Socket::INET(	PeerAddr => $remote,
										PeerPort => $port,
										Proto => 'tcp')
			or die "cannot connect to $_: $@\n";
	}

	$sock->autoflush (1);
}


########################################################################
#
#	FUNCTION:		CloseConnection
#
#	DESCRIPTION:	Close the socket connection to Poser.
#
#	PARAMETERS:		None.
#
#	RETURNED:		Nothing.
#
########################################################################

sub CloseConnection
{
	close ($sock);
	undef $sock;
}


########################################################################
#
#	FUNCTION:		DoRPC
#
#	DESCRIPTION:	Performs full, round-trip RPC service.
#
#	PARAMETERS:		Trap word of function to call.
#					Format string describing parameters.
#					Parameters to pass in the RPC call.
#
#					The format string contains a series of format
#					descriptors.  Descriptors must be seperated by
#					some sort of delimiter, which can be a space, a
#					common, a colon, or any combination of those. Each
#					descriptor has the following format:
#
#						<type><optional size><optional "*">
#
#					The "type" describes the parameter in the format
#					expected by the Palm OS.  The RPC routines will
#					convert the Perl variable corresponding to the
#					parameter into the described type.  The following
#					types are supported:
#
#						int:		integer
#						Err:		2 byte integer
#						Coord:		2 byte integer;
#						LocalID:	4 byte integer
#						HostErr:	4 byte integer
#						string:		C string
#						rptr:		Pointer to something back on
#									the emulated device
#						point:		Palm OS PointType
#						rect:		Palm OS RectangleType
#						block:		Block of arbitrary data
#
#					Some format types can accept a size specifier
#					after them.  This size specifier is used when
#					a default parameter size cannot be implied, or
#					when you want to override the default parameter
#					size.  The following describes how the size
#					specifier is handled for each parameter type:
#
#						int:
#							Length specifier must be supplied, and
#							must be one of 8, 16, or 32.
#
#						string:
#							Default length is the value as returned
#							by Perl's "length" function plus one.
#							You can override this value by including
#							your own length specifier.
#
#						block:
#							Default length is the value as returned
#							by Perl's "length" function.  You can
#							override this value by including your
#							own length specifier.
#
#						all others:
#							Any specified size is ignored.
#
#					In general, integer types are passed by value, and
#					all other types are passed by reference.  That is
#					after all the parameters are marhsalled, sent to
#					the emulator, and unmarshalled, the "pass by value"
#					parameters are pushed directly onto the emulated
#					stack, and "pass by reference" parameters have
#					their addresses pushed onto the stack.  You can
#					can change this behavior in one way: if you way
#					an integer to be passed by reference, then you
#					can append a "*" to its format specifier.
#
#					Examples:
#
#						"int16"
#							Pass a 2 byte integer
#
#						"int32 string"
#							Pass a 4 byte integer, followed by
#							a C-string
#
#						"block32"
#							Pass a 32 byte buffer, filling in
#							its contents as much as possible
#							with the given data
#
#						"int16 in32 int32*"
#							Pass a 2 byte integer, followed by
#							a 4 byte integer, followed by a
#							4 byte integer passed by reference.
#
#	RETURNED:		List containing:
#						Register D0
#						Register A0
#						Full parameter list.  If any parameters were
#							"pass by reference", you'll receive the
#							updated parameters.  If parameters are
#							"pass by value", you'll get them back just
#							the same way you provided them.
#
########################################################################

sub DoRPC
{
	my ($trap_word, $format, @parameters) = @_;

	my ($slkSocket)		= $sock_slkSocket;
	my ($slkPktType)	= slkPktTypeSystem;
	my ($send_body)		= EmRPC::MakeRPCBody ($trap_word, $format, @parameters);

	my ($packet) = MakePacket($slkSocket, $slkSocket, $slkPktType, $send_body);

	SendPacket($packet);

	my ($header, $body, $footer) = ReceivePacket();

	EmRPC::UnmakeRPCBody ($body, $format);
}


########################################################################
#
#	FUNCTION:		ReturnValue
#
#	DESCRIPTION:	.
#
#	PARAMETERS:		.
#
#	RETURNED:		.
#
########################################################################

sub ReturnValue
{
	my ($format, $D0, $A0, @parameters) = @_;

	my ($type, $size, $by_ref) = GetFormat ($format, 0);

	my ($result);

	if ($type eq "int")
	{
		return $D0;
	}
	elsif ($type eq "string")
	{
		return ($A0, ReadString ($A0));
	}
	elsif ($type eq "rptr")
	{
		return $A0;
	}

	die "Unexpected type \"$type\" in EmRPC::ReturnValue, stopped";
}


########################################################################
#
#	FUNCTION:		ReadBlock
#
#	DESCRIPTION:	Read a range of memory from the remote device.
#
#	PARAMETERS:		address of remote device to start reading from.
#					number of bytes to read (256 max).
#
#	RETURNED:		A Perl string containing the result.
#
########################################################################

$sysPktReadMemCmd		= 0x01;
$sysPktReadMemRsp		= 0x81;

	#	typedef struct SysPktReadMemCmdType {
	#		_sysPktBodyCommon;								// Common Body header
	#		void*					address;				// Address to read
	#		Word					numBytes;				// # of bytes to read
	#		} SysPktReadMemCmdType;
	#	typedef SysPktReadMemCmdType*	SysPktReadMemCmdPtr;
	#	
	#	typedef struct SysPktReadMemRspType {
	#		_sysPktBodyCommon;								// Common Body header
	#		// Byte				data[?];					// variable size
	#		} SysPktReadMemRspType;
	#	typedef SysPktReadMemRspType*	SysPktReadMemRspPtr;

sub ReadBlock
{
	my ($address, $num_bytes) = @_;

	my ($slkSocket)		= $sock_slkSocket;
	my ($slkPktType)	= slkPktTypeSystem;
	my ($send_body)		= pack ("cxNn", $sysPktReadMemCmd, $address, $num_bytes);

	my ($packet) = MakePacket($slkSocket, $slkSocket, $slkPktType, $send_body);

	SendPacket($packet);

	my ($header, $body, $footer) = ReceivePacket();

	unpack ("xx a$num_bytes", $body);
}


########################################################################
#
#	FUNCTION:		WriteBlock
#
#	DESCRIPTION:	Write a range of bytes to the remote device.
#
#	PARAMETERS:		address to start writing to.
#					a Perl string containing the stuff to write.
#
#	RETURNED:		nothing
#
########################################################################

$sysPktWriteMemCmd		= 0x02;
$sysPktWriteMemRsp		= 0x82;

	#	typedef struct SysPktWriteMemCmdType {
	#		_sysPktBodyCommon;								// Common Body header
	#		void*				address;					// Address to write
	#		Word				numBytes;					// # of bytes to write
	#		// Byte				data[?];					// variable size data
	#		} SysPktWriteMemCmdType;
	#	typedef SysPktWriteMemCmdType*	SysPktWriteMemCmdPtr;
	#	
	#	typedef struct SysPktWriteMemRspType {
	#		_sysPktBodyCommon;								// Common Body header
	#		} SysPktWriteMemRspType;
	#	typedef SysPktWriteMemRspType*	SysPktWriteMemRspPtr;

sub WriteBlock
{
	my ($address, $data) = @_;

	my ($slkSocket)		= $sock_slkSocket;
	my ($slkPktType)	= slkPktTypeSystem;
	my ($send_body)		= pack ("cxNn", $sysPktWriteMemCmd, $address, length ($data)) . $data;

	my ($packet) = MakePacket($slkSocket, $slkSocket, $slkPktType, $send_body);

	SendPacket($packet);

	ReceivePacket();	# receive the results, but we don't need to do anything with them
}


########################################################################
#
#	FUNCTION:		SendPacket
#
#	DESCRIPTION:	Send a fully-built packet to Poser.  The socket
#					connection to Poser should already have been
#					established
#
#	PARAMETERS:		The packet to be sent.
#
#	RETURNED:		Nothing.
#
########################################################################

sub SendPacket
{
	my ($packet) = @_;

	print $sock $packet;
}


########################################################################
#
#	FUNCTION:		ReceivePacket
#
#	DESCRIPTION:	Receive a packet from Poser.
#
#	PARAMETERS:		None.
#
#	RETURNED:		The packet header, body, and footer as an array.
#
########################################################################

sub ReceivePacket
{
	my ($header, $body, $footer);

	my ($header_length) = 10;
	sysread($sock, $header, $header_length);

	my ($body_length) = GetBodySize($header);
	sysread($sock, $body, $body_length);

	my ($footer_length) = 2;
	sysread($sock, $footer, $footer_length);

	($header, $body, $footer);
}


########################################################################
#
#	FUNCTION:		MakePacket
#
#	DESCRIPTION:	Builds up a complete packet for sending to Poser
#					including the header, body, and footer.
#
#	PARAMETERS:		$src - the source SLP socket.  Generally something
#						like slkSocketDebugger or slkSocketConsole.
#
#					$dest - the destination SLP socket.
#
#					$type - the type of packet.  Generally something
#						like slkPktTypeSystem or slkPktTypePAD.
#
#					$body - the body of the packet.
#
#	RETURNED:		The built packet as a Perl string.  The header and
#					footer checksums will be calculated and filled in.
#
########################################################################

	#	struct SlkPktHeaderType
	#	{
	#		Word	signature1;		// X  first 2 bytes of signature
	#		Byte	signature2;		// X  3 and final byte of signature
	#		Byte	dest;			// -> destination socket Id
	#		Byte	src;			// -> src socket Id
	#		Byte	type;			// -> packet type
	#		Word	bodySize;		// X  size of body
	#		Byte	transID;		// -> transaction Id
	#								//    if 0 specified, it will be replaced 
	#		SlkPktHeaderChecksum	checksum;	// X  check sum of header
	#	};
	#
	#	struct SlkPktFooterType
	#	{
	#		Word	crc16;			// header and body crc
	#	};

$header_template = "H6CCCnCC";		# 6 Hex digits, 3 unsigned chars, a B.E. short, 2 unsigned chars
$footer_template = "n";				# a B.E. short

$signature = "BEEFED";

sub MakePacket
{
	my ($src, $dest, $type, $body) = @_;

	if (not defined($transID))
	{
		$transID = 0;
	}

	++$transID;

	my ($bodySize) = length ($body);
	my ($header_checksum) = CalcHeaderChecksum ($signature, $dest, $src, $type, $bodySize, $transID);

	my ($header) = pack ($header_template, $signature, $dest, $src, $type, $bodySize, $transID, $header_checksum);

	my ($footer_checksum) = CalcFooterChecksum ($header, $body);
	#my ($footer_checksum) = 0;
	my ($footer) = pack ($footer_template, $footer_checksum);

	$header . $body . $footer;
}


########################################################################
#
#	FUNCTION:		CalcHeaderChecksum
#
#	DESCRIPTION:	Calculate that checksum value for the packet header.
#
#	PARAMETERS:		The components of the header.
#
#	RETURNED:		The checksum that should be placed in the SLP
#					packet header.
#
########################################################################

sub CalcHeaderChecksum
{
	my ($signature, $dest, $src, $type, $bodySize, $transID) = @_;

	my ($checksum, $temp_buffer);

	$checksum = 0;

	$temp_buffer = pack ($header_template, $signature, $dest, $src, $type, $bodySize, $transID, 0);
	@bytes = unpack("C9", $temp_buffer);
	$checksum = $bytes[0] + $bytes[1] + $bytes[2] + $bytes[3] + $bytes[4] +
				$bytes[5] + $bytes[6] + $bytes[7] + $bytes[8];

	$checksum % 256;
}


########################################################################
#
#	FUNCTION:		CalcFooterChecksum
#
#	DESCRIPTION:	Calculate the checksum value for the packet footer.
#
#	PARAMETERS:		The header and body.
#
#	RETURNED:		The checksum that should be placed in the SLP
#					packet footer.
#
########################################################################

sub Crc16CalcBlock
{
	my ($data) = @_;
	my ($crc, $i, $a, $b);

	my (@crctt) =
		(
		0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
		0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
		0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
		0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
		0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
		0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
		0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
		0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
		0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
		0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
		0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
		0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
		0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
		0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
		0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
		0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
		0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
		0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
		0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
		0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
		0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
		0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
		0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
		0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
		0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
		0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
		0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
		0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
		0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
		0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
		0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
		0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
		);

	@bytes = unpack('C*', $data);
	
	$crc = 0;

	foreach $i (@bytes)
	{
		$a = ($crc << 8) & 0xFFFF;
		
		$b = $crc >> 8;
		
		$crc = $a ^ $crctt [ ($b ^ $i) & 0xFF ];
	}

	return ($crc & 0xFFFF);
}


sub CalcFooterChecksum
{
	my ($header, $body) = @_;

	my ($checksum, $temp_buffer);

	$temp_buffer = $header . $body;

	$checksum = Crc16CalcBlock($temp_buffer);
}


########################################################################
#
#	FUNCTION:		MakeRPCBody
#
#	DESCRIPTION:	Create the body of an RPC packet, suitable for
#					being passed off to MakePacket.
#
#	PARAMETERS:		The "trap word" of the trap that needs to be called
#					(as defined by the constants in SysTraps.pm) and
#					the parameters of the RPC call, as created by the
#					MakeParam function.
#
#	RETURNED:		The body of the packet as a string.
#
########################################################################

	#	struct SysPktRPCType
	#	{
	#		_sysPktBodyCommon;		// Common Body header
	#		Word	trapWord;		// which trap to execute
	#		DWord	resultD0;		// result from D0 placed here
	#		DWord	resultA0;		// result from A0 placed here
	#		Word	numParams;		// how many parameters follow
	#		// Following is a variable length array ofSlkRPCParamInfo's
	#		SysPktRPCParamType	param[1];
	#	};

$rpc_header_template	= "CxH4NNn";		# unsigned byte, filler, 4 hex digits, 2 B.E. longs, B.E. short
$sysPktRPCCmd			= 0x0A;
$sysPktRPCRsp			= 0x8A;

sub MakeRPCBody
{
	my ($trapword, $format, @param_list) = @_;

	my ($rpc_header) = pack ($rpc_header_template, $sysPktRPCCmd, $trapword, 0, 0, $#param_list + 1);
	my ($rpc_body) = join ("", $rpc_header, Marshal($format, @param_list));

	$rpc_body;
}

sub UnmakeRPCBody
{
	my ($body, $format) = @_;

	my ($cmd, $trap_word, $D0, $A0, $num_params, $packed_parms) = unpack ("$rpc_header_template a*", $body);
	my (@parms) = Unmarshal($packed_parms, $format);

	return ($D0, $A0, @parms);
}


$rpc2_header_template	= "CxH4NNN";		# unsigned byte, filler, 4 hex digits, 3 B.E. longs
$sysPktRPC2Cmd			= 0x20;
$sysPktRPC2Rsp			= 0xA0;

sub MakeRPC2Body
{
	my ($trapword, $reg_list, @param_list) = @_;

	my ($rpc_header) = pack ($rpc_header_template, $sysPktRPCCmd, $trapword, 0, 0, 0);
	my ($param_count) = pack ("n", $#param_list + 1);
	my ($rpc_body) = join ("", $rpc_header, $reg_list, $param_count, reverse @param_list);

	$rpc_body;
}


########################################################################
#
#	FUNCTION:		PackRegList
#
#	DESCRIPTION:	Pack a list of register values into the format
#					needed by an RPC2 packet.
#
#	PARAMETERS:		An associative array, where each key contains Ax
#					or Dx, and the value contains the register value.
#
#	RETURNED:		The packed registers as a string.
#
########################################################################

sub PackRegList
{
	my (%reg_list) = @_;

	my ($dreg_bits, $areg_bits, $dregs, $aregs);

	$dreg_bits = 0;
	$areg_bits = 0;
	$dregs = "";
	$aregs = "";

	foreach $key (sort keys %reg_list)
	{
		my($reg_space) = substr($key, 0, 1);
		my($bit_to_set) = (1 << (ord(substr($key, 1, 1)) - ord("0")));
		my($value) = $reg_list{$key};

		if ($reg_space eq "D")
		{
			$dreg_bits |= $bit_to_set;
			$dregs .= pack ("N", $value);
		}
		else
		{
			$areg_bits |= $bit_to_set;
			$aregs .= pack ("N", $value);
		}
	}

	my ($result) = join ("", pack("CC", $dreg_bits, $areg_bits), $dregs, $aregs);
}


########################################################################
#
#	FUNCTION:		MakeParam
#
#	DESCRIPTION:	Create a parameter array element, suitable for being
#					added to other parameter array elements and --
#					eventually -- to an RPC packet body.
#
#	PARAMETERS:		$data - the data to be added.
#					$data_len - the length of the data to be added.  If
#						greater than zero, then we assume $data to be
#						an integer.  If equal to zero, then we assume
#						data to be a string where the length of the
#						string is determined by the length () function.
#						If less than zero, then data is assumed to be
#						a buffer with a length of -$data.
#					$by_ref - zero if the parameter is to be treated as
#						pass-by-value.  Non-zero if it's pass-by-ref.
#
#	RETURNED:		A parameter string that can be appended to a longer
#					string of parameters.  If the length of the string
#					would otherwise be odd, a padding byte is added.
#
########################################################################

	#	struct SysPktRPCParamInfo
	#	{
	#		Byte 	byRef;			// true if param is by reference
	#		Byte	size;			// # of Bytes of paramData	(must be even)			
	#		Word	data[1];		// variable length array of paramData
	#	};

sub ToParamBlock
{
	my ($data, $data_len) = @_;

	die "Undefined \$data, stopped" unless defined($data);
	die "\$data_len is negative, stopped" if ($data_len < 0);

	## If data_len == 0, determine the length using the length () function.
	## Else, use the given length.

	if ($data_len == 0)
	{
		$data_len = length ($data);
	}
	else
	{
		$data = pack ("a$data_len", $data);
	}

	## Pack up the data.

	my ($param) = pack ("CC", 1, $data_len) . $data;

	## Make sure the packed data is an even number of bytes long.

	if (($data_len % 2) != 0)
	{
		$param .= "\0";
	}

	$param;
}


sub FromParamBlock
{
	my ($param, $data_len) = @_;

	die "Undefined \$param, stopped" unless defined($param);
	die "\$data_len is negative, stopped" if ($data_len < 0);

	## Just ignore the $data_len and use what's in the parameter block.

	$data_len = unpack ("xC", $param);

	unpack ("xxa$data_len", $param);
}


sub ToParamInt
{
	my ($data, $data_len, $by_ref) = @_;

	die "Undefined \$data, stopped" unless defined($data);

	my ($format);

	if ($data_len == 8)
	{
		$format = ("CCCx");
		$data_len = 1;
	}
	elsif ($data_len == 16 || $data_len == 0)
	{
		$format = ("CCn");
		$data_len = 2;
	}
	elsif ($data_len == 32)
	{
		$format = ("CCN");
		$data_len = 4;
	}
	else
	{
		die "\$data_len not 8, 16, or 32, stopped";
	}

	## Pack up the data.

	pack ($format, $by_ref, $data_len, $data);
}


sub FromParamInt
{
	my ($param, $data_len) = @_;

	die "Undefined \$param, stopped" unless defined($param);

	my ($format);

	if ($data_len == 8)
	{
		$format = ("xxCx");
	}
	elsif ($data_len == 16 || $data_len == 0)
	{
		$format = ("xxn");
	}
	elsif ($data_len == 32)
	{
		$format = ("xxN");
	}
	else
	{
		die "\$data_len not 8, 16, or 32, stopped";
	}

	unpack ($format, $param);
}


sub ToParamPoint
{
	my ($point) = @_;
	my ($param);

	if (defined $point->{x})
	{
		$param = pack ("CCnn", 1, 4, $point->{x}, $point->{y});
	}
	else
	{
		$param = pack ("CCxxxx", 1, 4);
	}

	$param;
}


sub FromParamPoint
{
	my ($param) = @_;

	die "Undefined \$param, stopped" unless defined($param);

	my (@coords) = unpack ("xxnn", $param);

	{x	=> $coords[0],
	 y	=> $coords[1]};
}


sub ToParamRect
{
	my ($rect) = @_;
	my ($param);

	if (defined $rect->{height})
	{
		$param = pack ("CCnnnn", 1, 8, $rect->{left}, $rect->{top}, $rect->{width}, $rect->{height});
	}
	elsif (defined $rect->{bottom})
	{
		$param = pack ("CCnnnn", 1, 8, $rect->{left}, $rect->{top}, $rect->{right} - $rect->{left}, $rect->{bottom} - $rect->{top});
	}
	else
	{
		$param = pack ("CCxxxxxxxx", 1, 8);
	}

	$param;
}


sub FromParamRect
{
	my ($param) = @_;

	die "Undefined \$param, stopped" unless defined($param);

	my (@coords) = unpack ("xxnnnn", $param);

	{left	=> $coords[0],
	 top	=> $coords[1],
	 width	=> $coords[2],
	 height	=> $coords[3],
	 right	=> $coords[0] + $coords[2],
	 bottom	=> $coords[1] + $coords[3]};
}


sub ToParamString
{
	my ($data, $data_len) = @_;

	die "Undefined \$data, stopped" unless defined($data);
	die "\$data_len is negative, stopped" if ($data_len < 0);

	## If $data_len == 0, determine the length using the length () function.

	if ($data_len == 0)
	{
		$data_len = length ($data) + 1;	# Add 1 to get 1 byte of NULL padding
	}

	## Pack up the data.

	my ($param) = pack ("CCa$data_len", 1, $data_len, $data);

	## Make sure the packed data is an even number of bytes long.

	if (($data_len % 2) != 0)
	{
		$param .= "\0";
	}

	$param;
}


sub FromParamString
{
	my ($param) = @_;

	unpack ("xxA*", $param);
}


########################################################################
#
#	FUNCTION:		UnpackHeader
#
#	DESCRIPTION:	Disassemble a packet header into its consituent
#					parts.
#
#	PARAMETERS:		The packet header as received from Poser
#
#	RETURNED:		The signature, destination port, source port,
#					packet type, body size, transaction ID, and
#					checksum as an array.
#
########################################################################

sub UnpackHeader
{
	my($header) = @_;

	my ($signature, $dest, $src, $type, $bodySize, $transID, $checksum)
		= unpack ($header_template, $header);

	($signature, $dest, $src, $type, $bodySize, $transID, $checksum);
}


########################################################################
#
#	FUNCTION:		GetBodySize
#
#	DESCRIPTION:	Utility function to extract the packet body size
#					field from the packet header.
#
#	PARAMETERS:		The packet header as received from Poser.
#
#	RETURNED:		The size of the body following the header.
#
########################################################################

sub GetBodySize
{
	my($header) = @_;

	my ($signature, $dest, $srs, $type, $bodySize, $transID, $checksum)
		= UnpackHeader ($header);

	$bodySize;
}
	

sub SkipWhite
{
	my ($format, $format_index) = @_;

	while ()
	{
		last if ($format_index >= length ($format));

		my ($char) = substr ($format, $format_index, 1);
		last unless ($char eq " " || $char eq "," || $char eq ":");

		$format_index += 1;
	}

	$format_index
}


sub GetType
{
	my ($format, $format_index) = @_;
	my ($type) = "";

	$format_index = SkipWhite ($format, $format_index);

	while ()
	{
		last if ($format_index >= length ($format));

		my ($char) = substr ($format, $format_index, 1);
		last if (($char lt "a" || $char gt "z") && ($char lt "A" || $char gt "Z"));

		$type .= $char;
		$format_index += 1;
	}

	die "Unknown type (\"$type\" @ $format_index), stopped"
		unless ($type eq "int" ||
				$type eq "Err" ||
				$type eq "Coord" ||
				$type eq "LocalID" ||
				$type eq "HostErr" ||
				$type eq "string" ||
				$type eq "rptr" ||
				$type eq "point" ||
				$type eq "rect" ||
				$type eq "block");

	return ($type, $format_index);
}


sub GetSize
{
	my ($format, $format_index) = @_;
	my ($size) = 0;

	while ()
	{
		last if ($format_index >= length ($format));

		my ($char) = substr ($format, $format_index, 1);
		last if ($char lt "0" || $char gt "9");

		$size = $size * 10 + $char;
		$format_index += 1;
	}

	return ($size, $format_index);
}


sub GetByRef
{
	my ($format, $format_index) = @_;
	my ($by_ref) = 0;
	
	if (substr ($format, $format_index, 1) eq "*")
	{
		$by_ref = 1;
	}

	if ($by_ref)
	{
		$format_index += 1;
	}

	return ($by_ref, $format_index);
}


sub GetFormat
{
	my ($format, $format_index) = @_;
	my ($type, $size, $by_ref) = (" ", 0, 0);

	($type, $format_index) = GetType ($format, $format_index);
	($size, $format_index) = GetSize ($format, $format_index);
	($by_ref, $format_index) = GetByRef ($format, $format_index);

	## Deal with aliases

	if ($type eq "LocalID" or $type eq "HostErr")
	{
		$type = "int";
		$size = 32;
	}
	elsif ($type eq "Err" or $type eq "Coord")
	{
		$type = "int";
		$size = 16;
	}

	return ($type, $size, $by_ref, $format_index);
}


sub Marshal
{
	my ($format, @parameters) = @_;
	my (@result);

	my ($format_index) = 0;
	my ($parameter_index) = 0;

	while ($format_index < length ($format))
	{
		my ($parm);

		my ($type, $size);
		($type, $size, $by_ref, $format_index) = GetFormat ($format, $format_index);

		if ($type eq "int")
		{
			$parm = EmRPC::ToParamInt($parameters[$parameter_index], $size, $by_ref);
		}
		elsif ($type eq "rptr")
		{
			$parm = EmRPC::ToParamInt($parameters[$parameter_index], 32, 0);
		}
		elsif ($type eq "point")
		{
			$parm = EmRPC::ToParamPoint($parameters[$parameter_index], $size);
		}
		elsif ($type eq "rect")
		{
			$parm = EmRPC::ToParamRect($parameters[$parameter_index], $size);
		}
		elsif ($type eq "string")
		{
			$parm = EmRPC::ToParamString($parameters[$parameter_index], $size);
		}
		elsif ($type eq "block")
		{
			$parm = EmRPC::ToParamBlock($parameters[$parameter_index], $size);
		}
		else
		{
			die "Unexpected type \"$type\" in EmRPC::Marshal, stopped";
		}

		push (@result, $parm);

		$parameter_index += 1;
	}

	return join ("", reverse @result);
}


sub BreakApartParameters
{
	my ($packed_parms) = @_;
	my (@result) = 0;

	my ($offset) = 0;

	while ($offset < length ($packed_parms))
	{
		# Get the size field.

		my ($size) = unpack ("x$offset" . "xC", $packed_parms);

		# Add in the lengths of the byRef and size fields.

		$size += 2;

		# Make sure the field is word-aligned.

		if (($size % 2) != 0)
		{
			$size += 1;
		}

		# Get the SysPktRPCParamInfo.

		my ($parm) = unpack ("x$offset a$size", $packed_parms);

		push (@result, $parm);

		$offset += $size;
	}

	return @result;
}


sub Unmarshal
{
	my ($packed_parms, $format) = @_;
	my (@result);

	my ($format_index) = 0;
	my ($parameter_index) = 0;

	my (@parameters) = reverse BreakApartParameters($packed_parms);

	while ($format_index < length ($format))
	{
		my ($parm);

		my ($type, $size);
		($type, $size, $by_ref, $format_index) = GetFormat ($format, $format_index);

		if ($type eq "int")
		{
			$parm = EmRPC::FromParamInt($parameters[$parameter_index], $size);
		}
		elsif ($type eq "rptr")
		{
			$parm = EmRPC::FromParamInt($parameters[$parameter_index], 32);
		}
		elsif ($type eq "point")
		{
			$parm = EmRPC::FromParamPoint($parameters[$parameter_index]);
		}
		elsif ($type eq "rect")
		{
			$parm = EmRPC::FromParamRect($parameters[$parameter_index]);
		}
		elsif ($type eq "string")
		{
			$parm = EmRPC::FromParamString($parameters[$parameter_index]);
		}
		elsif ($type eq "block")
		{
			$parm = EmRPC::FromParamBlock($parameters[$parameter_index], $size);
		}
		else
		{
			die "Unexpected type \"$type\" in EmRPC::Unmarshal, stopped";
		}

		push (@result, $parm);

		$parameter_index += 1;
	}

	return @result;
}


sub ReadString
{
	my ($address) = @_;

	my ($block) = EmRPC::ReadBlock($address, 128);

	$block =~ /^([^\000]*)/;
	return $1;
}


sub PrintString
{
	my($string) = @_;

	foreach $ii (0..length ($string) - 1)
	{
		my($ch) = substr($string, $ii, 1);

		printf "0x%02X, ", ord($ch);

		if ($ii % 8 == 7)
		{
			print "\n";
		}
	}

	printf "\n";

	$string;
}

1;
