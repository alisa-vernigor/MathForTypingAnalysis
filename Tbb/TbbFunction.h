#ifndef TBBFUNCTION_H
#define TBBFUNCTION_H

#include <functional>
#include <tbb/blocked_range.h>

class TbbFunction {
    using func_signature =
          std::function<void(std::vector<double>& means,
                             double& arg)>;
public:
    TbbFunction( func_signature func,
                 std::vector<double>& means,
                 std::vector<double>& grid);

    void operator()(const tbb::blocked_range<size_t>& r);


private:
    func_signature func_;
    std::vector<double>& means_;
    std::vector<double>& grid_;
};

#endif // TBBFUNCTION_H
