#include "Field.h"
#include "Environment.h"
#include "Beetle.h"
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QMessageBox>

CField::CField (CEnvironment * env,QWidget * parent): QWidget(parent)
{
	setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);

	Env = env;
	setFixedSize(QSize(400,400));
	Zoom=2;

	ZoomToSqSize[0]=1;ZoomToGapSize[0]=0;
	ZoomToSqSize[1]=3;ZoomToGapSize[1]=1;
	ZoomToSqSize[2]=5;ZoomToGapSize[2]=1;
	ZoomToSqSize[3]=9;ZoomToGapSize[3]=1;
	ZoomToSqSize[4]=17;ZoomToGapSize[4]=3;

}

void CField::renewField()
{
	QMessageBox::information(this,"MyApp","2");
	update();
}


void CField::paintEvent(QPaintEvent *evnt)
{


	int I,J,what;
	CBeetle * beetle;
	if (Env==0) return;
	else
	{
	QMessageBox::information(this,"MyApp","3");

		QPainter painter(this);
		
		//painter.drawText(200,200,tr("Time"));
		
		/* acc to typeOfView I set the pen and brush*/
		/*painter.setPen(Qt::NoPen);
		painter.setBrush(QBrush(QColor(typeView)));
		
		if ((currentAngle*10 + 20)< width())
			painter.drawRect(QRect(currentAngle*10, x, 20, 10));
		else
			painter.drawRect(QRect(width()-20, x, 20, 10));*/

		painter.setPen(Qt::NoPen);
		for(J=0;J<Env->Grid.G_Height;J++)
		{
		for(I=0;I<Env->Grid.G_Width;I++)
		{
			what = Env->Grid.GetCellContent(I,J,&beetle);
			if (what==BEETLE)
			{
				painter.setBrush(QBrush(QColor("blue")));
				painter.drawRect(*(this->getCellRect(I,J,Zoom)));
				/*if ((beetle->Age)==0) putc('*',stdout);
				else
				{
					if (beetle->Direction == WEST)putc('<',stdout);
					if (beetle->Direction == NORTH)putc('A',stdout);
					if (beetle->Direction == EAST)putc('>',stdout);
					if (beetle->Direction == SOUTH)putc('V',stdout);
				}*/
				continue;
			}
			if (what==NOTHING) painter.setBrush(QBrush(QColor(COLOR_NOTHING)));						
			if (what==FLOWER) painter.setBrush(QBrush(QColor(COLOR_FLOWER)));		
			if (what==WALL) painter.setBrush(QBrush(QColor(COLOR_WALL)));		
			painter.drawRect(*(this->getCellRect(I,J,Zoom)));
			continue;
			
		}
		}
	}
}


void CField::setTypeView(const QString& type)
{
	typeView = type;
	update();
}

QImage * CField::getBeetleImage(int zoom, char direction, QString & typeView)
{
	QImage * img= new QImage("beetle.gif");
	return img;
}

QRect * CField::getCellRect(int row, int col, int zoom) //x,y are zero based!!
{
	int sizeSq= ZoomToSqSize[zoom];
	int sizeGap=ZoomToGapSize[zoom];
	int x=sizeGap+(col*(sizeSq+sizeGap));
	int y=sizeGap+(row*(sizeSq+sizeGap));

	QRect * rect = new QRect (x,y,sizeSq,sizeSq);
	return rect;
}

