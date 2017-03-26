#include <string>
#ifndef SETTINGARRAY
#define SETTINGARRAY
using namespace std;

enum{
    None=0,

    SD256=1,

    SaveToFile=1,
    SendOverBluetooth=2,


    Computer=1,
    TiltSensor=2,
    GPS=3,
    ModemReal=4,
    ModemFast=5

};

typedef struct{
    bool safemode;
    bool runnative;
}CPUsettings;

typedef struct{
    int serial;
    int sdcard;
    int beam;
}IOsettings;

typedef struct{
    IOsettings iosettings;
    CPUsettings cpusettings;
}settingarray;


#endif // SETTINGARRAY

