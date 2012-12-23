TEMPLATE = app
CONFIG -= debug
!ios:CONFIG -= app_bundle
TARGET = bin/opendune

#CONFIG += opendune_sdl_build
CONFIG += opendune_qt_build

include (src/src.pri)
