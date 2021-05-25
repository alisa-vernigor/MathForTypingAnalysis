#include "tests.h"

Tests::Tests(size_t size) {
    init_m(size);
    init_x(size, x1_, 1);
    init_x(size, x2_, 5);
    init_x(size, x3_, 10);
};

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

void Tests::init_m(size_t size) {
    m_.resize(size);
    for (size_t i = 0; i < size; ++i) {
        m_[i] = (double)rand() / RAND_MAX;
    }
}

void Tests::init_x(size_t size, std::vector<double>& x, double step) {
    x.resize(size);
    for (size_t i = 0; i < size; ++i) {
        x[i] = (i == 0) ? 0 : (x[i - 1] + step);
    }
}
