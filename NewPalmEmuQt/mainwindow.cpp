#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "processmanager.h"
#include "settingarray.h"

#include "palmwrapper.h"

#include <QDir>
#include <QFileDialog>
#include <QTimer>
#include <QTouchEvent>
#include <QSettings>
#include <QFont>
#include <QKeyEvent>

#include <vector>
#include <string>

//user settings
emu_config settings;

QImage video;
QTimer* refreshdisplay;
QApplication* thisapp;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	output = this;
	refreshdisplay = new QTimer(this);
    connect(refreshdisplay, SIGNAL(timeout()), this, SLOT(updatedisplay()));
	//update display every 16.67 miliseconds = 60*second
	refreshdisplay->start(16);
	ui->exitemulator->setEnabled(false);

	//palm tx
	//settings.screen_width = 320;
	//settings.screen_height  = 480;

	//palm z22
	settings.screen_width = 160;
	settings.screen_height = 160;

	//tapwave zodiac
	//settings.screen_width = 480;
	//settings.screen_height  = 320;
}

MainWindow::~MainWindow()
{
	emu_end();
	delete ui;
}

void MainWindow::on_keyboard_pressed()
{

}

void MainWindow::on_install_pressed()
{
	string app = QFileDialog::getOpenFileName(this,"Open Prc/Pdb",
											  QDir::root().path(),0).toStdString();
	if(app != "")settings.internal_files.push_back(app);
}

uint16_t formattedgfxbuffer[320 * 480];

void MainWindow::updatedisplay(){
	if(!emu_started())return;

	emu_get_framebuffer(formattedgfxbuffer);
	video = QImage((unsigned char*)formattedgfxbuffer, settings.screen_width, settings.screen_height, QImage::Format_RGB16);//16 bit
	ui->display->setPixmap(QPixmap::fromImage(video).scaled(
	                           ui->display->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->display->update();
}

void MainWindow::errdisplay(string err){
    ui->display->setText(QString::fromStdString(err));
}

void MainWindow::on_display_destroyed()
{

}

void MainWindow::on_mainleft_clicked()
{
    ui->controlpanel->setCurrentWidget(ui->controlpanel->widget(2));
}

void MainWindow::on_mainright_clicked()
{
    ui->controlpanel->setCurrentWidget(ui->controlpanel->widget(1));
}

void MainWindow::on_settingsleft_clicked()
{
    ui->controlpanel->setCurrentWidget(ui->controlpanel->widget(0));
}

void MainWindow::on_settingsright_clicked()
{
    ui->controlpanel->setCurrentWidget(ui->controlpanel->widget(2));
}

void MainWindow::on_joyleft_clicked()
{
    ui->controlpanel->setCurrentWidget(ui->controlpanel->widget(1));
}

void MainWindow::on_joyright_clicked()
{
    ui->controlpanel->setCurrentWidget(ui->controlpanel->widget(0));
}

void MainWindow::on_settings_clicked()
{
    setprocess(SETUP);
}

void MainWindow::on_controlemulator_clicked()
{
	if(!emu_started()){
		//QtEmu_init();
		//selectappandstart();
		/*
		bool pass = start(0);
		if(pass){
			ui->controlemulator->setText("Pause");
			ui->exitemulator->setEnabled(true);
		}
		*/
		return;
	}

	if(!emu_paused()){
		if(!emu_resume())return;
        ui->controlemulator->setText("Pause");
    }
	else{
		if(!emu_halt())return;
		ui->controlemulator->setText("Resume");
    }
}

void MainWindow::keyPressEvent(QKeyEvent* ev){
	emu_sendkeyboardchar(ev->key(),true);
}

void MainWindow::keyReleaseEvent(QKeyEvent* ev){
	emu_sendkeyboardchar(ev->key(),false);
}

void MainWindow::on_exitemulator_pressed()
{
	emu_end();
	ui->controlemulator->setText("Start");
	ui->exitemulator->setEnabled(false);
}

void MainWindow::on_exitemulator_released()
{
	//emu_sendbutton(Power,false);
}

void MainWindow::on_clock_pressed()
{
	emu_sendbutton(BTN_Calender,true);
}

void MainWindow::on_clock_released()
{
	emu_sendbutton(BTN_Calender,false);
}

void MainWindow::on_phone_pressed()
{
	emu_sendbutton(BTN_Contacts,true);
}

void MainWindow::on_phone_released()
{
	emu_sendbutton(BTN_Contacts,false);
}

void MainWindow::on_todo_pressed()
{
	emu_sendbutton(BTN_Todo,true);
}

void MainWindow::on_todo_released()
{
	emu_sendbutton(BTN_Todo,false);
}

void MainWindow::on_notes_pressed()
{
	emu_sendbutton(BTN_Notes,true);
}

void MainWindow::on_notes_released()
{
	emu_sendbutton(BTN_Notes,false);
}

void MainWindow::on_runtest_clicked()
{

#if OS_ANDROID
	settings.internal_files.push_back("/sdcard/palm/fonts.prc");
#else
	settings.internal_files.push_back("/Users/Hoppy/000prcs/osdata/fonts.prc");
#endif

#define SIMPAPP 13

#if SIMPAPP == -1
	settings.internal_files.push_back("/sdcard/palm/zap2016.prc");
#elif SIMPAPP == 0
	settings.internal_files.push_back("/sdcard/palm/test.pdb");
	settings.internal_files.push_back("/sdcard/palm/mulg.prc");
#elif SIMPAPP == 1
	//cant fix until i dump my TXes os resources and make font parseing
	settings.internal_files.push_back("/Users/Hoppy/000prcs/test.pdb");
	settings.internal_files.push_back("/Users/Hoppy/000prcs/mulg.prc");//broken font APIs (fntGetFontPtr)
#elif SIMPAPP == 2
	settings.internal_files.push_back("/Users/Hoppy/000prcs/argonv.prc");//dosent set frmdispatchevent event handler
	//cant set framebuffer to 4bpp yet
	//may work when 4 bit color is fixed
#elif SIMPAPP == 3
	settings.internal_files.push_back("/Users/Hoppy/000prcs/tetris.prc");
#elif SIMPAPP == 4
	settings.internal_files.push_back("/Users/Hoppy/000prcs/zap2016.prc");
#elif SIMPAPP == 5
	settings.internal_files.push_back("/Users/Hoppy/000prcs/invaders.prc");
#elif SIMPAPP == 6
	settings.internal_files.push_back("/sdcard/palm/invaders.prc");
#elif SIMPAPP == 7
	static_assert(RES >= 320,"Cant run in lores mode.");
	settings.internal_files.push_back("/Users/Hoppy/000prcs/platypus.prc");//broken at writeing to addr 0x0
#elif SIMPAPP == 8
	settings.internal_files.push_back("/Users/Hoppy/000prcs/Calculator_enUS.prc");
	settings.internal_files.push_back("/Users/Hoppy/000prcs/Calculator.prc");//shows crap in equasion display
#elif SIMPAPP == 9
	settings.internal_files.push_back("/Users/Hoppy/000prcs/atomsmash.prc");//calling memhandlelock on memptr
#elif SIMPAPP == 10
	settings.internal_files.push_back("/Users/Hoppy/000prcs/mylittletank.prc");//exits gracefuly but without reason
	//might be an issue with winscreenmode setscreenmode
#elif SIMPAPP == 11
	settings.internal_files.push_back("/Users/Hoppy/000prcs/galaxy/ingame.pdb");//these are used to prevent lores devices from drawing
	settings.internal_files.push_back("/Users/Hoppy/000prcs/galaxy/menu.pdb");//high res bitmaps.(The only valid field is NextBmpOffset)
	settings.internal_files.push_back("/Users/Hoppy/000prcs/galaxy/Galaxy2.prc");//crashes on drawing dummy bitmap (W:0, H:0,BPP:255)
#elif SIMPAPP == 12
	settings.internal_files.push_back("/Users/Hoppy/000prcs/cbasPad5.prc");//stuck on fldEnterEvent
#elif SIMPAPP == 13
	settings.internal_files.push_back("/Users/Hoppy/000prcs/aterrain/Mission_1.pdb");
	settings.internal_files.push_back("/Users/Hoppy/000prcs/aterrain/Mission_2.pdb");
	settings.internal_files.push_back("/Users/Hoppy/000prcs/aterrain/License.pdb");
	settings.internal_files.push_back("/Users/Hoppy/000prcs/aterrain/AlienTerrain.prc");
#elif SIMPAPP == 14
	//the file type of PlzmData is prc but its name is pdb (not broken,just wierd)
	settings.internal_files.push_back("/Users/Hoppy/000prcs/plazmoids/PlzmData.pdb");
	settings.internal_files.push_back("/Users/Hoppy/000prcs/plazmoids/PlzmMusic.pdb");
	settings.internal_files.push_back("/Users/Hoppy/000prcs/plazmoids/PlzmSounds.pdb");
	settings.internal_files.push_back("/Users/Hoppy/000prcs/plazmoids/MathLib.prc");
	settings.internal_files.push_back("/Users/Hoppy/000prcs/plazmoids/Plazmoids!.prc");
#elif SIMPAPP == 15
	settings.internal_files.push_back("/Users/Hoppy/000prcs/zodiac/Spyhunter.prc");
#elif SIMPAPP == 16
	settings.internal_files.push_back("/Users/Hoppy/000prcs/snails/SnailsCDataDB320.pdb");
	settings.internal_files.push_back("/Users/Hoppy/000prcs/snails/SnailsDDataDB320x320.pdb");
	settings.internal_files.push_back("/Users/Hoppy/000prcs/snails/Snails320x320.prc");
#elif SIMPAPP == 17
	settings.internal_files.push_back("/Users/Hoppy/000prcs/Galax.prc");
	//the screen is ment to be white on app launch and I made it black //fix this hack
	//says out of memory
#elif SIMPAPP == 18
	settings.internal_files.push_back("/Users/Hoppy/000prcs/bejeweled223/Bejeweled-music1.pdb");
	settings.internal_files.push_back("/Users/Hoppy/000prcs/bejeweled223/Bejeweled-music2.pdb");
	settings.internal_files.push_back("/Users/Hoppy/000prcs/bejeweled223/Bejeweled-music3.pdb");
	settings.internal_files.push_back("/Users/Hoppy/000prcs/bejeweled223/Bejeweled-global.prc");
#elif SIMPAPP == 19
	settings.internal_files.push_back("/Users/Hoppy/000prcs/quake/zquake.prc");
#elif SIMPAPP == 20
	settings.internal_files.push_back("/Users/Hoppy/000prcs/BikeOrDie-2.0d.prc");
#endif

	bool pass = emu_start(settings);
	if(pass){
		ui->controlemulator->setText("Pause");
		ui->runtest->setEnabled(false);
		ui->exitemulator->setEnabled(true);
	}
}
