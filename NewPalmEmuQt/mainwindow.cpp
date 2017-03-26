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
using namespace std;

//user settings
static vector<string> appstoload;
static string palmname;

int setting_x,setting_y;

//Qt emulator wrapper stuff
void QtEmu_init(){
	full_init(palmname,setting_x,setting_y);
	int xmany = appstoload.size();
	for(int count = 0;count < xmany;count++){
		int pass = loadfiletopalm(appstoload[count]);
		if(pass != 0)palmabrt();
		/*
		switch(pass){
			case 0:
				break;
			default:
				palmabrt();
		}
		*/
	}
	appstoload.clear();
}

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
    //update display every 16 miliseconds/60*second
	refreshdisplay->start(16);//palm dosent run at 30fps
	//refreshdisplay->start(50);
	ui->exitemulator->setEnabled(false);

	//palm tx
	setting_x = 320;
	setting_y = 480;

	//tapwave zodiac
	//setting_x = 480;
	//setting_y = 320;

	palmname = "wugbun";
}

MainWindow::~MainWindow()
{
	end();
	delete ui;
}

void MainWindow::on_keyboard_pressed()
{

}

void MainWindow::on_install_pressed()
{
	string app = QFileDialog::getOpenFileName(this,"Open Prc/Pdb",
											  QDir::root().path(),0).toStdString();
	if(app != "")appstoload.push_back(app);
}

UWORD formattedgfxbuffer[320 * 480];

void MainWindow::updatedisplay(){
	if(!running)return;

	get_palm_framebuffer(formattedgfxbuffer);
	video = QImage((unsigned char*)formattedgfxbuffer,LCDW,LCDH,QImage::Format_RGB16);//16 bit
	ui->display->setPixmap(QPixmap::fromImage(video).scaled(
							   ui->display->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
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
	if(!started){
		QtEmu_init();
		selectappandstart();
		/*
		bool pass = start(0);
		if(pass){
			ui->controlemulator->setText("Pause");
			ui->exitemulator->setEnabled(true);
		}
		*/
		return;
	}

    if(!running){
		if(!resume())return;
        ui->controlemulator->setText("Pause");
    }
	else{
		if(!halt())return;
		ui->controlemulator->setText("Resume");
    }
}

void MainWindow::keyPressEvent(QKeyEvent* ev){
	sendkeyboardchar(ev->key(),true);
}

void MainWindow::keyReleaseEvent(QKeyEvent* ev){
	sendkeyboardchar(ev->key(),false);
}

void MainWindow::on_exitemulator_pressed()
{
	end();
	ui->controlemulator->setText("Start");
	ui->exitemulator->setEnabled(false);
}

void MainWindow::on_exitemulator_released()
{
	//sendbutton(Power,false);
}

void MainWindow::on_clock_pressed()
{
	sendbutton(Calender,true);
}

void MainWindow::on_clock_released()
{
	sendbutton(Calender,false);
}

void MainWindow::on_phone_pressed()
{
	sendbutton(Contacts,true);
}

void MainWindow::on_phone_released()
{
	sendbutton(Contacts,false);
}

void MainWindow::on_todo_pressed()
{
	sendbutton(Todo,true);
}

void MainWindow::on_todo_released()
{
	sendbutton(Todo,false);
}

void MainWindow::on_notes_pressed()
{
	sendbutton(Notes,true);
}

void MainWindow::on_notes_released()
{
	sendbutton(Notes,false);
}

void MainWindow::on_runtest_clicked()
{
#define SIMPAPP 4

#if SIMPAPP == -1
	appstoload.push_back("/sdcard/palm/zap2016.prc");
#elif SIMPAPP == 0
	appstoload.push_back("/sdcard/palm/mulg.prc");
	appstoload.push_back("/sdcard/palm/test.pdb");
#elif SIMPAPP == 1
	//cant fix until i dump my TXes os resources and make font parseing
	appstoload.push_back("/Users/Hoppy/000prcs/mulg.prc");//broken font APIs (fntGetFontPtr)
	appstoload.push_back("/Users/Hoppy/000prcs/test.pdb");
#elif SIMPAPP == 2
	appstoload.push_back("/Users/Hoppy/000prcs/argonv.prc");//dosent set frmdispatchevent event handler
	//cant set framebuffer to 4bpp yet
	//may work when 4 bit color is fixed
#elif SIMPAPP == 3
	appstoload.push_back("/Users/Hoppy/000prcs/tetris.prc");
#elif SIMPAPP == 4
	appstoload.push_back("/Users/Hoppy/000prcs/zap2016.prc");
#elif SIMPAPP == 5
	appstoload.push_back("/Users/Hoppy/000prcs/invaders.prc");
#elif SIMPAPP == 6
	appstoload.push_back("/sdcard/palm/invaders.prc");
#elif SIMPAPP == 7
	static_assert(RES >= 320,"Cant run in lores mode.");
	appstoload.push_back("/Users/Hoppy/000prcs/platypus.prc");//broken at writeing to addr 0x0
#elif SIMPAPP == 8
	appstoload.push_back("/Users/Hoppy/000prcs/Calculator.prc");//shows crap in equasion display
	appstoload.push_back("/Users/Hoppy/000prcs/Calculator_enUS.prc");
#elif SIMPAPP == 9
	appstoload.push_back("/Users/Hoppy/000prcs/atomsmash.prc");//calling memhandlelock on memptr
#elif SIMPAPP == 10
	appstoload.push_back("/Users/Hoppy/000prcs/mylittletank.prc");//exits gracefuly but without reason
	//might be an issue with winscreenmode setscreenmode
#elif SIMPAPP == 11
	appstoload.push_back("/Users/Hoppy/000prcs/galaxy/Galaxy2.prc");//crashes on drawing dummy bitmap (W:0,H:0,BPP:255)
	appstoload.push_back("/Users/Hoppy/000prcs/galaxy/ingame.pdb");//these are used to prevent lores devices from drawing
	appstoload.push_back("/Users/Hoppy/000prcs/galaxy/menu.pdb");//high res bitmaps.(The only valid field is NextBmpOffset)
#elif SIMPAPP == 12
	appstoload.push_back("/Users/Hoppy/000prcs/cbasPad5.prc");//stuck on fldEnterEvent
#elif SIMPAPP == 13
	appstoload.push_back("/Users/Hoppy/000prcs/aterrain/AlienTerrain.prc");
	appstoload.push_back("/Users/Hoppy/000prcs/aterrain/Mission_1.pdb");
	appstoload.push_back("/Users/Hoppy/000prcs/aterrain/Mission_2.pdb");
	appstoload.push_back("/Users/Hoppy/000prcs/aterrain/License.pdb");
#elif SIMPAPP == 14
	//the file type of PlzmData is prc but its name is pdb (not broken,just wierd)
	appstoload.push_back("/Users/Hoppy/000prcs/plazmoids/Plazmoids!.prc");
	appstoload.push_back("/Users/Hoppy/000prcs/plazmoids/PlzmData.pdb");
	appstoload.push_back("/Users/Hoppy/000prcs/plazmoids/PlzmMusic.pdb");
	appstoload.push_back("/Users/Hoppy/000prcs/plazmoids/PlzmSounds.pdb");
	appstoload.push_back("/Users/Hoppy/000prcs/plazmoids/MathLib.prc");
#elif SIMPAPP == 15
	appstoload.push_back("/Users/Hoppy/000prcs/zodiac/Spyhunter.prc");
#elif SIMPAPP == 16
	appstoload.push_back("/Users/Hoppy/000prcs/snails/Snails320x320.prc");
	appstoload.push_back("/Users/Hoppy/000prcs/snails/SnailsCDataDB320.pdb");
	appstoload.push_back("/Users/Hoppy/000prcs/snails/SnailsDDataDB320x320.pdb");
#elif SIMPAPP == 17
	appstoload.push_back("/Users/Hoppy/000prcs/Galax.prc");
	//the screen is ment to be white on app launch and I made it black //fix this hack
	//says out of memory
#elif SIMPAPP == 18
	appstoload.push_back("/Users/Hoppy/000prcs/bejeweled223/Bejeweled-global.prc");
	appstoload.push_back("/Users/Hoppy/000prcs/bejeweled223/Bejeweled-music1.pdb");
	appstoload.push_back("/Users/Hoppy/000prcs/bejeweled223/Bejeweled-music2.pdb");
	appstoload.push_back("/Users/Hoppy/000prcs/bejeweled223/Bejeweled-music3.pdb");
#elif SIMPAPP == 19
	appstoload.push_back("/Users/Hoppy/000prcs/quake/zquake.prc");
#endif

#if OS_ANDROID
	appstoload.push_back("/sdcard/palm/fonts.prc");
#else
	appstoload.push_back("/Users/Hoppy/000prcs/osdata/fonts.prc");
#endif

	QtEmu_init();
	bool pass = start(0);
	if(pass){
		ui->controlemulator->setText("Pause");
		ui->runtest->setEnabled(false);
		ui->exitemulator->setEnabled(true);
	}
}
