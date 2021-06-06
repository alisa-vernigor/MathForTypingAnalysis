#include "Function.h"


#include "vectorclass/vectorclass.h"
#include "vectorclass/vectormath_exp.h"

namespace NSMathModule {
namespace NSFunctions {

double CDensity0::compute0(const std::vector<double>& means, double arg) {
  double tmp_result = 0;
  for (double mean : means) {
    tmp_result += find_derivative_0(mean, arg);
  }
  return tmp_result / static_cast<double>(means.size());
}

CDensity0::CDensity0(int instruction_level)
    : CBase(&compute0_AVX2, compute0_AVX, &compute0_SSE2, &compute0, instruction_level) {
}

CDensity1::CDensity1(int instruction_level)
    : CBase(&compute1_AVX2,&compute1_AVX, &compute1_SSE2, &compute1, instruction_level) {
}

double CDensity1::compute1(const std::vector<double>& means, double arg) {
  double tmp_result = 0;
  for (double mean : means) {
    tmp_result += find_derivative_1(mean, arg);
  }
  return tmp_result / static_cast<double>(means.size());
}

double CDensity2::compute2(const std::vector<double>& means, double arg) {
  double tmp_result = 0;
  for (double mean : means) {
    tmp_result += find_derivative_2(mean, arg);
  }
  return tmp_result / static_cast<double>(means.size());
}

CDensity2::CDensity2(int instruction_level)
    : CBase(&compute2_AVX2, &compute2_AVX, &compute2_SSE2, &compute2, instruction_level) {
}

CDensity::CDensity(int instruction_level):
d0_(instruction_level), d1_(instruction_level), d2_(instruction_level){}

double CDensity::compute0(const std::vector<double>& means, double arg) {
    return d0_(means, arg);
}
double CDensity::compute1(const std::vector<double>& means, double arg) {
    return d1_(means, arg);
}
double CDensity::compute2(const std::vector<double>& means, const double arg) {
    return d2_(means, arg);
}
}
}
