TEMPLATE = lib
TARGET = timesheeteditor

include(common.pro)

HEADERS += \
           timesheet.h         \
           timesheeteditor.h

SOURCES += \
           timesheet.cpp       \
           timesheeteditor.cpp

FORMS += timesheeteditor.ui

