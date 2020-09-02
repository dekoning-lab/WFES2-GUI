include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

QT += testlib
QT -= gui

TARGET = wfes-tests
TEMPLATE = app

CONFIG += C++11
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

INCLUDEPATH += source \
    ../wfes-lib/source \
    ../wfes-lib \

LIBS += -L$$PWD/../binaries/$$DESTINATION_PATH -lwfes-lib

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

SOURCES +=  \
    source/main.cpp \
    source/model/pardiso/testSparseMatrixPardiso.cpp \
    source/model/viennacl/testSparseMatrixViennaCL.cpp \
    source/model/viennacl/testSolverViennacl.cpp \
    source/testsuite.cpp

HEADERS += \
    source/model/pardiso/testSparseMatrixPardiso.h \
    source/model/viennacl/testSolverViennacl.h \
    source/model/viennacl/testSparseMatrixViennaCL.h \
    source/testsuite.h

unix {

    # TODO Change for compatibility with mac and windows
    LIBS +=  -L$$PWD/../dependencies/unix/intel/mkl/lib/intel64 -Wl,--no-as-needed -lmkl_intel_ilp64 -lmkl_intel_thread -lmkl_core -lpthread -lm -ldl
    LIBS +=  -L$$PWD/../dependencies/unix/intel/lib/intel64 -Wl,--no-as-needed -liomp5
    LIBS += -L$$PWD/../dependencies/unix/CL/lib/linux/ -lOpenCL

    INCLUDEPATH += \
        $$PWD/../dependencies/unix \
        $$PWD/../dependencies/unix/intel/mkl/include \
        $$PWD/../dependencies/unix/CL

    DEPENDPATH += $$PWD/../dependencies/unix/CL
}
