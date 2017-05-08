/***********************************************************************
 * Module:  comp.h
 * Author:  Samsung
 * Modified: 4 мая 2017 г. 4:55:17
 * Purpose: Declaration of the class comp
 ***********************************************************************/

#if !defined(__ObjectOrientedModel_1_comp_h)
#define __ObjectOrientedModel_1_comp_h

#include "line.h"

class comp : public lin
{
public:
   void addel(int n);

private:
   int re;
   int im;


};

#endif
