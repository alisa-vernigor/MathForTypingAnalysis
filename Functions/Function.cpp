#include "Function.h"


#include "vectorclass/vectorclass.h"
#include "vectorclass/vectormath_exp.h"

FindDensity0::FindDensity0(int instruction_level)
    : CBase(&find_density_0<Vec4d>, &find_density_0<Vec2d>, &find_density_0<double>, instruction_level) {
}

FindDensity1::FindDensity1(int instruction_level)
    : CBase(&find_density_1<Vec4d>, &find_density_1<Vec2d>, &find_density_1<double>, instruction_level) {
}

FindDensity2::FindDensity2(int instruction_level)
    : CBase(&find_density_2<Vec4d>, &find_density_2<Vec2d>, &find_density_2<double>, instruction_level) {
}

Function::Function(int instruction_level):
fd0_(instruction_level), fd1_(instruction_level), fd2_(instruction_level){}
