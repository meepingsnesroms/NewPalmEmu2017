#include "mainwindow.h"
#include <QApplication>
#include "processmanager.h"
#include "settingspanel.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
	settingspanel s;

	setpan = &s;
	thisapp = &a;

    w.show();

	return a.exec();
}
