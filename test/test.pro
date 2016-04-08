TEMPLATE = app
TARGET = test

include(../common.pro)

SOURCES = test.cpp

DESTDIR = ./
LIBS += -L../build_dir/lib -ltimesheeteditor
