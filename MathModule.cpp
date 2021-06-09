#include "MathModule.h"
#include <iostream>


namespace NSMathModule {
    СMathModule::СMathModule(): func_(level()) {}

    void СMathModule::find_density_0_on_grid(std::vector<double>& means,
                                std::vector<double>& grid,
                                std::vector<double>* result){
        parallel_.parallel_for(0, grid.size(), [this, &grid, &means, &result](size_t ind) mutable {
           (*result)[ind] = this->func_.compute0(means, grid[ind]);
        });
    }

    void СMathModule::find_density_1_on_grid(std::vector<double>& means,
                                std::vector<double>& grid,
                                std::vector<double>* result){
        parallel_.parallel_for(0, grid.size(), [this, &grid, &means, &result](size_t ind) mutable {
           (*result)[ind] = this->func_.compute1(means, grid[ind]);
        });
    }

    void СMathModule::find_density_2_on_grid(std::vector<double>& means,
                                std::vector<double>& grid,
                                std::vector<double>* result){
        parallel_.parallel_for(0, grid.size(), [this, &grid, &means, &result](size_t ind) mutable {
           (*result)[ind] = this->func_.compute2(means, grid[ind]);
        });
    }

    void СMathModule::switch_lib(NSParallel::EParallelLibrary lib) {
        parallel_.switch_lib(lib);
    }

    void СMathModule::print_current_lib() {
        parallel_.print_current_lib();
    }
}
