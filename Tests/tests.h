#ifndef TESTS_H
#define TESTS_H

#include "MathModule.h"
#include "Functions/Function.h"
#include "ParallelModule.h"

class Tests {
public:
    Tests(size_t size);

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
    void init_x(size_t size, std::vector<double>& x, double step);

    void init_m(size_t size);

    std::vector<double> m_;
    std::vector<double> x1_;
    std::vector<double> x2_;
    std::vector<double> x3_;
};

#endif // TESTS_H
