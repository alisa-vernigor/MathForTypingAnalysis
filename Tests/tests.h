#ifndef TESTS_H
#define TESTS_H

#include "MathModule.h"
#include "Functions/Function.h"
#include "ParallelModule.h"
#include "TimeMeasurer.h"

class Tests {
    using Result = struct {
                        std::chrono::microseconds max_time;
                        std::chrono::microseconds min_time;
                        std::chrono::microseconds average_time;
                   };

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
    template<typename TFunc>
    Result test_one(TFunc test, std::vector<double>& x,
                  size_t it_num, size_t skip_num = 0) {
        using namespace std::chrono;

        std::vector<double> res;
        Result measures;
        microseconds time;

        for (size_t i = 0; i < it_num; ++i) {
            if (i >= skip_num) {
                CTimeAnchor c;
                test(m_, x, &res);
                time = c.get_time();

                if (i == skip_num) {
                    measures.average_time = measures.max_time = measures.min_time = time;
                } else {
                    measures.average_time += time;
                    if (measures.max_time < time) {
                        measures.max_time = time;
                    }
                    if (measures.min_time > time) {
                        measures.min_time = time;
                    }
                }
            }
        }
        measures.average_time /= it_num - skip_num;
        return measures;
    }

    std::vector<double> m_;
    std::vector<double> x1_;
    std::vector<double> x2_;
    std::vector<double> x3_;
private:
    void init_x(size_t size, std::vector<double>& x, double step);

    void init_m(size_t size);
};

#endif // TESTS_H
