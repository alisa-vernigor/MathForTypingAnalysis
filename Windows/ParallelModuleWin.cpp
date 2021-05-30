#include "Windows/ParallelModuleWin.h"
#include <iostream>

namespace MathModule {
namespace Parallel {

ParallelModuleWin::ParallelModuleWin(): method_index_(0){}

void ParallelModuleWin::print_current_lib() {
    if (method_index_ == 0) {
        std::cout << "TBB" << std::endl;
    } else {
        std::cout << "PPL" << std::endl;
    }
}

void ParallelModuleWin::switch_lib(Libs lib) {
    if (lib == Libs::TBB) {
        method_index_ = 0;
    } else {
        method_index_ = 1;
    }
}
}
}
