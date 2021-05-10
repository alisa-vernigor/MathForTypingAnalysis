#ifndef PARALLELMODULETBB_H
#define PARALLELMODULETBB_H

#include <functional>
#include <tbb/blocked_range.h>
#include <tbb/tbb.h>

class ParallelModuleTbb  {
    using func_signature =
          std::function<void(std::vector<double>& means,
                             double& arg)>;
public:
    ParallelModuleTbb();
    void parallel_for(
            size_t begin,
            size_t end,
            func_signature func,
            std::vector<double>& means,
            std::vector<double>& grid);

private:
class EnvInit {
public:
    void operator()(const tbb::blocked_range<size_t> &r) const;
    };
};
#endif // PARALLELMODULETBB_H
