#ifndef MATHMODULE_H
#define MATHMODULE_H

#include "ParallelModule.h"
#include "SimdDetector.h"
#include "Functions/Function.h"

#include <vector>

namespace NSMathModule {
    class СMathModuleBase {
    public:
        int level() const {
            return detect_.level();
        }
    private:
        NSSimd::СSimdDetector detect_;
    };

    class СMathModule : protected СMathModuleBase {
    public:
        СMathModule();

        void find_density_0_on_grid(std::vector<double>& means,
                                    std::vector<double>& grid,
                                    std::vector<double>* result);
        void find_density_1_on_grid(std::vector<double>& means,
                                    std::vector<double>& grid,
                                    std::vector<double>* result);
        void find_density_2_on_grid(std::vector<double>& means,
                                    std::vector<double>& grid,
                                    std::vector<double>* result);
        void switch_lib(NSParallel::EParallelLibrary lib = NSParallel::EParallelLibrary::Tbb);
        void print_current_lib();

    private:
        NSParallel::СParallelModule parallel_;
        NSFunctions::CDensity func_;
    };
}

#endif // MATHMODULE_H
