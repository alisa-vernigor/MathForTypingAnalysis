#ifndef TBBINIT_H
#define TBBINIT_H

#include "tbb/blocked_range.h"

class TbbInit {
public:
    TbbInit(size_t iter_num = default_init_iter_num);

private:
    static size_t default_init_iter_num;

    class EnvInit {
    public:
        void operator()(const tbb::blocked_range<size_t> &r) const;
    };
};

#endif // TBBINIT_H
