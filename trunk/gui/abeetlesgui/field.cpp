#include "Field.h"
#include "Environment.h"
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
	}

void CField::renewField()
{
	update();
}


void CField::paintEvent(QPaintEvent *evnt)
{
	if (Env==0) return;
	else
	{

		QPainter painter(this);
		
		painter.drawText(200,200,tr("Time"));
		
		/* acc to typeOfView I set the pen and brush*/
		/*painter.setPen(Qt::NoPen);
		painter.setBrush(QBrush(QColor(typeView)));
		
		if ((currentAngle*10 + 20)< width())
			painter.drawRect(QRect(currentAngle*10, x, 20, 10));
		else
			painter.drawRect(QRect(width()-20, x, 20, 10));

		for(J=0;J<Grid.G_Height;J++)
		{
		putc((char)(J%10)+'0',stdout); //left column of numbers
		for(I=0;I<Grid.G_Width;I++)
		{
			what = Grid.GetCellContent(I,J,&beetle);
			if (what==NOTHING) {painter.drawRect('.',stdout);continue;}
			if (what==FLOWER) {putc('~',stdout);continue;}
			if (what==WALL) {putc('W',stdout);continue;}
			if (what==BEETLE)
			{
				if ((beetle->Age)==0) putc('*',stdout);
				else
				{
					if (beetle->Direction == WEST)putc('<',stdout);
					if (beetle->Direction == NORTH)putc('A',stdout);
					if (beetle->Direction == EAST)putc('>',stdout);
					if (beetle->Direction == SOUTH)putc('V',stdout);
				}
			}
		}*/
	}
}


void CField::setTypeView(const QString& type)
{
	typeView = type;
	update();
}

