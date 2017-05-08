/***********************************************************************
 * Module:  dfl.h
 * Author:  Samsung
 * Modified: 4 мая 2017 г. 4:54:36
 * Purpose: Declaration of the class dfl
 ***********************************************************************/

#if !defined(__ObjectOrientedModel_1_dfl_h)
#define __ObjectOrientedModel_1_dfl_h

#include "line.h"

class dfl : public lin
{
public:
   void addel(int n);

private:
   double num;


};

#endif
