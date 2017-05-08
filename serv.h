/***********************************************************************
 * Module:  line.h
 * Author:  Samsung
 * Modified: 4 мая 2017 г. 4:48:40
 * Purpose: Declaration of the class line
 ***********************************************************************/

#if !defined(__ObjectOrientedModel_1_line_h)
#define __ObjectOrientedModel_1_line_h

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


private:
    //int amlines;
    pline* pl;

};

#endif
