#include "s21_math.h"

// Arithmetic funtions

int s21_abs(int x) {
    return x < 0 ? -x : x;
}

long double s21_fabs(double x) {
    return x < 0 ? -x : x;
}

// Auxilary functions

long double s21_floor(double x) {
    long double answer = x;
    if (!s21_isinf(x) && !s21_isnan(x)) {
        answer = s21_trunc(x);
        if (x < 0 && x != (int)x) {
            answer -= 1;
        }
    }
    return answer;
}

long double s21_ceil(double x) {
    double res = x;
    int temp = res;
    if (x == S21_INF || x == -S21_INF)
        res = x;
    else if (x != x)
        res = S21_NAN;
    else if (temp == res)
        res = temp;
    else if (res < 0)
        res = temp;
    else
        res = temp + 1;
    return res;
}

long double s21_fmod(double x, double y) {
    long double i = s21_trunc(x/y);
    long double res = 0;
    if (s21_isinf(y) && s21_isfinite(x))
        res = x;
    else
        res =  x - i * y;
    return res;
}

long double s21_sin(double x) {
    if (!s21_isfinite(x))
        return S21_NAN;
    x =  s21_fmod(x, S21_2PI);
    return chebyshev_sin(x/S21_2PI);
}

long double s21_cos(double x) {
    if (!s21_isfinite(x))
        return S21_NAN;
    return s21_sin(S21_PI_2 - x);
}

long double s21_tan(double x) {
    if (!s21_isfinite(x) || s21_isnan(x)) return S21_NAN;
    return s21_sin(x) / s21_cos(x);
}

long double s21_acos(double x) {
    if (-1 > x || x > 1 || !s21_isfinite(x))
        return S21_NAN;
    else if (x < 0)
        return S21_PI - cordic_rotation_to0(s21_sqrt(1 - x*x), -x);
    return cordic_rotation_to0(s21_sqrt(1 - x*x), x);
}

long double s21_asin(double x) {
    if (-1 > x || x > 1 || !s21_isfinite(x))
        return S21_NAN;
    return cordic_rotation_to0(x, s21_sqrt(1 - x*x));
}

long double s21_atan(double x) {
    long double s21_atan = 0;
    if (s21_isnan(x)) return S21_NAN;
    if (x == S21_INF || x == -S21_INF) {
        s21_atan = x < 0 ? -S21_PI / 2 : S21_PI / 2;
    } else if (-1. < x && x < 1.) {
        for (register int i = 0; i < 500; i++) {
            s21_atan += ((s21_pow(-1, i) * s21_pow(x, 1 + (2 * i))) / (1 + (2 * i)));
        }
    } else {
        for (register int i = 0; i < 900; i++) {
            s21_atan += ((s21_pow(-1, i) * s21_pow(x, -1 - (2 * i))) / (1 + (2 * i)));
        }
        s21_atan = S21_PI * s21_sqrt(x * x) / (2 * x) - s21_atan;
    }
    return s21_atan;
}

long double s21_pow(double base, double exps) {
    long double n = base;
    long double res = 0;
    if ((base == 0) && (s21_isnan(exps))) {
        return S21_NAN;
    } else if ((base == 0) && (exps < 0)) {
        return S21_INF;
    } else if ((base == S21_INF) && (exps < 0)) {
        return 0;
    } else if ((base == -1) && (exps == -S21_INF)) {
        return 1;
    }
    if (exps == 0) {
        res = 1;
    } else {
        if (base == 0) {
            res = 0;
        } else {
            if (n < 0) {
                res = s21_exp(exps * s21_log(-n));
                if (s21_fmod(exps, 2) != 0) {
                    res = res * -1;
                }
            } else {
                res = s21_exp(exps * s21_log(n));
            }
        }
    }
    return res;
}

long double s21_exp(double x) {
    long double result = 1;
    long double temp = 1;
    long double i = 1;
    int flag = 0;
    if (x < 0) {
        x *= -1;
        flag = 1;
    }
    while (s21_fabs(result) > S21_EPS) {
        result = result * (x / i);
        i = i + 1;
        temp = temp + result;
        if (temp > MAX_LONG_DOUBLE) {
            temp = S21_INF;
            break;
        }
    }
     if (flag == 1) {
        if (temp > MAX_LONG_DOUBLE) temp = 0;
        else
            temp = 1./temp;
    }
    return temp > MAX_LONG_DOUBLE ? S21_INF : temp;
}

long double s21_sqrt(double x) {
    if (x < 0)
        return S21_NAN;
    long double xn = x/2;
    while (s21_fabs(x - xn*xn) > 1e-18 && s21_isfinite(x))
        xn = (xn + x/xn)*0.5;
    return xn;
}

long double s21_log(double x) {
    int ex_pow = 0;
    long double res = 0;
    long double result = 0, compare = result;
    if ((x < 0) || (s21_isnan(x))) {
        res = S21_NAN;
    } else if (x == 0) {
        res = -S21_INF;
    } else if ((s21_isinf(x))) {
        return S21_INF;
    }
    if (res == 0) {
        for (; x >= S21_E; x /= S21_E, ex_pow++) continue;

        for (int i = 0; i < 100; i++) {
            compare = result;
            result = compare + 2 * (x - s21_exp(compare)) / (x + s21_exp(compare));
        }
        res = result + ex_pow;
    }
    return res;
}

long double s21_trunc(double x) {
    long double res = 0;
    union flt {
        long double flt;
        int64_t byte8[OCTALC];
    } d;
    d.flt = x;
    short exp, ofs;
    exp = (d.byte8[OCTALC - 1] & EXPBITS) - 16383;
    ofs = MANBITC - exp;
    if (exp < 0) {
        res = 0;
    } else {
        for (int l = 0; l < OCTALC && ofs > 0; l++)
            for (int b = 0; b < 64 && (b + l*64) < ofs; b++)
                d.byte8[l] &= ~((int64_t)1 << b);
        res = d.flt;
    }
    return res;
}

int s21_isfinite(long double x) {
    return x == x && x < S21_INF && x > -S21_INF;
}

int s21_isinf(long double x) {
    return x == S21_INF || x == -S21_INF;
}

int s21_isnan(long double x) {
    return !(x == x);
}

// Trigonometric functions
long double chebyshev_sin(long double x) {
    long double bn, bn_1 = 0, bn_2 = 0;
    for (int i = 39; i > 0; i--) {
        long double t = i%2 ? c_sin[i/2] : 0;
        bn = t + 2.0*x*bn_1 - bn_2;
        bn_2 = bn_1;
        bn_1 = bn;
    }
    bn = 2.0*x*bn_1 - bn_2;
    return (bn - bn_2)/2.0l;
}

long double cordic_rotation_to0(long double sin, long double cos) {
    int n = 63;
    long double u[2] = {cos, sin};
    long double alpha = 0, s;
    for (int i = 0; i < n; alpha += s*tangent_angles[i], i++) {
        s = (0 > u[1]) - (0 < u[1]);
        long double v[2];
        v[0] = u[0] - s*s21_pow(2, -i)*u[1];
        v[1] = s*s21_pow(2, -i)*u[0] + u[1];
        u[0] = v[0];
        u[1] = v[1];
    }
    return -alpha;
}
