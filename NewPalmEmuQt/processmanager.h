#ifndef PROCESSMANAGER
#define PROCESSMANAGER

#include "settingspanel.h"
#include "mainwindow.h"

enum{
	EMULATOR = 1,
	SETUP = 2,
	EXIT = 3
};

extern settingspanel *setpan;
extern MainWindow *output;

void setprocess(int process);

#endif // PROCESSMANAGER

