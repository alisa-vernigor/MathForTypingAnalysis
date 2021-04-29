#include "TbbFunction.h"


TbbFunction::TbbFunction(func_signature new_func,
         std::vector<double>& new_grid,
         std::vector<double>& new_output,
         std::vector<double>& new_parameters):
    func(new_func), grid(new_grid), output(new_output),
    parameters(new_parameters){}

void TbbFunction::operator()(tbb::blocked_range<size_t>& r) const {
    for (size_t it = r.begin(); it != r.end(); ++it) {
        output[it] += func(grid[it], parameters);
    }
}
