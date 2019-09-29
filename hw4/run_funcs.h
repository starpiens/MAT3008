#ifndef HW4_RUN_FUNCS_H
#define HW4_RUN_FUNCS_H

#include "nr.h"

void run_rtbis(float (*f)(float), float x1, float x2, float xacc);
void run_rtflsp(float (*f)(float), float x1, float x2, float xacc);
void run_rtsec(float (*f)(float), float x1, float x2, float xacc);
void run_rtnewt(void (*df)(float, float *, float *), float x1, float x2, float xacc);
void run_rtsafe(void (*df)(float, float *, float *), float x1, float x2, float xacc);

#endif //HW4_RUN_FUNCS_H
