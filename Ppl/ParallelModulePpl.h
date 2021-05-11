#ifndef PARALLELMODULEPPL_H
#define PARALLELMODULEPPL_H

#include "ppl.h"

class ParallelModulePpl {
    using func_signature =
          std::function<void(std::vector<double>& means,
                             double& arg)>;
public:
    ParallelModulePpl();
    void parallel_for(
            size_t begin,
            size_t end,
            func_signature func,
            std::vector<double>& means,
            std::vector<double>& grid);
    ~ParallelModulePpl();
private:
     Concurrency::Scheduler *scheduler;
};
#endif // PARALLELMODULEPPL_H
