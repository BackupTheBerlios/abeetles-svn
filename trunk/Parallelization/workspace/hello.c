
static char rcsid[] =
	"$Id: hello.c,v 1.2 1997/07/09 13:24:44 pvmsrc Exp $";

/*
 *         PVM version 3.4:  Parallel Virtual Machine System
 *               University of Tennessee, Knoxville TN.
 *           Oak Ridge National Laboratory, Oak Ridge TN.
 *                   Emory University, Atlanta GA.
 *      Authors:  J. J. Dongarra, G. E. Fagg, M. Fischer
 *          G. A. Geist, J. A. Kohl, R. J. Manchek, P. Mucci,
 *         P. M. Papadopoulos, S. L. Scott, and V. S. Sunderam
 *                   (C) 1997 All Rights Reserved
 *
 *                              NOTICE
 *
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby granted
 * provided that the above copyright notice appear in all copies and
 * that both the copyright notice and this permission notice appear in
 * supporting documentation.
 *
 * Neither the Institutions (Emory University, Oak Ridge National
 * Laboratory, and University of Tennessee) nor the Authors make any
 * representations about the suitability of this software for any
 * purpose.  This software is provided ``as is'' without express or
 * implied warranty.
 *
 * PVM version 3 was funded in part by the U.S. Department of Energy,
 * the National Science Foundation and the State of Tennessee.
 */

#include <stdio.h>
#include "pvm3.h"

main()
{
	int cc, tid;
	char buf[100];

	printf("i'm t%x\n", pvm_mytid());

	//function pvm_spawn returns the number of started processes
	cc = pvm_spawn("hello_other", //name of executable of the process that I want to spawn
					(char**)0, //args for the process to be started
					0, 			//Options about where to start the task. Sum of: 0 - choose any machine, 1 - "Where" specifies a particular host, ...
					"", //"Where"
					1, //number if copies to start
					&tid);//place to store tid(s) of started process(es)

	if (cc == 1) {
		//pvm_recv blocks until desired message comes and returns value of the new active receive buffer identifier. The buffer is created by pvm itself. If some error occurs then bufid will be < 0.
		cc = pvm_recv(	-1, //tid of the process I should get the message from
						-1);//tag of the message, I should receive
						//-1 in any of previous means, that receive matches any value of tid(tag)
						
		pvm_bufinfo(cc, (int*)0, (int*)0, &tid); //gets info about buffer that received the mesage
		pvm_upkstr(buf);//Unpack the active message buffer into arrays of prescribed data type - in this case into array of char
		printf("from t%x: %s\n", tid, buf);

	} else
		printf("can't start hello_other\n");

	pvm_exit();
	exit(0);
}


