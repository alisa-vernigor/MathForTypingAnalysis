#ifndef PARALLELMODULEWIN_H
#define PARALLELMODULEWIN_H

#include "Tbb/ParallelModuleTbb.h"
#include "Ppl/ParallelModulePpl.h"
#include <string>

namespace NSMathModule {
namespace NSParallel {
enum Libs {
    TBB, PPL
};

class ParallelModuleWin : public CParallelModuleTbb, CParallelModulePpl {
public:
    ParallelModuleWin();
    template<typename TFunc>
    void parallel_for(
            size_t begin,
            size_t end,
            TFunc func) {

        switch(method_index_) {
          case 0:
              CParallelModuleTbb::parallel_for(begin, end, func);
          break;
          case 1:
             CParallelModulePpl::parallel_for(begin, end, func);
          break;
        }
    }

    void print_current_lib();
    void switch_lib(Libs lib = Libs::TBB);

private:
    size_t method_index_ = 0;
};
}
}

#endif // PARALLELMODULEWIN_H
