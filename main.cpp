#include <iostream>
#include <TbbInit.h>
#include "Windows/ParallelModuleWin.h"

void func(std::vector<double>& v, double& a) {
    std::cout << "Test" << std::endl;
}

int main() {
    ParallelModuleWin obj;
    std::vector<double> v(2000000, 0);
    std::vector<double> v1(2000000, 0);
    std::vector<double> v2(2000000, 0);
    //obj.parallel_for(0, 2000000, func, v, v1);
}
