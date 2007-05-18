
static char rcsid[] =
	"$Id: hello_other.c,v 1.2 1997/07/09 13:24:45 pvmsrc Exp $";

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

#include "pvm3.h"

main()
{
	int ptid;
	char buf[100];

	ptid = pvm_parent(); //gets the tid of process, that spawned this process (it was hello.c)

	strcpy(buf, "hello, world from ");
	gethostname(buf + strlen(buf), 64); //function of unix, that obtains the hostname of this machine

	pvm_initsend(PvmDataDefault); //the constant variable PvmDataDefault lets data be coded by XDR. PvmDataRaw doesn't encode it at all and expects, it will be sent to the same type of machine. 
	pvm_pkstr(buf);//Pack the active message buffer with arrays of prescribed data type
	pvm_send(ptid, 1);//Nonblocking send

	pvm_exit();//this routine tells the pvmd, that this process is leaving pvm.
	exit(0);
}

