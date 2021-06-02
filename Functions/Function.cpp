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

double CDensity0::compute0_SSE(const std::vector<double>& means, double arg) {
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

  return tmp_result / static_cast<double>(means.size());
}

double CDensity0::compute0_AVX(const std::vector<double>& means, double arg) {
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
  return tmp_result / static_cast<double>(means.size());
}

CDensity0::CDensity0(int instruction_level)
    : CBase(&compute0_AVX, &compute0_SSE, &compute0, instruction_level) {
}

CDensity1::CDensity1(int instruction_level)
    : CBase(&compute1_AVX, &compute1_SSE, &compute1, instruction_level) {
}

double CDensity1::compute1(const std::vector<double>& means, double arg) {
  double tmp_result = 0;
  for (double mean : means) {
    tmp_result += find_derivative_1(mean, arg);
  }
  return tmp_result / static_cast<double>(means.size());
}

double CDensity1::compute1_SSE(const std::vector<double>& means, double arg) {
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

  return tmp_result / static_cast<double>(means.size());
}

double CDensity1::compute1_AVX(const std::vector<double>& means, double arg) {
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
   return tmp_result / static_cast<double>(means.size());
}

double CDensity2::compute2(const std::vector<double>& means, double arg) {
  double tmp_result = 0;
  for (double mean : means) {
    tmp_result += find_derivative_2(mean, arg);
  }
  return tmp_result / static_cast<double>(means.size());
}

double CDensity2::compute2_SSE(const std::vector<double>& means, double arg) {
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

  return tmp_result / static_cast<double>(means.size());
}

double CDensity2::compute2_AVX(const std::vector<double>& means, double arg) {
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
  return tmp_result / static_cast<double>(means.size());
}

CDensity2::CDensity2(int instruction_level)
    : CBase(&compute2_AVX, &compute2_SSE, &compute2, instruction_level) {
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
