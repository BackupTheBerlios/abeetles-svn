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
	
	
	ZoomToSqSize[0]=1;ZoomToGapSize[0]=0;
	ZoomToSqSize[1]=3;ZoomToGapSize[1]=1;
	ZoomToSqSize[2]=5;ZoomToGapSize[2]=1;
	ZoomToSqSize[3]=9;ZoomToGapSize[3]=1;
	ZoomToSqSize[4]=17;ZoomToGapSize[4]=3;


	int fieldWidth=EMPTY_FIELD_SIZE;
	int fieldHeight=EMPTY_FIELD_SIZE;

	setFixedSize(QSize(fieldWidth,fieldHeight));
}

void CField::renewField()
{
	//QMessageBox::information(this,"MyApp","2");
	update();
}


void CField::paintEvent(QPaintEvent *evnt)
{


	int I,J,what;
	CBeetle * beetle;
	if (Env==0) 
	{
		//QMessageBox::information(this,"MyApp","3 - No Env");
		return;
	}
	else
	{
		//QMessageBox::information(this,"MyApp","3 - Drawing field");

		QPainter painter(this);
		
		//painter.drawText(200,200,tr("Time: ")+QString::number(Env->Time));
		
		
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
				//painter.drawRect(*(this->getCellRect(I,J,Zoom)));
				painter.drawImage(*(this->getCellRect(I,J,Zoom)),*(getBeetleImage(Zoom, beetle->Direction,TypeView)));
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
	TypeView = type;
	update();
}

QImage * CField::getBeetleImage(int zoom, char direction, QString & typeView)
{
	QString fname = "beetle_";
	fname+=QString::number(zoom);
	fname+="_";
	fname+=QString::number(direction);
	fname+=".gif";
	QImage * img= new QImage(fname);
	//if (img==0) QMessageBox::information(this,"MyApp","No image");
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

void CField::setEnvRef(CEnvironment *env)
{
	Env=env;

	int fieldWidth=EMPTY_FIELD_SIZE;
	if (Env) fieldWidth= ZoomToGapSize[Zoom]+((Env->Grid.G_Width)*(ZoomToSqSize[Zoom]+ZoomToGapSize[Zoom]));
	int fieldHeight=EMPTY_FIELD_SIZE;
	if (Env) fieldHeight= ZoomToGapSize[Zoom]+((Env->Grid.G_Height)*(ZoomToSqSize[Zoom]+ZoomToGapSize[Zoom]));

	setFixedSize(QSize(fieldWidth,fieldHeight));
	update();
}

void CField::setZoom(int zoom)
{
	if ((zoom<0) || (zoom >=NUM_ZOOM) || (zoom==Zoom)) return;
	else
	{
		Zoom=zoom;
		int fieldWidth=EMPTY_FIELD_SIZE;
		if (Env) fieldWidth= ZoomToGapSize[Zoom]+((Env->Grid.G_Width)*(ZoomToSqSize[Zoom]+ZoomToGapSize[Zoom]));
		int fieldHeight=EMPTY_FIELD_SIZE;
		if (Env) fieldHeight= ZoomToGapSize[Zoom]+((Env->Grid.G_Height)*(ZoomToSqSize[Zoom]+ZoomToGapSize[Zoom]));

		setFixedSize(QSize(fieldWidth,fieldHeight));
		update();
	}

}
