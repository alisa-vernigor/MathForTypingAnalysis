#include "tests.h"

namespace NSTests {
std::ostream& operator<<(std::ostream& os, const CResult& res) {
    os << "    > Maximum time: " << std:: chrono::duration_cast<std::chrono::microseconds>(res.max_time).count() <<
               " microseconds\n"
    "    > Minimum time: " << std::chrono::duration_cast<std::chrono::microseconds>(res.min_time).count() << " microseconds\n"
    "    > Average time: " << std::chrono::duration_cast<std::chrono::microseconds>(res.average_time).count() << " microseconds";
    return os;
}

std::ostream& operator<<(std::ostream& os, const CResults& res) {
    os << "  a) Vector x1:\n";
    os << res.res_x1 << "\n";
    os << "  b) Vector x2:\n";
    os << res.res_x2 << "\n";
    os << "  c) Vector x3:\n";
    os << res.res_x3 << "\n";

    return os;
}

CTests::CTests(size_t size, std::string file_name):
func_avx_(NSSimd::CInstrLevel::AVX), func_avx2_(NSSimd::CInstrLevel::AVX2),
func_sse_(NSSimd::CInstrLevel::SSE2), func_default_(NSSimd::CInstrLevel::Default){
    output_stream_.open(file_name);
    init_m(size);
    init_x(size, x1_, 1);
    init_x(size, x2_, 5);
    init_x(size, x3_, 10);
};

CTests::~CTests() {
    output_stream_.close();
}

void CTests::test_density_avx_ppl(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {

    parallel_ppl_.parallel_for(0, grid.size(), [this, &grid, &means, &result](size_t ind) mutable {
       (*result)[ind] = func_avx_.compute0(means, grid[ind]);
    });
}

void CTests::test_density_avx_tbb(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {

    parallel_tbb_.parallel_for(0, grid.size(), [this, &grid, &means, &result](size_t ind) mutable {
       (*result)[ind] = func_avx_.compute0(means, grid[ind]);
    });
}

void CTests::test_density_avx2_tbb(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {

    parallel_tbb_.parallel_for(0, grid.size(), [this, &grid, &means, &result](size_t ind) mutable {
         (*result)[ind] = func_avx2_.compute0(means, grid[ind]);
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
    parallel_tbb_.parallel_for(0, grid.size(), [this, &grid, &means, &result](size_t ind) mutable {
       (*result)[ind] = func_sse_.compute0(means, grid[ind]);
    });
}

void CTests::test_density_sse_ppl(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    parallel_ppl_.parallel_for(0, grid.size(), [this, &grid, &means, &result](size_t ind) mutable {
       (*result)[ind] = func_sse_.compute0(means, grid[ind]);
    });
}

void CTests::test_density_avx2_ppl(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    parallel_ppl_.parallel_for(0, grid.size(), [this, &grid, &means, &result](size_t ind) mutable {
       (*result)[ind] = func_avx2_.compute0(means, grid[ind]);
    });
}

void CTests::test_density_sse_default(std::vector<double> &means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    for (size_t i = 0; i < grid.size(); ++i) {
        (*result)[i] =func_sse_.compute0(means, grid[i]);
    }
}

void CTests::test_density_avx2_default(std::vector<double> &means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    for (size_t i = 0; i < grid.size(); ++i) {
        (*result)[i] =func_avx2_.compute0(means, grid[i]);
    }
}

void CTests::test_density_default_tbb(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    parallel_tbb_.parallel_for(0, grid.size(), [this, &grid, &means, &result](size_t ind) mutable {
       (*result)[ind] = func_default_.compute0(means, grid[ind]);
    });
}

void CTests::test_density_default_ppl(std::vector<double>& means,
                                 std::vector<double>& grid,
                                 std::vector<double>* result) {
    parallel_ppl_.parallel_for(0, grid.size(), [this, &grid, &means, &result](size_t ind) mutable {
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

void CTests::test_all() {
    output_stream_ << "Input data:\n1) Random vector of doubles means (size = "
                   << m_.size() << ")." << std::endl;

    output_stream_ << "2) Vectors of doubles x1 (from 0 to "
                   << m_.size() << " with step 1), x2 (from 0 to "
                   << m_.size() << " with step 5) and x3 (from 0 to "
                   << m_.size() << " with step 10)." << "\n" << std::endl;

    CResults res;

    output_stream_ << "Results (number of iterations = " << CCurrentConfiguration::kItNum << "):\n";

    // Without tbb and ppl
    fill_results(&CTests::test_density_default_default, CCurrentConfiguration::kItNum, &res, CCurrentConfiguration::kSkipNum);
    output_results(1, "Without the use of parallel libraries and SIMD instructions", res);

    fill_results(&CTests::test_density_sse_default, CCurrentConfiguration::kItNum, &res);
    output_results(2, "Without the use of parallel libraries and with level of SIMD instructions SSE", res);

    fill_results(&CTests::test_density_avx_default, CCurrentConfiguration::kItNum, &res, CCurrentConfiguration::kSkipNum);
    output_results(3, "Without the use of parallel libraries and with level of SIMD instructions AVX", res);

    fill_results(&CTests::test_density_avx2_default, CCurrentConfiguration::kItNum, &res, CCurrentConfiguration::kSkipNum);
    output_results(4, "Without the use of parallel libraries and with level of SIMD instructions AVX2", res);

    // Tbb
    fill_results(&CTests::test_density_default_tbb, CCurrentConfiguration::kItNum, &res, CCurrentConfiguration::kSkipNum);
    output_results(5, "Using TBB library and without use of SIMD instructions", res);

    fill_results(&CTests::test_density_sse_tbb, CCurrentConfiguration::kItNum, &res, CCurrentConfiguration::kSkipNum);
    output_results(6, "Using TBB library and and with level of SIMD instructions SSE", res);

    fill_results(&CTests::test_density_avx_tbb, CCurrentConfiguration::kItNum, &res, CCurrentConfiguration::kSkipNum);
    output_results(7, "Using TBB library and and with level of SIMD instructions AVX", res);

    fill_results(&CTests::test_density_avx2_tbb, CCurrentConfiguration::kItNum, &res, CCurrentConfiguration::kSkipNum);
    output_results(8, "Using TBB library and and with level of SIMD instructions AVX2", res);

    // PPL
    fill_results(&CTests::test_density_default_ppl, CCurrentConfiguration::kItNum, &res, CCurrentConfiguration::kSkipNum);
    output_results(9, "Using PPL library and without use of SIMD instructions", res);

    fill_results(&CTests::test_density_sse_ppl, CCurrentConfiguration::kItNum, &res, CCurrentConfiguration::kSkipNum);
    output_results(10, "Using PPL library and and with level of SIMD instructions SSE", res);

    fill_results(&CTests::test_density_avx_ppl, CCurrentConfiguration::kItNum, &res, CCurrentConfiguration::kSkipNum);
    output_results(11, "Using PPL library and and with level of SIMD instructions AVX", res);

    fill_results(&CTests::test_density_avx2_ppl, CCurrentConfiguration::kItNum, &res, CCurrentConfiguration::kSkipNum);
    output_results(12, "Using PPL library and and with level of SIMD instructions AVX2", res);
}

void CTests::output_results(size_t id, std::string name, CResults res) {
    output_stream_ << id << ") " << name << ":\n";
    output_stream_ << res << "\n";
}

}
