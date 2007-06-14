#include "hello.h"
#include "quitwin.h"
#include "SlidComp.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QLCDNumber>
#include <QSlider>
#include <QSpinBox>
#include <QGridLayout>

#include "Field.h"

QuitWin::QuitWin(QWidget * parent):QWidget(parent)
{
  resize(200, 120);
  
  //Tlacitko Quit
  MyPushButton * quitBut = new MyPushButton(tr("&Quit"));
  quitBut->setGeometry(62, 40, 75, 30);
  quitBut->setFont(QFont("Times", 18, QFont::Bold));

  connect(quitBut, SIGNAL(clicked()), qApp, SLOT(quit()));
  
  

  //SlidComp  - slider plus LCDdisplay
  SlidComp * slidComp = new SlidComp();

  //Field
	Field * field= new Field();

	connect(field,SIGNAL(AngleChanged(int)),slidComp,SLOT(setValue(int)));
	connect(slidComp,SIGNAL(valueChanged(int)),field,SLOT(setAngle(int)));

	//tlacitko start/stop
  QPushButton * startStopBut = new MyPushButton(tr("&Start"));
  startStopBut->setGeometry(62, 40, 75, 30);
  startStopBut->setFont(QFont("Times", 18, QFont::Bold));

  connect(startStopBut,SIGNAL(clicked()),field, SLOT(startstop()));

  //Grid layout
  QGridLayout *grid = new QGridLayout();
  
  grid->addWidget(quitBut,0,0);
  grid->addWidget(slidComp,1,0);
  grid->addWidget(field,1,1,2,1); 
  grid->addWidget(startStopBut,0,1);
  grid->setColumnStretch(1, 10);
   setLayout(grid);

	slidComp->setFocus();

}
