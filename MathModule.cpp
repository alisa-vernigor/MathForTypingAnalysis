#include "MathModule.h"

MathModule::MathModule(): func_(detect_.level()) {}

void MathModule::find_density_0_on_grid(std::vector<double>& means,
                            std::vector<double>& grid,
                            std::vector<double>* result){
    parallel_.parallel_for(0, grid.size(), [this, &grid, &means, &result](size_t ind) mutable {
       this->func_.find_density_0(means, grid[ind], &(*result)[ind]);
    });
}

void MathModule::find_density_1_on_grid(std::vector<double>& means,
                            std::vector<double>& grid,
                            std::vector<double>* result){
    parallel_.parallel_for(0, grid.size(), [this, &grid, &means, &result](size_t ind) mutable {
       this->func_.find_density_1(means, grid[ind], &(*result)[ind]);
    });
}

void MathModule::find_density_2_on_grid(std::vector<double>& means,
                            std::vector<double>& grid,
                            std::vector<double>* result){
    parallel_.parallel_for(0, grid.size(), [this, &grid, &means, &result](size_t ind) mutable {
       this->func_.find_density_2(means, grid[ind], &(*result)[ind]);
    });
}
