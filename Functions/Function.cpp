#include "Function.h"


#include "vectorclass/vectorclass.h"
#include "vectorclass/vectormath_exp.h"

namespace MathModule {
namespace Functions {

FindDensity0::FindDensity0(int instruction_level)
    : CBase(&find_density_0_AVX, &find_density_0_SSE, &find_density_0, instruction_level) {
}

FindDensity1::FindDensity1(int instruction_level)
    : CBase(&find_density_1_AVX, &find_density_1_SSE, &find_density_1, instruction_level) {
}

FindDensity2::FindDensity2(int instruction_level)
    : CBase(&find_density_2_AVX, &find_density_2_SSE, &find_density_2, instruction_level) {
}

FindDensity::FindDensity(int instruction_level):
fd0_(instruction_level), fd1_(instruction_level), fd2_(instruction_level){}

void FindDensity::find_density_0(const std::vector<double>& means, const double arg,
                    double* result) {
    fd0_(means, arg, result);
}
void FindDensity::find_density_1(const std::vector<double>& means, const double arg,
                                 double* result) {
      fd1_(means, arg, result);
}
void FindDensity::find_density_2(const std::vector<double>& means, const double arg,
                                 double* result) {
      fd2_(means, arg, result);
}
}
}
