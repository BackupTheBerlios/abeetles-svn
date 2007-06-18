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

#include "mainwindow.h"
#include "field.h"
#include "zoomslider.h"
#include "defines.h"

MainWindow::MainWindow()
{
	//setting of central widget of the window
    QWidget *mainWidget = new QWidget;
    setCentralWidget(mainWidget);
	
	//ComboBox - Type of view
	QLabel *typeViewLabel = new QLabel(tr("Type of view: "));
	typeViewLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); 

	QComboBox *typeViewCombo = new QComboBox;
	typeViewCombo->addItem("blue");
    typeViewCombo->addItem("green");
    typeViewCombo->addItem("red");
    typeViewCombo->addItem("grey");
    typeViewCombo->addItem("navy");
	typeViewCombo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

	 QVBoxLayout * typeViewLayout= new QVBoxLayout();
	 typeViewLayout->addWidget(typeViewLabel);
	 typeViewLayout->addWidget(typeViewCombo);
	 typeViewLayout->addStretch(1);

	//Field
	Field * field= new Field();

    connect(typeViewCombo, SIGNAL(activated(const QString &)),field, SLOT(setTypeView(const QString &)));

	//ScrollArea
	QScrollArea * scrollArea = new QScrollArea ();
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidget(field); 

	//Zoom
	ZoomSlider * zoomSlid = new ZoomSlider(tr("Zoom: "));
	
	//Time LCD
	
     QLCDNumber * timeLCD = new QLCDNumber(6);
     timeLCD->setSegmentStyle(QLCDNumber::Filled);
	 timeLCD->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed); 

     QLabel *timeLabel = new QLabel(tr("TIME"));
	 timeLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed); 

	//Start, Stop, Make n steps buttons
	 QPushButton * runBut = new QPushButton(tr("Run"));
	 runBut-> setCheckable(true);
	 QSpinBox * numStepsSpin = new QSpinBox();
	 numStepsSpin ->setMaximum(MAX_TIME);
	 numStepsSpin->setValue(100);
	 QPushButton * makeNStepsBut = new QPushButton(tr("Make steps"));
	 makeNStepsBut-> setCheckable(true);
	 if (false ==connect(runBut,SIGNAL(toggled(bool)),makeNStepsBut,SLOT(setChecked(bool))))
		 QMessageBox::information(this,"MyApp","not connected: runBut,makeNStepsBut");
	 if (false ==connect(makeNStepsBut,SIGNAL(toggled(bool)),runBut,SLOT(setChecked(bool))))
		 QMessageBox::information(this,"MyApp","not connected: runBut,makeNStepsBut");
	 //connect(startBut,SIGNAL(clicked()),stopBut,SLOT(setEnabled(true)));
	 //connect(stopBut,SIGNAL(clicked()),stopBut,SLOT(setEnabled(false)));
	 //connect(stopBut,SIGNAL(clicked()),startBut,SLOT(setEnabled(true)));


	 QVBoxLayout * rightLayout= new QVBoxLayout();
	 rightLayout->addWidget(timeLabel);
	 rightLayout->addWidget(timeLCD);
	 rightLayout->addStretch(1);
	 rightLayout->addWidget(runBut);
	 rightLayout->addWidget(numStepsSpin);
	 rightLayout->addWidget(makeNStepsBut);
	 rightLayout->addStretch(1);

	 

	//This was original stripe with info in the middle of the window and two fillers.
	/*
    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
                              "invoke a context menu</i>"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);*/

    QGridLayout * gridLayout = new QGridLayout;
    //gridLayout->setMargin(5);
	gridLayout->addWidget(scrollArea,0,0);
	gridLayout->addLayout(typeViewLayout,1,1);
	gridLayout->addWidget(zoomSlid,1,0);
	gridLayout->addLayout(rightLayout,0,1);
	//gridLayout->setColumnStretch(1, 1);
   /* layout->addWidget(topFiller);
    layout->addWidget(infoLabel);
    layout->addWidget(bottomFiller);*/
    mainWidget->setLayout(gridLayout);

	//creation of menu and its actions
    createActions();
    createMenus();

	QString message = tr("Environment can be opened or created in the menu in \"File\" section.");
    statusBar()->showMessage(message);
	

    setWindowTitle(tr("Abeetles"));
    setMinimumSize(300, 300);
    resize(480, 320);
}
//Context menu - not used now.
/*
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(cutAct);
    menu.addAction(copyAct);
    menu.addAction(pasteAct);
    menu.exec(event->globalPos());
}*/

void MainWindow::newEnv()
{
    //infoLabel->setText(tr("Invoked <b>File|New</b>"));
}

void MainWindow::openEnv()
{
    //infoLabel->setText(tr("Invoked <b>File|Open</b>"));
}

void MainWindow::saveEnv()
{
    //infoLabel->setText(tr("Invoked <b>File|Save</b>"));
}

void MainWindow::saveEnvAs()
{
    //infoLabel->setText(tr("Invoked <b>File|Print</b>"));
}
/*
void MainWindow::undo()
{
    //infoLabel->setText(tr("Invoked <b>Statistics|Undo</b>"));
}

void MainWindow::redo()
{
    //infoLabel->setText(tr("Invoked <b>Statistics|Redo</b>"));
}

void MainWindow::cut()
{
    //infoLabel->setText(tr("Invoked <b>Statistics|Cut</b>"));
}

void MainWindow::copy()
{
    //infoLabel->setText(tr("Invoked <b>Statistics|Copy</b>"));
}

void MainWindow::paste()
{
    //infoLabel->setText(tr("Invoked <b>Statistics|Paste</b>"));
}

void MainWindow::bold()
{
    //infoLabel->setText(tr("Invoked <b>Statistics|Format|Bold</b>"));
}

void MainWindow::italic()
{
    //infoLabel->setText(tr("Invoked <b>Statistics|Format|Italic</b>"));
}

void MainWindow::leftAlign()
{
    //infoLabel->setText(tr("Invoked <b>Statistics|Format|Left Align</b>"));
}

void MainWindow::rightAlign()
{
    //infoLabel->setText(tr("Invoked <b>Statistics|Format|Right Align</b>"));
}

void MainWindow::justify()
{
    //infoLabel->setText(tr("Invoked <b>Statistics|Format|Justify</b>"));
}

void MainWindow::center()
{
    //infoLabel->setText(tr("Invoked <b>Statistics|Format|Center</b>"));
}

void MainWindow::setLineSpacing()
{
    //infoLabel->setText(tr("Invoked <b>Statistics|Format|Set Line Spacing</b>"));
}

void MainWindow::setParagraphSpacing()
{
    //infoLabel->setText(tr("Invoked <b>Statistics|Format|Set Paragraph Spacing</b>"));
}
*/
void MainWindow::about()
{
    //infoLabel->setText(tr("Invoked <b>Help|Aboutp</b>"));
    QMessageBox::about(this, tr("About Menu"),
            tr("The application Abeetles."));
}
/*
void MainWindow::aboutQt()
{
    //infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
}*/

void MainWindow::createActions()
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
/*
    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcut(tr("Ctrl+Z"));
    undoAct->setStatusTip(tr("Undo the last operation"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcut(tr("Ctrl+Y"));
    redoAct->setStatusTip(tr("Redo the last operation"));
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));

    cutAct = new QAction(tr("Cu&t"), this);
    cutAct->setShortcut(tr("Ctrl+X"));
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcut(tr("Ctrl+C"));
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcut(tr("Ctrl+V"));
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));

    boldAct = new QAction(tr("&Bold"), this);
    boldAct->setCheckable(true);
    boldAct->setShortcut(tr("Ctrl+B"));
    boldAct->setStatusTip(tr("Make the text bold"));
    connect(boldAct, SIGNAL(triggered()), this, SLOT(bold()));

    QFont boldFont = boldAct->font();
    boldFont.setBold(true);
    boldAct->setFont(boldFont);

    italicAct = new QAction(tr("&Italic"), this);
    italicAct->setCheckable(true);
    italicAct->setShortcut(tr("Ctrl+I"));
    italicAct->setStatusTip(tr("Make the text italic"));
    connect(italicAct, SIGNAL(triggered()), this, SLOT(italic()));

    QFont italicFont = italicAct->font();
    italicFont.setItalic(true);
    italicAct->setFont(italicFont);

    setLineSpacingAct = new QAction(tr("Set &Line Spacing..."), this);
    setLineSpacingAct->setStatusTip(tr("Change the gap between the lines of a "
                                       "paragraph"));
    connect(setLineSpacingAct, SIGNAL(triggered()), this, SLOT(setLineSpacing()));

    setParagraphSpacingAct = new QAction(tr("Set &Paragraph Spacing..."), this);
    setLineSpacingAct->setStatusTip(tr("Change the gap between paragraphs"));
    connect(setParagraphSpacingAct, SIGNAL(triggered()),
            this, SLOT(setParagraphSpacing()));*/

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    /*aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));*/
/*
    leftAlignAct = new QAction(tr("&Left Align"), this);
    leftAlignAct->setCheckable(true);
    leftAlignAct->setShortcut(tr("Ctrl+L"));
    leftAlignAct->setStatusTip(tr("Left align the selected text"));
    connect(leftAlignAct, SIGNAL(triggered()), this, SLOT(leftAlign()));

    rightAlignAct = new QAction(tr("&Right Align"), this);
    rightAlignAct->setCheckable(true);
    rightAlignAct->setShortcut(tr("Ctrl+R"));
    rightAlignAct->setStatusTip(tr("Right align the selected text"));
    connect(rightAlignAct, SIGNAL(triggered()), this, SLOT(rightAlign()));

    justifyAct = new QAction(tr("&Justify"), this);
    justifyAct->setCheckable(true);
    justifyAct->setShortcut(tr("Ctrl+J"));
    justifyAct->setStatusTip(tr("Justify the selected text"));
    connect(justifyAct, SIGNAL(triggered()), this, SLOT(justify()));

    centerAct = new QAction(tr("&Center"), this);
    centerAct->setCheckable(true);
    centerAct->setShortcut(tr("Ctrl+E"));
    centerAct->setStatusTip(tr("Center the selected text"));
    connect(centerAct, SIGNAL(triggered()), this, SLOT(center()));

    alignmentGroup = new QActionGroup(this);
    alignmentGroup->addAction(leftAlignAct);
    alignmentGroup->addAction(rightAlignAct);
    alignmentGroup->addAction(justifyAct);
    alignmentGroup->addAction(centerAct);
    leftAlignAct->setChecked(true);*/
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newEnvAct);
    fileMenu->addAction(openEnvAct);
    fileMenu->addAction(saveEnvAct);
    fileMenu->addAction(saveEnvAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Statistics"));
	/*
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    formatMenu = editMenu->addMenu(tr("&Format"));
    formatMenu->addAction(boldAct);
    formatMenu->addAction(italicAct);
    formatMenu->addSeparator()->setText(tr("Alignment"));
    formatMenu->addAction(leftAlignAct);
    formatMenu->addAction(rightAlignAct);
    formatMenu->addAction(justifyAct);
    formatMenu->addAction(centerAct);
    formatMenu->addSeparator();
    formatMenu->addAction(setLineSpacingAct);
    formatMenu->addAction(setParagraphSpacingAct);*/
}
