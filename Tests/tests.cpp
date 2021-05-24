#include "tests.h"

void Tests::test_density_avx_ppl(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    FindDensity func(7);
    ParallelModulePpl parallel;

    parallel.parallel_for(0, grid.size(), [&func, &grid, &means, &result](size_t ind) mutable {
       func.find_density_0(means, grid[ind], &(*result)[ind]);
    });
}

void Tests::test_density_avx_tbb(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    FindDensity func(7);
    ParallelModuleTbb parallel;

    parallel.parallel_for(0, grid.size(), [&func, &grid, &means, &result](size_t ind) mutable {
       func.find_density_0(means, grid[ind], &(*result)[ind]);
    });
}

void Tests::test_density_avx_default(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    FindDensity func(7);
    ParallelModulePpl parallel;

    for (size_t i = 0; i < grid.size(); ++i) {
        func.find_density_0(means, grid[i], &(*result)[i]);
    }
}

void Tests::test_density_sse_tbb(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    FindDensity func(2);
    ParallelModuleTbb parallel;

    parallel.parallel_for(0, grid.size(), [&func, &grid, &means, &result](size_t ind) mutable {
       func.find_density_0(means, grid[ind], &(*result)[ind]);
    });
}

void Tests::test_density_sse_ppl(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    FindDensity func(2);
    ParallelModulePpl parallel;

    parallel.parallel_for(0, grid.size(), [&func, &grid, &means, &result](size_t ind) mutable {
       func.find_density_0(means, grid[ind], &(*result)[ind]);
    });
}

void Tests::test_density_sse_default(std::vector<double> &means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    FindDensity func(2);
    ParallelModulePpl parallel;

    for (size_t i = 0; i < grid.size(); ++i) {
        func.find_density_0(means, grid[i], &(*result)[i]);
    }
}

void Tests::test_density_default_tbb(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    FindDensity func(0);
    ParallelModuleTbb parallel;

    parallel.parallel_for(0, grid.size(), [&func, &grid, &means, &result](size_t ind) mutable {
       func.find_density_0(means, grid[ind], &(*result)[ind]);
    });
}

void Tests::test_density_default_ppl(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    FindDensity func(0);
    ParallelModulePpl parallel;

    parallel.parallel_for(0, grid.size(), [&func, &grid, &means, &result](size_t ind) mutable {
       func.find_density_0(means, grid[ind], &(*result)[ind]);
    });
}

void Tests::test_density_default_default(std::vector<double> &means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    FindDensity func(0);
    ParallelModulePpl parallel;

    for (size_t i = 0; i < grid.size(); ++i) {
        func.find_density_0(means, grid[i], &(*result)[i]);
    }
}
