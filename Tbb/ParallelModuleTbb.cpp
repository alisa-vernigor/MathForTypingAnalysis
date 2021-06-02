#include "Tbb/ParallelModuleTbb.h"

namespace NSMathModule {
namespace NSParallel {
CParallelModuleTbb::CParallelModuleTbb(size_t init_iter) {
    tbb::parallel_for(tbb::blocked_range<size_t>(0, init_iter),
                      [](tbb::blocked_range<size_t>& r) {
                        size_t p = 1;
                        for (size_t it = r.begin(); it != r.end(); ++it) {
                          for(size_t i = 0; i < 10000; ++i) {
                              for (size_t j = 0; j < 100; ++j) {
                                    p += i * j;
                               }
                            }
                           }
                         });

}

}
}
