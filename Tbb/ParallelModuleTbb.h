#ifndef PARALLELMODULETBB_H
#define PARALLELMODULETBB_H

#include <functional>
#include <tbb/blocked_range.h>
#include <tbb/tbb.h>

namespace NSMathModule {
namespace NSParallel {
class CParallelModuleTbb  {
public:
    CParallelModuleTbb(size_t init_iter = kdefault_init_iter_num);

    template<typename TFunc>
    void parallel_for(
            size_t begin,
            size_t end,
            TFunc func) {
        tbb::parallel_for(
                    tbb::blocked_range<size_t>(begin, end),
                    [&func](tbb::blocked_range<size_t>& r) {
            for (size_t it = r.begin(); it != r.end(); ++it) {
                func(it);
            }
        });
    }

private:
    static constexpr size_t kdefault_init_iter_num = 1000;
};
}
}
#endif // PARALLELMODULETBB_H
