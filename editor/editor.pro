######################################################################
# Automatically generated by qmake (3.1) Sat Feb 25 04:31:38 2023
######################################################################

TEMPLATE = app
TARGET = editor
INCLUDEPATH += .
QT += widgets gui
# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
RESOURCES += resources.qrc
# Input
HEADERS += main_window.hpp new_window.hpp tool_window.hpp run_window.hpp debug_window.hpp gfx_window.hpp ../level.hpp
SOURCES += main.cpp main_window.cpp new_window.cpp tool_window.cpp run_window.cpp debug_window.cpp gfx_window.cpp ../level.cpp
