#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T20:01:37
#
#-------------------------------------------------

QT  += core gui
QT  += opengl
QT  += serialport
QT  += network

CONFIG += c++11

INCLUDEPATH += $$EIO_SDK_QT_PATH

#===================================== Graphics =================================#
SOURCES += \
    $$EIO_SDK_QT_PATH/eio_qte_graphics/eio_qte_ArcBall.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_graphics/eio_qte_Canvas.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_graphics/eio_qte_Light.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_graphics/eio_qte_Mesh.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_graphics/eio_qte_ModelLoader.cpp
    $$EIO_SDK_QT_PATH/eio_qte_graphics/eio_qte_Shader.cpp

HEADERS  += \
    $$EIO_SDK_QT_PATH/eio_qte_graphics/eio_qte_ArcBall.h \
    $$EIO_SDK_QT_PATH/eio_qte_graphics/eio_qte_Canvas.h \
    $$EIO_SDK_QT_PATH/eio_qte_graphics/eio_qte_Light.h \
    $$EIO_SDK_QT_PATH/eio_qte_graphics/eio_qte_Mesh.h \
    $$EIO_SDK_QT_PATH/eio_qte_graphics/eio_qte_ModelLoader.h
    $$EIO_SDK_QT_PATH/eio_qte_graphics/eio_qte_Shader.h

OTHER_FILES += \
    $$EIO_SDK_QT_PATH/eio_qte_graphics/eio_qte_Shader_Desktop_Template.frag \
    $$EIO_SDK_QT_PATH/eio_qte_graphics/eio_qte_Shader_Desktop_Template.vert \
    $$EIO_SDK_QT_PATH/eio_qte_graphics/eio_qte_Shader_Desktop_Snippets.glsl


#===================================== MIDI =================================#
SOURCES += \
    $$EIO_SDK_QT_PATH/eio_qte_midi/eio_qte_AudioMIDIIO.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_midi/eio_qte_MIDIParser.cpp

HEADERS  += \
    $$EIO_SDK_QT_PATH/eio_qte_midi/eio_qte_AudioMIDIIO.h \
    $$EIO_SDK_QT_PATH/eio_qte_midi/eio_qte_MIDIParser.h

#===================================== Libs =================================#
#---- JUCE
INCLUDEPATH += $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE

HEADERS  += \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/AppConfig.h \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/JuceHeader.h \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_core/juce_core.h \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_audio_basics/juce_audio_basics.h \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_audio_devices/juce_audio_devices.h \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_audio_formats/juce_audio_formats.h \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_audio_processors/juce_audio_processors.h \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_audio_utils/juce_audio_utils.h \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_cryptography/juce_cryptography.h \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_data_structures/juce_data_structures.h \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_events/juce_events.h \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_graphics/juce_graphics.h \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_gui_basics/juce_gui_basics.h \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_gui_extra/juce_gui_extra.h \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_opengl/juce_opengl.h \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_video/juce_video.h

macx{
LIBS += -framework Accelerate
LIBS += -framework AudioToolbox
LIBS += -framework Carbon
LIBS += -framework Cocoa
LIBS += -framework CoreAudio
LIBS += -framework CoreMIDI
LIBS += -framework DiscRecording
LIBS += -framework IOKit
LIBS += -framework OpenGL
LIBS += -framework QTKit
LIBS += -framework QuartzCore
LIBS += -framework QuickTime
LIBS += -framework WebKit

OBJECTIVE_SOURCES += \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_core/juce_core.mm \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_audio_basics/juce_audio_basics.mm \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_audio_devices/juce_audio_devices.mm \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_audio_formats/juce_audio_formats.mm \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_audio_processors/juce_audio_processors.mm \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_audio_utils/juce_audio_utils.mm \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_cryptography/juce_cryptography.mm \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_data_structures/juce_data_structures.mm \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_events/juce_events.mm \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_graphics/juce_graphics.mm \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_gui_basics/juce_gui_basics.mm \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_gui_extra/juce_gui_extra.mm \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_opengl/juce_opengl.mm \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_video/juce_video.mm
}

win32{
SOURCES += \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_core/juce_core.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_audio_basics/juce_audio_basics.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_audio_devices/juce_audio_devices.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_audio_formats/juce_audio_formats.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_audio_processors/juce_audio_processors.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_audio_utils/juce_audio_utils.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_cryptography/juce_cryptography.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_data_structures/juce_data_structures.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_events/juce_events.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_graphics/juce_graphics.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_gui_basics/juce_gui_basics.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_gui_extra/juce_gui_extra.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_opengl/juce_opengl.cpp \
    $$EIO_SDK_QT_PATH/eio_qte_libs/JUCE/modules/juce_video/juce_video.cpp

LIBS += \
  -lcomdlg32 \
  -limm32 \
  -lole32 \
  -loleaut32 \
  -lrpcrt4 \
  -lshlwapi \
  -luuid \
  -lversion \
  -lwininet \
  -lwinmm \
  -lws2_32 \
  -lwsock32 \
  -lshell32
}

#---- Open Asset Import Library
macx{
LIBS += -L$$EIO_SDK_QT_PATH/eio_qte_libs/Assimp/ -lassimp
INCLUDEPATH += $$EIO_SDK_QT_PATH/eio_qte_libs/Assimp/include
DEPENDPATH += $$EIO_SDK_QT_PATH/eio_qte_libs/Assimp/include
}


HEADERS +=  \
    $$EIO_SDK_QT_PATH/eio_qte_Include.h




