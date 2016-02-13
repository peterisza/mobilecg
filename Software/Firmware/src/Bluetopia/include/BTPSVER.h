/*****< btpsver.h >************************************************************/
/*                                                                            */
/* Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/     */
/* ALL RIGHTS RESERVED.                                                       */
/*                                                                            */
/*  BTPSVER - Texas Instruments Bluetooth Protocol Stack Version Information. */
/*                                                                            */
/*  Author:  Ram Malovany                                                     */
/*                                                                            */
/*** MODIFICATION HISTORY *****************************************************/
/*                                                                            */
/*   dd/mm/yy  F. Lastname    Description of Modification                     */
/*   --------  -----------    ------------------------------------------------*/
/*   12/09/14  R. Malovany    Initial creation.                               */
/*   03/05/15  D. Horowitz    Delete platforms defines and macros		 	  */
/******************************************************************************/
#ifndef __BTPSVER_H__
#define __BTPSVER_H__


/* Bluetooth Protocol Stack Core Support .                      */
#define BTPS_VERSION_MAJOR_CORE_SUPPORT                         4

/* Bluetooth Protocol Stack Core Support .                      */
#define BTPS_VERSION_MINOR_CORE_SUPPORT                         0


 /* Bluetooth Protocol Stack Major Version Release Numbers.     */
#ifndef BTPS_VERSION_MAJOR_VERSION_NUMBER
    #define BTPS_VERSION_MAJOR_VERSION_NUMBER                   2
#endif

/* Bluetooth Protocol Stack Minor Version Release Numbers.      */
#ifndef BTPS_VERSION_MINOR_VERSION_NUMBER
    #define BTPS_VERSION_MINOR_VERSION_NUMBER                   1
#endif




   /* Constants used to convert numeric constants to string constants   */
   /* (used in MACRO's below).                                          */
#define BTPS_VERSION_NUMBER_TO_STRING(_x)                   #_x
#define BTPS_VERSION_CONSTANT_TO_STRING(_y)                 BTPS_VERSION_NUMBER_TO_STRING(_y)

   /* Bluetooth Protocol Stack Constant Version String of the form      */
   /*    "a.b.c.d"                                                      */
   /* where:                                                            */
   /*    a - BTPS_VERSION_MAJOR_CORE_SUPPORT                            */
   /*    b - BTPS_VERSION_MINOR_CORE_SUPPORT                            */
   /*    c - BTPS_VERSION_MAJOR_VERSION_NUMBER                          */
   /*    d - BTPS_VERSION_MINOR_VERSION_NUMBER                          */


#define BTPS_VERSION_VERSION_STRING                         BTPS_VERSION_CONSTANT_TO_STRING(BTPS_VERSION_MAJOR_CORE_SUPPORT) "." BTPS_VERSION_CONSTANT_TO_STRING(BTPS_VERSION_MINOR_CORE_SUPPORT) "." BTPS_VERSION_CONSTANT_TO_STRING(BTPS_VERSION_MAJOR_VERSION_NUMBER) "." BTPS_VERSION_CONSTANT_TO_STRING(BTPS_VERSION_MINOR_VERSION_NUMBER)



   /* File/Product/Company Name Copyrights and Descriptions.            */
#define BTPS_VERSION_PRODUCT_NAME_STRING                    "TI's Bluetooth Protocol Stack"

#define BTPS_VERSION_COMPANY_NAME_STRING                    "Texas Instruments"

#define BTPS_VERSION_COPYRIGHT_STRING                       "Copyright (C) 2014 Texas Instruments"

#endif
