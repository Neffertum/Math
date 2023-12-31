#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define S21_INF 1.0/0.0
#define S21_NAN 0.0/0.0

#define S21_PI   3.1415926535897931159l
#define S21_PI_2 1.5707963267948966l
#define S21_2PI  6.283185307179586l
#define S21_E    2.71828182845904523l
#define S21_LN2  0.69314718055994530l
#define S21_LN10 2.3025850929940456l
#define S21_EPS  1e-99l

#define MAX_LONG_DOUBLE 1.79769313486231571e+308


#define OCTALC (int)(sizeof(long double)/sizeof(int64_t))
#define EXPBITS 0x7FFF
#define MANBITC 63

static long double c_sin[] = {
        -0.42476506015273822865,
        -0.058224392078514572072,
        0.74564931593694056499,
        -0.31504226022478564438,
        0.058247768279542445596,
        -0.0062956504847546091678,
        0.00045277117470981463257,
        -2.3376886594574810396e-05,
        9.1161719852743175551e-07,
        -2.7852910787037387064e-08,
        6.8556995117086238587e-10,
        -1.3895858880252567668e-11,
        2.3609810458726357887e-13,
        -3.4124466240223290358e-15,
        4.248069303240149625e-17,
        -4.6033425716743938346e-19,
        4.3822134883976752157e-21,
        -3.6943087026160027476e-23,
        2.7775492482464429791e-25,
        -1.8741618426444227021e-27
    };

static long double tangent_angles[] = {
        S21_PI_2/2.0l,
        0.4636476090008061162,
        0.24497866312686415417,
        0.12435499454676143503,
        0.062418809995957348475,
        0.031239833430268276253,
        0.015623728620476830803,
        0.0078123410601011112965,
        0.0039062301319669718277,
        0.0019531225164788186852,
        0.00097656218955931943043,
        0.00048828121119489827547,
        0.00024414062014936176402,
        0.00012207031189367020424,
        6.1035156174208775022e-05,
        3.0517578115526096862e-05,
        1.5258789061315762107e-05,
        7.6293945311019702635e-06,
        3.814697265606496283e-06,
        1.9073486328101870354e-06,
        9.5367431640596087944e-07,
        4.7683715820308885994e-07,
        2.384185791015579825e-07,
        1.1920928955078068531e-07,
        5.9604644775390554415e-08,
        2.9802322387695303677e-08,
        1.4901161193847655147e-08,
        7.4505805969238279873e-09,
        3.7252902984619140453e-09,
        1.8626451492309570291e-09,
        9.3132257461547851537e-10,
        4.6566128730773925779e-10,
        2.3283064365386962891e-10,
        1.1641532182693481445e-10,
        5.8207660913467407227e-11,
        2.9103830456733703613e-11,
        1.4551915228366851807e-11,
        7.2759576141834259033e-12,
        3.6379788070917129517e-12,
        1.8189894035458564758e-12,
        9.0949470177292823792e-13,
        4.5474735088646411896e-13,
        2.2737367544323205948e-13,
        1.1368683772161602974e-13,
        5.684341886080801487e-14,
        2.8421709430404007435e-14,
        1.4210854715202003717e-14,
        7.1054273576010018587e-15,
        3.5527136788005009294e-15,
        1.7763568394002504647e-15,
        8.8817841970012523234e-16,
        4.4408920985006261617e-16,
        2.2204460492503130808e-16,
        1.1102230246251565404e-16,
        5.5511151231257827021e-17,
        2.7755575615628913511e-17,
        1.3877787807814456755e-17,
        6.9388939039072283776e-18,
        3.4694469519536141888e-18,
        1.7347234759768070944e-18,
        8.6736173798840354721e-19,
        4.336808689942017736e-19,
        2.168404344971008868e-19
};

/**
 * Возвращает модуль целочисленного значения
 */
int s21_abs(int x);
long double s21_fabs(double x);

long double s21_floor(double x);
long double s21_ceil(double x);
long double s21_trunc(double x);
long double s21_fmod(double x, double y);

long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);

/**
 * Возвращает синус угла, переданного в радианах
 */
long double s21_acos(double x);

/**
 * Возвращает косинус угла, переданного в радианах
 */
long double s21_asin(double x);

/**
 * Возвращает тангенс угла, переданного в радианах
 */
long double s21_atan(double x);

/**
 * Возвращает арккосинус
 */
long double s21_pow(double base, double exp);

/**
 * Возвращает арксинус
 */
long double s21_exp(double x);
long double s21_sqrt(double x);

/**
 * Возвращает арктангенс
 */
long double s21_log(double x);

// additional functions
// long double pow2i(double exp);
// long double powi(double base, double exp);
int s21_isfinite(long double x);
int s21_isinf(long double x);
int s21_isnan(long double x);
long double chebyshev_sin(long double x);
long double cordic_rotation_to0(long double sin, long double cos);
long double pade_exp(long double x);

#endif  // SRC_S21_MATH_H_
