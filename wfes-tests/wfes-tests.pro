include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

QT += testlib
QT -= gui

TARGET = wfes-tests
TEMPLATE = app

CONFIG += C++14
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

INCLUDEPATH += source \
    ../wfes-lib/source \
    ../wfes-lib

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

LIBS += -L$$PWD/../binaries/$$DESTINATION_PATH -lwfes-lib

SOURCES +=  \
    source/main.cpp \
    #source/model/pardiso/testSparseMatrixPardiso.cpp \
    source/model/viennacl/testSparseMatrixViennaCL.cpp \
    source/model/viennacl/testSolverViennacl.cpp \
    source/testsuite.cpp

HEADERS += \
    #source/model/pardiso/testSparseMatrixPardiso.h \
    source/model/viennacl/testSolverViennacl.h \
    source/model/viennacl/testSparseMatrixViennaCL.h \
    source/testsuite.h

# Default rules for deployment.
unix {
    # TODO Change for compatibility with mac and windows
    LIBS += -L$$PWD/../dependencies/unix/CL/lib/linux/ -lOpenCL
    LIBS += -L$$PWD/../dependencies/unix/pardiso-project/ -lpardiso600-GNU800-X86-64
    LIBS += -L$$PWD/../dependencies/unix/openblas/lib/ -lopenblas

    INCLUDEPATH += \
        $$PWD/../dependencies/unix \
        $$PWD/../dependencies/unix/CL \
        $$PWD/../dependencies/unix/openblas/include \
        $$PWD/../dependencies/unix/pardiso-project \
        $$PWD/source

    DEPENDPATH += $$PWD/../dependencies/unix/pardiso-project
    DEPENDPATH += $$PWD/../dependencies/unix/openblas/include
    DEPENDPATH += $$PWD/../dependencies/unix/CL

    PRE_TARGETDEPS += $$PWD/../dependencies/unix/openblas/lib/libopenblas.a
}


win32 {

    INCLUDEPATH += $$PWD/source/
    INCLUDEPATH += $$PWD/../dependencies/windows/

    # OpenCL
    LIBS += -L$$PWD/../dependencies/windows/CL/lib/ -lOpenCL
    INCLUDEPATH += $$PWD/../dependencies/windows/CL
    DEPENDPATH += $$PWD/../dependencies/windows/CL

    # Intel MKL
    LIBS += -L$$PWD/../dependencies/windows/intel/mkl/lib/intel64_win/ -Wl,--no-as-needed -lmkl_core_dll
    LIBS += -L$$PWD/../dependencies/windows/intel/mkl/lib/intel64_win/ -Wl,--no-as-needed -lmkl_intel_ilp64_dll
    LIBS += -L$$PWD/../dependencies/windows/intel/mkl/lib/intel64_win/ -Wl,--no-as-needed -lmkl_intel_thread_dll
    LIBS += -L$$PWD/../dependencies/windows/intel/mkl/compiler/ -Wl,--no-as-needed -llibiomp5md
    INCLUDEPATH += $$PWD/../dependencies/windows/intel/mkl/include
    DEPENDPATH += $$PWD/../dependencies/windows/intel/mkl/include

}


