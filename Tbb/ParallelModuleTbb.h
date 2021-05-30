#ifndef PARALLELMODULETBB_H
#define PARALLELMODULETBB_H

#include <functional>
#include <tbb/blocked_range.h>
#include <tbb/tbb.h>

namespace MathModule {
namespace Parallel {
class ParallelModuleTbb  {
public:
    ParallelModuleTbb();

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
class EnvInit {
public:
    void operator()(tbb::blocked_range<size_t> &r) const;
    };
};
}
}
#endif // PARALLELMODULETBB_H
