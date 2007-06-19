/* ========================================================================== */
/*                                                                            */
/*   LabeledLCD.cpp                                                            */
/*   (c) 2007 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */


#include <QLCDNumber>
#include <QSlider>
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include "LabeledLCD.h"

LabeledLCD::LabeledLCD(QWidget*parent):QWidget(parent)
{
 init(tr("text")); 
}
LabeledLCD::LabeledLCD(const QString & labelText,QWidget*parent):QWidget(parent)
{
	init(labelText); 
}
void LabeledLCD::init(const QString & labelText)
{
	QLCDNumber *lcd = new QLCDNumber(6);
	lcd->setSegmentStyle(QLCDNumber::Filled);
	lcd->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed); 
	Label=new QLabel(labelText);
	Label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed); 

	connect (this, SIGNAL(valueChanged(int)),lcd, SLOT(display(int))); 

	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(Label);
	layout->addWidget(lcd);

	setLayout(layout);  //make layout to be a child of this

	Value=0;
	lcd->display(0);

}
void LabeledLCD::setValue(int newValue)
{
	if (newValue == Value)
        return;
	Value=newValue;
	emit valueChanged(newValue);
}

