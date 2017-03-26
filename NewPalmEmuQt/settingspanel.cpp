#include "settingspanel.h"
#include "ui_settingspanel.h"
#include "processmanager.h"
#include "settingarray.h"
#include <QDir>
#include <QFileDialog>
#include <stdio.h>

using namespace std;

string selecteddir = "err";

settingspanel::settingspanel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::settingspanel)
{
    ui->setupUi(this);
}

settingspanel::~settingspanel()
{
    delete ui;
}

void settingspanel::on_returntopalm_clicked()
{



    if(selecteddir=="err"){
        ui->optionpanels->setCurrentIndex(2);
        ui->listdir->setText("You must select a root directory.");
        return;
    }


    settingarray finalresult;
    finalresult.cpusettings.runnative=ui->runnative->checkState();
    finalresult.cpusettings.safemode=ui->safemode->checkState();
    finalresult.iosettings.serial=ui->serialport->currentIndex();
    finalresult.iosettings.beam=ui->irsettings->currentIndex();
    finalresult.iosettings.sdcard=ui->sdselector->currentIndex();
    string filename=QDir::currentPath().toStdString()+"/settings.bin";

    FILE *savesettings=fopen(filename.c_str(),"w");
    fprintf (savesettings,"%s\n",selecteddir.c_str());
    fprintf (savesettings,"%d\n",finalresult.cpusettings.runnative);
    fprintf (savesettings,"%d\n",finalresult.cpusettings.safemode);
    fprintf (savesettings,"%d\n",finalresult.iosettings.serial);
    fprintf (savesettings,"%d\n",finalresult.iosettings.beam);
    fprintf (savesettings,"%d\n",finalresult.iosettings.sdcard);
    fclose(savesettings);

    setprocess(EMULATOR);
}

void settingspanel::on_selectrootdir_clicked()
{
    selecteddir=QFileDialog::getExistingDirectory(
                this,"Open Emu Root", QDir::root().path(), QFileDialog::ShowDirsOnly).toStdString();
    ui->listdir->setText(QString::fromStdString(selecteddir));

}
