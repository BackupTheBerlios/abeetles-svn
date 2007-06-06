
/* $Id: pvmtev.h,v 1.7 1997/07/09 13:29:39 pvmsrc Exp $ */

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

/*
 *	pvmtev.h
 *
 *	Libpvm tracing includes.
 *
$Log: pvmtev.h,v $
Revision 1.7  1997/07/09 13:29:39  pvmsrc
Fixed Author Header.

 * Revision 1.6  1997/05/01  20:16:50  pvmsrc
 * Renamed TEV_MBOXINFO -> TEV_GETMBOXINFO.
 *
 * Revision 1.5  1997/04/10  20:25:52  pvmsrc
 * TEV_GETNAMES -> TEV_MBOXINFO.
 *
 * Revision 1.4  1997/02/17  21:26:44  pvmsrc
 * Fixed comments for Steve (who actually reads them, hahahaha).
 * 	- decls for pvmtevdidlist[] & pvmtevinfo[] are now in global.c.
 *
 * Revision 1.3  1997/01/28  19:14:23  pvmsrc
 * New Copyright Notice & Authors.
 *
 * Revision 1.2  1996/10/24  19:35:12  pvmsrc
 * Modified for New Tracing Facility:
 * 	- added trace buffer marker constants, TEV_MARK_*.
 * 	- added dummy user-defined trace tid & message code,
 * 		PVM_TRACE_TID & PVM_TRACE_CODE.
 * 	- added trace event data types, TEV_DATA_*.
 * 	- added semantic data IDs, TEV_DID_*, with new struct Pvmtevdid.
 * 	- replaced old trace event IDs, no longer TEV_*0 / TEV_*1,
 * 		use TEV_EVENT_ENTRY & TEV_EVENT_EXIT to distinguish.
 * 	- added new struct Pvmtevinfo.
 * 	- modified trace mask defn & macros, fix length large enough for
 * 		compatible growth.
 * 	- renamed macros for consistency -> TEV_MASK_*().
 * 	- added new struct Pvmtracer.
 *
 * Revision 1.1  1996/09/23  21:06:34  pvmsrc
 * Initial revision
 *
 */

#ifndef	_PVMTEV_H_

#define	_PVMTEV_H_

/* Trace Markers */

#define	TEV_MARK_EVENT_BUFFER			-1
#define	TEV_MARK_EVENT_BUFFER_END		-2
#define	TEV_MARK_DATA_ID				-3
#define	TEV_MARK_DATA_ID_END			-4
#define	TEV_MARK_EVENT_DESC				-5
#define	TEV_MARK_EVENT_DESC_END			-6
#define	TEV_MARK_EVENT_RECORD			-7
#define	TEV_MARK_EVENT_RECORD_END		-8
#define	TEV_MARK_USER_EVENT_RECORD		-9
#define	TEV_MARK_USER_EVENT_RECORD_END	-10


/* Dummy Trace Tid & Code for User Defined Events */

#define	PVM_TRACE_TID		-1111
#define	PVM_TRACE_CODE		-2222


/* Trace Event Data Types */

#define	TEV_DATA_NULL			0
#define	TEV_DATA_BYTE			1
#define	TEV_DATA_CPLX			2
#define	TEV_DATA_DCPLX			3
#define	TEV_DATA_DOUBLE			4
#define	TEV_DATA_FLOAT			5
#define	TEV_DATA_INT			6
#define	TEV_DATA_UINT			7
#define	TEV_DATA_LONG			8
#define	TEV_DATA_ULONG			9
#define	TEV_DATA_SHORT			10
#define	TEV_DATA_USHORT			11
#define	TEV_DATA_STRING			12
#define	TEV_DATA_STRUCT_START	13
#define	TEV_DATA_STRUCT_END		14
#define	TEV_DATA_DEFERRED		15

#define	TEV_DATA_SCALAR			0x00
#define	TEV_DATA_ARRAY			0x80


/* Trace Event Data Identifier ID Constants */

/************* PLEASE NOTE ******************/
/*											*/
/*	When Adding or Changing, ALWAYS Update:	*/
/*		struct Pvmtevdid pvmtevdidlist[];	*/
/*	in file $PVM_ROOT/src/global.c			*/
/*											*/
/************* PLEASE NOTE ******************/

#define	TEV_DID_FIRST	0
#define	TEV_DID_AN		0
#define	TEV_DID_AC		1
#define	TEV_DID_AS		2
#define	TEV_DID_BF		3
#define	TEV_DID_CC		4
#define	TEV_DID_CN		5
#define	TEV_DID_CI		6
#define	TEV_DID_CF		7
#define	TEV_DID_CD		8
#define	TEV_DID_CR		9
#define	TEV_DID_CL		10
#define	TEV_DID_CDA		11
#define	TEV_DID_CDT		12
#define	TEV_DID_CDX		13
#define	TEV_DID_CDC		14
#define	TEV_DID_CGI		15
#define	TEV_DID_CRF		16
#define	TEV_DID_CXC		17
#define	TEV_DID_CXF		18
#define	TEV_DID_CXN		19
#define	TEV_DID_CXS		20
#define	TEV_DID_ERI		21
#define	TEV_DID_ERR		22
#define	TEV_DID_FDS		23
#define	TEV_DID_FP		24
#define	TEV_DID_GN		25
#define	TEV_DID_GI		26
#define	TEV_DID_GT		27
#define	TEV_DID_GS		28
#define	TEV_DID_GBC		29
#define	TEV_DID_HN		30
#define	TEV_DID_HNL		31
#define	TEV_DID_HNA		32
#define	TEV_DID_HPT		33
#define	TEV_DID_HA		34
#define	TEV_DID_HSP		35
#define	TEV_DID_HIS		36
#define	TEV_DID_HCS		37
#define	TEV_DID_HCU		38
#define	TEV_DID_HDS		39
#define	TEV_DID_HDU		40
#define	TEV_DID_HS		41
#define	TEV_DID_INB		42
#define	TEV_DID_IMC		43
#define	TEV_DID_IST		44
#define	TEV_DID_MC		45
#define	TEV_DID_MB		46
#define	TEV_DID_MNB		47
#define	TEV_DID_SRC		48
#define	TEV_DID_DST		49
#define	TEV_DID_MDL		50
#define	TEV_DID_MTS		51
#define	TEV_DID_MTU		52
#define	TEV_DID_MRF		53
#define	TEV_DID_MRB		54
#define	TEV_DID_MSB		55
#define	TEV_DID_ME		56
#define	TEV_DID_AST		57
#define	TEV_DID_AMC		58
#define	TEV_DID_AML		59
#define	TEV_DID_NE		60
#define	TEV_DID_NMC		61
#define	TEV_DID_NCT		62
#define	TEV_DID_NTL		63
#define	TEV_DID_NH		64
#define	TEV_DID_NA		65
#define	TEV_DID_OPT		66
#define	TEV_DID_OPV		67
#define	TEV_DID_OS		68
#define	TEV_DID_PDA		69
#define	TEV_DID_PDT		70
#define	TEV_DID_PC		71
#define	TEV_DID_PSD		72
#define	TEV_DID_PSG		73
#define	TEV_DID_PF		74
#define	TEV_DID_PRF		75
#define	TEV_DID_RST		76
#define	TEV_DID_RMC		77
#define	TEV_DID_SN		78
#define	TEV_DID_SE		79
#define	TEV_DID_SF		80
#define	TEV_DID_SW		81
#define	TEV_DID_SC		82
#define	TEV_DID_STL		83
#define	TEV_DID_SIB		84
#define	TEV_DID_TID		85
#define	TEV_DID_PT		86
#define	TEV_DID_MT		87
#define	TEV_DID_TF		88
#define	TEV_DID_TN		89
#define	TEV_DID_PID		90
#define	TEV_DID_TT		91
#define	TEV_DID_TW		92
#define	TEV_DID_TIS		93
#define	TEV_DID_TNT		94
#define	TEV_DID_TST		95
#define	TEV_DID_TUS		96
#define	TEV_DID_TUU		97
#define	TEV_DID_TSS		98
#define	TEV_DID_TSU		99
#define	TEV_DID_TES		100
#define	TEV_DID_TA		101
#define	TEV_DID_TR		102
#define	TEV_DID_TS		103
#define	TEV_DID_TU		104
#define	TEV_DID_TGS		105
#define	TEV_DID_TGU		106
#define	TEV_DID_TMW		107
#define	TEV_DID_TM		108
#define	TEV_DID_TRC		109
#define	TEV_DID_TRT		110
#define	TEV_DID_TRX		111
#define	TEV_DID_TRO		112
#define	TEV_DID_TRM		113
#define	TEV_DID_TRB		114
#define	TEV_DID_TRL		115
#define	TEV_DID_VER		116
#define	TEV_DID_VCT		117
#define	TEV_DID_VID		118
#define	TEV_DID_WID		119
#define	TEV_DID_MAX		119


/* Trace Data Identifier Structure */

struct Pvmtevdid
{
	char *did;		/* Semantic Data ID */
	char *desc;		/* Semantic Data Description */
};


/* Trace Event ID Constants */

/************* PLEASE NOTE ******************/
/*											*/
/*	When Adding or Changing, ALWAYS Update:	*/
/*		struct Pvmtevinfo pvmtevinfo[];		*/
/*	in file $PVM_ROOT/src/global.c			*/
/*											*/
/************* PLEASE NOTE ******************/

#define	TEV_FIRST				0
#define	TEV_ADDHOSTS			0
#define	TEV_BARRIER				1
#define	TEV_BCAST				2
#define	TEV_BUFINFO				3
#define	TEV_CONFIG				4
#define	TEV_DELETE				5
#define	TEV_DELHOSTS			6
#define	TEV_EXIT				7
#define	TEV_FREEBUF				8
#define	TEV_GETFDS				9
#define	TEV_GETINST				10
#define	TEV_GETOPT				11
#define	TEV_GETRBUF				12
#define	TEV_GETSBUF				13
#define	TEV_GETTID				14
#define	TEV_GSIZE				15
#define	TEV_HALT				16
#define	TEV_INITSEND			17
#define	TEV_INSERT				18
#define	TEV_JOINGROUP			19
#define	TEV_KILL				20
#define	TEV_LOOKUP				21
#define	TEV_LVGROUP				22
#define	TEV_MCAST				23
#define	TEV_MKBUF				24
#define	TEV_MSTAT				25
#define	TEV_MYTID				26
#define	TEV_NOTIFY				27
#define	TEV_NRECV				28
#define	TEV_PARENT				29
#define	TEV_PERROR				30
#define	TEV_PKBYTE				31
#define	TEV_PKCPLX				32
#define	TEV_PKDCPLX				33
#define	TEV_PKDOUBLE			34
#define	TEV_PKFLOAT				35
#define	TEV_PKINT				36
#define	TEV_PKUINT				37
#define	TEV_PKLONG				38
#define	TEV_PKULONG				39
#define	TEV_PKSHORT				40
#define	TEV_PKUSHORT			41
#define	TEV_PKSTR				42
#define	TEV_PROBE				43
#define	TEV_PSTAT				44
#define	TEV_RECV				45
#define	TEV_RECVF				46
#define	TEV_SEND				47
#define	TEV_SENDSIG				48
#define	TEV_SETOPT				49
#define	TEV_SETRBUF				50
#define	TEV_SETSBUF				51
#define	TEV_SPAWN				52
#define	TEV_START_PVMD			53
#define	TEV_TASKS				54
#define	TEV_TICKLE				55
#define	TEV_TIDTOHOST			56
#define	TEV_TRECV				57
#define	TEV_UPKBYTE				58
#define	TEV_UPKCPLX				59
#define	TEV_UPKDCPLX			60
#define	TEV_UPKDOUBLE			61
#define	TEV_UPKFLOAT			62
#define	TEV_UPKINT				63
#define	TEV_UPKUINT				64
#define	TEV_UPKLONG				65
#define	TEV_UPKULONG			66
#define	TEV_UPKSHORT			67
#define	TEV_UPKUSHORT			68
#define	TEV_UPKSTR				69
#define	TEV_VERSION				70
#define	TEV_REG_HOSTER			71
#define	TEV_REG_RM				72
#define	TEV_REG_TASKER			73
#define	TEV_REG_TRACER			74
#define	TEV_NEWTASK				75
#define	TEV_ENDTASK				76
#define	TEV_SPNTASK				77
#define	TEV_ARCHCODE			78
#define	TEV_CATCHOUT			79
#define	TEV_GETMWID				80
#define	TEV_GETTMASK			81
#define	TEV_HOSTSYNC			82
#define	TEV_PACKF				83
#define	TEV_PRECV				84
#define	TEV_PSEND				85
#define	TEV_REDUCE				86
#define	TEV_SETMWID				87
#define	TEV_SETTMASK			88
#define	TEV_UNPACKF				89
#define	TEV_GATHER				90
#define	TEV_SCATTER				91
#define	TEV_PUTINFO				92
#define	TEV_GETINFO				93
#define	TEV_REMOVE				94
#define	TEV_GETMBOXINFO			95
#define	TEV_NEWCONTEXT			96
#define	TEV_FREECONTEXT			97
#define	TEV_SETCONTEXT			98
#define	TEV_GETCONTEXT			99
#define	TEV_SIBLINGS			100
#define	TEV_GETMINFO			101
#define	TEV_SETMINFO			102
#define	TEV_TIMING				103
#define	TEV_PROFILING			104
#define	TEV_USER_DEFINED		105
#define	TEV_MAX					105

#define	TEV_EVENT_ENTRY			0x4000
#define	TEV_EVENT_EXIT			0x8000


/* Trace Event Info Structure */

struct Pvmtevinfo
{
	char *name;				/* trace event name */
	int desc_status;		/* trace descriptor status */
	struct timeval mark;	/* trace time marker */
	struct timeval total;	/* trace cumulative time */
	int count;				/* trace invocation counter */
};


/* Trace Mask Definitions */

/****************************************************************/
/*																*/
/*	Fix Length Larger Than Necessary to Allow Interoperability	*/
/*	with Different Effective Mask Lengths:						*/
/*																*/
/*		-> for TEV_MAX of 101, Min Length is (101/4 + 2) = 26.	*/
/*			=> bump to 36, sufficient for TEV_MAX up to 139.	*/
/*																*/
/****************************************************************/

#define	TEV_MASK_LENGTH		36


/* Trace Event Mask Kept as Ascii String */

typedef char Pvmtmask[TEV_MASK_LENGTH];


/* Trace Mask Macros */

#define	TEV_MASK_SET( m, k )	( m[ (k) / 4 ] |= ( 1 << ((k) & 3) ) )

#define	TEV_MASK_UNSET( m, k )	( m[ (k) / 4 ] &= ~( 1 << ((k) & 3) ) )

#define	TEV_MASK_CHECK( m, k )	( m[ (k) / 4 ] & ( 1 << ((k) & 3) ) )

#define	TEV_MASK_INIT( m ) \
{ \
	int tev_init_mask_i = TEV_MASK_LENGTH - 1; \
	m[ tev_init_mask_i ] = 0; \
	while ( tev_init_mask_i-- > 0 ) \
		m[ tev_init_mask_i ] = '@'; \
}


/* Tracer Info Structure */

struct Pvmtracer
{
	int trctid;			/* trace dst */
	int trcctx;			/* trace context */
	int trctag;			/* trace message tag */
	int outtid;			/* stdout dst */
	int outctx;			/* stdout context */
	int outtag;			/* stdout message tag */
	int trcbuf;			/* trace buffering */
	int trcopt;			/* trace options */
	Pvmtmask tmask;		/* trace bitmask */
};


#ifdef __ProtoGlarp__
#undef __ProtoGlarp__
#endif
#if defined(__STDC__) || defined(__cplusplus)
#define __ProtoGlarp__(x) x
#else
#define __ProtoGlarp__(x) ()
#endif

#ifdef __cplusplus
extern "C" {
#endif

int pvm_gettmask	__ProtoGlarp__(( int, Pvmtmask ));
int pvm_settmask	__ProtoGlarp__(( int, Pvmtmask ));

#ifdef __cplusplus
}
#endif

#endif	/*_PVMTEV_H_*/

