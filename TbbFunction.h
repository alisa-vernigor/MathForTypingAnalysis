#ifndef FUNCTION_H
#define FUNCTION_H

#include <functional>
#include "tbb/blocked_range.h"

class TbbFunction {
    using func_signature = std::function<double(double arg,
    std::vector<double>& parameters)>;
public:
    TbbFunction(func_signature new_func,
             std::vector<double>& new_grid,
             std::vector<double>& new_output,
             std::vector<double>& new_parameters);

    void operator()(tbb::blocked_range<size_t>&) const;

private:
    func_signature func;
    std::vector<double>& grid;
    std::vector<double>& output;
    std::vector<double>& parameters;
};

#endif // FUNCTION_H
