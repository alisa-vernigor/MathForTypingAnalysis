#include "ParallelModulePpl.h"

namespace MathModule {
namespace Parallel {
ParallelModulePpl::ParallelModulePpl() {
    scheduler = Concurrency::Scheduler::Create(Concurrency::SchedulerPolicy{});
    scheduler->Attach();
}

ParallelModulePpl::~ParallelModulePpl() {
    Concurrency::CurrentScheduler::Detach();
}
}
}
