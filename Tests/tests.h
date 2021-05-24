#ifndef TESTS_H
#define TESTS_H

#include "MathModule.h"
#include "Functions/Function.h"
#include "ParallelModule.h"

class Tests {
public:
    Tests();
    void test_density_avx_ppl(std::vector<double>& means,
                              std::vector<double>& grid,
                              std::vector<double>* result);
    void test_density_avx_tbb(std::vector<double>& means,
                              std::vector<double>& grid,
                              std::vector<double>* result);
    void test_density_avx_default(std::vector<double>& means,
                                  std::vector<double>& grid,
                                  std::vector<double>* result);

    void test_density_sse_tbb(std::vector<double>& means,
                              std::vector<double>& grid,
                              std::vector<double>* result);
    void test_density_sse_ppl(std::vector<double>& means,
                              std::vector<double>& grid,
                              std::vector<double>* result);
    void test_density_sse_default(std::vector<double>& means,
                                  std::vector<double>& grid,
                                  std::vector<double>* result);

    void test_density_default_tbb(std::vector<double>& means,
                                  std::vector<double>& grid,
                                  std::vector<double>* result);
    void test_density_default_ppl(std::vector<double>& means,
                                  std::vector<double>& grid,
                                  std::vector<double>* result);
    void test_density_default_default(std::vector<double>& means,
                                      std::vector<double>& grid,
                                      std::vector<double>* result);

private:
    MathModule m_;
    FindDensity func_;
    ParallelModule parallel_;
};

#endif // TESTS_H
