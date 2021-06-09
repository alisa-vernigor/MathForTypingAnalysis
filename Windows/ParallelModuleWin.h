#ifndef PARALLELMODULEWIN_H
#define PARALLELMODULEWIN_H

#include "Tbb/ParallelModuleTbb.h"
#include "Ppl/ParallelModulePpl.h"
#include <string>

namespace NSMathModule {
namespace NSParallel {

enum class EParallelLibrary : unsigned char {
  Tbb = 0,
  Ppl = 1
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
          case EParallelLibrary::Tbb:
              CParallelModuleTbb::parallel_for(begin, end, func);
          break;
          case EParallelLibrary::Ppl:
             CParallelModulePpl::parallel_for(begin, end, func);
          break;
        }
    }

    void print_current_lib();
    void switch_lib(EParallelLibrary lib = EParallelLibrary::Tbb);

private:
    EParallelLibrary method_index_ = EParallelLibrary::Tbb;
};
}
}

#endif // PARALLELMODULEWIN_H
