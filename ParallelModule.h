#ifndef PARALLELMODULE_H
#define PARALLELMODULE_H

#include <QtCore/qglobal.h>

#ifdef Q_OS_WIN
#include "Windows/ParallelModuleWin.h"
namespace NSMathModule {
namespace NSParallel {
using СParallelModule = ParallelModuleWin;
}
}

#endif // Q_OS_WIN

#endif // PARALLELMODULE_H
