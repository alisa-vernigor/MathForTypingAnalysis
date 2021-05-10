#ifndef PARALLELMODULEPPL_H
#define PARALLELMODULEPPL_H

#include "ppl.h"

class ParallelModulePpl {
    using func_signature =
    std::function<void(double arg,
    std::vector<double>& parameters)>;

public:
    ParallelModulePpl();
    ~ParallelModulePpl();
    void parallel_for(
            Range range,
            func_signature func,
            std::vector<double>& grid,
            std::vector<double>& output,
            std::vector<double>& parameters) override;
private:
     Concurrency::Scheduler *scheduler;
};
#endif // PARALLELMODULEPPL_H
