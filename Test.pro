TEMPLATE = app
CONFIG += c++17 rtti_off warn_on console
CONFIG -= app_bundle
CONFIG -= qt

# Make warning level to be W4
win32-msvc* {
    # Visual Studio flags
    QMAKE_CXXFLAGS_WARN_ON ~= s/-W./-W4
}

# Exception handling model for MSVC
# Required for PPL
win32-msvc* {
    QMAKE_CXXFLAGS += -EHsc
}

win32-g++*{
    # MinGW flags
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Parallel.cpp \
        ParallelModuleWin.cpp \
        Ppl/ParallelModulePpl.cpp \
        Tbb/ParallelModuleTbb.cpp \
        Tbb/TbbFunction.cpp \
        TbbFunction.cpp \
        main.cpp \
        SimdDetector.cpp \
        vectorclass/instrset_detect.cpp


INCLUDEPATH += "C:\Program Files (x86)\Intel\oneAPI\tbb\2021.1.1\include"
LIBS += "C:\Program Files (x86)\Intel\oneAPI\tbb\2021.1.1\lib\intel64\vc_mt\tbb.lib"
LIBS += "C:\Program Files (x86)\Intel\oneAPI\tbb\2021.1.1\lib\intel64\vc_mt\tbb12.lib"
LIBS += "C:\Program Files (x86)\Intel\oneAPI\tbb\2021.1.1\lib\intel64\vc_mt\tbb_debug.lib"
LIBS += "C:\Program Files (x86)\Intel\oneAPI\tbb\2021.1.1\lib\intel64\vc_mt\tbb12_debug.lib"
LIBS += "C:\Program Files (x86)\Intel\oneAPI\tbb\2021.1.1\lib\intel64\vc_mt\tbbbind.lib"
LIBS += "C:\Program Files (x86)\Intel\oneAPI\tbb\2021.1.1\lib\intel64\vc_mt\tbbbind_2_0.lib"
LIBS += "C:\Program Files (x86)\Intel\oneAPI\tbb\2021.1.1\lib\intel64\vc_mt\tbbbind_2_0_debug.lib"
LIBS += "C:\Program Files (x86)\Intel\oneAPI\tbb\2021.1.1\lib\intel64\vc_mt\tbbbind_debug.lib"
LIBS += "C:\Program Files (x86)\Intel\oneAPI\tbb\2021.1.1\lib\intel64\vc_mt\tbbmalloc.lib"
LIBS += "C:\Program Files (x86)\Intel\oneAPI\tbb\2021.1.1\lib\intel64\vc_mt\tbbmalloc_debug.lib"
LIBS += "C:\Program Files (x86)\Intel\oneAPI\tbb\2021.1.1\lib\intel64\vc_mt\tbbmalloc_proxy.lib"
LIBS += "C:\Program Files (x86)\Intel\oneAPI\tbb\2021.1.1\lib\intel64\vc_mt\tbbmalloc_proxy_debug.lib"
LIBS += -L"$$PWD/dll/*.dll"

HEADERS += \
    MathModule.h \
    Parallel.h \
    ParallelModuleWin.h \
    Ppl/ParallelModulePpl.h \
    Tbb/ParallelModuleTbb.h \
    Tbb/TbbFunction.h \
    TbbFunction.h\
    SimdDetector.h
    Selector.h

win32 {
    HEADERS += Windows/ParallelModuleWin.h

    SOURCES += Windows/ParallelModuleWin.cpp
}

# A custom compiler
# The compiler compiles on AVX level
SOURCES_AVX = PrintIntAVX.cpp MathFunctionExecuterAVX.cpp
AVX_FLAGS =
win32-msvc*:AVX_FLAGS = /arch:AVX
AVX_OUT =
win32-msvc*:AVX_OUT = /Fo${QMAKE_FILE_OUT}
avx_compiler.name = avx_compiler
avx_compiler.input = SOURCES_AVX
avx_compiler.dependency_type = TYPE_C
avx_compiler.variable_out = OBJECTS
avx_compiler.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
avx_compiler.commands = $${QMAKE_CXX} $(CXXFLAGS) $${AVX_FLAGS} $(INCPATH) -c ${QMAKE_FILE_IN} $${AVX_OUT}
QMAKE_EXTRA_COMPILERS += avx_compiler

# A custom compiler
# The compiler compiles on AVX2 level
SOURCES_AVX2 = PrintIntAVX2.cpp MathFunctionExecuterAVX2.cpp
AVX2_FLAGS =
win32-msvc*:AVX2_FLAGS = /arch:AVX2
AVX2_OUT =
win32-msvc*:AVX2_OUT = /Fo${QMAKE_FILE_OUT}
avx2_compiler.name = avx2_compiler
avx2_compiler.input = SOURCES_AVX2
avx2_compiler.dependency_type = TYPE_C
avx2_compiler.variable_out = OBJECTS
avx2_compiler.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
avx2_compiler.commands = $${QMAKE_CXX} $(CXXFLAGS) $${AVX2_FLAGS} $(INCPATH) -c ${QMAKE_FILE_IN} $${AVX2_OUT}
QMAKE_EXTRA_COMPILERS += avx2_compiler
