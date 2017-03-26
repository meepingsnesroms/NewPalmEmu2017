#include "touchscreen.h"
#include "palmwrapper.h"
#include "mainwindow.h"


float rangeswap(float r1start,float r1end,float r2start,float r2end,float r2val){
	float r1size = r1end - r1start;
	float r2size = r2end - r2start;

	float Xto1 = r2size / r1size;

	return r2val * Xto1 + r2start;
}

TouchScreen::TouchScreen(QWidget* parent)
    : QLabel(parent)
{

}

TouchScreen::~TouchScreen()
{

}

void TouchScreen::mousePressEvent(QMouseEvent *ev){
	int x = (int)rangeswap(0,this->width(),0,setting_x,ev->x());
	int y = (int)rangeswap(0,this->height(),0,setting_y,ev->y());
	sendtouch(x,y,true);
}
void TouchScreen::mouseMoveEvent(QMouseEvent *ev){
	int x = (int)rangeswap(0,this->width(),0,setting_x,ev->x());
	int y = (int)rangeswap(0,this->height(),0,setting_y,ev->y());
	sendtouch(x,y,true);
}

void TouchScreen::mouseReleaseEvent(QMouseEvent *ev){
	int x = (int)rangeswap(0,this->width(),0,setting_x,ev->x());
	int y = (int)rangeswap(0,this->height(),0,setting_y,ev->y());
	sendtouch(x,y,false);
}

/*
void TouchScreen::touchPressEvent(QTouchEvent *ev){

}
*/
