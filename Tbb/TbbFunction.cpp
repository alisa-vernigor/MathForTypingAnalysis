#include "Tbb/TbbFunction.h"

TbbFunction::TbbFunction(func_signature func,
                         std::vector<double>& means,
                         std::vector<double>& grid):
    func_(func), means_(means), grid_(grid) {}

void TbbFunction::operator()(tbb::blocked_range<size_t>& r) const {
    for (size_t it = r.begin(); it != r.end(); ++it) {
        func_(means_, grid_[it]);
    }
}
