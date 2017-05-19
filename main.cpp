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
   void incram();
   void decram();
   int Testconcsep(serv& S);
   void Testser(serv& S);


private:
    int amlines;
    pline* pl;

};

class line
{
public:
   //virtual void addel(int n);
   int serch(serv& S, int n1, int n2);
   void concat(serv& S, int n1, int n2);
   int sep (serv& S, int n);
   void subseq (serv& S, int line, int len, int disp);

protected:
   void* pnext;
   int typenext;

};

class in : public line
{
public:
   void addel(int n);
   void prin();
   int check(void* p);
   void setc1(int n1, int n2, int& t);
   void set7(int n1, double d1, double d2, int re1, int im1, int re2, int im2, int n2, int n3, int& t);

private:
   int num;

};

class dfl : public line
{
public:
   void addel(int n);
   void prin();
   int check(void* p);
   void setc1(double n1, double n2, int& t);
   void set3(double d, int re1, int im1, int re2, int im2, int& t);

private:
   double num;

};

class comp : public line
{
public:
   void addel(int n);
   void prin();
   int check(void* p);
   void setc1(int n1, int n2, int n3, int n4, int& t);

private:
   int re;
   int im;

};


serv::serv()
{
    pl = 0;
    amlines=0;
}

void serv::decram()
{
    amlines--;
}

void serv::incram()
{
    amlines++;
}

pline* serv::getpl()
{
    return pl;
}

int serv::getam()
{
    return amlines;
}


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


void line::concat(serv& S, int n1, int n2)
{
    if ((n1>S.getam())||(n2>S.getam()))
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
    if (n1>n2)
    {
        printf("Error\n");
        return;
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
    S.decram();
}

int line::sep(serv& S, int n)
{
    pline* p = S.getpl();
    for (int i = 0; i<n-1; i++)
    {
        p= p->pnext;
    }
    int t= p->type;
    void* pl=p->plin;
    while (t==((line*)pl)->typenext)
    {
        if (((line*)pl)->pnext==0)
        {
            return 0;
        }
        pl = ((line*)pl)->pnext;
    }
    if (((line*)pl)->pnext==0)
    {
        return 0;
    }
    int newt = ((line*)pl)->typenext;
    while (p->pnext!=0)
    {
        p = p->pnext;
    }
    p->pnext = (pline*)malloc(sizeof(pline));
    p= p->pnext;
    p->type = newt;
    p->pnext = 0;
    p->plin = ((line*)pl)->pnext;
    ((line*)pl)->pnext=((line*)((line*)pl)->pnext)->pnext;
    void* plnew = p->plin;
    ((line*)plnew)->pnext = 0;

    while (((line*)pl)->pnext!=0)
    {
        if (t!=((line*)pl)->typenext)
        {

            ((line*)plnew)->pnext = ((line*)pl)->pnext;
            ((line*)plnew)->typenext = ((line*)pl)->typenext;
            ((line*)pl)->typenext = ((line*)((line*)pl)->pnext)->typenext;
            ((line*)pl)->pnext=((line*)((line*)pl)->pnext)->pnext;
            plnew = ((line*)plnew)->pnext;
            ((line*)plnew)->pnext = 0;
        }
        else
        {
            pl = ((line*)pl)->pnext;
        }
    }
    S.incram();
    ((line*)p)->sep(S, S.getam());
    return 1;
}


int in::check(void* p)
{
    if (num == ((in*)p)->num)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int dfl::check(void* p)
{
    if (num == ((dfl*)p)->num)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int comp::check(void* p)
{
    if ((re == ((comp*)p)->re)&&(im== ((comp*)p)->im))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int line::serch(serv& S, int n1, int n2)
{

    if ((n1>S.getam())||(n2>S.getam()))
    {
        printf("Uncorrect numbers\n");
        return 0;
    }
    pline* p1 = S.getpl();
    pline* p2 = S.getpl();
    for (int i = 0; i< n1; i++)
    {
        p1 = p1->pnext;
    }
    for (int i = 0; i< n2; i++)
    {
        p2 = p2->pnext;
    }
    int t1 = p1->type;
    int t2 = p2->type;
    void* pinitial1 = p1->plin;
    void* pt1 = pinitial1;
    void* pt2 = p2->plin;

    while (1<2)
    {
        while (pt2!=0)
        {
            if (pt1 == 0)
            {
                return 0;
            }
            if (t1==t2)
            {
                if (t1 == 0)
                {
                    if (((in*)pt1)->check(pt2)!=0)
                    {
                        t1  = ((line*)pt1)->typenext;
                        t2 = ((line*)pt2)->typenext;
                        pt1 = ((line*)pt1)->pnext;
                        pt2 = ((line*)pt2)->pnext;
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                if (t1 == 1)
                {
                    if (((dfl*)pt1)->check(pt2)!=0)
                    {
                        t1  = ((line*)pt1)->typenext;
                        t2 = ((line*)pt2)->typenext;
                        pt1 = ((line*)pt1)->pnext;
                        pt2 = ((line*)pt2)->pnext;
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                if (t1 == 2)
                {
                    if (((comp*)pt1)->check(pt2)!=0)
                    {
                        t1  = ((line*)pt1)->typenext;
                        t2 = ((line*)pt2)->typenext;
                        pt1 = ((line*)pt1)->pnext;
                        pt2 = ((line*)pt2)->pnext;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                break;
            }
        }
        if (pt2==0)
        {
            return 1;
        }
        t1 = ((line*)pinitial1)->typenext;
        t2 = p2->type;
        pinitial1 = ((line*)pinitial1)->pnext;
        pt1 = pinitial1;
        pt2 = p2->plin;
    }
}

void line::subseq(serv& S, int lin, int len, int disp)
{
    pline* pl = S.getpl();
    for (int i=0; i< lin-1; i++)
    {
        if (pl->pnext==0)
        {
            printf("Uncorrect number of line\n");
            return;
        }
        pl = pl->pnext;
    }
    void* p = pl->plin;
    int t;
    if (disp<1)
    {
        t=pl->type;
    }
    else
    {
        for (int i = 0; i<disp-1; i++)
        {
            if (((line*)p)->pnext==0)
            {
                printf("Uncorrect displacement\n");
                return;
            }
            p = ((line*)p)->pnext;
        }
        t = ((line*)p)->typenext;
        if (((line*)p)->pnext==0)
        {
            printf("Uncorrect displacement\n");
            return;
        }
        p = ((line*)p)->pnext;
    }

    while (pl->pnext!=0)
    {
        pl= pl->pnext;
    }
    pl->pnext = (pline*)malloc(sizeof(pline));
    pl = pl->pnext;
    pl->pnext = 0;
    pl->type = t;
    void* pnew;
    if (t==0)
    {
        pl->plin = malloc(sizeof(in));
        *((in*)pl->plin) = *((in*)p);
        pnew = pl->plin;
        ((in*)pnew)->pnext = 0;
    }
    else
    {
        if (t==1)
        {
            pl->plin = malloc(sizeof(dfl));
            *((dfl*)pl->plin) = *((dfl*)p);
            pnew = pl->plin;
            ((dfl*)pnew)->pnext = 0;
        }
        else
        {
            if (t==2)
            {
                pl->plin = malloc(sizeof(comp));
                *((comp*)pl->plin) = *((comp*)p);
                pnew = pl->plin;
                ((comp*)pnew)->pnext = 0;
            }
        }
    }
    for (int i = 0; i<len-1; i++)
    {
        if (((line*)p)->pnext==0)
        {
            return;
        }
        ((line*)pnew)->typenext = ((line*)p)->typenext;
        t = ((line*)pnew)->typenext;
        p = ((line*)p)->pnext;
        if (t==0)
        {
            ((in*)pnew)->pnext = malloc(sizeof(in));
            *((in*)((in*)pnew)->pnext) = *((in*)p);
            pnew = ((in*)pnew)->pnext;
            ((in*)pnew)->pnext = 0;
        }
        else
        {
            if (t==1)
            {
                ((dfl*)pnew)->pnext = malloc(sizeof(in));
                *((dfl*)((dfl*)pnew)->pnext) = *((dfl*)p);
                pnew = ((dfl*)pnew)->pnext;
                ((dfl*)pnew)->pnext = 0;
            }
            else
            {
                if (t==2)
                {
                    ((comp*)pnew)->pnext = malloc(sizeof(in));
                    *((comp*)((comp*)pnew)->pnext) = *((comp*)p);
                    pnew = ((comp*)pnew)->pnext;
                    ((comp*)pnew)->pnext = 0;
                }
            }
        }
    }
    S.incram();
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


void in::setc1(int n1, int n2, int& t)
{
    t = 0;
    num = n1;
    typenext = 0;
    pnext = malloc(sizeof(in));
    ((in*)pnext)->pnext = 0;
    ((in*)pnext)->num = n2;
}

void dfl::setc1(double n1, double n2, int& t)
{
    t = 1;
    num = n1;
    typenext = 1;
    pnext = malloc(sizeof(dfl));
    ((dfl*)pnext)->pnext = 0;
    ((dfl*)pnext)->num = n2;
}

void comp::setc1(int n1, int n2, int n3, int n4, int& t)
{
    t = 2;
    re = n1;
    im = n2;
    typenext = 2;
    pnext = malloc(sizeof(comp));
    ((comp*)pnext)->pnext = 0;
    ((comp*)pnext)->re = n3;
    ((comp*)pnext)->im = n4;
}

void in::set7(int n1, double d1, double d2, int re1, int im1, int re2, int im2, int n2, int n3, int& t)
{
    t = 0;
    num = n1;
    pnext = malloc(sizeof(dfl));
    ((dfl*)pnext)->setc1(d1, d2, typenext);
    void* p;
    p = pnext;

    p = ((in*)p)->pnext;

    ((in*)p)->pnext = malloc(sizeof(comp*));

    ((comp*)((in*)p)->pnext)->setc1(re1, im1, re2, im2, (((in*)p)->typenext));

    p = ((in*)p)->pnext;
    p = ((in*)p)->pnext;
    ((in*)p)->pnext = malloc(sizeof(in));
    ((in*)((in*)p)->pnext)->setc1(n2, n3, (((in*)p)->typenext));
}

void dfl::set3(double d, int re1, int im1, int re2, int im2, int& t)
{
    num = d;
    t = 1;
    pnext = malloc(sizeof(comp));
    ((comp*)pnext)->setc1(re1, im1, re2, im2, typenext);
}

void serv::Testser(serv& S)
{
    amlines = 4;
    pl = (pline*)malloc(sizeof(pline));
    pl->pnext = (pline*)malloc(sizeof(pline));
    pl->pnext->pnext = (pline*)malloc(sizeof(pline));
    pl->pnext->pnext->pnext = (pline*)malloc(sizeof(pline));
    pl->pnext->pnext->pnext->pnext=0;
    pl->plin = malloc(sizeof(in));
    ((in*)pl->plin)->set7(1, 2.03, 4.005, 6, 7, 8, 9, 10, 13, pl->type);
    pl->pnext->plin = malloc(sizeof(dfl));
    ((dfl*)pl->pnext->plin)->set3(4.005, 6, 7, 8, 9, pl->pnext->type);
    pl->pnext->pnext->plin = malloc(sizeof(dfl));
    ((dfl*)pl->pnext->pnext->plin)->setc1(2.03, -4.005, pl->pnext->pnext->type);
    pl->pnext->pnext->pnext->plin = malloc(sizeof(in));
    ((in*)pl->pnext->pnext->pnext->plin)->setc1(1, 2, pl->pnext->pnext->pnext->type);
    line L;
    if (L.serch(S, 0, 1)!=1)
        printf("Test 1 for search failed\n");
    else
        printf("Success\n");
    if (L.serch(S, 0, 2)!=0)
        printf("Test 2 for search failed\n");
    else
        printf("Success\n");
    if (L.serch(S, 0, 3)!=0)
        printf("Test 3 for search failed\n");
    else
        printf("Success\n");
    if (L.serch(S, 1, 0)!=0)
        printf("Test 4 for search failed\n");
    else
        printf("Success\n");
    if (L.serch(S, 1, 1)==0)
        printf("Test 5 for search failed\n");
    else
        printf("Success\n");
    ((in*)pl->pnext->pnext->plin)->setc1(10, 13, pl->pnext->pnext->type);
    L.subseq(S, 5, 1, 0);
    if (amlines==4)
    {
        printf("^Uncorrect means success\n");
    }
    else
        printf("Test 1 for subsequences failed\n");
    L.subseq(S, 1, 3, 2);
    if ((L.serch(S, 1, 4)==1)&&((L.serch(S, 4, 1)==1)))
        printf("Success\n");
    else
        printf("Test 2 for subsequence failed\n");
    L.subseq(S, 1, 3, 5);
    if ((L.serch(S, 2, 5)==1)&&((L.serch(S, 2, 5)==1)))
        printf("Success\n");
    else
        printf("Test 3 for subsequence failed\n");
}

int serv::Testconcsep(serv& S)
{
    amlines = 3;
    pl = (pline*)malloc(sizeof(pline));
    pl->pnext = (pline*)malloc(sizeof(pline));
    pl->pnext->pnext = (pline*)malloc(sizeof(pline));
    pl->pnext->pnext->pnext = 0;
    pl->plin = malloc(sizeof(in));
    ((in*)pl->plin)->setc1(1, 2, pl->type);
    pl->pnext->plin = malloc(sizeof(comp));
    ((comp*)pl->pnext->plin)->setc1(3, 4, 5, 6, pl->pnext->type);
    pl->pnext->pnext->plin = malloc(sizeof(dfl));
    ((dfl*)pl->pnext->pnext->plin)->setc1(7.08, 9.1, pl->pnext->pnext->type);
    line L;
    L.concat(S, 1, 2);
    L.concat(S, 1, 2);
    pl->pnext = (pline*)malloc(sizeof(pline));
    pl->pnext->pnext = (pline*)malloc(sizeof(pline));
    pl->pnext->pnext->pnext = (pline*)malloc(sizeof(pline));
    pl->pnext->pnext->pnext->pnext=0;
    amlines=4;
    pl->pnext->plin = malloc(sizeof(in));
    ((in*)pl->pnext->plin)->setc1(1, 2, pl->pnext->type);
    pl->pnext->pnext->plin = malloc(sizeof(comp));
    ((comp*)pl->pnext->pnext->plin)->setc1(3, 4, 5, 6, pl->pnext->pnext->type);
    pl->pnext->pnext->pnext->plin = malloc(sizeof(dfl));
    ((dfl*)pl->pnext->pnext->pnext->plin)->setc1(7.08, 9.1, pl->pnext->pnext->pnext->type);
    L.subseq(S, 1, 2, 0);
    L.subseq(S, 1, 2, 2);
    L.subseq(S, 1, 2, 4);
    int f = 1;
    if ((L.serch(S, 1, 4)!=1)||(L.serch(S, 4, 1)!=1))
    {
        f=0;
    }
    if ((L.serch(S, 2, 5)!=1)||(L.serch(S, 5, 2)!=1))
    {
        f=0;
    }
    if ((L.serch(S, 3, 6)!=1)||(L.serch(S, 6, 3)!=1))
    {
        f=0;
    }
    if (f!=0)
    {
        printf("Success\n");
    }
    else
    {
        printf("Test 1 for concatination failed\n");
    }
    L.concat(S, 2, 3);
    L.concat(S, 2, 3);
    L.concat(S, 1, 6);
    L.concat(S, 1, 1);
    L.concat(S, 2, 2);
    if ((L.serch(S, 0, 1)!=1)||(L.serch(S, 1, 0))!=1)
    {
        printf("Test 2 for concatination failed\n");
    }
    else
    {
        printf("^Error means Success\n");
    }
    L.sep(S, 2);
    f = 1;
    if ((L.serch(S, 1, 2)!=1)||(L.serch(S, 2, 1)!=1))
    {
        f=0;
    }
    if ((L.serch(S, 3, 5)!=1)||(L.serch(S, 5, 3)!=1))
    {
        f=0;
    }
    if ((L.serch(S, 4, 6)!=1)||(L.serch(S, 6, 4)!=1))
    {
        f=0;
    }
    if (f!=0)
    {
        printf("Success\n");
    }
    else
    {
        printf("Test for separation failed\n");
    }
}

int main()
{
    int ch=1;
    int n1, n2;
    line L;
    serv S;
    while (ch!=0)
    {
        printf("0-quit\n1-set line\n2-concatination\n3-separation\n4-get subsequence\n5-search of subsequence\n6-to test\n");
        scanf("%d", &ch);
        if (ch==1)
        {
            S.addline();
            S.printlines();
            continue;
        }
        if (ch==2)
        {
            printf("Enter numbers of concantinating lines\n");
            scanf("%d%d", &n1, &n2);
            L.concat(S, n1, n2);
            S.printlines();
            continue;
        }
        if (ch==3)
        {
            printf("Enter line's number\n");
            scanf("%d", &ch);
            if (ch>S.getam())
            {
                printf("Error\n");
            }
            else
                L.sep(S, ch);
            S.printlines();
            ch=-1;
            continue;
        }
        if (ch==4)
        {
            printf("Enter line's number\n");
            scanf("%d", &ch);
            printf("Enter length of subsequence\n");
            scanf("%d", &n1);
            printf("Enter displacement of subsequence in line\n");
            scanf("%d", &n2);
            L.subseq(S, ch, n1, n2);
            S.printlines();
            ch = -1;
            continue;
        }
        if (ch==5)
        {
            printf("Enter number of line for searching\n");
            scanf("%d", &n2);
            printf("Enter number of line where search will do\n");
            scanf("%d", &n1);
            if (L.serch(S, n1-1, n2-1)==1)
            {
                printf("Has found\n");
            }
            else
            {
                printf("Hasn't found\n");
            }
            S.printlines();
            continue;
        }
        if (ch==6)
        {
            serv ST;
            S.Testser(S);
            ST.Testconcsep(ST);
            return 0;
        }
    }
    return 0;
}
