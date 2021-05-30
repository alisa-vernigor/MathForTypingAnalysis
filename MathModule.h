#ifndef MATHMODULE_H
#define MATHMODULE_H

#include "ParallelModule.h"
#include "SimdDetector.h"
#include "Functions/Function.h"

#include <vector>

namespace MathModule {
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
        void switch_lib(Parallel::Libs lib = Parallel::Libs::TBB);
        void print_current_lib();

    private:
        Parallel::ParallelModule parallel_;
        Functions::FindDensity func_;
    };
}

#endif // MATHMODULE_H
