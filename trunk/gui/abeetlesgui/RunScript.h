#pragma once
#include <QString>
#include <QList>
#include "COneRun.h"
#include "Environment.h"

class CRunScript
{
public:
	CRunScript(QString script);

	QList<COneRun*> ListRuns;

	//CEnvironment env;

	int run ();

};

