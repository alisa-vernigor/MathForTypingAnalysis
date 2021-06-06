#include <iostream>

#include <MathModule.h>

#include <vector>
#include <string>
#include <cmath>

#include <Tests/tests.h>

using namespace std;

enum СCurrentConfiguration {
    IT_NUM = 250,
    SKIP_NUM = 63
};

struct CResults {
    NSTests::CResult res_x1;
    NSTests::CResult res_x2;
    NSTests::CResult res_x3;

    friend std::ostream& operator<<(std::ostream& os, const CResults& res);
};

std::ostream& operator<<(std::ostream& os, const CResults& res) {
    cout << "  a) Vector x1:\n";
    cout << res.res_x1 << "\n";
    cout << "  b) Vector x2:\n";
    cout << res.res_x2 << "\n";
    cout << "  c) Vector x3:\n";
    cout << res.res_x3 << "\n";

    return os;
}

template<typename TFunc>
void fill_results(NSTests::CTests& t, TFunc func, size_t it_num, CResults *res, size_t skip_num = 0) {
    res->res_x1 = t.test_one(func, t.x1_, it_num, skip_num);
    res->res_x2 = t.test_one(func, t.x2_, it_num, skip_num);
    res->res_x3 = t.test_one(func, t.x3_, it_num, skip_num);
}

void output_results(size_t id, string name, CResults res) {
    cout << id << ") " << name << ":\n";
    cout << res << "\n";
}

int main() {
   freopen("results.txt", "w", stdout);
   NSTests::CTests t(2500);

   cout << "Input data:\n1) Random vector of doubles means (size = 2500).\n"
"2) Vectors of doubles x1 (from 0 to 2500 with step 1), x2 (from 0 to 2500 step 5) and "
"x3 (from 0 to 2500 step 10)." << "\n\n";

   CResults res;
/*
   cout << "Results (number of iterations = " << СCurrentConfiguration::IT_NUM << "):\n";


   // Without tbb and ppl
   fill_results(t, &t.test_density_default_default, СCurrentConfiguration::IT_NUM, &res);
   output_results(1, "Without the use of parallel libraries and SIMD instructions", res);

   fill_results(t, &t.test_density_sse_default, СCurrentConfiguration::IT_NUM, &res);
   output_results(2, "Without the use of parallel libraries and with level of SIMD instructions SSE", res);
*/
   fill_results(t, &t.test_density_avx_default, СCurrentConfiguration::IT_NUM, &res, СCurrentConfiguration::SKIP_NUM);
   output_results(3, "Without the use of parallel libraries and with level of SIMD instructions AVX", res);
/*
   // Tbb
   fill_results(t, &t.test_density_default_tbb, СCurrentConfiguration::IT_NUM, &res);
   output_results(4, "Using TBB library and without use of SIMD instructions", res);

   fill_results(t, &t.test_density_sse_tbb, СCurrentConfiguration::IT_NUM, &res);
   output_results(5, "Using TBB library and and with level of SIMD instructions SSE", res);
*/
   fill_results(t, &t.test_density_avx_tbb, СCurrentConfiguration::IT_NUM, &res, СCurrentConfiguration::SKIP_NUM);
   output_results(6, "Using TBB library and and with level of SIMD instructions AVX", res);
/*
   // PPL
   fill_results(t, &t.test_density_default_ppl, СCurrentConfiguration::IT_NUM, &res);
   output_results(7, "Using PPL library and without use of SIMD instructions", res);

   fill_results(t, &t.test_density_sse_ppl, СCurrentConfiguration::IT_NUM, &res);
   output_results(8, "Using PPL library and and with level of SIMD instructions SSE", res);
*/
   fill_results(t, &t.test_density_avx_ppl, СCurrentConfiguration::IT_NUM, &res, СCurrentConfiguration::SKIP_NUM);
   output_results(9, "Using PPL library and and with level of SIMD instructions AVX", res);
/*
   //std::cout << "AVX_TBB: " <<
     //           std::chrono::duration_cast<std::chrono::microseconds>(res.average_time).count()
       //      << std::endl;

   //res = t.test_one(t.test_density_default_default, t.x1_, 250);

   //std::cout << "DEFAULT_DEFAULT: " <<
     //           std::chrono::duration_cast<std::chrono::microseconds>(res.average_time).count()
       //      << std::endl;
*/

   return 0;
}
