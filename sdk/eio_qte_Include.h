#ifndef EIO_INCLUDE_H
#define EIO_INCLUDE_H

#include <QDebug>
#include <QMutex>
#include <QMutexLocker>
#include <QThread>
#include <QVector>
#include <QBasicTimer>

//================================ Graphics
#include "eio_qte_graphics/eio_qte_Canvas.h"
#include "eio_qte_graphics/eio_qte_ArcBall.h"
#include "eio_qte_graphics/eio_qte_Mesh.h"
#include "eio_qte_graphics/eio_qte_Light.h"
#include "eio_qte_graphics/eio_qte_Shader.h"
#include "eio_qte_graphics/eio_qte_ModelLoader.h"

//================================ MIDI
#include "eio_qte_midi/eio_qte_AudioMIDIIO.h"
#include "eio_qte_midi/eio_qte_MIDIParser.h"

//================================ Libs
//---- JUCE
#include "eio_qte_libs/JUCE/JuceHeader.h"

//---- Open Asset Import Library (Assimp)
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//---- libnoise
#include "noise.h"
using namespace noise;


#define EIO_QTE_MAX_LIGHTS 8


#endif // EIO_INCLUDE_H
