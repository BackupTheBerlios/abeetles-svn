/* ========================================================================== */
/*                                                                            */
/*   SlidComp.cpp                                                            */
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
#include "SlidComp.h"

SlidComp::SlidComp(QWidget*parent):QWidget(parent)
{
 init(tr("text")); 
}
SlidComp::SlidComp(QString & labelText,QWidget*parent):QWidget(parent)
{
	init(labelText); 
}
void SlidComp::init(const QString & labelText)
{
	QLCDNumber *lcd = new QLCDNumber(3);
  lcd->setSegmentStyle(QLCDNumber::Filled);

  Slider = new QSlider(Qt::Horizontal);
  Slider->setRange(0, 200);
  Slider->setValue(0);

  Label=new QLabel(labelText);
  Label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed); 

  
  
  connect (Slider, SIGNAL(valueChanged(int)),lcd, SLOT(display(int))); 
  connect (Slider, SIGNAL(valueChanged(int)),this,SIGNAL(valueChanged(int)));
 
  
  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(lcd);
  layout->addWidget(Slider);
  layout->addWidget(Label);
  
  setLayout(layout);  //make layout to be a child of this

  setFocusProxy(Slider);
}
void SlidComp::setValue(int newValue)
{
	if (newValue == value())
        return;
	Slider->setValue(newValue);
	emit valueChanged(newValue);
}

int SlidComp::value() const
{
  return Slider->value();
}
