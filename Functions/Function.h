#pragma once

#ifndef FUNCTION_H
#define FUNCTION_H

#include "FunctionModuleBase.h"
#include "InstructionLevels.h"
#include "MathFunction.h"
#include "vectorclass/vectorclass.h"
#include "vectorclass/vectormath_exp.h"

#include <vector>

// Helping function
static double find_sum(double arg) {
    return arg;
}

static double find_sum(Vec2d arg) {
    return arg[0] + arg[1];
}

static double find_sum(Vec4d arg) {
    return arg[0] + arg[1] + arg[3] + arg[4];
}

// FindDensity0
namespace MathModule {
namespace Functions {

using CFindDensity0Base =
    NSMath::FunctionModuleBase<void(const std::vector<double>&,
                            const double, double*),
                       NSSimd::CInstrLevel::AVX, NSSimd::CInstrLevel::SSE>;


class FindDensity0 : public CFindDensity0Base {
    using CBase = CFindDensity0Base;

public:
    FindDensity0(int instruction_level);

    static void find_density_0(const std::vector<double>& means, const double arg,
                               double* result) {
      double tmp_result = 0;
      for (double mean : means) {
        tmp_result += find_derivative_0(mean, arg);
      }
      *result = tmp_result / static_cast<double>(means.size());
    }

    static void find_density_0_SSE(const std::vector<double>& means, const double arg,
                               double* result) {
      double tmp_result = 0;
      size_t regular_part = means.size() & static_cast<size_t>(-2);

      for (size_t index = 0; index < regular_part; index += 2) {
        Vec2d means_block(means[index], means[index + 1]);
        tmp_result += find_derivative_0(means_block, arg);
      }

      size_t remainder_size = means.size() - regular_part;
      if (remainder_size != 0) {
        double mean = means[regular_part];
        tmp_result += find_derivative_0(mean, arg);
      }

      *result = tmp_result / static_cast<double>(means.size());
    }

    static void find_density_0_AVX(const std::vector<double>& means, const double arg,
                               double* result) {
      double tmp_result = 0;
      size_t regular_part = means.size() & static_cast<size_t>(-4);

      for (size_t index = 0; index < regular_part; index += 4) {
        Vec4d means_block(means[index], means[index + 1], means[index + 2],
                means[index + 3]);
        tmp_result += find_derivative_0(means_block, arg);
      }

      size_t remainder_size = means.size() - regular_part;
      if (remainder_size != 0) {
            if (remainder_size == 2) {
                Vec2d means_block(means[regular_part], means[regular_part + 1]);
                tmp_result += find_derivative_0(means_block, arg);
            } else if (remainder_size == 1) {
                double mean = means[regular_part];
                tmp_result += find_derivative_0(mean, arg);
            } else {
                Vec2d means_block(means[regular_part], means[regular_part + 1]);
                tmp_result += find_derivative_0(means_block, arg);
                double mean = means[regular_part + 2];
                tmp_result += find_derivative_0(mean, arg);
            }
       }
      *result = tmp_result / static_cast<double>(means.size());
    }

    template<typename T>
    static double find_derivative_0(T mean, double arg) {
      T deviation = 1.25 * sqrt(mean);
      T one_over_div = 1. / deviation;
      T arg_minus_mean = arg - mean;

      return find_sum(exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
                 one_over_div) *
             one_over_div * one_over_sqrt_two_pi);
    }

private:
    static constexpr const double one_over_sqrt_two_pi = 0.398942280401432702863218082712;
};





// FindDensity1
using CFindDensity1Base =
NSMath::FunctionModuleBase<void(const std::vector<double>&,
                        const double, double*),
                   NSSimd::CInstrLevel::AVX, NSSimd::CInstrLevel::SSE>;

class FindDensity1 : public CFindDensity1Base {
    using CBase = CFindDensity1Base;

public:
    FindDensity1(int instruction_level);

    static void find_density_1(const std::vector<double>& means, const double arg,
                               double* result) {
      double tmp_result = 0;
      for (double mean : means) {
        tmp_result += find_derivative_1(mean, arg);
      }
      *result = tmp_result / static_cast<double>(means.size());
    }

    static void find_density_1_SSE(const std::vector<double>& means, const double arg,
                               double* result) {
      double tmp_result = 0;
      size_t regular_part = means.size() & static_cast<size_t>(-2);

      for (size_t index = 0; index < regular_part; index += 2) {
        Vec2d means_block(means[index], means[index + 1]);
        tmp_result += find_derivative_1(means_block, arg);
      }

      size_t remainder_size = means.size() - regular_part;
      if (remainder_size != 0) {
        double mean = means[regular_part];
        tmp_result += find_derivative_1(mean, arg);
      }

      *result = tmp_result / static_cast<double>(means.size());
    }

    static void find_density_1_AVX(const std::vector<double>& means, const double arg,
                               double* result) {
      double tmp_result = 0;
      size_t regular_part = means.size() & static_cast<size_t>(-4);

      for (size_t index = 0; index < regular_part; index += 4) {
        Vec4d means_block(means[index], means[index + 1], means[index + 2],
                means[index + 3]);
        tmp_result += find_derivative_1(means_block, arg);
      }

      size_t remainder_size = means.size() - regular_part;
      if (remainder_size != 0) {
            if (remainder_size == 2) {
                Vec2d means_block(means[regular_part], means[regular_part + 1]);
                tmp_result += find_derivative_1(means_block, arg);
            } else if (remainder_size == 1) {
                double mean = means[regular_part];
                tmp_result += find_derivative_1(mean, arg);
            } else {
                Vec2d means_block(means[regular_part], means[regular_part + 1]);
                tmp_result += find_derivative_1(means_block, arg);
                double mean = means[regular_part + 2];
                tmp_result += find_derivative_1(mean, arg);
            }
       }
      *result = tmp_result / static_cast<double>(means.size());
    }

    template<typename T>
    static double find_derivative_1(T mean, double arg) {
      T deviation = 1.25 * sqrt(mean);
      T one_over_div = 1. / deviation;
      T arg_minus_mean = arg - mean;

      return find_sum(-exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
                  one_over_div) *
             one_over_sqrt_two_pi * one_over_div * one_over_div * one_over_div *
             arg_minus_mean);
    }

private:
    static constexpr const double one_over_sqrt_two_pi = 0.398942280401432702863218082712;
};


// FindDensity2
using CFindDensity2Base =
NSMath::FunctionModuleBase<void(const std::vector<double>&,
                        const double, double*),
                   NSSimd::CInstrLevel::AVX, NSSimd::CInstrLevel::SSE>;

class FindDensity2 : public CFindDensity0Base {
    using CBase = CFindDensity0Base;

public:
    FindDensity2(int instruction_level);

    static void find_density_2(const std::vector<double>& means, const double arg,
                               double* result) {
      double tmp_result = 0;
      for (double mean : means) {
        tmp_result += find_derivative_2(mean, arg);
      }
      *result = tmp_result / static_cast<double>(means.size());
    }

    static void find_density_2_SSE(const std::vector<double>& means, const double arg,
                               double* result) {
      double tmp_result = 0;
      size_t regular_part = means.size() & static_cast<size_t>(-2);

      for (size_t index = 0; index < regular_part; index += 2) {
        Vec2d means_block(means[index], means[index + 1]);
        tmp_result += find_derivative_2(means_block, arg);
      }

      size_t remainder_size = means.size() - regular_part;
      if (remainder_size != 0) {
        double mean = means[regular_part];
        tmp_result += find_derivative_2(mean, arg);
      }

      *result = tmp_result / static_cast<double>(means.size());
    }

    static void find_density_2_AVX(const std::vector<double>& means, const double arg,
                               double* result) {
      double tmp_result = 0;
      size_t regular_part = means.size() & static_cast<size_t>(-4);

      for (size_t index = 0; index < regular_part; index += 4) {
        Vec4d means_block(means[index], means[index + 1], means[index + 2],
                means[index + 3]);
        tmp_result += find_derivative_2(means_block, arg);
      }

      size_t remainder_size = means.size() - regular_part;
      if (remainder_size != 0) {
            if (remainder_size == 2) {
                Vec2d means_block(means[regular_part], means[regular_part + 1]);
                tmp_result += find_derivative_2(means_block, arg);
            } else if (remainder_size == 1) {
                double mean = means[regular_part];
                tmp_result += find_derivative_2(mean, arg);
            } else {
                Vec2d means_block(means[regular_part], means[regular_part + 1]);
                tmp_result += find_derivative_2(means_block, arg);
                double mean = means[regular_part + 2];
                tmp_result += find_derivative_2(mean, arg);
            }
       }
      *result = tmp_result / static_cast<double>(means.size());
    }

    template<typename T>
    static double find_derivative_2(T mean, double arg) {
      T deviation = 1.25 * sqrt(mean);
      T one_over_div = 1. / deviation;
      T arg_minus_mean = arg - mean;

      return find_sum(exp(-0.5 * arg_minus_mean * arg_minus_mean * one_over_div *
                 one_over_div) *
             one_over_sqrt_two_pi * one_over_div * one_over_div * one_over_div *
             (1. - arg_minus_mean * arg_minus_mean * one_over_div * one_over_div));
    }

private:
    static constexpr const double one_over_sqrt_two_pi = 0.398942280401432702863218082712;
};

class FindDensity  {
public:
    FindDensity(int instruction_level);

    void find_density_0(const std::vector<double>& means, const double arg,
                        double* result);
    void find_density_1(const std::vector<double>& means, const double arg,
                        double* result);
    void find_density_2(const std::vector<double>& means, const double arg,
                        double* result);

private:
    FindDensity0 fd0_;
    FindDensity1 fd1_;
    FindDensity2 fd2_;
};
}
}

#endif // FUNCTION_H
