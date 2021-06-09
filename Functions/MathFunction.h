#ifndef MATHFUNCTION_H
#define MATHFUNCTION_H

//#include <math.h>
//#include "vectorclass\vectorclass.h"
#include  <vector>

namespace NSMath {

// constexpr const double math_pi = 3.14159265358979323846264338327950288;
constexpr const double one_over_sqrt_two_pi = 0.398942280401432702863218082712;

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

template<typename T>
void find_density_0(const std::vector<double>& means, double& arg) {
  double result = 0;
  for (T mean : means)
    result += find_derivative_0(arg, mean);
  result /= static_cast<double>(means.size());
  arg = result;
}
template<typename T>
void find_density_1(const std::vector<double>& means, double& arg) {
  double result = 0;
  for (T mean : means)
    result += find_derivative_1(arg, mean);
  result /= static_cast<double>(means.size());
  arg = result;
}

template<typename T>
void find_density_2(const std::vector<double>& means, double& arg) {
  double result = 0;
  for (T mean : means)
    result += find_derivative_2(arg, mean);
  result /= static_cast<double>(means.size());
  arg = result;
}

} // namespace NSMath

#endif // MATHFUNCTION_H
