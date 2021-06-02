#include "tests.h"

namespace NSTests {
std::ostream& operator<<(std::ostream& os, const Result& res) {
    os << "    > Maximum time: " << std:: chrono::duration_cast<std::chrono::microseconds>(res.max_time).count() <<
               " microseconds\n"
    "    > Minimum time: " << std::chrono::duration_cast<std::chrono::microseconds>(res.min_time).count() << " microseconds\n"
    "    > Average time: " << std::chrono::duration_cast<std::chrono::microseconds>(res.average_time).count() << " microseconds";
    return os;
}

NSMathModule::NSFunctions::CDensity CTests::func_avx_(NSSimd::CInstrLevel::AVX);
NSMathModule::NSFunctions::CDensity CTests::func_sse_(NSSimd::CInstrLevel::SSE2);
NSMathModule::NSFunctions::CDensity CTests::func_default_(NSSimd::CInstrLevel::Default);
NSMathModule::NSParallel::CParallelModuleTbb CTests::parallel_tbb_;
NSMathModule::NSParallel::CParallelModulePpl CTests::parallel_ppl_;

CTests::CTests(size_t size) {
    init_m(size);
    init_x(size, x1_, 1);
    init_x(size, x2_, 5);
    init_x(size, x3_, 10);
};

void CTests::test_density_avx_ppl(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {

    parallel_ppl_.parallel_for(0, grid.size(), [&grid, &means, &result](size_t ind) mutable {
       (*result)[ind] = func_avx_.compute0(means, grid[ind]);
    });
}

void CTests::test_density_avx_tbb(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {

    parallel_tbb_.parallel_for(0, grid.size(), [&grid, &means, &result](size_t ind) mutable {
       (*result)[ind] = func_avx_.compute0(means, grid[ind]);
    });
}

void CTests::test_density_avx_default(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {

    for (size_t i = 0; i < grid.size(); ++i) {
        (*result)[i] = func_avx_.compute0(means, grid[i]);
    }
}

void CTests::test_density_sse_tbb(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    parallel_tbb_.parallel_for(0, grid.size(), [&grid, &means, &result](size_t ind) mutable {
       (*result)[ind] = func_sse_.compute0(means, grid[ind]);
    });
}

void CTests::test_density_sse_ppl(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    parallel_ppl_.parallel_for(0, grid.size(), [&grid, &means, &result](size_t ind) mutable {
       (*result)[ind] = func_sse_.compute0(means, grid[ind]);
    });
}

void CTests::test_density_sse_default(std::vector<double> &means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    for (size_t i = 0; i < grid.size(); ++i) {
        (*result)[i] =func_sse_.compute0(means, grid[i]);
    }
}

void CTests::test_density_default_tbb(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    parallel_tbb_.parallel_for(0, grid.size(), [&grid, &means, &result](size_t ind) mutable {
       (*result)[ind] = func_default_.compute0(means, grid[ind]);
    });
}

void CTests::test_density_default_ppl(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    parallel_ppl_.parallel_for(0, grid.size(), [&grid, &means, &result](size_t ind) mutable {
       (*result)[ind] = func_default_.compute0(means, grid[ind]);
    });
}

void CTests::test_density_default_default(std::vector<double> &means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    for (size_t i = 0; i < grid.size(); ++i) {
        (*result)[i] = func_default_.compute0(means, grid[i]);
    }
}

void CTests::init_m(size_t size) {
    m_.resize(size);
    for (size_t i = 0; i < size; ++i) {
        m_[i] = (double)rand() / RAND_MAX;
    }
}

void CTests::init_x(size_t max, std::vector<double>& x, size_t step) {
    x.resize(max / step + 1);

    for (size_t i = 0; i < x.size(); ++i) {
        x[i] = i * step;
    }
}
}
