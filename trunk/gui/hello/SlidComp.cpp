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
#include "SlidComp.h"

SlidComp::SlidComp(QWidget*parent):QWidget(parent)
{
  QLCDNumber *lcd = new QLCDNumber(2);
  lcd->setSegmentStyle(QLCDNumber::Filled);

  Slider = new QSlider(Qt::Horizontal);
  Slider->setRange(0, 105);
  Slider->setValue(0);
  
  
  connect (Slider, SIGNAL(valueChanged(int)),lcd, SLOT(display(int))); 
  connect (lcd,SIGNAL(overflow()),qApp,SLOT(quit()));
  connect (Slider, SIGNAL(valueChanged(int)),this,SIGNAL(valueChanged(int)));
 
  
  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(lcd);
  layout->addWidget(Slider);
  
  setLayout(layout);  //make layout to be a child of this
  
}

void SlidComp::setValue(int newValue)
{
  Slider->setValue(newValue);
}

int SlidComp::value() const
{
  return Slider->value();
}
