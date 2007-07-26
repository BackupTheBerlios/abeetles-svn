/****************************************************************************
**
** Copyright (C) 2004-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://www.trolltech.com/products/qt/opensource.html
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://www.trolltech.com/products/qt/licensing.html or contact the
** sales department at sales@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <QtGui>

#include "CRunGui.h"
#include "field.h"
#include "zoomslider.h"
#include "defines.h"
#include "Environment.h"
#include "LabeledLCD.h"
#include "StatisticsEnv.h"
#include "BeetleDialog.h"
#include "Legend.h"
#include <QTimer>
#include <QString>

CRunGui::CRunGui():Env()
{
	//Env=new CEnvironment();

	//setting of central widget of the window
    QWidget *mainWidget = new QWidget;
    setCentralWidget(mainWidget);

	//non-gui attributes:
//	Env=NULL;Env is now non dynamic attribute.
//	emit envIsEmpty(true); No need
	NumSteps=-1;
	
	Timer = new QTimer(this);
	connect(Timer,SIGNAL(timeout()),this,SLOT(make1Step()));
	
	//ComboBox - Type of view
	QLabel *typeViewLabel = new QLabel(tr("Type of view: "));
	typeViewLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); 

	TypeViewCombo = new QComboBox;
	TypeViewCombo->addItem(TYPE_VIEW_1);
    TypeViewCombo->addItem(TYPE_VIEW_2);
    TypeViewCombo->addItem(TYPE_VIEW_3);
    TypeViewCombo->addItem(TYPE_VIEW_4);
    TypeViewCombo->addItem(TYPE_VIEW_5);
    TypeViewCombo->addItem(TYPE_VIEW_6);

	TypeViewCombo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

	 QVBoxLayout * typeViewLayout= new QVBoxLayout();
	 typeViewLayout->addWidget(typeViewLabel);
	 typeViewLayout->addWidget(TypeViewCombo);
	 //typeViewLayout->addStretch(1);

	//Field
	Field= new CField(&Env);

    connect(TypeViewCombo, SIGNAL(activated(const QString &)),Field, SLOT(setTypeView(const QString &)));
	connect(this,SIGNAL(envChanged()),Field,SLOT(renewField()));
	connect (Field,SIGNAL(cellDetails(int,int)),this,SLOT(showCellDetails(int,int)));

	//Legend
	CLegend * legend = new CLegend();
	connect(TypeViewCombo, SIGNAL(activated(const QString &)),legend, SLOT(setTypeView(const QString &)));

	//ScrollArea
	QScrollArea * scrollArea = new QScrollArea ();
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidget(Field); 

	//Zoom
	ZoomSlid = new ZoomSlider(tr("Zoom: "));
	ZoomSlid->setDisabled(true);
	connect(ZoomSlid,SIGNAL(valueChanged(int)),Field,SLOT(setZoom(int)));

	//Growing Flowers Ratio Slider
	QSlider * GFSlider = new QSlider(Qt::Horizontal);
	GFSlider->setRange(0, FLOWERGROWINGRATIO_NUM-1);
	GFSlider->setValue(FLOWERGROWINGRATIO_INIT);
	GFSlider->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed); 
	connect(GFSlider,SIGNAL(valueChanged(int)),this,SLOT(FlowerGrowingRatioInEnvChanged(int)));

	QLabel * GFLabel=new QLabel("Ratio of growth of flowers: ");
	GFLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); 

	QVBoxLayout * GFLayout= new QVBoxLayout();
	GFLayout->addWidget(GFLabel);
	GFLayout->addWidget(GFSlider);


	//connect(this,SIGNAL(envIsEmpty(bool)),ZoomSlid,SLOT(setDisabled(bool)));
	
	//CheckBox for display
	DisplayCheck = new QCheckBox(tr("Display On"));
	//DisplayCheck->resize(100,30);
	//DisplayCheck->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	connect(DisplayCheck, SIGNAL(stateChanged(int)),this,SLOT(DisplayChanged(int)));
	DisplayCheck->setCheckState(Qt::Checked);
	
	//CheckBox for LearningOn
	LearningCheck = new QCheckBox(tr("Learning On"));
	connect(LearningCheck, SIGNAL(stateChanged(int)),this,SLOT(LearningChanged(int)));
	if (Env.LearningOn) LearningCheck->setCheckState(Qt::Checked);
	else LearningCheck->setCheckState(Qt::Unchecked);
	
	QVBoxLayout * checksLayout= new QVBoxLayout();
	checksLayout->addWidget(DisplayCheck);
	checksLayout->addWidget(LearningCheck);

	//Time LCD
	
     TimeLCD = new LabeledLCD(tr("Time"));
     

	//Start, Stop, Make n steps buttons
	 QPushButton * runBut = new QPushButton(tr("Run"));
	 runBut-> setCheckable(true);
	 NumStepsSpin = new QSpinBox();
	 NumStepsSpin ->setMaximum(MAXTIME);
	 NumStepsSpin->setValue(100);
	 MakeNStepsBut = new QPushButton(tr("Make steps"));
	 MakeNStepsBut-> setCheckable(true);

	 runBut->setDisabled(true);MakeNStepsBut->setDisabled(true);NumStepsSpin->setDisabled(true);

	 if (false ==connect(runBut,SIGNAL(toggled(bool)),MakeNStepsBut,SLOT(setDisabled(bool))))
		 QMessageBox::information(this,"MyApp","not connected: runBut,MakeNStepsBut");
	 if (false ==connect(MakeNStepsBut,SIGNAL(toggled(bool)),runBut,SLOT(setDisabled(bool))))
		 QMessageBox::information(this,"MyApp","not connected: runBut,MakeNStepsBut");

	if (false ==connect(runBut,SIGNAL(toggled(bool)),NumStepsSpin,SLOT(setDisabled(bool))))
		 QMessageBox::information(this,"MyApp","not connected: runBut,NumStepsSpin");
	
	connect(MakeNStepsBut,SIGNAL(toggled(bool)),this,SLOT(runNSteps(bool)));
	connect(runBut,SIGNAL(toggled(bool)),this,SLOT(run(bool)));

	//If there is no environment opened, all buttons are disabled
	connect(this, SIGNAL(envIsEmpty(bool)),runBut,SLOT(setDisabled(bool)));
	connect(this, SIGNAL(envIsEmpty(bool)),NumStepsSpin,SLOT(setDisabled(bool)));
	connect(this, SIGNAL(envIsEmpty(bool)),MakeNStepsBut,SLOT(setDisabled(bool)));


	
	 //Legend Field:
	 

	 QVBoxLayout * rightLayout= new QVBoxLayout();
	 rightLayout->addWidget(TimeLCD);
	 //rightLayout->addStretch(1);
	 rightLayout->addWidget(runBut);
	 rightLayout->addWidget(NumStepsSpin);
	 rightLayout->addWidget(MakeNStepsBut);
	 rightLayout->addStretch(1);
	 rightLayout->addLayout(checksLayout,Qt::AlignHCenter);
	 rightLayout->addWidget(legend);


	 
	//numBeetles LCD
	NumBeetlesLCD = new LabeledLCD(tr("Beetles"));

	//numFlowers LCD     
	NumFlowersLCD = new LabeledLCD(tr("Flowers"));

	 //numBirths LCD	
	NumBirthsLCD= new LabeledLCD(tr("Births"));

	 //Bottom layout strip
	QHBoxLayout * bottomLayout= new QHBoxLayout();
	bottomLayout->addWidget(NumBeetlesLCD);
	bottomLayout->addWidget(NumFlowersLCD);
	bottomLayout->addWidget(NumBirthsLCD);
	
//	QMessageBox::information(this,"MyApp","7");
    QGridLayout * gridLayout = new QGridLayout;
    //gridLayout->setMargin(5);
	gridLayout->addWidget(scrollArea,0,0,1,2);
	gridLayout->addLayout(typeViewLayout,1,2);
	gridLayout->addWidget(ZoomSlid,1,0);
	gridLayout->addLayout(GFLayout,1,1);//DisplayCheck,1,1,Qt::AlignHCenter);
	gridLayout->addLayout(rightLayout,0,2);
	gridLayout->addLayout(bottomLayout,2,0,1,3);
	//gridLayout->addLayout(
	gridLayout->setRowStretch(0, 1);
   /* layout->addWidget(topFiller);
    layout->addWidget(infoLabel);
    layout->addWidget(bottomFiller);*/
    mainWidget->setLayout(gridLayout);

//	QMessageBox::information(this,"MyApp","8");
	//creation of menu and its actions
    createActions();
    createMenus();

	QString message = tr("Environment can be opened or created in the menu in \"File\" section.");
    statusBar()->showMessage(message);
	
//	QMessageBox::information(this,"MyApp","9");

    setWindowTitle(tr("Abeetles"));
    setMinimumSize(300, 400);
    resize(480, 500);
	renewAllChildren();
	
	
//	QMessageBox::information(this,"MyApp","10");

}
//Context menu - not used now.
/*
void CRunGui::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(saveHistStatsAct);
    menu.addAction(copyAct);
    menu.addAction(pasteAct);
    menu.exec(event->globalPos());
}*/

void CRunGui::newEnv()
{
   //Preliminarily:
	//1QMessage::information(NULL,"MyApp","Before cleaning");
	Env.CleanEnv();
	//1QMessage::information(NULL,"MyApp","Env is cleaned");
	Env.FillEmptyEnvRandomly(100);	
	//1QMessage::information(NULL,"MyApp","Env is filled"); //ch1
	//emit envChanged();//uprav tak, aby to nastalo jen if Env was 0
	//Field->setEnvRef(Env);	
	emit envIsEmpty(Env.IsEmpty);
	//1QMessage::information(NULL,"MyApp","Message is emited"); //ch1
	
	renewAllChildren();
	statusBar()->showMessage(tr("Random Env made."));

}

void CRunGui::openEnv() //pozor! tahle funkce ulozi jenom broucky - chybi: ulozit cas, kytky, statistiky.
{
	QFileDialog openDlg;
	openDlg.setFilter("Abeetles files (*.txt;*.bmp)");
	openDlg.setFilter("All files (*.*)");
    ActualFN = openDlg.getOpenFileName(this);
	if (!ActualFN.isEmpty()) ActualFN=ActualFN.left(ActualFN.lastIndexOf("_"));

    if (!ActualFN.isEmpty()) 
	{
		Env.CleanEnv();
		Env.LoadEnv(ActualFN.toAscii().data()); //!! zmen soubor beetles.txt tak, aby ukladal i jmeno prislusne mapy!
		//emit envChanged(); 
		emit envIsEmpty(Env.IsEmpty);
		renewAllChildren();
		statusBar()->showMessage(tr("Environment opened."));
	}
}

void CRunGui::saveEnv()//pozor! tahle funkce ulozi jenom broucky - chybi: ulozit cas, kytky, statistiky.
{
    if (ActualFN.isEmpty())
		saveEnvAs();
	else
	{
		if (Env.SaveEnv(ActualFN.toAscii().data()))
			statusBar()->showMessage(tr("Environment saved."));
		else statusBar()->showMessage(tr("Environment was not successfully saved."));
	}
}

void CRunGui::saveEnvAs()//pozor! tahle funkce ulozi jenom broucky - chybi: ulozit cas, kytky, statistiky.
{
    QFileDialog saveDlg;
	//saveDlg.setFilter("Abeetles files (*.txt;*.bmp)");
	saveDlg.setFilter("All files (*.*)");
	ActualFN = saveDlg.getSaveFileName(this);
	//1QMessage::information(NULL,"MyApp",ActualFN); 
    if (ActualFN.isEmpty())return;
		//if the filename already contains the suffix, I want to remove it
	if ( (-1!=ActualFN.lastIndexOf("_btl.txt"))||(-1!=ActualFN.lastIndexOf("_flw.txt"))||(-1!=ActualFN.lastIndexOf("_map.bmp"))||(-1!=ActualFN.lastIndexOf("_tst.csv")) )
		ActualFN=ActualFN.left(ActualFN.lastIndexOf("_"));
	else	//otherwise I remove only the ending
		ActualFN=ActualFN.left(ActualFN.lastIndexOf("."));

	//1QMessage::information(NULL,"MyApp",ActualFN);
    if (ActualFN.isEmpty())return;

	if (Env.SaveEnv(ActualFN.toAscii().data()))
		statusBar()->showMessage(tr("Environment saved."));
	else statusBar()->showMessage(tr("Environment was not successfully saved."));
	
}

void CRunGui::saveAggrStats()
{
	QFileDialog saveAggrDlg;
	saveAggrDlg.setFilter("Text files (*.txt)");
	saveAggrDlg.setFilter("All files (*.*)");
	ActualFN = saveAggrDlg.getSaveFileName(this);
	if (ActualFN.isEmpty())return;
	ActualFN=ActualFN.left(ActualFN.lastIndexOf("."))+".txt";
	
	Env.CountStatistics();
    if (Env.Statist.SaveActAgrStatist(ActualFN.toAscii().data(),Env.Time))
		statusBar()->showMessage(tr("Aggregated statistics saved."));
	else
		statusBar()->showMessage(tr("Aggregated statistics were not saved."));
}

void CRunGui::saveTimeStats()
{
	QFileDialog saveAggrDlg;
	saveAggrDlg.setFilter("Text files (*.csv)");
	saveAggrDlg.setFilter("All files (*.*)");
	ActualFN = saveAggrDlg.getSaveFileName(this);
	if (ActualFN.isEmpty())return;
	ActualFN=ActualFN.left(ActualFN.lastIndexOf("."))+".csv";

    if (Env.Statist.SaveTimeStatist_InColumnsAppend(ActualFN.toAscii().data()))
		statusBar()->showMessage(tr("Time statistics saved."));
	else
		statusBar()->showMessage(tr("Time statistics were not saved."));
}

void CRunGui::saveHistStats()
{
	QFileDialog saveHistDlg;
	saveHistDlg.setFilter("Text files (*.csv)");
	saveHistDlg.setFilter("All files (*.*)");
	ActualFN = saveHistDlg.getSaveFileName(this);
	if (ActualFN.isEmpty())return;
	ActualFN=ActualFN.left(ActualFN.lastIndexOf("."))+".csv";
	if (Env.Statist.SaveActHistStatist(ActualFN.toAscii().data(),Env.Time,&Env.Grid))
		statusBar()->showMessage(tr("Histogram statistics saved."));
	else
		statusBar()->showMessage(tr("Histogram statistics were not saved."));
}

void CRunGui::about()
{
    //infoLabel->setText(tr("Invoked <b>Help|Aboutp</b>"));
    QMessageBox::about(this, tr("About Menu"),
            tr("The application Abeetles."));
}


void CRunGui::createActions()
{
    newEnvAct = new QAction(tr("&New Environment"), this);
    newEnvAct->setShortcut(tr("Ctrl+N"));
    newEnvAct->setStatusTip(tr("Create a new environment"));
    connect(newEnvAct, SIGNAL(triggered()), this, SLOT(newEnv()));

    openEnvAct = new QAction(tr("&Open Environment..."), this);
    openEnvAct->setShortcut(tr("Ctrl+O"));
    openEnvAct->setStatusTip(tr("Open an existing environment"));
    connect(openEnvAct, SIGNAL(triggered()), this, SLOT(openEnv()));

    saveEnvAct = new QAction(tr("&Save Environment"), this);
    saveEnvAct->setShortcut(tr("Ctrl+S"));
    saveEnvAct->setStatusTip(tr("Save the environment to disk"));
    connect(saveEnvAct, SIGNAL(triggered()), this, SLOT(saveEnv()));

    saveEnvAsAct = new QAction(tr("Save &Environment As..."), this);
    saveEnvAsAct->setShortcut(tr("Ctrl+E"));
    saveEnvAsAct->setStatusTip(tr("Save the environment to disk"));
    connect(saveEnvAsAct, SIGNAL(triggered()), this, SLOT(saveEnvAs()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    saveAggrStatsAct = new QAction(tr("Save &Aggregated Statistics"), this);
    saveAggrStatsAct->setShortcut(tr("Ctrl+A"));
    saveAggrStatsAct->setStatusTip(tr("Saves various aggregated statistics into a text file."));
    connect(saveAggrStatsAct, SIGNAL(triggered()), this, SLOT(saveAggrStats()));

    saveTimeStatsAct = new QAction(tr("Save &Time Statistics"), this);
    saveTimeStatsAct->setShortcut(tr("Ctrl+T"));
    saveTimeStatsAct->setStatusTip(tr("Saves various time dependent statistics into a .csv file."));
    connect(saveTimeStatsAct, SIGNAL(triggered()), this, SLOT(saveTimeStats()));

    saveHistStatsAct = new QAction(tr("Save &Histogram Statistics"), this);
    saveHistStatsAct->setShortcut(tr("Ctrl+H"));
    saveHistStatsAct->setStatusTip(tr("Saves data for view in histogram graph."));
    connect(saveHistStatsAct, SIGNAL(triggered()), this, SLOT(saveHistStats()));



    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    
}

void CRunGui::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newEnvAct);
    fileMenu->addAction(openEnvAct);
    fileMenu->addAction(saveEnvAct);
    fileMenu->addAction(saveEnvAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    statistsMenu = menuBar()->addMenu(tr("&Statistics"));
	
    statistsMenu->addAction(saveAggrStatsAct);
    statistsMenu->addAction(saveTimeStatsAct);
    statistsMenu->addAction(saveHistStatsAct);
   
}
/**
* Public method <br>
* Description: Updates all widgets of the main window according to actual state of Environment.<br>
* System dependence: OS - no, lib - qt.<br>
* Usage comments: Used when: new env, open env, make1step.<br>
* @see reference : adds reference to the "See Also" section. The reference can be any of the following:
*          o HTML tag/text, which is added unmodified
*          o a quoted string (e.g., "Foo Bar"), the contents of which are added unmodified
*          o [project].[ class-name][#member] [text ], which adds a link to the given member in class class-name in project project . If project is omitted, the current entity's project is assumed. If class-name is omitted, the current class is assumed. If member is omitted, the link is to the class-file. If text is omitted, default display text is added, based on the actual link.
* {@link reference } replaced with a reference that is built using the exact same syntax as the @see tag (above). For example:
*/
void CRunGui::renewAllChildren()
{
	NumBeetlesLCD->setValue(Env.Statist.NumBeetles);
	NumFlowersLCD->setValue(Env.Statist.NumFlowers);
	NumBirthsLCD->setValue(Env.Statist.NumBirths);
	TimeLCD->setValue(Env.Time);

	if (Env.LearningOn) LearningCheck->setCheckState(Qt::Checked);
	else LearningCheck->setCheckState(Qt::Unchecked);

	//QMessageBox::information(this,"MyApp","1");
	if (Field == NULL){
		QMessageBox::information(this,"MyApp","Field was not created");
		return;
	}
	if (DisplayCheck->checkState() == Qt::Checked)
	{
		//1QMessageBox::information(this,"MyApp","Field is gonna be renewed.");
		Field->renewField(); //Pozor! Tohle pusobilo padani aplikace v necekanych pripadech!
		Field->update();
	}
}

void CRunGui::run(bool bStart)
{
	if (bStart == true)
	{
		NumSteps=-1;
		Timer->start();//TIME_STEP); // interval is now set as set at DisplayChanged() function.
		//QMessageBox::information(this,"MyApp","Run infinitely.");
		
	}
	else
	{
		Timer->stop();
		NumSteps=0;
		//QMessageBox::information(this,"MyApp","Stop timer.");
	}
	
		
}

void CRunGui::runNSteps(bool bStart)
{
	if (bStart == true)
	{
		NumSteps=NumStepsSpin->value();
		Timer->start(); // interval is now set as set at DisplayChanged() function.
		//QMessageBox::information(this,"MyApp","Start "+QString::number(NumStepsSpin->value())+" steps.");
				
	}
	else
	{		
		Timer->stop();
		NumSteps=0;
		//QMessageBox::information(this,"MyApp","Stop timer.");
	}
	
		
}
void CRunGui::make1Step()
{
	int I,J;

	if (NumSteps==0) 
	{
		MakeNStepsBut->toggle();
		return;
	}
	if (Env.Time>=MAXTIME) 
	{
		QMessageBox::information(this,"MyApp","Maximum of time reached. Start a new environment.");
		Timer->stop();
		NumSteps=-1;
	}

	for(I=0;I<Env.Grid_Past.G_Width;I++)
		for(J=0;J<Env.Grid_Past.G_Height;J++)
		{
			if (Env.Grid_Past.GetCellContent(I,J)==BEETLE) Env.MakeBeetleAction(I,J);
			else if (Env.Grid_Past.GetCellContent(I,J)==NOTHING) Env.MakeFlowerGrow(I,J);
			else if (Env.Grid_Past.GetCellContent(I,J)==FLOWER) Env.MakeFlowerDie(I,J);
			//if there is a wall, flower of something bad, do nothing
		}

		//output 
		/*
		if (Env.DisplayOn)
		{
			printf(" NumBeetles: %d, NumBirths: %d, NumFlowers: %d ",Env.Statist.NumBeetles,Env.Statist.NumBirths,Env.Statist.NumFlowers);		
			Env.PrintEnv();	
		}*/
	if (NumSteps>0) NumSteps--;
			
	Env.NextTime();
	renewAllChildren();


}

void CRunGui::showCellDetails(int x,int y)
{
	CBeetle * beetle=NULL;
	if (Env.Grid.GetCellContent(x,y,&beetle) == BEETLE)
	{
		//QMessageBox::information(this,"","1");
		if (beetle==NULL) QMessageBox::information(this,"","XX");
		//QMessageBox::information(this,"","2");
		BeetleDialog beetleDlq(beetle,this);
		beetleDlq.exec();
	}
	else
		QMessageBox::information(this,"Cell details","Coords: "+QString::number(x)+", "+QString::number(y));
}

void CRunGui::DisplayChanged(int value)//Qt values: Qt::Checked, Qt::Unchecked
{
	if (value==Qt::Unchecked)//Displaying stops
	{
		TypeViewCombo->setDisabled(true);
		ZoomSlid->setDisabled(true);
		Field->setDisabled(true);
		Timer->setInterval(0);
	}
	if (value==Qt::Checked)//Displaying starts
	{
		TypeViewCombo->setDisabled(false);
		ZoomSlid->setDisabled(false);
		Field->setDisabled(false);
		Timer->setInterval(TIME_STEP);
	}

}

void CRunGui::LearningChanged(int value)//Qt values: Qt::Checked, Qt::Unchecked
{
	if (value==Qt::Unchecked)//Learning stops
	{
		Env.LearningOn = false;
	}
	if (value==Qt::Checked)//Displaying starts
	{
		Env.LearningOn = true;
	}
}

void CRunGui::FlowerGrowingRatioInEnvChanged(int value)
{
	Env.FlowerGrowingRatio=value;
	//QMessageBox::information(this,"",QString::number(value));
}

