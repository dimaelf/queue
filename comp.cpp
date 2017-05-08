/***********************************************************************
 * Module:  comp.cpp
 * Author:  Samsung
 * Modified: 4 мая 2017 г. 4:55:17
 * Purpose: Implementation of the class comp
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "line.h"
#include "comp.h"

void comp::addel(int n)
{
   scanf("%d%d", &re, &im);
   if (n==1)
   {
       pnext=0;
       return;
   }
   pnext = malloc(sizeof (comp*));
   typenext = 2;
   ((comp*)pnext)->addel(n-1);
}
