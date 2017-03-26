#include "settingspanel.h"
#include "mainwindow.h"
#include "processmanager.h"
#include "palmwrapper.h"
MainWindow *output;
settingspanel *setpan;

void setprocess(int process){
		if(running)halt();
		if(process == EMULATOR){
			setpan->hide();
            output->show();
        }
		if(process == SETUP){
			setpan->show();
            output->hide();
        }
		if(process == EXIT)output->~MainWindow();
}
