#include "Field.h"
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QMessageBox>

Field::Field (QWidget * parent): QWidget(parent)
{
	setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);
	autoShootTimer = new QTimer(this);
	connect(autoShootTimer,SIGNAL(timeout()),this,SLOT(moveRect()));
	x=50;
	currentAngle=45;
	color=QColor("blue");
	setFixedSize(QSize(400,400));
	}

void Field::setAngle(int angle)
{
	//QMessageBox::information(this,"MyApp","setAngle entered");

	if (currentAngle == angle)
        return;
	currentAngle=angle;
	update();
    emit angleChanged(currentAngle);
}

int Field::angle()
{
	return currentAngle;
}

void Field::paintEvent(QPaintEvent *evnt)
{
	QPainter painter(this);
	
	painter.drawText(200,200,tr("Position = ") + QString::number(currentAngle));

	painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(color));
	
	if ((currentAngle*10 + 20)< width())
		painter.drawRect(QRect(currentAngle*10, x, 20, 10));
	else
		painter.drawRect(QRect(width()-20, x, 20, 10));
}

void Field::startstop()
{
	//QMessageBox::information(this,"MyApp","startstopentered");
	if (autoShootTimer->isActive())
	{
		autoShootTimer->stop();
	}
	else
	{
		autoShootTimer->start(10);
	}

	
}
void Field::moveRect()
{
	//QMessageBox::information(this,"MyApp","moverect entered");
	x+=10;
	update();

}

void Field::setTypeView(const QString & type)
{
	color=type;
	update();
}
