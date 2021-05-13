#ifndef MATHMODULE_H
#define MATHMODULE_H

#include "ParallelModule.h"
#include "SimdDetector.h"

class MathModuleBase {
private:

};

class MathModule : public MathModuleBase {
private:
    ParallelModule parallel_;
public:
};

#endif // MATHMODULE_H
