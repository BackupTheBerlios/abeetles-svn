#include "Legend.h"
#include "Environment.h"
#include "Beetle.h"
#include <QtGui>


CLegend::CLegend (CEnvironment * env,QWidget * parent): QWidget(parent)
{
	setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);

	Env = env;
	
	
	ZoomToSqSize[0]=1;ZoomToGapSize[0]=0;
	ZoomToSqSize[1]=3;ZoomToGapSize[1]=1;
	ZoomToSqSize[2]=5;ZoomToGapSize[2]=1;
	ZoomToSqSize[3]=9;ZoomToGapSize[3]=1;
	ZoomToSqSize[4]=17;ZoomToGapSize[4]=3;
	
	
	if (false ==loadBeetleImages())
	{
		QErrorMessage errDlg;
		errDlg.showMessage(QString::fromAscii("Loading of images of beetles was not successful."));
		exit (EXIT_FAILURE);
	}

	int fieldWidth=EMPTY_FIELD_SIZE;
	int fieldHeight=EMPTY_FIELD_SIZE;

	setFixedSize(QSize(fieldWidth,fieldHeight));
}

void CLegend::mousePressEvent ( QMouseEvent * evnt )
{
	 QPoint  * cell = getCellFromPoint(evnt->x(),evnt->y(),Zoom);
	 emit cellDetails(cell->x(), cell->y());
}


void CLegend::renewLegend()
{
	//QMessageBox::information(this,"MyApp","2");
	update();
}


void CLegend::paintEvent(QPaintEvent *evnt)
{


	int I,J,what;
	CBeetle * beetle;
/*	if (Env==0) 
	{
		//QMessageBox::information(this,"MyApp","3 - No Env");
		return;
	}
	else
	{*/
		//QMessageBox::information(this,"MyApp","3 - Drawing field");

		QPainter painter(this);
		QString topText="";
		QString bottomText="";
		painter.drawText(1,1,tr("Legend: "));
		
		QRgb curClr=qRgb(255,255,255);

		if (typeView==0)//"normal"
			//nothing
			return;
		if (typeView==4)//Hunger..color: red=(255,0,0)
		{
			curClr= qRgb(255,0,0);
			painter.setBrush(QBrush(QColor("white")));
			painter.drawRect(10,20,10,15);
			painter.setBrush(QBrush(QColor(curClr)));
			painter.drawRect(10,35,10,15);
			QString topText="Not hungry";
			QString bottomText="Hungry";
			painter.drawText(20,50,bottomText);
			return;
		}
		if (typeView==1)//age...color: cyan=(_,255,255)
		{
			int age = beetle->Age; if (age>MAX_AGE) age=MAX_AGE; //Age must be somehow restricted.
			curClr= qRgb(0,255,255);
			topText="Age=0";
			bottomText="Age="+QString:number(MAX_AGE);
		}
		if (typeView==2)//energy..color: red=(255,_,_)
		{
			curClr= qRgb(255,0,0);
			topText="Energy=0";
			bottomText="Energy="+QString:number(MAX_ENERGY);
		}
		if (typeView==3)//fertility..color: magenta=(255,_,255)
		{
			curClr= qRgb(255,0,255);
			topText="Children=0";
			bottomText="Children=10");
		}		
		if (typeView==5)//"growth of flowers"..color: green=(_,255,_)
		{
			curClr=qRgb(0,255,0);
			topText="Growth=0%";
			bottomText="Growth=100%");
		}
		painter.setBrush(QBrush(QColor(curClr),Qt::LinearGradientPattern));
		painter.drawRect(10,20,10,30);

//	}

}


void CLegend::setTypeView(const QString& type)
{
	if (type==TYPE_VIEW_1)TypeView=0;//"normal"
    if (type==TYPE_VIEW_2)TypeView=1;//age
    if (type==TYPE_VIEW_3)TypeView=2;//energy
    if (type==TYPE_VIEW_4)TypeView=3;//fertility
    if (type==TYPE_VIEW_5)TypeView=4;//Hunger
	if (type==TYPE_VIEW_6) TypeView=5;//"growth of flowers"
	update();
}

QImage * CLegend::getBeetleImage(CBeetle * beetle,int x, int y, int zoom,int typeView)
{
	

}
