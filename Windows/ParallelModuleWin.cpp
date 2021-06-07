#include "Windows/ParallelModuleWin.h"
#include <iostream>

namespace NSMathModule {
namespace NSParallel {

ParallelModuleWin::ParallelModuleWin(): method_index_(EParallelLibrary::Tbb){}

void ParallelModuleWin::print_current_lib() {
    if (method_index_ == EParallelLibrary::Tbb) {
        std::cout << "TBB" << std::endl;
    } else {
        std::cout << "PPL" << std::endl;
    }
}

void ParallelModuleWin::switch_lib(EParallelLibrary lib) {
    method_index_ = lib;
}
}
}
