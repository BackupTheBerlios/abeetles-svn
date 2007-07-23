/* ========================================================================== */
/*                                                                            */
/*   ZoomSlider.cpp                                                            */
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
#include "zoomslider.h"
#include "defines.h"

ZoomSlider::ZoomSlider(QWidget*parent):QWidget(parent)
{
 init(tr("text")); 
}
ZoomSlider::ZoomSlider(const QString & labelText,QWidget*parent):QWidget(parent)
{
	init(labelText); 
}
void ZoomSlider::init(const QString & labelText)
{
	/*
	QLCDNumber *lcd = new QLCDNumber(3);
  lcd->setSegmentStyle(QLCDNumber::Filled);*/
  counterDisable=0;	//it was not disabled yet.

  Slider = new QSlider(Qt::Horizontal);
  Slider->setRange(0, NUM_ZOOM-1);
  Slider->setValue(INIT_ZOOM);
  Slider->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed); 

  Label=new QLabel(labelText);
  Label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); 

 // connect (Slider, SIGNAL(valueChanged(int)),lcd, SLOT(display(int))); 
  connect (Slider, SIGNAL(valueChanged(int)),this,SIGNAL(valueChanged(int)));
 
  
  QVBoxLayout *layout = new QVBoxLayout();
  //layout->addWidget(lcd);
  layout->addWidget(Label);
  layout->addWidget(Slider);  
  
  setLayout(layout);  //make layout to be a child of this

  setFocusProxy(Slider);
}
void ZoomSlider::setValue(int newValue)
{
	if (newValue == value())
        return;
	Slider->setValue(newValue);
	emit valueChanged(newValue);
}

int ZoomSlider::value() const
{
  return Slider->value();
}

void ZoomSlider::setDisabled(bool isDis)
{
	if (isDis)
	{
		counterDisable++;
		Slider->setDisabled(isDis);
	}
	else //isDis==false
	{
		counterDisable--;
		if(counterDisable==0) Slider->setDisabled(isDis);
	}
}
