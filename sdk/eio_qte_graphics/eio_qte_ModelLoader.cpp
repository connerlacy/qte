#include "eio_qte_ModelLoader.h"

ModelLoader::ModelLoader(QObject *parent) :
    QObject(parent)
{
    scene = NULL;
}

bool ModelLoader::importAsset(QString pathToFile)
{
    qDebug() << "IMPORT ASSET: " << pathToFile;

    Assimp::Importer importer;

    scene = importer.ReadFile(pathToFile.toStdString(),  aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    if(scene == NULL)
    {
        qDebug() << "Asset could not be loaded: " << pathToFile;

        return false;
    }

    // For now we'll only deal with meshses and handle lights, etc. separately
    // even thought the assimp supports these classes

    //------------------------------------ MESHES ------------------------------------//
    if(scene->HasMeshes())
    {
        //Clear our mesh vectors
        meshes.clear();
        aiMeshes.clear();

        //qDebug() << "NUM MESHES:" << scene->mNumMeshes;

        //Iterate meshes
        for(int i = 0; i < scene->mNumMeshes; i++)
        {
            aiMesh *currentMesh = scene->mMeshes[i];
            //qDebug() << "MESH Bones:" << i << currentMesh->mNumBones;
            //qDebug() << "MESH NUM Verticies:" << i << currentMesh->mNumVertices;

            //----------------------------- BONES -----------------------------//
            for(int b = 0; b < currentMesh->mNumBones; b++)
            {
                QVector<int> indicies;
                QVector<float> weights;

                aiBone *currentBone = currentMesh->mBones[b];

                for(int v = 0; v < currentBone->mNumWeights; v++)
                {
                    indicies.append(currentBone->mWeights[v].mVertexId);
                    weights.append(currentBone->mWeights[v].mWeight);
                }

                bones.append(new Bone(indicies, weights));
            }

            //Add to mesh aiMesh vector
            aiMeshes.push_back(scene->mMeshes[i]);

            //---- VERTEX
            QVector<QVector3D> verts;
            QVector<QVector3D> normals;
            for(int vert = 0; vert < currentMesh->mNumVertices; vert++)
            {
                //qDebug() << "\tVertex:" << QVector3D(currentMesh->mVertices[vert].x, currentMesh->mVertices[vert].y, currentMesh->mVertices[vert].z);
                verts.append(QVector3D(currentMesh->mVertices[vert].x, currentMesh->mVertices[vert].y, currentMesh->mVertices[vert].z));

                if(currentMesh->HasNormals())
                {
                    normals.append(QVector3D(currentMesh->mNormals[vert].x, currentMesh->mNormals[vert].y,currentMesh->mNormals[vert].z));
                }
            }

            meshes.push_back(new Mesh(verts));
            meshes.back()->setNormals(normals);

            //---- NORMALS
            //qDebug() << "HAS NORMALS" << currentMesh->HasNormals();

            //---- INDEX
            QVector<GLushort>   indicies;

            //Iterate faecs
            for(int face = 0; face < currentMesh->mNumFaces; face++)
            {
                for(int indx = 0; indx < currentMesh->mFaces[face].mNumIndices; indx++)
                {
                    indicies.append(currentMesh->mFaces[face].mIndices[indx]);
                }
            }

            meshes.back()->setIndices(indicies);
            //qDebug() << "MESHES NUM INDICIES:" << indicies.size();
        }
    }

    //qDebug() << "Indicies Size: " << indicies.

    return true;
}

aiMesh* ModelLoader::getAiMesh(int index)
{
    return aiMeshes[index];
}

vector<aiMesh *> ModelLoader::getAiMeshes()
{
    return aiMeshes;
}

Mesh* ModelLoader::getMesh(int index)
{
    if(index < meshes.size())
    {
        return meshes.at(index);
    }
}

QVector<Mesh *> ModelLoader::getMeshes()
{
    return meshes;
}

QVector<Bone *> ModelLoader::getBones()
{
    return bones;
}

//==========================================================================================
//=========================================== BONE =========================================
//==========================================================================================
Bone::Bone(QObject *parent) :
    QObject(parent)
{
}

Bone::Bone(QVector<int> indicies, QVector<float> weights, QObject *parent) :
    QObject(parent)
{
    m_Indicies = indicies;
    m_Weights = weights;
}
