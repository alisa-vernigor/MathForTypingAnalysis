#include <iostream>

#include <MathModule.h>

#include <vector>

#include <Tests/tests.h>

int main() {
   Tests t(2500);
   Result res = t.test_one(t.test_density_avx_tbb, t.x1_, 250);

   std::cout << "AVX_TBB: " <<
                std::chrono::duration_cast<std::chrono::microseconds>(res.average_time).count()
             << std::endl;

   res = t.test_one(t.test_density_default_default, t.x1_, 250);

   std::cout << "DEFAULT_DEFAULT: " <<
                std::chrono::duration_cast<std::chrono::microseconds>(res.average_time).count()
             << std::endl;
}
