#ifndef PARALLELMODULEWIN_H
#define PARALLELMODULEWIN_H

#include "Tbb/ParallelModuleTbb.h"

class ParallelModuleWin : public ParallelModuleTbb, ParallelModulePpl {
    using func_signature = std::function<double(double arg,
        std::vector<double>& parameters)>;
    using ParallelFor = std::function<void(Range range,
                                       func_signature func,
                                       std::vector<double>& grid,
                                       std::vector<double>& output,
                                       std::vector<double>& parameters)>;
public:
    ParallelModuleWin();

    void parallel_for (
            Range range,
            func_signature func,
            std::vector<double>& grid,
            std::vector<double>& output,
            std::vector<double>& parameters) override;


private:
    ParallelFor current_for_method;
};

#endif // PARALLELMODULEWIN_H
