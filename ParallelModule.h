#ifndef PARALLELMODULE_H
#define PARALLELMODULE_H

#include <QtCore/qglobal.h>

#ifdef Q_OS_WIN
#include "Windows/ParallelModuleWin.h"

using ParallelModule = ParallelModuleWin;

#endif // Q_OS_WIN

#endif // PARALLELMODULE_H
