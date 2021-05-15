#ifndef PARALLELMODULEWIN_H
#define PARALLELMODULEWIN_H

#include "Tbb/ParallelModuleTbb.h"
#include "Ppl/ParallelModulePpl.h"

class ParallelModuleWin : public ParallelModuleTbb, ParallelModulePpl {
public:
    ParallelModuleWin();

    template<typename TFunc>
    void parallel_for(
            size_t begin,
            size_t end,
            TFunc func) {

        switch(method_index_) {
          case 0:
              ParallelModuleTbb::parallel_for(begin, end, func);
          break;
          case 1:
             ParallelModulePpl::parallel_for(begin, end, func);
          break;
        }
    }

private:
    size_t method_index_ = 0;
};

#endif // PARALLELMODULEWIN_H
