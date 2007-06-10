#include "hello.h"
#include "quitwin.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QLCDNumber>
#include <QSlider>
#include <QSpinBox>

QuitWin::QuitWin(QWidget * parent):QWidget(parent)
{
  resize(200, 120);
  
  MyPushButton * quitBut = new MyPushButton(tr("Quit"));
  //quitBut->setGeometry(62, 40, 75, 30);
  quitBut->setFont(QFont("Times", 18, QFont::Bold));

  connect(quitBut, SIGNAL(clicked()), qApp, SLOT(quit()));
  
  QPushButton * but2 = new QPushButton(tr("Enlarge"));
  //but2->setGeometry(85,35,100,45);
  
  connect(but2,SIGNAL(clicked()), this, SLOT(showMaximized()));
  
  QLCDNumber *lcd = new QLCDNumber(2);
  lcd->setSegmentStyle(QLCDNumber::Filled);
/*
  QSlider *slider = new QSlider(Qt::Horizontal);
  slider->setRange(0, 105);
  slider->setValue(0);
  
  
  connect(slider, SIGNAL(valueChanged(int)),lcd, SLOT(display(int))); */
  connect (lcd,SIGNAL(overflow()),qApp,SLOT(quit()));
 
  QSpinBox * spin = new QSpinBox();
  spin->setRange(0, 99);
  spin->setSingleStep(1);
  spin->setValue(0);
  
   connect(spin, SIGNAL(valueChanged(int)),lcd, SLOT(display(int))); 
  
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(quitBut); //makes quitBut to be a child of parent of layout
  layout->addWidget(but2);
  layout->addWidget(lcd);
  layout->addWidget(spin);
  
  setLayout(layout);  //make layout to be a child of this

}
