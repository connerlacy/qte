#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QVector3D>
#include <QVector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "BeBopSensors_Mesh.h"
#include "BeBopSensors_Bone.h"

using namespace std;

class BeBopSensors_ModelLoader : public QObject
{
    Q_OBJECT

    const aiScene *scene;
    vector<aiMesh *>aiMeshes;
    QVector<Mesh *> meshes;
    QVector<Bone *> bones;

public:
    explicit BeBopSensors_ModelLoader(QObject *parent = 0);

    bool importAsset(QString pathToFile);

    //Assimp Format
    vector<aiMesh *> getAiMeshes();
    aiMesh* getAiMesh(int index);

    //BeBop Format
    //---- Mesh
    QVector<Mesh *> getMeshes();
    Mesh *getMesh(int index);

    //---- Bone
    QVector<Bone *> getBones();



signals:

public slots:

};




#endif // MODELLOADER_H
