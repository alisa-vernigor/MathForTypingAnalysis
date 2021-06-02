#include "ParallelModulePpl.h"

namespace NSMathModule {
namespace NSParallel {
CParallelModulePpl::CParallelModulePpl() {
    scheduler = Concurrency::Scheduler::Create(Concurrency::SchedulerPolicy{});
    scheduler->Attach();
}

CParallelModulePpl::~CParallelModulePpl() {
    Concurrency::CurrentScheduler::Detach();
}
}
}
