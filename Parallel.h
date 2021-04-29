#ifndef PARALLEL_H
#define PARALLEL_H

#include <functional>
#include <array>
#include <tbb/blocked_range.h>

#include <ppl.h>

class Range {
public:
    Range(size_t new_begin, size_t new_end);
    size_t begin, end;
};

class ParallelModule {
    using func_signature = std::function<double(double arg,
    std::vector<double>& parameters)>;
public:
    virtual void parallel_for(
            Range range,
            func_signature func,
            std::vector<double>& grid,
            std::vector<double>& output,
            std::vector<double>& parameters) = 0;
};


class ParallelModuleTbb : ParallelModule {
    using func_signature = std::function<double(double arg,
    std::vector<double>& parameters)>;
public:
    ParallelModuleTbb();
    void parallel_for(
            Range range,
            func_signature func,
            std::vector<double>& grid,
            std::vector<double>& output,
            std::vector<double>& parameters) override;

private:
class EnvInit {
public:
    void operator()(const tbb::blocked_range<size_t> &r) const;
    };
};

class ParallelModulePpl : ParallelModule {
    using func_signature = std::function<double(double arg,
    std::vector<double>& parameters)>;
public:
    ParallelModulePpl();
    ~ParallelModulePpl();
    void parallel_for(
            Range range,
            func_signature func,
            std::vector<double>& grid,
            std::vector<double>& output,
            std::vector<double>& parameters) override;
private:
     Concurrency::Scheduler *scheduler;
};

class ParallelModuleWin : public ParallelModuleTbb, ParallelModulePpl {
    using func_signature = std::function<double(double arg,
        std::vector<double>& parameters)>;
    using ParallelFor = std::function<void(Range range,
                                       func_signature func,
                                       std::vector<double>& grid,
                                       std::vector<double>& output,
                                       std::vector<double>& parameters)>;
public:
    ParallelModuleWin();

    void parallel_for (
            Range range,
            func_signature func,
            std::vector<double>& grid,
            std::vector<double>& output,
            std::vector<double>& parameters) override;


private:
    ParallelFor current_for_method;
};

#endif // PARALLEL_H
