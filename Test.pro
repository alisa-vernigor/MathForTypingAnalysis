TEMPLATE = app
CONFIG += c++17 rtti_off warn_on console
CONFIG -= app_bundle

QT += core gui

# Make warning level to be W4
win32-msvc* {
    # Visual Studio flags
    QMAKE_CXXFLAGS_WARN_ON ~= s/-W./-W4
}

SOURCES += main.cpp \
    Functions/Function.cpp \
    Functions/FunctionSSE2.cpp \
        MathModule.cpp \
        SimdDetector.cpp \
    Tests/tests.cpp \
        vectorclass/instrset_detect.cpp \
        TimeMeasurer.cpp


# Exception handling model for MSVC
# Required for PPL
win32-msvc* {
    QMAKE_CXXFLAGS += -EHsc

    # A custom compiler
    # The compiler compiles on AVX level
    SOURCES_AVX += Functions/FunctionAVX.cpp
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
    SOURCES_AVX += Functions/FunctionAVX2.cpp
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
}

win32-g++*{
    # MinGW flags
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TBBPATH = "C:\Program Files (x86)\Intel\oneAPI\tbb\latest"
INCLUDEPATH += $${TBBPATH}"\include"
LIBS += "-L"$${TBBPATH}"\lib\intel64\vc_mt"
LIBS += -L"$$PWD/dll/*.dll"

HEADERS += \
    Functions/Function.h \
    MathModule.h \
    ParallelModule.h \
    SimdDetector.h\
    Functions/Selector.h \
    Functions/ElementList.h \
    Functions/FunctionHelper.h \
    Functions/FunctionModuleBase.h \
    Functions/NullType.h \
    Functions/TypeList.h \
    Functions/MathFunction.h \
    Functions/InstructionLevels.h \
    Tests/tests.h \
    TimeMeasurer.h \
    InstructionLevels.h

win32 {
    HEADERS += Windows/ParallelModuleWin.h \
            Ppl/ParallelModulePpl.h \
            Tbb/ParallelModuleTbb.h \

    SOURCES += Windows/ParallelModuleWin.cpp \
            Ppl/ParallelModulePpl.cpp \
            Tbb/ParallelModuleTbb.cpp \
}
