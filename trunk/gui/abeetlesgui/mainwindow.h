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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class CField;
class CEnvironment;
class QLCDNumber;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

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
	/*
    void undo();
    void redo();
    void cut();
    void copy();
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

protected:
	void paintEvent(QPaintEvent * /* event */);
 

private:
    void createActions();
    void createMenus();


    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
    QActionGroup *alignmentGroup;

	//Menu "File"
		QAction *newEnvAct;
		QAction *openEnvAct;
		QAction *saveEnvAct;
		QAction *saveEnvAsAct;
		QAction *exitAct;

	//Menu "Statistics"
		/*
		QAction *undoAct;
		QAction *redoAct;
		QAction *cutAct;
		QAction *copyAct;
		QAction *pasteAct;
		QAction *boldAct;
		QAction *italicAct;
		QAction *leftAlignAct;
		QAction *rightAlignAct;
		QAction *justifyAct;
		QAction *centerAct;
		QAction *setLineSpacingAct;
		QAction *setParagraphSpacingAct;*/

	//Menu "Help"
		QAction *aboutAct;
		QAction *aboutQtAct;
		//QLabel *infoLabel;
	
	CField * Field;
	QLCDNumber * NumBeetlesLCD;
	QLCDNumber * NumFlowersLCD;
	QLCDNumber * NumBirthsLCD;
	
	CEnvironment * Env;
	//QString beetleFN;
	//QString mapFN;
};

#endif
