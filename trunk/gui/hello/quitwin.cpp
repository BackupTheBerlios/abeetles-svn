#include "hello.h"
#include "quitwin.h"
#include "SlidComp.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QLCDNumber>
#include <QSlider>
#include <QSpinBox>
#include <QGridLayout>

QuitWin::QuitWin(QWidget * parent):QWidget(parent)
{
  //resize(200, 120);
  
  MyPushButton * quitBut = new MyPushButton(tr("Quit"));
  //quitBut->setGeometry(62, 40, 75, 30);
  quitBut->setFont(QFont("Times", 18, QFont::Bold));

  connect(quitBut, SIGNAL(clicked()), qApp, SLOT(quit()));
  
  QPushButton * but2 = new QPushButton(tr("Enlarge"));
  //but2->setGeometry(85,35,100,45);  
  connect(but2,SIGNAL(clicked()), this, SLOT(showMaximized()));
  SlidComp * slidComp = 0;
  QGridLayout *grid = new QGridLayout;
  int I,J;

  SlidComp * prevSC=0;
  
  for(I=0;I<4;I++)
    for (J=0;J<4;J++)
    {
      slidComp = new SlidComp();
      grid->addWidget(slidComp,I,J);
      if (prevSC!=0)
        connect(slidComp,SIGNAL(valueChanged(int)),prevSC,SLOT(setValue(int)));
      prevSC=slidComp;
      
    }
  
  QVBoxLayout * layout = new QVBoxLayout();
  layout->addWidget(quitBut);
  layout->addLayout(grid);
  
  setLayout(layout);
}
