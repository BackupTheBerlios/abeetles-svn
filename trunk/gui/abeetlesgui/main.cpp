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

#include "CRunGui.h"
#include "CfgManager.h"
#include "RunScript.h"
#include "COneRun.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

#include <QtPlugin>

//Q_IMPORT_PLUGIN(qgif)

//Global variables
CfgManager CfgMng; 


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
	//fprintf(stdout,"Ahoj");

	int i;
	bool isScript=false;
	for (i=0;i<app.arguments().size();i++)
	{
		
		if (isScript==true) 
		{
			//QMessageBox::information(NULL,"",QString::number(i)+" "+app.arguments().at(i));			
			break;
		}
			
		if (app.arguments().at(i) =="-s") isScript=true;

	}
	if (isScript) 
	{
		QString scriptFN=app.arguments().at(i);
		//fprintf(stdout,("Script "+scriptFN+" starts execution.\n").toAscii().data());
		//predelej: trida CRunScript dostane jako vstup konstruktoru jmeno skriptu, v konstruktoru zavola CfgMng.LoadScript. Zde nasledne prikazem spustim run().
		CRunScript runScript(scriptFN);
		runScript.run();
		app.quit();
		return (0);

	}
	
	CRunGui window;
	window.show();
	
    return app.exec();
}
