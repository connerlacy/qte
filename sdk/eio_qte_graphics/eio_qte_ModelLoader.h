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

#include "eio_qte_Mesh.h"

using namespace std;

#ifndef BONE_H
#define BONE_H

#include <QObject>
#include <QVector>

class Bone : public QObject
{
    Q_OBJECT
public:
    explicit Bone(QObject *parent = 0);
    Bone(QVector<int> indicies, QVector<float> weights, QObject *parent = 0);

    QVector<int> m_Indicies;
    QVector<float> m_Weights;

signals:

public slots:

};

#endif // BONE_H

class ModelLoader : public QObject
{
    Q_OBJECT

    const aiScene *scene;
    vector<aiMesh *>aiMeshes;
    QVector<Mesh *> meshes;
    QVector<Bone *> bones;

public:
    explicit ModelLoader(QObject *parent = 0);

    bool importAsset(QString pathToFile);

    //Assimp Format
    vector<aiMesh *> getAiMeshes();
    aiMesh* getAiMesh(int index);

    //---- Mesh
    QVector<Mesh *> getMeshes();
    Mesh *getMesh(int index);

    //---- Bone
    QVector<Bone *> getBones();



signals:

public slots:

};




#endif // MODELLOADER_H
