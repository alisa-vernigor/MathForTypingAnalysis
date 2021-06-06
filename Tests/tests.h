#ifndef TESTS_H
#define TESTS_H

#include "MathModule.h"
#include "Functions/Function.h"
#include "ParallelModule.h"
#include "TimeMeasurer.h"

#include <iostream>

namespace NSTests {

struct CResult {
    std::chrono::microseconds max_time;
    std::chrono::microseconds min_time;
    std::chrono::microseconds average_time;

    friend std::ostream& operator<<(std::ostream& os, const CResult& res);
};

class CTests {
public:
    CTests(size_t size);

    static void test_density_avx_ppl(std::vector<double>& means,
                              std::vector<double>& grid,
                              std::vector<double>* result);
    static void test_density_avx_tbb(std::vector<double>& means,
                              std::vector<double>& grid,
                              std::vector<double>* result);
    static void test_density_avx_default(std::vector<double>& means,
                                  std::vector<double>& grid,
                                  std::vector<double>* result);

    static void test_density_sse_tbb(std::vector<double>& means,
                              std::vector<double>& grid,
                              std::vector<double>* result);

    static void test_density_avx2_tbb(std::vector<double>& means,
                              std::vector<double>& grid,
                              std::vector<double>* result);


    static void test_density_sse_ppl(std::vector<double>& means,
                              std::vector<double>& grid,
                              std::vector<double>* result);



    static void test_density_sse_default(std::vector<double>& means,
                                  std::vector<double>& grid,
                                  std::vector<double>* result);

    static void test_density_default_tbb(std::vector<double>& means,
                                  std::vector<double>& grid,
                                  std::vector<double>* result);
    static void test_density_default_ppl(std::vector<double>& means,
                                  std::vector<double>& grid,
                                  std::vector<double>* result);

    static void test_density_avx2_ppl(std::vector<double>& means,
                                  std::vector<double>& grid,
                                  std::vector<double>* result);
    static void test_density_default_default(std::vector<double>& means,
                                      std::vector<double>& grid,
                                      std::vector<double>* result);

    static void test_density_avx2_default(std::vector<double>& means,
                                      std::vector<double>& grid,
                                      std::vector<double>* result);

    template<typename TFunc>
    CResult test_one(TFunc test, std::vector<double>& x,
                  size_t it_num, size_t skip_num = 0,
                     std::vector<double> *result = NULL) {
        using namespace std::chrono;

        std::vector<double> res(x.size());

        CResult measures;
        microseconds time;

        for (size_t i = 0; i < it_num; ++i) {
            if (i >= skip_num) {
                NSTimeMeasurer::CTimeAnchor c;

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
            } else {
                test(m_, x, &res);
            }
        }
        if (result) {
            (*result).resize(res.size());
            for (size_t i = 0; i < res.size(); ++i) {
                (*result)[i] = res[i];
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
    void init_x(size_t size, std::vector<double>& x, size_t step);

    void init_m(size_t size);

    static NSMathModule::NSFunctions::CDensity func_avx_;
    static NSMathModule::NSFunctions::CDensity func_avx2_;
    static NSMathModule::NSFunctions::CDensity func_sse_;
    static NSMathModule::NSFunctions::CDensity func_default_;
    static NSMathModule::NSParallel::CParallelModulePpl parallel_ppl_;
    static NSMathModule::NSParallel::CParallelModuleTbb parallel_tbb_;
};
}

#endif // TESTS_H
