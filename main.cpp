#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct pline
{
    void* plin;
    int type;
    pline* pnext;
};

class serv
{
public:
   serv();
   void addline();
   void printlines();
   pline* getpl();
   int getam();


private:
    int amlines;
    pline* pl;

};

pline* serv::getpl()
{
    return pl;
}

int serv::getam()
{
    return amlines;
}

class line
{
public:
   //virtual void addel(int n);
   void concat(serv& S);

protected:
   void* pnext;
   int typenext;

};

void line::concat(serv& S)
{
    printf("Enter numbers of concantinating lines\n");
    int n1, n2;
    scanf("%d%d", &n1, &n2);
    if ((n1>S.getam()+1)||(n2>S.getam()))
    {
        printf("Error\n");
        return;
    }
    if (n1==n2)
    {
        return;
    }
    pline* p1;
    pline* p2;
    p1 = S.getpl();
    p2 = S.getpl();
    for (int i = 0; i<n1-1; i++)
    {
        p1 = p1->pnext;
    }
    for (int i = 0; i<n2-1; i++)
    {
        p2 = p2->pnext;
    }
    line* lp;
    lp = (line*)(p1->plin);
    while (lp->pnext!=0)
    {
        lp = (line*)(lp->pnext);
    }
    lp->typenext=p2->type;
    lp->pnext=p2->plin;
    p1 = S.getpl();
    for (int i = 0; i<n2-2; i++)
    {
        p1 = p1->pnext;
    }
    p1->pnext=p2->pnext;
    delete p2;
}

class in : public line
{
public:
   void addel(int n);
   void prin();

private:
   int num;


};

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


class dfl : public line
{
public:
   void addel(int n);
   void prin();

private:
   double num;

};

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

class comp : public line
{
public:
   void addel(int n);
   void prin();

private:
   int re;
   int im;


};

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

serv::serv()
{
    pl = 0;
    amlines=0;
}

void serv::addline()
{
   printf("Add line with int(0), float(1) or complex(2)\n");
   int ch, am;
   scanf("%d", &ch);
   printf("Hom many numbers is it?\n");
   scanf("%d", &am);
   if (am<1)
   {
       return;
   }
   amlines++;
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

void serv::printlines()
{
    pline* p;
    p=pl;
    int i = 1;
    while (p!=0)
    {
        printf("Line %d: ", i);
        if (p->type==0)
        {
            ((in*)(p->plin))->prin();
        }
        else
        {
            if (p->type==1)
            {
                ((dfl*)(p->plin))->prin();
            }
            else
            {
                ((comp*)(p->plin))->prin();
            }
        }
        p = p->pnext;
        i++;
    }
}

void in::prin()
{
    printf("%d ", num);
    if (pnext!=0)
    {
        if (typenext==0)
        {
            ((in*)pnext)->prin();
        }
        else
        {
            if (typenext==1)
            {
                ((dfl*)pnext)->prin();
            }
            else
            {
                ((comp*)pnext)->prin();
            }
        }
    }
    else
    {
        printf("\n");
    }
}

void dfl::prin()
{
    printf("%lf ", num);
    if (pnext!=0)
    {
        if (typenext==0)
        {
            ((in*)pnext)->prin();
        }
        else
        {
            if (typenext==1)
            {
                ((dfl*)pnext)->prin();
            }
            else
            {
                ((comp*)pnext)->prin();
            }
        }
    }
    else
    {
        printf("\n");
    }
}

void comp::prin()
{
    printf("%d+i*(%d) ", re, im);
    if (pnext!=0)
    {
        if (typenext==0)
        {
            ((in*)pnext)->prin();
        }
        else
        {
            if (typenext==1)
            {
                ((dfl*)pnext)->prin();
            }
            else
            {
                ((comp*)pnext)->prin();
            }
        }
    }
    else
    {
        printf("\n");
    }
}
int main()
{
    serv S;
    S.addline();
    S.printlines();
    S.addline();
    S.printlines();
    line L;
    L.concat(S);
    S.printlines();
    S.addline();
    S.printlines();
    L.concat(S);
    S.printlines();
    S.addline();
    S.printlines();
    L.concat(S);
    S.printlines();
    return 0;
}
