TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    wfes-lib \
    #wfes-tests \
    wfes-ui

INCLUDEPATH += dependencies

message(wfes project dir: $${PWD})
