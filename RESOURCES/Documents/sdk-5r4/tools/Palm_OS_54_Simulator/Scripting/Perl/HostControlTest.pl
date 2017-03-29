#@INC = push (@INC, "D:/Emulator");
#@INC = push (@INC, "D:/Emulator/Scripting/Perl");
#print $INC;

use EmRPC;			# EmRPC::OpenConnection, CloseConnection
use HostControl;
use EmFunctions;
use EmUtils;		# TapPenSync, TapButtonSync

print "Start HostControlTest.pl\n";



EmRPC::OpenConnection("localhost:2000#Console");


my ($hostVers) = HostGetHostVersion();
print "HostGetHostVersion = $hostVers\n";

my ($hostID) = HostGetHostID();
print "HostGetHostID = $hostID\n";

my ($hostPlatform) = HostGetHostPlatform();
print "HostGetHostPlatform = $hostPlatform\n";

my ($hostSelector1) = HostIsSelectorImplemented(hostSelectorGetHostVersion);
print "HostIsSelectorImplemented (hostSelectorGetHostVersion) = $hostSelector1\n";

my ($hostSelector2) = HostIsSelectorImplemented(hostSelectorGetHostID);
print "HostIsSelectorImplemented (hostSelectorGetHostID) = $hostSelector2\n";

my ($hostSelector3) = HostIsSelectorImplemented(hostSelectorProfileInit);
print "HostIsSelectorImplemented (hostSelectorProfileInit) = $hostSelector3\n";

my ($hostGestalt) = HostGestalt(1000);
print ("HostGestalt 1000 = $hostGestalt\n");

my ($hostIsCallingTrap) = HostIsCallingTrap();
print ("HostIsCallingTrap = $hostIsCallingTrap\n");


#// Profiling Calls
my ($profileInit) = HostProfileInit(1000, 1000);
print ("HostProfileInit = $profileInit\n");

#my ($profileDetailFn) = HostProfileDetailFn();
#print ("HostProfileDetailFn = $profileDetailFn\n");

#// profileStart crashed the Emulator Profiler 3.0a5e3.
my ($profileStart) = HostProfileStart();
print ("HostProfileStart = $profileStart\n");

	my ($gremlinResponse) = HostGremlinNew(0, 0, 10000, 1000, 10000, "Address");
	print ("HostGremlinNew = $gremlinResponse\n");

	my ($gremlinResponse) = HostGremlinLimit();
	print ("HostGremlinLimit = $gremlinResponse\n");
	
	my ($gremlinResponse) = HostGremlinNumber();
	print ("HostGremlinNumber = $gremlinResponse\n");
	
	my ($gremlinResponse) = HostGremlinLimit();
	print ("HostGremlinLimit = $gremlinResponse\n");
	
	my ($gremlinResponse) = HostGremlinIsRunning();
	print ("HostGremlinIsRunning = $gremlinResponse\n");
	
	my ($gremlinResponse) = HostGremlinCounter();
	print ("HostGremlinCounter = $gremlinResponse\n");


#// profileStart crashed the Emulator Profiler 3.0a5e3.
#// x outside of string at d:\Emulator\Scripting\Perl/EmRPC.pm line 594
my ($profileResponse) = HostProfileStop();
print ("HostProfileStop = $profileResponse\n");

my ($profileResponse) = HostProfileDump("D:\Emulator\Dump.txt");
print ("HostProfileDump = $profileResponse\n");

my ($profileResponse) = HostProfileCleanup();
print ("HostProfileCleanup = $profileResponse\n");


	


EmRPC::CloseConnection();
