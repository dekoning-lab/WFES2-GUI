TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    wfes-lib \
    wfes-tests \
    wfes-ui

message(wfes project dir: $${PWD})
