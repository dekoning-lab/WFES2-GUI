include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

QT += qml quick quickcontrols2 widgets charts

TEMPLATE = app

RC_ICONS = icon.ico
ICON = icon.ico

CONFIG += c++11
CONFIG += app_bundle

INCLUDEPATH += source \
    ../wfes-lib \
    ../wfes-lib/source

QMAKE_CXXFLAGS += -DMKL_ILP64 -m64
DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        source/main.cpp

RESOURCES += views.qrc \
    assets.qrc \
    components.qrc

LIBS += -L$$PWD/../binaries/$$DESTINATION_PATH -lwfes-lib

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD \
                    $$PWD/executionviews

# Additional import path used to resolve QML modules just for Qt Quick Designer
#QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


unix: !macx {

    # TODO Change for compatibility with mac and windows
    LIBS +=  -L$$PWD/../dependencies/unix/intel/mkl/lib/intel64 -Wl,--no-as-needed -lmkl_intel_ilp64 -lmkl_intel_thread -lmkl_core -lpthread -lm -ldl
    LIBS +=  -L$$PWD/../dependencies/unix/intel/mkl/compiler/ -Wl,--no-as-needed -liomp5
    LIBS += -L$$PWD/../dependencies/unix/CL/lib/linux/ -lOpenCL

    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/lib
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN

    INCLUDEPATH += \
        $$PWD/../dependencies/unix \
        $$PWD/../dependencies/unix/intel/mkl/include \
        $$PWD/../dependencies/unix/CL

    DEPENDPATH += $$PWD/../dependencies/unix/CL
}


macx {
    INCLUDEPATH += $$PWD/source/
    INCLUDEPATH += $$PWD/../dependencies/mac/

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

