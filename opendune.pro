TEMPLATE = app
CONFIG -= app_bundle debug
TARGET = bin/opendune

#CONFIG += opendune_sdl_build
CONFIG += opendune_qt_build

include (src/src.pri)
