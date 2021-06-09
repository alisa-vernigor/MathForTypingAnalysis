#pragma once

#ifndef FUNCTION_H
#define FUNCTION_H

#include "FunctionModuleBase.h"
#include "InstructionLevels.h"
#include "MathFunction.h"
#include "vectorclass/vectorclass.h"
#include "vectorclass/vectormath_exp.h"

#include <vector>

namespace NSMathModule {
namespace NSFunctions {
namespace NSFunctionsDetail {


inline double find_sum(double arg) {
    return arg;
}

inline double find_sum(Vec2d arg) {
    return arg[0] + arg[1];
}

inline double find_sum(Vec4d arg) {
    return arg[0] + arg[1] + arg[3] + arg[4];
}
}


using CDensity0Base =
    NSMath::FunctionModuleBase<double(const std::vector<double>&, const double),
                       NSSimd::CInstrLevel::AVX2, NSSimd::CInstrLevel::AVX, NSSimd::CInstrLevel::SSE>;


class CDensity0 : public CDensity0Base {
    using CBase = CDensity0Base;

public:
    CDensity0(int instruction_level);

    template<typename T>
    static double find_derivative_0(T mean, double arg) {
      T deviation = 1.25 * sqrt(mean);
      T one_over_div = 1. / deviation;
      T arg_minus_mean = arg - mean;

      return NSFunctionsDetail::find_sum(exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
                 one_over_div) *
             one_over_div * one_over_sqrt_two_pi);
    }

private:
    static double compute0(const std::vector<double>& means, double arg);
    static double compute0_SSE2(const std::vector<double>& means, double arg);
    static double compute0_AVX(const std::vector<double>& means, double arg);
    static double compute0_AVX2(const std::vector<double>& means, double arg);

    static constexpr const double one_over_sqrt_two_pi = 0.398942280401432702863218082712;
};



using CDensity1Base =
NSMath::FunctionModuleBase<double(const std::vector<double>&, double),
                   NSSimd::CInstrLevel::AVX2, NSSimd::CInstrLevel::AVX, NSSimd::CInstrLevel::SSE>;

class CDensity1 : public CDensity1Base {
    using CBase = CDensity1Base;

public:
    CDensity1(int instruction_level);

    template<typename T>
    static double find_derivative_1(T mean, double arg) {
      T deviation = 1.25 * sqrt(mean);
      T one_over_div = 1. / deviation;
      T arg_minus_mean = arg - mean;

      return NSFunctionsDetail::find_sum(-exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
                  one_over_div) *
             one_over_sqrt_two_pi * one_over_div * one_over_div * one_over_div *
             arg_minus_mean);
    }

private:
    static double compute1(const std::vector<double>& means, double arg);
    static double compute1_AVX(const std::vector<double>& means, double arg);
    static double compute1_SSE2(const std::vector<double>& means, double arg);
    static double compute1_AVX2(const std::vector<double>& means, double arg);

    static constexpr const double one_over_sqrt_two_pi = 0.398942280401432702863218082712;
};



using CDensity2Base =
NSMath::FunctionModuleBase<double(const std::vector<double>&, double),
                   NSSimd::CInstrLevel::AVX2, NSSimd::CInstrLevel::AVX, NSSimd::CInstrLevel::SSE>;

class CDensity2 : public CDensity0Base {
    using CBase = CDensity0Base;

public:
    CDensity2(int instruction_level);

    template<typename T>
    static double find_derivative_2(T mean, double arg) {
      T deviation = 1.25 * sqrt(mean);
      T one_over_div = 1. / deviation;
      T arg_minus_mean = arg - mean;

      return NSFunctionsDetail::find_sum(exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
                 one_over_div) *
             one_over_sqrt_two_pi * one_over_div * one_over_div * one_over_div *
             (1. - arg_minus_mean * arg_minus_mean * one_over_div * one_over_div));
    }

private:
    static double compute2(const std::vector<double>& means, double arg);
    static double compute2_AVX(const std::vector<double>& means, double arg);
    static double compute2_SSE2(const std::vector<double>& means, double arg);
    static double compute2_AVX2(const std::vector<double>& means, double arg);

    static constexpr const double one_over_sqrt_two_pi = 0.398942280401432702863218082712;
};

class CDensity  {
public:
    CDensity(int instruction_level);

    double compute0(const std::vector<double>& means, double arg);
    double compute1(const std::vector<double>& means, double arg);
    double compute2(const std::vector<double>& means, double arg);

private:
    CDensity0 d0_;
    CDensity1 d1_;
    CDensity2 d2_;
};
}
}

#endif // FUNCTION_H
