#include "Windows/ParallelModuleWin.h"

ParallelModuleWin::ParallelModuleWin() {
    current_for_method = [this](size_t begin,
            size_t end,
            func_signature func,
            std::vector<double>& means,
            std::vector<double>& grid) {
                this->ParallelModuleTbb::parallel_for(begin, end, func, means, grid);
            };
}

void ParallelModuleWin::parallel_for(
            size_t begin,
            size_t end,
            func_signature func,
            std::vector<double>& means,
            std::vector<double>& grid
        ) {
    current_for_method(begin, end, func, means, grid);
}

