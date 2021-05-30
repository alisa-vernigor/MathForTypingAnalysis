#include "tests.h"

std::ostream& operator<<(std::ostream& os, const Result& res) {
    os << "    > Maximum time: " << std:: chrono::duration_cast<std::chrono::microseconds>(res.max_time).count() <<
               " microseconds\n"
    "    > Minimum time: " << std::chrono::duration_cast<std::chrono::microseconds>(res.min_time).count() << " microseconds\n"
    "    > Average time: " << std::chrono::duration_cast<std::chrono::microseconds>(res.average_time).count() << " microseconds";
    return os;
}

MathModule::Functions::FindDensity Tests::func_avx_(7);
MathModule::Functions::FindDensity Tests::func_sse_(2);
MathModule::Functions::FindDensity Tests::func_default_(0);
MathModule::Parallel::ParallelModuleTbb Tests::parallel_tbb_;
MathModule::Parallel::ParallelModulePpl Tests::parallel_ppl_;

Tests::Tests(size_t size) {
    init_m(size);
    init_x(size, x1_, 1);
    init_x(size, x2_, 5);
    init_x(size, x3_, 10);
};

void Tests::test_density_avx_ppl(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {

    parallel_ppl_.parallel_for(0, grid.size(), [&grid, &means, &result](size_t ind) mutable {
       func_avx_.find_density_0(means, grid[ind], &(*result)[ind]);
    });
}

void Tests::test_density_avx_tbb(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {

    parallel_tbb_.parallel_for(0, grid.size(), [&grid, &means, &result](size_t ind) mutable {
       func_avx_.find_density_0(means, grid[ind], &(*result)[ind]);
    });
}

void Tests::test_density_avx_default(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {

    for (size_t i = 0; i < grid.size(); ++i) {
        func_avx_.find_density_0(means, grid[i], &(*result)[i]);
    }
}

void Tests::test_density_sse_tbb(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    parallel_tbb_.parallel_for(0, grid.size(), [&grid, &means, &result](size_t ind) mutable {
       func_sse_.find_density_0(means, grid[ind], &(*result)[ind]);
    });
}

void Tests::test_density_sse_ppl(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    parallel_ppl_.parallel_for(0, grid.size(), [&grid, &means, &result](size_t ind) mutable {
       func_sse_.find_density_0(means, grid[ind], &(*result)[ind]);
    });
}

void Tests::test_density_sse_default(std::vector<double> &means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    for (size_t i = 0; i < grid.size(); ++i) {
        func_sse_.find_density_0(means, grid[i], &(*result)[i]);
    }
}

void Tests::test_density_default_tbb(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    parallel_tbb_.parallel_for(0, grid.size(), [&grid, &means, &result](size_t ind) mutable {
       func_default_.find_density_0(means, grid[ind], &(*result)[ind]);
    });
}

void Tests::test_density_default_ppl(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    parallel_ppl_.parallel_for(0, grid.size(), [&grid, &means, &result](size_t ind) mutable {
       func_default_.find_density_0(means, grid[ind], &(*result)[ind]);
    });
}

void Tests::test_density_default_default(std::vector<double> &means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    for (size_t i = 0; i < grid.size(); ++i) {
        func_default_.find_density_0(means, grid[i], &(*result)[i]);
    }
}

void Tests::init_m(size_t size) {
    m_.resize(size);
    for (size_t i = 0; i < size; ++i) {
        m_[i] = (double)rand() / RAND_MAX;
    }
}

void Tests::init_x(size_t max, std::vector<double>& x, size_t step) {
    x.resize(max / step + 1);

    for (size_t i = 0; i < x.size(); ++i) {
        x[i] = i * step;
    }
}
