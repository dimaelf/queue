/***********************************************************************
 * Module:  in.cpp
 * Author:  Samsung
 * Modified: 4 мая 2017 г. 4:54:07
 * Purpose: Implementation of the class in
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "line.h"
#include "in.h"

////////////////////////////////////////////////////////////////////////
// Name:       in::Operation_1()
// Purpose:    Implementation of in::Operation_1()
// Return:     int
////////////////////////////////////////////////////////////////////////

void in::addel(int n)
{
   scanf("%d", &num);
   if (n==1)
   {
       pnext=0;
       return;
   }
   pnext = malloc(sizeof (in*));
   typenext = 0;
   ((in*)pnext)->addel(n-1);
}
