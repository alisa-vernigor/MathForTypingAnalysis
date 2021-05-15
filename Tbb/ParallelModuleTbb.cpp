#include "Tbb/ParallelModuleTbb.h"

ParallelModuleTbb::ParallelModuleTbb() {
    tbb::parallel_for(tbb::blocked_range<size_t>(0, 1000),
                      ParallelModuleTbb::EnvInit());
}

void ParallelModuleTbb::EnvInit::operator()(tbb::blocked_range<size_t>& r) const {
    size_t p = 1;
    for (size_t it = r.begin(); it != r.end(); ++it) {
      for(size_t i = 0; i < 10000; ++i) {
          for (size_t j = 0; j < 100; ++j) {
         p += i * j;
          }
      }
    }
}
