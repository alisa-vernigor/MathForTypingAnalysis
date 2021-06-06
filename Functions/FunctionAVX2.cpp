#include "Function.h"


#include "vectorclass/vectorclass.h"
#include "vectorclass/vectormath_exp.h"

namespace NSMathModule {
namespace NSFunctions {
    double CDensity0::compute0_AVX2(const std::vector<double>& means, double arg) {
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

    double CDensity1::compute1_AVX2(const std::vector<double>& means, double arg) {
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

    double CDensity2::compute2_AVX2(const std::vector<double>& means, double arg) {
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
}
}
