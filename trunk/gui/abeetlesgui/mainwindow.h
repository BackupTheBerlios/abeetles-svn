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

#pragma once

#include <QMainWindow>
#include <QtGui>
#include "Environment.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class CField;
class CEnvironment;
class LabeledLCD;
class ZoomSlider;
class QWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

	CEnvironment Env;	

//Context menu - not used now.
/* 
protected:
    void contextMenuEvent(QContextMenuEvent *event);
*/

private slots:
    void newEnv();
    void openEnv();
    void saveEnv();
    void saveEnvAs();

	void run(bool bStart);
	void runNSteps(bool bStart);
	void make1Step();

	void DisplayChanged(int value);//Qt values: Qt::checked, Qt::unchecked
	
    void saveAggrStats();
    void saveTimeStats();
    void saveHistStats();

	void showCellDetails(int x,int y);
  /*  void copy();
    void paste();
    void bold();
    void italic();
    void leftAlign();
    void rightAlign();
    void justify();
    void center();
    void setLineSpacing();
    void setParagraphSpacing();*/
    void about();
    //void aboutQt();

signals:
	void envChanged();
	void envIsEmpty(bool isNull);

private:
	LabeledLCD * NumFlowersLCD;
	LabeledLCD * NumBeetlesLCD;
	LabeledLCD * NumBirthsLCD;
	LabeledLCD * TimeLCD;//Shows the time slice, that is about to begin.


	QComboBox * TypeViewCombo;
	QSpinBox * NumStepsSpin;
	QPushButton * MakeNStepsBut;
	ZoomSlider * ZoomSlid;
	QCheckBox * DisplayCheck;

	QTimer * Timer;

	CField * Field;
	int NumSteps;

	
	
	QString ActualFN;
	//QString mapFN;

private:
    void createActions();
    void createMenus();
	void renewAllChildren();


    QMenu *fileMenu;
    QMenu *statistsMenu;
    QMenu *helpMenu;

	//Menu "File"
		QAction *newEnvAct;
		QAction *openEnvAct;
		QAction *saveEnvAct;
		QAction *saveEnvAsAct;
		QAction *exitAct;

	//Menu "Statistics"
		
		QAction *saveAggrStatsAct;
		QAction *saveTimeStatsAct;
		QAction *saveHistStatsAct;


	//Menu "Help"
		QAction *aboutAct;
		QAction *aboutQtAct;
		//QLabel *infoLabel;

};

