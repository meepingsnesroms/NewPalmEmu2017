#include "settingspanel.h"
#include "mainwindow.h"
#include "processmanager.h"
#include "palmwrapper.h"
MainWindow *output;
settingspanel *setpan;

void setprocess(int process){
	    if(emu_started() && !emu_paused())emu_halt();
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
