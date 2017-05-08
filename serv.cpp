/***********************************************************************
 * Module:  line.cpp
 * Author:  Samsung
 * Modified: 4 мая 2017 г. 4:48:40
 * Purpose: Implementation of the class line
 ***********************************************************************/

#include "serv.h"
#include "in.h"
#include "dfl.h"
#include "comp.h"


serv::serv()
{
    pl = 0;
}

int serv::addline()
{
   printf("Add line with int(0), float(1) or complex(2)\n");
   int ch, am;
   scanf("%d", &ch);
   printf("Hom many numbers is it?");
   scanf("%d", &am);
   if (am<1)
   {
       return;
   }
   pline* p;
   if (pl ==0)
   {
       pl=(pline*)malloc(sizeof(pline));
       p = pl;
   }
   else
   {
       p = pl;
       while (p->pnext != 0)
       {
           p = p->pnext;
       }
       p->pnext = (pline*)malloc(sizeof(pline));
       p=p->pnext;
   }
    p->pnext=0;
    printf("Enqueue elemnts\n");
    if (ch==0)
    {
        p->type = 0;
        p->plin = malloc(sizeof(in));
        ((in*)(p->plin))->addel(am);
        return;
    }
    if (ch==1)
    {
        p->type = 1;
        p->plin = malloc(sizeof(dfl));
        ((dfl*)(p->plin))->addel(am);
        return;
    }
    if (ch==2)
    {
        p->type = 2;
        p->plin = malloc(sizeof(comp));
        ((comp*)(p->plin))->addel(am);
    }
}

