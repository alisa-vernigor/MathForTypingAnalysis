#ifndef FUNCTION_H
#define FUNCTION_H

#include "FunctionModuleBase.h"
#include "InstructionLevels.h"
#include "MathFunction.h"

#include <vector>

using CFindDensity0Base =
    NSMath::FunctionModuleBase<void(const std::vector<double>&,
                            double&),
                       NSSimd::CInstrLevel::AVX2, NSSimd::CInstrLevel::SSE>;

class FindDensity0 : public CFindDensity0Base {
    using CBase = CFindDensity0Base;

public:
    FindDensity0(int instruction_level);

    template<typename T>
    static void find_density_0(const std::vector<double>& means, double& arg) {
      T result = 0;
      for (T mean : means)
        result += find_derivative_0(mean, arg);
      result /= static_cast<double>(means.size());
      arg = result;
    }

    template<typename T>
    static T find_derivative_0(T mean, double arg) {
      T deviation = 1.25 * sqrt(mean);
      T one_over_div = 1. / deviation;
      T arg_minus_mean = arg - mean;

      return exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
                 one_over_div) *
             one_over_div * one_over_sqrt_two_pi;
    }

private:
    static constexpr const double one_over_sqrt_two_pi = 0.398942280401432702863218082712;
};

using CFindDensity1Base =
    NSMath::FunctionModuleBase<void(const std::vector<double>&,
                            double&),
                       NSSimd::CInstrLevel::AVX2, NSSimd::CInstrLevel::SSE>;

class FindDensity1 : public CFindDensity1Base {
    using CBase = CFindDensity1Base;

public:
    FindDensity1(int instruction_level);



    template<typename T>
    static void find_density_1(const std::vector<double>& means, double& arg) {
      T result = 0;
      for (T mean : means)
        result += find_derivative_1(mean, arg);
      result /= static_cast<double>(means.size());
      arg = result;
    }

    template<typename T>
    static T find_derivative_1(T mean, double arg) {
      T deviation = 1.25 * sqrt(mean);
      T one_over_div = 1. / deviation;
      T arg_minus_mean = arg - mean;

      return -exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
                  one_over_div) *
             one_over_sqrt_two_pi * one_over_div * one_over_div * one_over_div *
             arg_minus_mean;
    }

private:
    static constexpr const double one_over_sqrt_two_pi = 0.398942280401432702863218082712;
};

using CFindDensity2Base =
    NSMath::FunctionModuleBase<void(const std::vector<double>&,
                            double&),
                       NSSimd::CInstrLevel::AVX2, NSSimd::CInstrLevel::SSE>;

class FindDensity2 : public CFindDensity0Base {
    using CBase = CFindDensity0Base;

public:
    FindDensity2(int instruction_level);

    template<typename T>
    static void find_density_2(const std::vector<double>& means, double& arg) {
      T result = 0;
      for (T mean : means)
        result += find_derivative_2<T>(mean, arg);
      result /= static_cast<double>(means.size());
      arg = result;
    }

    template<typename T>
    static T find_derivative_2(T mean, double arg) {
      T deviation = 1.25 * sqrt(mean);
      T one_over_div = 1. / deviation;
      T arg_minus_mean = arg - mean;

      return exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
                 one_over_div) *
             one_over_sqrt_two_pi * one_over_div * one_over_div * one_over_div *
             (1. - arg_minus_mean * arg_minus_mean * one_over_div * one_over_div);
    }

private:
    static constexpr const double one_over_sqrt_two_pi = 0.398942280401432702863218082712;
};

class Function  {
public:
    Function(int instruction_level);

private:
    FindDensity0 fd0_;
    FindDensity1 fd1_;
    FindDensity2 fd2_;
};

static constexpr const double one_over_sqrt_two_pi = 0.398942280401432702863218082712;

template<typename T>
T find_derivative_0T(T mean, double arg) {
  T deviation = 1.25 * sqrt(mean);
  T one_over_div = 1. / deviation;
  T arg_minus_mean = arg - mean;

  return exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
             one_over_div) *
         one_over_div * one_over_sqrt_two_pi;
}

template<typename T>
T find_derivative_1T(T mean, double arg) {
  T deviation = 1.25 * sqrt(mean);
  T one_over_div = 1. / deviation;
  T arg_minus_mean = arg - mean;

  return -exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
              one_over_div) *
         one_over_sqrt_two_pi * one_over_div * one_over_div * one_over_div *
         arg_minus_mean;
}

template<typename T>
T find_derivative_2T(T mean, double arg) {
  T deviation = 1.25 * sqrt(mean);
  T one_over_div = 1. / deviation;
  T arg_minus_mean = arg - mean;

  return exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
             one_over_div) *
         one_over_sqrt_two_pi * one_over_div * one_over_div * one_over_div *
         (1. - arg_minus_mean * arg_minus_mean * one_over_div * one_over_div);
}

#endif // FUNCTION_H
