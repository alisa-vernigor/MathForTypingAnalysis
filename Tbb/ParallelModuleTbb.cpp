#include "Tbb/ParallelModuleTbb.h"
#include "Tbb/TbbFunction.h"

void ParallelModuleTbb::parallel_for(
        size_t begin,
        size_t end,
        func_signature func,
        std::vector<double>& means,
        std::vector<double>& grid) {
    tbb::parallel_for(
                tbb::blocked_range<size_t>(begin, end),
                TbbFunction(func, means, grid));
}

ParallelModuleTbb::ParallelModuleTbb() {
    tbb::parallel_for(tbb::blocked_range<size_t>(0, 1000), ParallelModuleTbb::EnvInit());
}
