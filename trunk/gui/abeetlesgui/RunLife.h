#pragma once
#include "Environment.h"

class CRunLife
{
public:
	CRunLife(void);
	~CRunLife(void);
	static int run(void);
	static bool DialogWithUser(CEnvironment * Env, int* jumpTime);
};
