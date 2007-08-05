#include "Legend.h"
#include "Environment.h"
#include "Beetle.h"
#include "field.h"
#include "defines.h"
#include <QtGui>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


CLegend::CLegend (QWidget * parent): QWidget(parent)
{
	setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);
	
	TypeView=0;
			
	setFixedSize(QSize(120,100));
}



/*
void CLegend::renewLegend()
{
	//QMessageBox::information(this,"MyApp","2");
	update();
}*/


void CLegend::paintEvent(QPaintEvent *evnt)
{
	
	QPainter painter(this);
	QString topText="";
	QString bottomText="";

	if ((TypeView<0) ||(TypeView>NUM_TYPE_VIEW))return;

	painter.drawText(QRect(3,0,100,20),tr("Legend: "),Qt::AlignTop |Qt::AlignLeft );
	
	QRgb curClr=qRgb(255,255,255);

	if (TypeView==0)//"normal"	
	{
		painter.setBrush(QBrush(QColor("yellow")));
		painter.drawRect(10,20,15,15);
		painter.drawText(40,30,"Flower");
		painter.setBrush(QBrush(QColor("black")));
		painter.drawRect(10,40,15,15);
		painter.drawText(40,50,"Wall");
		return;
	}

	if (TypeView==4)//Hunger..color: red=(255,0,0)
	{
		curClr= qRgb(255,0,0);
		painter.setBrush(QBrush(QColor("white")));
		painter.drawRect(10,20,15,35);
		painter.setBrush(QBrush(QColor(curClr)));
		painter.drawRect(10,55,15,35);
		QString topText="Not hungry";
		QString bottomText="Hungry";
		painter.drawText(40,30,topText);
		painter.drawText(40,90,bottomText);
		return;
	}
	if (TypeView==1)//age...color: cyan=(_,255,255)
	{
		curClr= qRgb(0,255,255);
		topText="Age=0";
		bottomText="Age="+QString::number(MAX_AGE);
	}
	if (TypeView==2)//energy..color: red=(255,_,_)
	{
		curClr= qRgb(255,0,0);
		topText="Energy=0";
		bottomText="Energy="+QString::number(MAX_ENERGY);
	}
	if (TypeView==3)//fertility..color: magenta=(255,_,255)
	{
		curClr= qRgb(255,0,255);
		topText="Children=0";
		bottomText="Children=10";
	}		
	if (TypeView==5)//"growth of flowers"..color: green=(_,255,_)
	{
		curClr=qRgb(0,255,0);
		topText="Growth=0%";
		bottomText="Growth=100%";
	}
	if (TypeView==6)//"species"	
	{
		painter.setBrush(QBrush(QColor(CField::getSpeciesColor(0))));
		painter.drawRect(10,20,15,15);
		painter.drawText(40,30,"Species A");
		painter.setBrush(QBrush(QColor(CField::getSpeciesColor(1))));
		painter.drawRect(10,40,15,15);
		painter.drawText(40,50,"Species B");
		painter.setBrush(QBrush(QColor(CField::getSpeciesColor(2))));
		painter.drawRect(10,60,15,15);
		painter.drawText(40,70,"Species C");
		painter.drawText(10,90,"etc.");

		return;
	}

	//QMessageBox::information(this,"MyApp","2");

	QLinearGradient linearGrad(QPointF(17,20), QPointF(17, 90));
	linearGrad.setColorAt(0, Qt::white);
	linearGrad.setColorAt(1, QColor(curClr)); 

	painter.setBrush(QBrush(linearGrad));
	//painter.setBrush(QBrush(QColor(curClr),Qt::LinearGradientPattern));
	painter.drawRect(10,20,15,70);
	painter.drawText(40,30,topText);
	painter.drawText(40,90,bottomText);


}


void CLegend::setTypeView(const QString& type)
{
	if (type==TYPE_VIEW_1)TypeView=0;//"normal"
    if (type==TYPE_VIEW_2)TypeView=1;//age
    if (type==TYPE_VIEW_3)TypeView=2;//energy
    if (type==TYPE_VIEW_4)TypeView=3;//fertility
    if (type==TYPE_VIEW_5)TypeView=4;//Hunger
	if (type==TYPE_VIEW_6) TypeView=5;//"growth of flowers"
	if (type==TYPE_VIEW_7) TypeView=6;//species

	update();
}


