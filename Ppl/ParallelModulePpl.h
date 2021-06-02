#ifndef PARALLELMODULEPPL_H
#define PARALLELMODULEPPL_H

#include "ppl.h"

namespace NSMathModule {
namespace NSParallel {

class CParallelModulePpl {
public:
    CParallelModulePpl();

    template<typename TFunc>
    void parallel_for(
            size_t begin,
            size_t end,
            TFunc func) {
        Concurrency::parallel_for(begin,
                                  end,
                                  [&func](size_t ind){
                                        func(ind);
                                  });
    }
    ~CParallelModulePpl();
private:
     Concurrency::Scheduler *scheduler;
};
}
}
#endif // PARALLELMODULEPPL_H
