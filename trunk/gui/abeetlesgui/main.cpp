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

#include <QApplication>
#include <QMessageBox>
//#include <QStringList>

#include "mainwindow.h"
#include "CfgManager.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

//Global variables
CfgManager CfgMng; 
QString ScriptFN;

int RandInBound (int bound)
{
    unsigned int    number;
    int  err=0;	

	number=rand();

    
       if (err != 0)
    {
       printf("The rand_s function failed!\n");
	   return 0;
    }
	unsigned int Res = ((int)((((double)number /(double) RAND_MAX ) * bound))) % bound;
    return Res;

}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	
	int i;
	bool isScript=false;
	for (i=0;i<app.arguments().size();i++)
	{
		
		if (isScript==true) 
		{
			QMessageBox::information(NULL,"",QString::number(i)+" "+app.arguments().at(i));
			ScriptFN=app.arguments().at(i);
			break;
		}
			
		if (app.arguments().at(i) =="-s") isScript=true;

	}
	if (isScript) 
	{

		QMessageBox::information(NULL,"","Script will be executed.");
		app.quit();
		return (0);

	}
	
	MainWindow window;
	window.show();
	
    return app.exec();
}
