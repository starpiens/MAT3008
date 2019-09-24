//
// Created by 김지훈 on 2019/09/23.
//

#ifndef HW3_RUN_FUNCS_H
#define HW3_RUN_FUNCS_H

void run_type1(float (*method)(float (*func)(float), float, float, float),
               float (*func)(float),
               float *xb1,
               float *xb2,
               int num_roots,
               float xacc);

void run_type2(float (*method)(void (*func)(float, float *, float *), float, float, float),
               void (*func)(float, float *, float *),
               float *xb1,
               float *xb2,
               int num_roots,
               float xacc);

#endif //HW3_RUN_FUNCS_H
