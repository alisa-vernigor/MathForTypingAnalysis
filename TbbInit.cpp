#include <TbbInit.h>

#include <tbb/parallel_for.h>
#include <iostream>

size_t TbbInit::default_init_iter_num = 1000;

void TbbInit::EnvInit::operator()(const tbb::blocked_range<size_t>& r) const {
    size_t p = 1;
    for (size_t it = r.begin(); it != r.end(); ++it) {
      for(size_t i = 0; i < 10000; ++i) {
          for (size_t j = 0; j < 100; ++j) {
         p += i * j;
          }
      }
    }
}

TbbInit::TbbInit(size_t iter_num) {
    tbb::parallel_for(tbb::blocked_range<size_t>(0, iter_num),
                      TbbInit::EnvInit());
}
