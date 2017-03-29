#Usage for #define format is `perl MakeSysTraps.pl -d /path/to/systrap.h'.

use strict;

if (@ARGV == 0)
{
	print <<EOF;
Usage: $0 [-cds] file...
Generates an annotated list of systraps from the named files.
	<default>	Produces output suitable for the build-prc data file.
	-s			Produces an asm include file.
	-d			Produces a bunch of #defines.
	-c			Produces a list of Perl constants.
EOF
	exit;
}

my ($format, $forConst);
$forConst = 0;

if ($ARGV[0] eq "-s")
{
	shift;
	$format = "\t.equ %s,%s\n";
	print <<EOF;
/* DO NOT EDIT!  This file was automatically produced by $0
	from @ARGV */

	.macro systrap trapname
	trap #15
	.word \\trapname
	.endm

EOF
	}
elsif ($ARGV[0] eq "-d")
{
	shift;
	$format = "#define _P_sysTrap%s\t%s\n";
	print <<EOF;
/* DO NOT EDIT! This section was automatically produced by $0
	from @ARGV  */

EOF
}
elsif ($ARGV[0] eq "-c")
{
	shift;
	$format = "use constant sysTrap%s\t=> %s;\n";
	$forConst = 1;
	print <<EOF;
# DO NOT EDIT! This section was automatically produced by $0
# from @ARGV

EOF
}
else
{
	$format = "<%s>\t%s\n";
	print <<EOF;
DO NOT EDIT!  This file was automatically produced by $0
from @ARGV

EOF
}

my $num = 0;

while (<>)
{
	s"//.*$"";			# eat C++-style comments
	s"/\*[^/]*\*/""g;	# eat simple C-style comments (just in case)

	if (/define\W+sysTrapBase\W+((0[xX][\da-fA-F]+)|(\d+))/)
	{
		$num = $1;
		$num = oct $num if $num =~ /^0/;
	}

	next unless /=.*sysTrapBase.*,/ .. /}.*SysTrapNumber.*;/;

	printf $format, $1, sprintf("\"%lX\"", $num++) if /sysTrap(\w+)\b/;
}

if ($forConst != 0)
{
	print "\n", "1;", "\n";
}
