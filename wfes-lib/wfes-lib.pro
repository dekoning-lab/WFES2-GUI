include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

QT += gui

TARGET = wfes-lib
TEMPLATE = lib

CONFIG += c++11

DEFINES += WFESLIB_LIBRARY

QMAKE_CXXFLAGS += -DMKL_ILP64 -m64

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    source/model/executables/wfes_single/config/configWfesSingle.h \
    source/model/executables/wfes_single/controllers/inputControllerWfesSingle.h \
    source/model/executables/wfes_single/controllers/outputControllerWfesSingle.h \
    source/model/pardiso/MKL_Consts.h \
    source/model/pardiso/solverPardiso.h \
    source/model/solver/solver.h \
    source/model/solver/solverFactory.h \
    source/model/sparse-matrix/sparseMatrix.h \
    source/model/sparse-matrix/sparseMatrixFactory.h \
    source/model/pardiso/sparseMatrixPardiso.h \
    source/model/viennacl/solverViennaCL.h \
    source/model/viennacl/sparseMatrixViennacl.h \
    source/model/executables/wfes_single/wfes_single.h \
    source/model/wright-fisher/rdist.h \
    source/model/wright-fisher/wrightFisher.h \
    source/model/executables/wfes_single/results/resultsWfesSingle.h \
    source/model/executables/wfes_single/thread/threadwfessingle.h \
    source/utils/exceptions.h \
    source/utils/observer/observer.h \
    source/utils/observer/subject.h \
    source/utils/parsing.h \
    source/utils/types.h \
    source/utils/utils.h \
    wfes-lib_global.h

SOURCES += \
    source/model/executables/wfes_single/config/configWfesSingle.cpp \
    source/model/executables/wfes_single/controllers/inputControllerWfesSingle.cpp \
    source/model/executables/wfes_single/controllers/outputControllerWfesSingle.cpp \
    source/model/pardiso/solverPardiso.cpp \
    source/model/solver/solver.cpp \
    source/model/solver/solverFactory.cpp \
    source/model/sparse-matrix/sparseMatrix.cpp \
    source/model/sparse-matrix/sparseMatrixFactory.cpp \
    source/model/pardiso/sparseMatrixPardiso.cpp \
    source/model/viennacl/solverViennaCL.cpp \
    source/model/viennacl/sparseMatrixViennacl.cpp \
    source/model/executables/wfes_single/wfes_single.cpp \
    source/model/wright-fisher/rdist.cpp \
    source/model/wright-fisher/wrightFisher.cpp \
    source/model/executables/wfes_single/results/resultsWfesSingle.cpp \
    source/model/executables/wfes_single/thread/threadwfessingle.cpp \
    source/utils/observer/observer.cpp \
    source/utils/observer/subject.cpp \
    source/utils/parsing.cpp \
    source/utils/utils.cpp

# Default rules for deployment.
unix {
    target.path = /usr/lib

    INCLUDEPATH += source \
        $$PWD/../dependencies/unix \
        $$PWD/../dependencies/unix/intel/mkl/include

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

!isEmpty(target.path): INSTALLS += target
