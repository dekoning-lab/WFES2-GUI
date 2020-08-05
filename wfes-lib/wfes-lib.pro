include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

QT -= gui

TARGET = wfes-lib
TEMPLATE = lib

CONFIG += c++11

DEFINES += WFESLIB_LIBRARY

INCLUDEPATH += source \
    ../dependencies \
    ../dependencies/intel/mkl/include

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
    source/config/config.h \
    source/controllers/outputController.h \
    source/model/pardiso/MKL_Consts.h \
    source/model/pardiso/solverPardiso.h \
    source/model/solver/solver.h \
    source/model/solver/solverFactory.h \
    source/model/sparse-matrix/sparseMatrix.h \
    source/model/sparse-matrix/sparseMatrixFactory.h \
    source/model/pardiso/sparseMatrixPardiso.h \
    source/model/wfes_single.h \
    source/model/wright-fisher/rdist.h \
    source/model/wright-fisher/wrightFisher.h \
    source/results/results.h \
    source/utils/exceptions.h \
    source/utils/parsing.h \
    source/utils/types.h \
    source/utils/utils.h \
    wfes-lib_global.h \
    source/wfesLib.h

SOURCES += \
    source/config/config.cpp \
    source/controllers/outputController.cpp \
    source/model/pardiso/solverPardiso.cpp \
    source/model/solver/solver.cpp \
    source/model/solver/solverFactory.cpp \
    source/model/sparse-matrix/sparseMatrix.cpp \
    source/model/sparse-matrix/sparseMatrixFactory.cpp \
    source/model/pardiso/sparseMatrixPardiso.cpp \
    source/model/wfes_single.cpp \
    source/model/wright-fisher/rdist.cpp \
    source/model/wright-fisher/wrightFisher.cpp \
    source/results/results.cpp \
    source/utils/parsing.cpp \
    source/utils/utils.cpp \
    source/wfesLib.cpp

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
