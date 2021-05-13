#ifndef MATHMODULE_H
#define MATHMODULE_H

#include "ParallelModule.h"
#include "SimdDetector.h"
#include "Functions/Function.h"

class MathModuleBase {
public:
    NSSimd::SimdDetector detect_;
};

class MathModule : private MathModuleBase {
public:
    MathModule();
private:
    ParallelModule parallel_;
    Function func_;
};

#endif // MATHMODULE_H
