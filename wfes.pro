TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    wfes-lib \
    wfes-ui

message(wfes project dir: $${PWD})
