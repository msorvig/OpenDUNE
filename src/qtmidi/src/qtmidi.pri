
INCLUDEPATH += $$PWD

SOURCES += $$PWD/midi.cpp

mac {
    HEADERS += $$PWD/midi_coremidi.h \
           $$PWD/midi_coreaudio.h \

    LIBS += -framework CoreMidi
}

HEADERS += $$PWD/midi_win32.h \
           $$PWD/midi_oss.h \
           $$PWD/midi_alsa.h

HEADERS += $$PWD/qtmidi.h


