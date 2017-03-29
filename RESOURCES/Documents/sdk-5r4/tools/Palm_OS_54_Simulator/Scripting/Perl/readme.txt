These are modified versions of the Perl libraries provided with POSE.

The modifications are:

- SLK checksums are now calculated ; this is because the simulator directly relies on the Palm OS Serial Link Manager
- pen taps are now expressed in screen coordinates rather than raw digitizer coordinates

In order to execute scripts with PalmSim, those files must be used. The connection must be opened on the local machine TCP port 2000 using the Console Serial Link Manager socket rather than PoserRPC socket.

Ex: OpenConnection("localhost:2000#Console");

