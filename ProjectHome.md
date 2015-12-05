Soviet calssic simulation (SCS) script gauge for Prepar3D Flight Simulator.

To compile:

1. Put gauges.h, simconnect.h, simconnect.lib from Prepar3D SDK to Ext\Prepar3D in project dir.

2. Set environment variable PREPAR3DDIR to your Prepar3D installation (example PREPAR3DDIR=c:\Prepar3D)

3. Set environment variable BOOST\_DIR to your BOOST dir (example BOOST\_DIR=c:\Boost)

4. If you use VS2012 in any binary editor change in simconnect.lib /FAILIFMISMATCH:"_MSC\_VER=1600" to /FAILIFMISMATCH:"_MSC\_VER=1700". There are two places to change.

After compile SCSScript.gau will be in $(PREPAR3DDIR)\Gauges

Work still in progress. Stay tuned.