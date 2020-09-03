include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

QT += qml quick quickcontrols2

TEMPLATE = app

CONFIG += c++11

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
QML_IMPORT_PATH = $$PWD

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


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

win32 {

    # TODO Change for compatibility with mac and windows
    LIBS +=  -L$$PWD/../dependencies/windows/intel/compilers_and_libraries_2020.3.279/windows/mkl/lib/intel64_win -Wl,--no-as-needed -lmkl_intel_ilp64 -lmkl_intel_thread -lmkl_core -lpthread -lm
    LIBS +=  -L$$PWD/../dependencies/windows/intel/compilers_and_libraries_2020.3.279/windows/redist/intel64_win/compiler -Wl,--no-as-needed -liomp5md
    LIBS += -L$$PWD/../dependencies/windows/CL/lib/ -lOpenCL

    INCLUDEPATH += \
        $$PWD/../dependencies/windows \
        $$PWD/../dependencies/windows/intel/compilers_and_libraries_2020.3.279/windows/mkl/include \
        $$PWD/../dependencies/windows/CL

    DEPENDPATH += $$PWD/../dependencies/windows/CL

}
