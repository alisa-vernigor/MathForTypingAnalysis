#include "ParallelModulePpl.h"

ParallelModulePpl::ParallelModulePpl() {
    scheduler = Concurrency::Scheduler::Create(Concurrency::SchedulerPolicy{});
    scheduler->Attach();
}

ParallelModulePpl::~ParallelModulePpl() {
    Concurrency::CurrentScheduler::Detach();
}

void ParallelModulePpl::parallel_for(
        size_t begin,
        size_t end,
        func_signature func,
        std::vector<double>& means,
        std::vector<double>& grid)  {
    Concurrency::parallel_for(begin,
                              end,
                              [&grid, &means, &func](size_t ind){
                                    func(means, grid[ind]);
                              });
}
