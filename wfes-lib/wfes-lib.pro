include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

QT += gui quick charts svg

TARGET = wfes-lib
TEMPLATE = lib

CONFIG += c++11 optimize_full

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
    source/model/config/globalConfiguration.h \
    source/model/config/systemoperations.h \
    source/model/executables/phase_type/config/configPhaseType.h \
    source/model/executables/phase_type/controllers/inputControllerPhaseType.h \
    source/model/executables/phase_type/controllers/outputControllerPhaseType.h \
    source/model/executables/phase_type/phase_type.h \
    source/model/executables/phase_type/results/resultsPhaseType.h \
    source/model/executables/phase_type/thread/workerThreadPhaseType.h \
    source/model/executables/time_dist/config/configTimeDist.h \
    source/model/executables/time_dist/config/configTimeDistSGV.h \
    source/model/executables/time_dist/controllers/inputControllerTimeDist.h \
    source/model/executables/time_dist/controllers/outputControllerTimeDist.h \
    source/model/executables/time_dist/results/resultsTimeDist.h \
    source/model/executables/time_dist/thread/workerThreadTimeDist.h \
    source/model/executables/time_dist/time_dist.h \
    source/model/executables/wfafd/config/configWfafd.h \
    source/model/executables/wfafd/controllers/inputControllerWfafd.h \
    source/model/executables/wfafd/controllers/outputControllerWfafd.h \
    source/model/executables/wfafd/results/resultsWfafd.h \
    source/model/executables/wfafd/thread/workerThreadWfafd.h \
    source/model/executables/wfafd/wfafd.h \
    source/model/executables/wfafs/config/configWfafs.h \
    source/model/executables/wfafs/controllers/inputControllerWfafs.h \
    source/model/executables/wfafs/controllers/outputControllerWfafs.h \
    source/model/executables/wfafs/results/resultsWfafs.h \
    source/model/executables/wfafs/thread/workerThreadWfafs.h \
    source/model/executables/wfafs/wfafs.h \
    source/model/executables/wfes_sequential/config/configWfesSequential.h \
    source/model/executables/wfes_sequential/controllers/inputControllerWfesSequential.h \
    source/model/executables/wfes_sequential/controllers/outputControllerWfesSequential.h \
    source/model/executables/wfes_sequential/results/resultsWfesSequential.h \
    source/model/executables/wfes_sequential/thread/workerThreadWfesSequential.h \
    source/model/executables/wfes_sequential/wfes_sequential.h \
    source/model/executables/wfes_single/config/configWfesSingle.h \
    source/model/executables/wfes_single/controllers/inputControllerWfesSingle.h \
    source/model/executables/wfes_single/controllers/outputControllerWfesSingle.h \
    source/model/executables/wfes_single/thread/workerThreadWfesSingle.h \
    source/model/executables/wfes_sweep/config/configWfesSweep.h \
    source/model/executables/wfes_sweep/controllers/inputControllerWfesSweep.h \
    source/model/executables/wfes_sweep/controllers/outputControllerWfesSweep.h \
    source/model/executables/wfes_sweep/results/resultsWfesSweep.h \
    source/model/executables/wfes_sweep/thread/workerThreadWfesSweep.h \
    source/model/executables/wfes_sweep/wfes_sweep.h \
    source/model/executables/wfes_switching/config/configWfesSwitching.h \
    source/model/executables/wfes_switching/controllers/inputControllerWfesSwitching.h \
    source/model/executables/wfes_switching/controllers/outputControllerWfesSwitching.h \
    source/model/executables/wfes_switching/results/resultsWfesSwitching.h \
    source/model/executables/wfes_switching/thread/workerThreadWfesSwitching.h \
    source/model/executables/wfes_switching/wfes_switching.h \
    source/model/solver/pardiso/MKL_Consts.h \
    source/model/solver/pardiso/solverPardiso.h \
    source/model/solver/solver.h \
    source/model/solver/solverFactory.h \
    source/model/sparse-matrix/sparseMatrix.h \
    source/model/sparse-matrix/sparseMatrixFactory.h \
    source/model/sparse-matrix/pardiso/sparseMatrixPardiso.h \
    source/model/solver/viennacl/solverViennaCL.h \
    source/model/sparse-matrix/viennacl/sparseMatrixViennacl.h \
    source/model/executables/wfes_single/wfes_single.h \
    source/model/visualization/charts/chartResults.h \
    source/model/visualization/imageOutputController.h \
    source/model/visualization/imageresults.h \
    source/model/visualization/visualizationImageProvider.h \
    source/model/wright-fisher/rdist.h \
    source/model/wright-fisher/wrightFisher.h \
    source/model/executables/wfes_single/results/resultsWfesSingle.h \
    source/utils/exceptions.h \
    source/utils/observer/observer.h \
    source/utils/observer/subject.h \
    source/utils/parsing.h \
    source/utils/types.h \
    source/utils/utils.h \
    wfes-lib_global.h

SOURCES += \
    source/model/config/globalConfiguration.cpp \
    source/model/config/systemoperations.cpp \
    source/model/executables/phase_type/config/configPhaseType.cpp \
    source/model/executables/phase_type/controllers/inputControllerPhaseType.cpp \
    source/model/executables/phase_type/controllers/outputControllerPhaseType.cpp \
    source/model/executables/phase_type/phase_type.cpp \
    source/model/executables/phase_type/results/resultsPhaseType.cpp \
    source/model/executables/phase_type/thread/workerThreadPhaseType.cpp \
    source/model/executables/time_dist/config/configTimeDist.cpp \
    source/model/executables/time_dist/config/configTimeDistSGV.cpp \
    source/model/executables/time_dist/controllers/inputControllerTimeDist.cpp \
    source/model/executables/time_dist/controllers/outputControllerTimeDist.cpp \
    source/model/executables/time_dist/results/resultsTimeDist.cpp \
    source/model/executables/time_dist/thread/workerThreadTimeDist.cpp \
    source/model/executables/time_dist/time_dist.cpp \
    source/model/executables/wfafd/config/configWfafd.cpp \
    source/model/executables/wfafd/controllers/inputControllerWfafd.cpp \
    source/model/executables/wfafd/controllers/outputControllerWfafd.cpp \
    source/model/executables/wfafd/results/resultsWfafd.cpp \
    source/model/executables/wfafd/thread/workerThreadWfafd.cpp \
    source/model/executables/wfafd/wfafd.cpp \
    source/model/executables/wfafs/config/configWfafs.cpp \
    source/model/executables/wfafs/controllers/inputControllerWfafs.cpp \
    source/model/executables/wfafs/controllers/outputControllerWfafs.cpp \
    source/model/executables/wfafs/results/resultsWfafs.cpp \
    source/model/executables/wfafs/thread/workerThreadWfafs.cpp \
    source/model/executables/wfafs/wfafs.cpp \
    source/model/executables/wfes_sequential/config/configWfesSequential.cpp \
    source/model/executables/wfes_sequential/controllers/inputControllerWfesSequential.cpp \
    source/model/executables/wfes_sequential/controllers/outputControllerWfesSequential.cpp \
    source/model/executables/wfes_sequential/results/resultsWfesSequential.cpp \
    source/model/executables/wfes_sequential/thread/workerThreadWfesSequential.cpp \
    source/model/executables/wfes_sequential/wfes_sequential.cpp \
    source/model/executables/wfes_single/config/configWfesSingle.cpp \
    source/model/executables/wfes_single/controllers/inputControllerWfesSingle.cpp \
    source/model/executables/wfes_single/controllers/outputControllerWfesSingle.cpp \
    source/model/executables/wfes_single/thread/workerThreadWfesSingle.cpp \
    source/model/executables/wfes_sweep/config/configWfesSweep.cpp \
    source/model/executables/wfes_sweep/controllers/inputControllerWfesSweep.cpp \
    source/model/executables/wfes_sweep/controllers/outputControllerWfesSweep.cpp \
    source/model/executables/wfes_sweep/results/resultsWfesSweep.cpp \
    source/model/executables/wfes_sweep/thread/workerThreadWfesSweep.cpp \
    source/model/executables/wfes_sweep/wfes_sweep.cpp \
    source/model/executables/wfes_switching/config/configWfesSwitching.cpp \
    source/model/executables/wfes_switching/controllers/inputControllerWfesSwitching.cpp \
    source/model/executables/wfes_switching/controllers/outputControllerWfesSwitching.cpp \
    source/model/executables/wfes_switching/results/resultsWfesSwitching.cpp \
    source/model/executables/wfes_switching/thread/workerThreadWfesSwitching.cpp \
    source/model/executables/wfes_switching/wfes_switching.cpp \
    source/model/solver/pardiso/solverPardiso.cpp \
    source/model/solver/solver.cpp \
    source/model/solver/solverFactory.cpp \
    source/model/sparse-matrix/sparseMatrix.cpp \
    source/model/sparse-matrix/sparseMatrixFactory.cpp \
    source/model/sparse-matrix/pardiso/sparseMatrixPardiso.cpp \
    source/model/solver/viennacl/solverViennaCL.cpp \
    source/model/sparse-matrix/viennacl/sparseMatrixViennacl.cpp \
    source/model/executables/wfes_single/wfes_single.cpp \
    source/model/visualization/charts/chartResults.cpp \
    source/model/visualization/imageOutputController.cpp \
    source/model/visualization/imageresults.cpp \
    source/model/visualization/visualizationImageProvider.cpp \
    source/model/wright-fisher/rdist.cpp \
    source/model/wright-fisher/wrightFisher.cpp \
    source/model/executables/wfes_single/results/resultsWfesSingle.cpp \
    source/utils/observer/subject.cpp \
    source/utils/parsing.cpp \
    source/utils/utils.cpp

# Default rules for deployment.
unix: !macx {

    QMAKE_CXXFLAGS += -fopenmp

    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/lib
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN

    target.path = /usr/lib

    INCLUDEPATH += source \
        $$PWD/../dependencies/unix

    # OpenCL
    LIBS += -L$$PWD/../dependencies/unix/CL/lib -lOpenCL
    INCLUDEPATH += $$PWD/../dependencies/unix/CL
    DEPENDPATH += $$PWD/../dependencies/unix/CL

    # Intel MKL
    LIBS +=  -L$$PWD/../dependencies/unix/intel/mkl/lib/intel64 -Wl,--no-as-needed -lmkl_intel_ilp64 -lmkl_intel_thread -lmkl_core -lpthread -lm -ldl
    LIBS +=  -L$$PWD/../dependencies/unix/intel/mkl/compiler/ -Wl,--no-as-needed -liomp5
    INCLUDEPATH += $$PWD/../dependencies/unix/intel/mkl/include
    DEPENDPATH += $$PWD/../dependencies/unix/intel/mkl/include
}

macx {

    QMAKE_CXXFLAGS *= "-Xpreprocessor -fopenmp"
    INCLUDEPATH += $$PWD/source/
    INCLUDEPATH += $$PWD/../dependencies/mac/
    INCLUDEPATH += /usr/local/include
    QMAKE_LFLAGS += -Wl,-rpath,@executable_path/../Frameworks

    # Intel MKL
    LIBS += -L$$PWD/../dependencies/mac/intel/mkl/lib/ -lmkl_core
    LIBS += -L$$PWD/../dependencies/mac/intel/mkl/lib/ -lmkl_intel_ilp64
    LIBS += -L$$PWD/../dependencies/mac/intel/mkl/lib/ -lmkl_intel_thread
    LIBS += -L$$PWD/../dependencies/mac/intel/lib/ -liomp5
    LIBS +=  -lpthread -lm -ldl -framework OpenCL
    INCLUDEPATH += $$PWD/../dependencies/mac/intel/mkl/include
    DEPENDPATH += $$PWD/../dependencies/mac/intel/mkl/include
}

win32 {

    QMAKE_CXXFLAGS += -openmp -arch:AVX2 -fp:fast -GL -Oi

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
