#include "TbbFunction.h"

TbbFunction::TbbFunction(func_signature func,
                         std::vector<double>& means,
                         std::vector<double>& grid):
    func_(func), means_(means), grid_(grid) {}

void TbbFunction::operator()(const tbb::blocked_range<size_t>& r) {
    for (size_t it = r.begin(); it != r.end(); ++it) {
        func_(means_, grid_[it]);
    }
}
