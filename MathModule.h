#ifndef MATHMODULE_H
#define MATHMODULE_H

#include "ParallelModule.h"
#include "SimdDetector.h"
#include "Functions/Function.h"

#include <vector>

class MathModuleBase {
public:
    NSSimd::SimdDetector detect_;
};

class MathModule : private MathModuleBase {
public:
    MathModule();

    void find_density_0_on_grid(std::vector<double>& means,
                                std::vector<double>& grid,
                                std::vector<double>* result);
    void find_density_1_on_grid(std::vector<double>& means,
                                std::vector<double>& grid,
                                std::vector<double>* result);
    void find_density_2_on_grid(std::vector<double>& means,
                                std::vector<double>& grid,
                                std::vector<double>* result);

private:
    ParallelModule parallel_;
    FindDensity func_;
};

#endif // MATHMODULE_H
