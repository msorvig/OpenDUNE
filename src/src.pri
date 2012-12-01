

DEPENDPATH += $$PWD/. \
              $$PWD/audio \
              $$PWD/codec \
              $$PWD/crashlog \
              $$PWD/gui \
              $$PWD/input \
              $$PWD/os \
              $$PWD/pool \
              $$PWD/saveload \
              $$PWD/script \
              $$PWD/table \
              $$PWD/video
INCLUDEPATH += $$PWD/. \
               $$PWD/../include \
               $$PWD/audio \
               $$PWD/script \
               $$PWD/os \
               $$PWD/gui \
               $$PWD/video \
               $$PWD/pool \
               $$PWD/table \
               $$PWD/saveload \
               $$PWD/crashlog \
               $$PWD/input \
               $$PWD/codec



# SDL build:
DEFINES += SDL_BUILD
SOURCES +=  $$PWD/audio/dsp_sdl.c \
            $$PWD/video/video_sdl.c

INCLUDEPATH += /opt/local/include/SDL/
LIBS += -L/opt/local/lib -lSDL -lSDLmain -framework CoreFoundation -framework AppKit

#none build
#SOURCES +=  $$PWD/audio/dsp_none.c

# Input
HEADERS +=  $$PWD/animation.h \
            $$PWD/config.h \
            $$PWD/explosion.h \
            $$PWD/file.h \
            $$PWD/gfx.h \
            $$PWD/house.h \
            $$PWD/ini.h \
            $$PWD/load.h \
            $$PWD/map.h \
            $$PWD/object.h \
            $$PWD/opendune.h \
            $$PWD/save.h \
            $$PWD/scenario.h \
            $$PWD/sprites.h \
           $$PWD/string.h \
           $$PWD/structure.h \
           $$PWD/team.h \
           $$PWD/tile.h \
           $$PWD/timer.h \
           $$PWD/tools.h \
           $$PWD/unit.h \
           $$PWD/wsa.h \
           $$PWD/audio/driver.h \
           $$PWD/audio/dsp.h \
           $$PWD/audio/midi.h \
           $$PWD/audio/mt32mpu.h \
           $$PWD/audio/sound.h \
           $$PWD/codec/format40.h \
           $$PWD/codec/format80.h \
           $$PWD/crashlog/crashlog.h \
           $$PWD/gui/font.h \
           $$PWD/gui/gui.h \
           $$PWD/gui/mentat.h \
           $$PWD/gui/security.h \
           $$PWD/gui/widget.h \
           $$PWD/input/input.h \
           $$PWD/input/mouse.h \
           $$PWD/os/common.h \
           $$PWD/os/endian.h \
           $$PWD/os/error.h \
           $$PWD/os/file.h \
           $$PWD/os/math.h \
           $$PWD/os/sleep.h \
           $$PWD/os/strings.h \
           $$PWD/pool/house.h \
           $$PWD/pool/pool.h \
           $$PWD/pool/structure.h \
           $$PWD/pool/team.h \
           $$PWD/pool/unit.h \
           $$PWD/saveload/saveload.h \
           $$PWD/script/script.h \
           $$PWD/table/strings.h \
           $$PWD/video/video.h

SOURCES += $$PWD/animation.c \
           $$PWD/config.c \
           $$PWD/explosion.c \
           $$PWD/file.c \
           $$PWD/gfx.c \
           $$PWD/house.c \
           $$PWD/ini.c \
           $$PWD/load.c \
           $$PWD/map.c \
           $$PWD/object.c \
           $$PWD/opendune.c \
           $$PWD/save.c \
           $$PWD/scenario.c \
           $$PWD/sprites.c \
           $$PWD/string.c \
           $$PWD/structure.c \
           $$PWD/team.c \
           $$PWD/tile.c \
           $$PWD/timer.c \
           $$PWD/tools.c \
           $$PWD/unit.c \
           $$PWD/wsa.c \
           $$PWD/audio/driver.c \
#           $$PWD/audio/dsp_alsa.c \
#           $$PWD/audio/dsp_none.c \
#           $$PWD/audio/dsp_win32.c \
#           $$PWD/audio/midi_alsa.c \
           $$PWD/audio/midi_none.c \
#           $$PWD/audio/midi_win32.c \
           $$PWD/audio/mt32mpu.c \
           $$PWD/audio/sound.c \
           $$PWD/codec/format40.c \
           $$PWD/codec/format80.c \
           $$PWD/crashlog/crashlog.c \
           $$PWD/crashlog/crashlog_none.c \
#           $$PWD/crashlog/crashlog_win32.c \
           $$PWD/gui/editbox.c \
           $$PWD/gui/font.c \
           $$PWD/gui/gui.c \
           $$PWD/gui/mentat.c \
           $$PWD/gui/security.c \
           $$PWD/gui/viewport.c \
           $$PWD/gui/widget.c \
           $$PWD/gui/widget_click.c \
           $$PWD/gui/widget_draw.c \
           $$PWD/input/input.c \
           $$PWD/input/mouse.c \
           $$PWD/os/error.c \
#           $$PWD/os/error_win32.c \
           $$PWD/pool/poolhouse.c \
           $$PWD/pool/poolstructure.c \
           $$PWD/pool/poolteam.c \
           $$PWD/pool/poolunit.c \
           $$PWD/saveload/saveloadhouse.c \
           $$PWD/saveload/saveloadinfo.c \
           $$PWD/saveload/saveloadobject.c \
           $$PWD/saveload/saveload.c \
           $$PWD/saveload/saveloadscenario.c \
           $$PWD/saveload/saveloadscriptengine.c \
           $$PWD/saveload/saveloadstructure.c \
           $$PWD/saveload/saveloadteam.c \
           $$PWD/saveload/saveloadunit.c \
           $$PWD/script/scriptgeneral.c \
           $$PWD/script/script.c \
           $$PWD/script/scriptstructure.c \
           $$PWD/script/scriptteam.c \
           $$PWD/script/scriptunit.c \
           $$PWD/table/tableactioninfo.c \
           $$PWD/table/tableanimation.c \
           $$PWD/table/tableexplosion.c \
           $$PWD/table/tablefileinfo.c \
           $$PWD/table/tablehouseanimation.c \
           $$PWD/table/tablehouseinfo.c \
           $$PWD/table/tablelandscapeinfo.c \
           $$PWD/table/tablemovementtype.c \
           $$PWD/table/tableselectiontype.c \
           $$PWD/table/tablesound.c \
           $$PWD/table/tablestructureinfo.c \
           $$PWD/table/tableteamaction.c \
           $$PWD/table/tabletilediff.c \
           $$PWD/table/tableunitinfo.c \
           $$PWD/table/tablewidget.c \
           $$PWD/table/tablewidgetinfo.c \
           $$PWD/table/tablewindowdesc.c \
#           $$PWD/video/video_win32.c
