/*! \file
 * GameGraph.cpp <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: GameGraph.cpp,v 1.3 2003/09/04 12:26:31 toni Exp $
 * $Date: 2003/09/04 12:26:31 $
 * $Revision: 1.3 $
 */

#include <xforge.h>
#include <xfcore/XFcHashtable.h>
#include <xfutil/XFuParticleSystem.h>
#include "GameGraph.h"
#include "Group.h"
#include "Camera.h"
#include "Mesh.h"
#include "Material.h"
#include "Buffers.h"
#include "Texture.h"
#include "PRSAnimation.h"
#include "ParticleSystem.h"

//! Static creation
GameGraph * GameGraph::create(XFcGL *aGL)
{
    GameGraph *gg = new GameGraph(aGL);
    if(gg)
    {
        // Further initializations, memory allocations etc. here
        gg->mNodes = new XFcHashtable<UINT32, Node *>();
    }
    return gg;
}

GameGraph::GameGraph(XFcGL *aGL) : mRootNode(NULL), mLastFrame(0), mActiveCamera(NULL), mGL(aGL), mNodes(NULL)
{

}

GameGraph::~GameGraph()
{
    // delete all nodes
    XFcHashtable<UINT32, Node *>::iterator itr = mNodes->begin();
    while(itr != mNodes->end())
    {
        delete itr.getValue();
        itr++;
    }
    delete mNodes;
}

void GameGraph::addNode(Node *aNode)
{
    mNodes->put(aNode->getId(), aNode);
}

void GameGraph::render()
{
    // Advance one frame
    mLastFrame++;

    XFCASSERT(mRootNode);
    XFCASSERT(mActiveCamera);

    // Prepare pass
    mRootNode->prepare();

    // Initialize camera
    mActiveCamera->setCamera();

    // Render pass
    mRootNode->render();
}

//! Finds a node by its id
Node *GameGraph::getNodeById(UINT32 aId)
{
    if(aId == 0xffffffff)
        return NULL;

    XFcHashtable<UINT32, Node *>::iterator itr = mNodes->find(aId);
    if(itr == mNodes->end())
        return NULL;
    
    return itr.getValue();
}

/**
*
*   XFF file loader starts here.
*/



//! Chunk type codes
enum CHUNK_TYPE
{
    CT_NODE = 1,
        CT_GROUP,
        CT_GEOMETRY,
        CT_MESH,
        CT_CAMERA,
        CT_LIGHT,
        CT_HELPER,
        CT_PARTICLESYSTEM,
        CT_SPRITE,
        CT_SOUNDSOURCE,
        CT_MICROPHONE,
        CT_COLLIDER,
        CT_VERTEXBUFFER = 1001,
        CT_FACELIST,
        CT_MATERIAL,
        CT_TEXTURE,
        CT_ANIMATION,
        CT_LOADER,
        CT_SPRING,
        CT_TRIANGLEINFOBUFFER,
        CT_NODEATTRIBUTE
};

//! Loads the scene from XFF file
INT GameGraph::loadFromXFF(char *aFilename)
{
    INT loadSuccess = 1;

    XFcFile *file = XFcFile::open(aFilename, XFCSTR("rb"));
    XFCASSERT(file);

    file->seek(0, SEEK_END);
    INT32 fileLen = file->tell();
    
    file->seek(0, SEEK_SET);
    while (file->tell() < fileLen && loadSuccess)
    {
        
        // read header
        UINT16 chunkType = file->readUINT16();
        UINT16 chunkVersion = file->readUINT16();
        UINT32 chunkId = file->readUINT32();
        UINT32 chunkBlockLength = file->readUINT32();
        
        // save position
        INT32 pos = file->tell();
        
        // load chunk with suitable chunk loader (or skip if none found)
        switch(chunkType)
        {
        case CT_GROUP:
            {
                // Read a group node
                XFCASSERT(chunkVersion == 1);
                // All nodes are self-registering
                Group *g = Group::create(this, chunkId);
                g->setParentId(file->readUINT32());
                g->setAlias(getString(file));
                XFcMatrix4 mat;
                readPRS(file, mat);
                g->setTransformation(mat);
            }
            break;
            
        case CT_GEOMETRY:
            {
                // We don't yet know if there is mesh or particle system under this node, so make it a group
                XFCASSERT(chunkVersion == 1);
                Group *g = Group::create(this, chunkId);
                g->setParentId(file->readUINT32());
                g->setAlias(getString(file));
                XFcMatrix4 mat;
                readPRS(file, mat);
                g->setTransformation(mat);
            }
            break;
            
        case CT_MESH:
            {
                XFCASSERT(chunkVersion == 3);
                //! Create a mesh
                Mesh *g = Mesh::create(this, chunkId);
                g->setParentId(file->readUINT32());
                g->setAlias(getString(file));
                // Identity transformation
                XFcMatrix4 mat;
                XFcMath::matrixIdentity(mat);
                g->setTransformation(mat);

                UINT16 submeshes = file->readUINT16();
                int i;    
                for(i = 0; i < submeshes; i++)
                {
                    // Read a submesh
                    Submesh *sm = new Submesh();
                    sm->mVertexBufferId = file->readUINT32();
                    sm->mFaceListId = file->readUINT32();
                    sm->mTriangleInfoBufferId = file->readUINT32();
                    sm->mMaterialId = file->readUINT32();
                    sm->mTextureId = file->readUINT32();
                    file->readUINT32();
                    sm->mVertexOffset = file->readUINT32();
                    sm->mVertexCount = file->readUINT32();
                    file->readUINT8();

                    g->addSubmesh(sm);    
                }
            }
            break;
        case CT_CAMERA:
            {
                // Read a camera node
                XFCASSERT(chunkVersion == 1);
                Camera *g = Camera::create(this, chunkId);
                g->setParentId(file->readUINT32());
                // skip target node id
                file->readUINT32();

                g->setAlias(getString(file));
                XFcMatrix4 mat;
                readPRS(file, mat, true);
                g->setTransformation(mat);
                g->mFOV = file->readFLOAT32();
                g->mNear = file->readFLOAT32();
                g->mFar = file->readFLOAT32();

                // Make this camera the active one
                mActiveCamera = g;
            }
            break;
        case CT_VERTEXBUFFER:
            {
                XFCASSERT(chunkVersion == 1);
                
                UINT32 vertexFlags = file->readUINT32();
                UINT16 vertexSize = file->readUINT16();
                UINT32 vertexCount = file->readUINT32();
                
                INT hasNormal = (vertexFlags & 0x01);
                INT hasDiffuseColor = (vertexFlags & 0x02);
                INT hasUVCoords = (vertexFlags & 0x04);
                
                UINT32 vertexBufferFlags = XFCGLVF_XYZ;
                if (hasNormal) vertexBufferFlags |= XFCGLVF_NORMAL;
                // Shove the diffuse color in the vertex buffer anyway
                /*if (hasDiffuseColor)*/ vertexBufferFlags |= XFCGLVF_DIFFUSECOLOR;
                if (hasUVCoords) vertexBufferFlags |= XFCGLVF_TEXTURE1;

                if(!hasDiffuseColor)
                    vertexSize += 4;
                
                XFcGLVertexBuffer *vertexBuffer = XFcGLVertexBuffer::create(vertexBufferFlags, vertexSize, vertexCount);
                
                XFCASSERT(vertexBuffer);
                
                UINT8 *vertexData = (UINT8*)vertexBuffer->lock(XFCGLVBLOCK_MODIFY);
                UINT32 vertexI;
                for (vertexI = 0; vertexI < vertexCount; vertexI++)
                {
                    
                    readREALToBuffer(file, &vertexData); // pos x
                    readREALToBuffer(file, &vertexData); // pos y
                    readREALToBuffer(file, &vertexData); // pos z
                    
                    if (hasNormal)
                    {
                        readREALToBuffer(file, &vertexData); // normal x
                        readREALToBuffer(file, &vertexData); // normal y
                        readREALToBuffer(file, &vertexData); // normal z
                    }
                    
                    if (hasDiffuseColor)
                    {
                        readUINT32ToBuffer(file, &vertexData); // diffuse color
                    }
                    else
                    {
                        *((UINT32 *)vertexData) = 0xffffffff;
                        vertexData += 4;
                    }
                    
                    if (hasUVCoords)
                    {
                        readREALToBuffer(file, &vertexData); // texture u
                        readREALToBuffer(file, &vertexData); // texture v
                    }
                }
                
                vertexBuffer->unlock();

                // Build the vertex buffer node
                VertexBuffer *vb = new VertexBuffer(this, chunkId);
                vb->setVB(vertexBuffer);
            }
            break;
        case CT_FACELIST:
            {
                XFCASSERT(chunkVersion == 2);
                UINT32 vertexCount = file->readUINT16();
                vertexCount *= 3; // version 1 assumes triangle list (indexes in triples)
                UINT16 *indexArray = new UINT16[vertexCount];
                XFCASSERT(indexArray);
                UINT16 readI;
                for (readI = 0; readI < vertexCount; readI++)
                    indexArray[readI] = file->readUINT16();

                FaceList *fl = new FaceList(this, chunkId);
                fl->setIndices(indexArray, vertexCount);
            }
            break;
        case CT_TRIANGLEINFOBUFFER:
            {
                // Read the Triangleinfobuffer
                XFCASSERT(chunkVersion == 1);
                UINT16 triangleCount = file->readUINT16();
                UINT32 triangleFlags = file->readUINT32();
                
                INT hasDiffuseColor = (triangleFlags & 0x01);
                INT hasNormal = (triangleFlags & 0x02);
                INT hasUVCoords = (triangleFlags & 0x04);
                
                UINT32 triangleInfoSize = 0;
                UINT32 triangleInfoFlags = 0;
                
                if (hasDiffuseColor)
                {
                    triangleInfoSize += (3 * sizeof(UINT32));
                    triangleInfoFlags |= XFCGLTR_DIFFUSECOLOR;
                }
                
                if (hasNormal)
                {
                    triangleInfoSize += (3 * sizeof(REAL));
                    triangleInfoFlags |= XFCGLTR_NORMAL;
                }
                
                if (hasUVCoords)
                {
                    triangleInfoSize += (3 * 2 * sizeof(REAL));
                    triangleInfoFlags |= XFCGLTR_TEXTURE1;
                }
                
                // make sure the triangle info buffer is valid
                XFCASSERT(triangleInfoFlags);
                
                XFcGLTriangleInfoBuffer *triangleInfoBuffer = XFcGLTriangleInfoBuffer::create(triangleInfoFlags, triangleInfoSize, triangleCount);

                XFCASSERT(triangleInfoBuffer);
                
                UINT8 *buffer = (UINT8*)triangleInfoBuffer->lock();
                
                UINT16 triI;
                for (triI = 0; triI < triangleCount; triI++)
                {
                    
                    if (hasDiffuseColor)
                    {
                        readUINT32ToBuffer(file, &buffer); // corner 1
                        readUINT32ToBuffer(file, &buffer); // corner 2
                        readUINT32ToBuffer(file, &buffer); // corner 2
                    }
                    
                    if (hasNormal)
                    {
                        readREALToBuffer(file, &buffer); // normal x
                        readREALToBuffer(file, &buffer); // normal y
                        readREALToBuffer(file, &buffer); // normal z
                    }
                    
                    if (hasUVCoords)
                    {
                        // (triangle info buffer is u1,u2,u3,v1,v2,v3 file format is u1,v1,u2,v2,u3,v3)
                        REAL *rBuf = (REAL*)buffer;
                        *(rBuf + 0) = file->readFLOAT32(); // corner 1 u
                        *(rBuf + 3) = file->readFLOAT32(); // corner 1 v
                        *(rBuf + 1) = file->readFLOAT32(); // corner 2 u
                        *(rBuf + 4) = file->readFLOAT32(); // corner 2 v
                        *(rBuf + 2) = file->readFLOAT32(); // corner 3 u
                        *(rBuf + 5) = file->readFLOAT32(); // corner 3 v
                        buffer += (6 * sizeof(REAL));
                    }
                    
                }
                
                triangleInfoBuffer->unlock();
                // Create the node
                TriangleInfoBuffer *tib = new TriangleInfoBuffer(this, chunkId);
                tib->setTIB(triangleInfoBuffer);
                
            }
            break;
        case CT_MATERIAL:
            {
                XFCASSERT(chunkVersion == 2);
                Material *material = new Material(this, chunkId);
                
                // Skip dynamic lighting colors (diffuse, specular, ambient, emissive and specpower)
                file->readUINT32();
                file->readUINT32();
                file->readUINT32();
                file->readUINT32();
                file->readFLOAT32();
                
                UINT32 materialFlags = file->readUINT32();
                
                material->mAlphaBlend = (materialFlags & 0x01) ? 1 : 0;
                material->mPerspectiveCorrection = (materialFlags & 0x02) ? 1 : 0;
                material->mWireframeMode = (materialFlags & 0x04) ? 1 : 0;
                material->mDoubleSided = (materialFlags & 0x08) ? 1 : 0;
                
                material->mShadingMode = file->readUINT32();
                
                material->mSourceBlend = (INT32)file->readUINT8();
                material->mTargetBlend = (INT32)file->readUINT8();
                
                material->mPolygonOffset = (REAL)file->readFLOAT32();
                
            }
            break;
        case CT_TEXTURE:
            {
                // Load the texture
                CHAR *filename = getString(file);
                XFcGLTexture *tex = XFcGLTextureFromFile::create(filename, XFCTC_MIPMAP_LINEAR);
                XFCASSERT(tex);
                Texture *t = new Texture(this, chunkId);
                t->setTex(tex);
            }
            break;
        case CT_ANIMATION:
            {
                // Animation chunk
                XFCASSERT(chunkVersion == 3);

                Group *g = Group::create(this, chunkId);
                PRSAnimation *prs = PRSAnimation::create();
                g->setAnimation(prs);
                g->setParentId(file->readUINT32());
                g->setAlias(getString(file));
                // Read only the first sequence
                UINT16 seqCount = file->readUINT16();
                XFCASSERT(seqCount > 0);
                // Skip start/end time and samplerate
                file->readINT32();
                file->readINT32();
                file->readFLOAT32();
                UINT16 flags = file->readUINT16();
                PRS sample;
                // Read the default values
                if(!(flags & 2))
                {
                    sample.mPos.x = file->readFLOAT32();
                    sample.mPos.y = file->readFLOAT32();
                    sample.mPos.z = file->readFLOAT32();
                }
                if(!(flags & 4))
                {
                    sample.mRot.x = file->readFLOAT32();
                    sample.mRot.y = file->readFLOAT32();
                    sample.mRot.z = file->readFLOAT32();
                    sample.mRot.w = file->readFLOAT32();
                }
                if(!(flags & 8))
                {
                    sample.mScale.x = file->readFLOAT32();
                    sample.mScale.y = file->readFLOAT32();
                    sample.mScale.z = file->readFLOAT32();
                }
                UINT32 sampleCount = file->readUINT32();
                for(UINT32 i = 0; i < sampleCount; i++)
                {
                    if(flags & 2)
                    {
                        sample.mPos.x = file->readFLOAT32();
                        sample.mPos.y = file->readFLOAT32();
                        sample.mPos.z = file->readFLOAT32();
                    }
                    if(flags & 4)
                    {
                        sample.mRot.x = file->readFLOAT32();
                        sample.mRot.y = file->readFLOAT32();
                        sample.mRot.z = file->readFLOAT32();
                        sample.mRot.w = file->readFLOAT32();
                    }
                    if(flags & 8)
                    {
                        sample.mScale.x = file->readFLOAT32();
                        sample.mScale.y = file->readFLOAT32();
                        sample.mScale.z = file->readFLOAT32();
                    }
                    prs->addFrame(sample);
                }
                
            }
            break;
        case CT_PARTICLESYSTEM:
            {
                XFCASSERT(chunkVersion == 1);
                ParticleSystem *g = ParticleSystem::create(this, chunkId);
                g->setParentId(file->readUINT32());
                g->setAlias(getString(file));
                REAL scale = file->readFLOAT32();
                CHAR *filename = getString(file);
                
                XFuParticleSystem *ps = new XFuParticleSystem();
                ps->load(filename);
                ps->loadTextures();
                ps->mSizeScale *= scale;
                g->setPS(ps);
            }
            break;
        default:
            break;
        }
        // set position
        file->seek(pos + chunkBlockLength, SEEK_SET);
    }
    
    file->close();
    
    // Initload all nodes
    XFcHashtable<UINT32, Node *>::iterator itr = mNodes->begin();
    while(itr != mNodes->end())
    {
        itr.getValue()->initLoad();
        ++itr;
    }
    
    return loadSuccess;
}

CHAR *GameGraph::getString(XFcFile *aFile)
{
    UINT8 len = aFile->readUINT8();
    CHAR8 *val = new CHAR8[len + 1];
    aFile->read(val, sizeof(CHAR8), len);
    val[len] = '\0';
    return val;
}

void GameGraph::readPRS(XFcFile *aFile, XFcMatrix4 &aMat, bool aNoScale)
{
    XFcVector3 pos;
    XFcQuaternion rot;
    XFcVector3 scale;
    pos.x = aFile->readFLOAT32();
    pos.y = aFile->readFLOAT32();
    pos.z = aFile->readFLOAT32();
    rot.x = aFile->readFLOAT32();
    rot.y = aFile->readFLOAT32();
    rot.z = aFile->readFLOAT32();
    rot.w = aFile->readFLOAT32();
    if(!aNoScale)
    {
        scale.x = aFile->readFLOAT32();
        scale.y = aFile->readFLOAT32();
        scale.z = aFile->readFLOAT32();
    }
    else
    {
        scale.x = scale.y = scale.z = REALi(1);
    }

    XFcMatrix4 rotation;
    XFcMath::matrixFromQuaternion(rotation, rot);
    
    XFcMath::matrixIdentity(aMat);
    aMat.m[0][0] = scale.x;
    aMat.m[1][1] = scale.y;
    aMat.m[2][2] = scale.z;
    
    aMat *= rotation;
    
    aMat.m[3][0] = pos.x;
    aMat.m[3][1] = pos.y;
    aMat.m[3][2] = pos.z;

}

//! Reads a 32-bit float and writes it as a REAL into the buffer and advances the buffer pointer.
void GameGraph::readREALToBuffer(XFcFile *aFile, UINT8 **aBuffer)
{
    UINT8 *buf = *aBuffer;
    *((REAL*)buf) = aFile->readFLOAT32();
    *aBuffer += sizeof(REAL);
}

//! Reads an UINT32 into the buffer and advances the buffer pointer.
void GameGraph::readUINT32ToBuffer(XFcFile *aFile, UINT8 **aBuffer)
{
    UINT8 *buf = *aBuffer;
    *((UINT32*)buf) = aFile->readUINT32();
    *aBuffer += sizeof(UINT32);
}

