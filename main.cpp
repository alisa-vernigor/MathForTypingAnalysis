#include <iostream>
#include <TbbInit.h>
#include <Parallel.h>

double func(double a, std::vector<double>& v) {
    std::cout << "Jopa" << std::endl;
    return a;
}

int main() {
    ParallelModuleWin obj;
    std::vector<double> v(2000000, 0);
    std::vector<double> v1(2000000, 0);
    std::vector<double> v2(2000000, 0);
    obj.parallel_for(Range(0, 2000000), func, v, v1, v2);
}
