/***********************************************************************
 * Module:  dfl.cpp
 * Author:  Samsung
 * Modified: 4 мая 2017 г. 4:54:36
 * Purpose: Implementation of the class dfl
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "line.h"
#include "dfl.h"

void dfl::addel(int n)
{
   scanf("%lf", &num);
   if (n==1)
   {
       pnext=0;
       return;
   }
   pnext = malloc(sizeof (dfl*));
   typenext = 1;
   ((dfl*)pnext)->addel(n-1);
}
