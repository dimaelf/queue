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


private:
    int amlines;
    pline* pl;

};



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

class line
{
public:
   //virtual void addel(int n);
   int serch(serv& S, int n1, int n2);
   void concat(serv& S, int n1, int n2);
   void sep (serv& S, int n);
   void subseq (serv& S, int line, int len, int disp);

protected:
   void* pnext;
   int typenext;

};

void line::concat(serv& S, int n1, int n2)
{
    if ((n1>S.getam()+1)||(n2>S.getam()+1))
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

        void* pt;
        pt = p1->plin;
        p1->plin = p2->plin;
        p2->plin = pt;
        int temp;
        temp = p1->type;
        p1->type = p2->type;
        p2->type = temp;
        temp = n1;
        n1 = n2;
        n2 = temp;
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

void line::sep(serv& S, int n)
{
    pline* p = S.getpl();
    for (int i = 0; i<n-1; i++) //дошли до разделяемой очереди
    {
        p= p->pnext;
    }
    int t= p->type;  //запомнили тип первого элемента
    void* pl=p->plin;  //для работы в очереди
    while (t==((line*)pl)->typenext)  //ищем другой тип
    {
        if (((line*)pl)->pnext==0)   //проверяем, не дошли ли до конца
        {
            return;
        }
        pl = ((line*)pl)->pnext;
    }
    if (((line*)pl)->pnext==0)   //проверяем, не дошли ли до конца
    {
        return;
    }
    int newt = ((line*)pl)->typenext;   //запомнили новый тип
    while (p->pnext!=0)    //бежим в конец
    {
        p = p->pnext;
    }
    p->pnext = (pline*)malloc(sizeof(pline));  //добавляем новую очередь
    p= p->pnext; //работаем с последней
    p->type = newt; //устанавливаем нужный тип первого элемента
    p->pnext = 0; //замыкаем
    p->plin = ((line*)pl)->pnext; //вставляем первый элемент
    ((line*)pl)->pnext=((line*)((line*)pl)->pnext)->pnext;  //чистим начало
    //((line*)pl)->typenext = ((line*)((line*)pl)->pnext)->typenext;
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
}


class in : public line
{
public:
   void addel(int n);
   void prin();
   int check(void* p);

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

class dfl : public line
{
public:
   void addel(int n);
   void prin();
   int check(void* p);

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

class comp : public line
{
public:
   void addel(int n);
   void prin();
   int check(void* p);

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
int main()
{
    int ch=1;
    int n1, n2;
    line L;
    serv S;
    while (ch!=0)
    {
        printf("0-quit\n1-set line\n2-concatination\n3-separation\n4-get subsequence\n5-search of subsequence\n");
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
    }
    return 0;
}
