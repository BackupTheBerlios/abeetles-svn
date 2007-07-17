#pragma once
#include <QString>
#include <QList>
#include "COneRun.h"
#include "Environment.h"

class CRunScript
{
public:
	CRunScript(QList<COneRun*>);

	QList<COneRun*> ListRuns;

	//CEnvironment env;

	int run ();

};

