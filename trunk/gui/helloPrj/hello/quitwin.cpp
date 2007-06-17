#include "hello.h"
#include "quitwin.h"
#include "SlidComp.h"

#include <QtGui>

#include "Field.h"

QuitWin::QuitWin(QWidget * parent):QWidget(parent)
{
	resize(200, 120);

	//Tlacitko Quit
	MyPushButton * quitBut = new MyPushButton(tr("&Quit"));
	quitBut->setGeometry(62, 40, 75, 30);
	quitBut->setFont(QFont("Times", 18, QFont::Bold));

	connect(quitBut, SIGNAL(clicked()), qApp, SLOT(quit()));

	//ComboBox
	QComboBox *typeView = new QComboBox;
	typeView->addItem("blue");
    typeView->addItem("green");
    typeView->addItem("red");
    typeView->addItem("grey");
    typeView->addItem("navy");





	//SlidComp  - slider plus LCDdisplay
	SlidComp * slidComp = new SlidComp();

	//Field
	Field * field= new Field();

	connect(field,SIGNAL(AngleChanged(int)),slidComp,SLOT(setValue(int)));
	connect(slidComp,SIGNAL(valueChanged(int)),field,SLOT(setAngle(int)));
    connect(typeView, SIGNAL(activated(const QString &)),
            field, SLOT(setTypeView(const QString &)));
	//ScrollArea

	QScrollArea * scrollArea = new QScrollArea ();
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidget(field); 

	//tlacitko start/stop
	QPushButton * startStopBut = new MyPushButton(tr("&Start"));
	startStopBut->setGeometry(62, 40, 75, 30);
	startStopBut->setFont(QFont("Times", 18, QFont::Bold));

	connect(startStopBut,SIGNAL(clicked()),field, SLOT(startstop()));

	//Grid layout
	QGridLayout *grid = new QGridLayout();

	grid->addWidget(quitBut,0,0);
	grid->addWidget(slidComp,1,0);
	grid->addWidget(scrollArea,1,1,2,1);
	grid->addWidget(typeView,2,0);
	grid->addWidget(startStopBut,0,1);
	grid->setColumnStretch(1, 10);
	setLayout(grid);

	slidComp->setFocus();

}
