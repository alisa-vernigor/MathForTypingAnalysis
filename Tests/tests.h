#ifndef TESTS_H
#define TESTS_H

#include "MathModule.h"
#include "Functions/Function.h"
#include "ParallelModule.h"
#include "TimeMeasurer.h"

#include <iostream>
#include <fstream>
#include <string>

namespace NSTests {

struct CResult {
    std::chrono::microseconds max_time;
    std::chrono::microseconds min_time;
    std::chrono::microseconds average_time;

    friend std::ostream& operator<<(std::ostream& os, const CResult& res);
};

struct CResults {
    NSTests::CResult res_x1;
    NSTests::CResult res_x2;
    NSTests::CResult res_x3;

    friend std::ostream& operator<<(std::ostream& os, const CResults& res);
};

struct CCurrentConfiguration {
  static constexpr const size_t kItNum = 1;
  static constexpr const size_t kSkipNum = 0;
};

class CTests {
public:
    CTests(size_t size, std::string file_name);
    ~CTests();

    void test_all();
private:
    std::vector<double> m_;
    std::vector<double> x1_;
    std::vector<double> x2_;
    std::vector<double> x3_;

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

    void test_density_avx2_tbb(std::vector<double>& means,
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

    void test_density_avx2_ppl(std::vector<double>& means,
                                  std::vector<double>& grid,
                                  std::vector<double>* result);
    void test_density_default_default(std::vector<double>& means,
                                      std::vector<double>& grid,
                                      std::vector<double>* result);

    void test_density_avx2_default(std::vector<double>& means,
                                      std::vector<double>& grid,
                                      std::vector<double>* result);


    void init_x(size_t size, std::vector<double>& x, size_t step);

    void init_m(size_t size);

    std::ofstream output_stream_;

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

                (this->*test)(m_, x, &res);
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
                (this->*test)(m_, x, &res);
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

    NSMathModule::NSFunctions::CDensity func_avx_;
    NSMathModule::NSFunctions::CDensity func_avx2_;
    NSMathModule::NSFunctions::CDensity func_sse_;
    NSMathModule::NSFunctions::CDensity func_default_;
    NSMathModule::NSParallel::CParallelModulePpl parallel_ppl_;
    NSMathModule::NSParallel::CParallelModuleTbb parallel_tbb_;


    template<typename TFunc>
    void fill_results(TFunc func, size_t it_num, CResults *res, size_t skip_num = 0) {
        res->res_x1 = test_one(func, x1_, it_num, skip_num);
        res->res_x2 = test_one(func, x2_, it_num, skip_num);
        res->res_x3 = test_one(func, x3_, it_num, skip_num);
    }

    void output_results(size_t id, std::string name, CResults res);
};
}

#endif // TESTS_H
