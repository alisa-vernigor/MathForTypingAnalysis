#ifndef PARALLELMODULEWIN_H
#define PARALLELMODULEWIN_H

#include "Tbb/ParallelModuleTbb.h"
#include "Ppl/ParallelModulePpl.h"

class ParallelModuleWin : public ParallelModuleTbb, ParallelModulePpl {
    using func_signature =
          std::function<void(std::vector<double>& means,
                             double& arg)>;

    using ParallelFor = std::function<void(size_t begin,
                                    size_t end,
                                    func_signature func,
                                    std::vector<double>& means,
                                    std::vector<double>& grid)>;
public:
    ParallelModuleWin();
    void parallel_for(
            size_t begin,
            size_t end,
            func_signature func,
            std::vector<double>& means,
            std::vector<double>& grid);

private:
    ParallelFor current_for_method;
};

#endif // PARALLELMODULEWIN_H
