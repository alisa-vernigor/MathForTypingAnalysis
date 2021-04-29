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
        TbbFunction.cpp \
        main.cpp

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
    Parallel.h \
    TbbFunction.h
