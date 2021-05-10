#include "Parallel.h"
#include "TbbFunction.h"

#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"

#include <ppl.h>

Range::Range(size_t new_begin, size_t new_end):
    begin(new_begin),
    end(new_end) {}

void ParallelModuleTbb::EnvInit::operator()(const tbb::blocked_range<size_t>& r) const {
    size_t p = 1;
    for (size_t it = r.begin(); it != r.end(); ++it) {
      for(size_t i = 0; i < 10000; ++i) {
          for (size_t j = 0; j < 100; ++j) {
         p += i * j;
          }
      }
    }
}

ParallelModuleTbb::ParallelModuleTbb() {
    tbb::parallel_for(tbb::blocked_range<size_t>(0, 1000), ParallelModuleTbb::EnvInit());
}

ParallelModulePpl::ParallelModulePpl() {
    scheduler = Concurrency::Scheduler::Create(Concurrency::SchedulerPolicy{});
    scheduler->Attach();
}

ParallelModulePpl::~ParallelModulePpl() {
    Concurrency::CurrentScheduler::Detach();
}

void ParallelModulePpl::parallel_for(
        Range range,
        func_signature func,
        std::vector<double>& grid,
        std::vector<double>& output,
        std::vector<double>& parameters) {
    Concurrency::parallel_for(range.begin,
                              range.end,
                              [&grid, &output, &func, &parameters](size_t id){
                                    output[id] = func(grid[id], parameters);
                              });
}

ParallelModuleWin::ParallelModuleWin() {
    current_for_method = [this](Range range,
            func_signature func,
            std::vector<double>& grid,
            std::vector<double>& output,
            std::vector<double>& parameters) {
                this->ParallelModuleTbb::parallel_for(range, func, grid, output, parameters);
            };
}

void ParallelModuleWin::parallel_for(
        Range range,
        func_signature func,
        std::vector<double>& grid,
        std::vector<double>& output,
        std::vector<double>& parameters
        ) {
    current_for_method(range, func, grid, output, parameters);
}
