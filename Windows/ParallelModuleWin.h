#ifndef PARALLELMODULEWIN_H
#define PARALLELMODULEWIN_H

#include "Tbb/ParallelModuleTbb.h"
#include "Ppl/ParallelModulePpl.h"
#include <string>

enum Libs {
    TBB, PPL
};

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

    void print_current_lib();
    void switch_lib(Libs lib = Libs::TBB);

private:
    size_t method_index_ = 0;
};

#endif // PARALLELMODULEWIN_H
