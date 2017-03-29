/*! \file
 * Plane.cpp <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Plane.cpp,v 1.8 2003/08/07 07:50:42 lars Exp $
 * $Date: 2003/08/07 07:50:42 $
 * $Revision: 1.8 $
 */

#include <xforge.h>
#include <xfcore/XFcHashTable.h>
#include <xfutil/XFuDynamicArray.h>

#include "Node.h"
#include "Mesh.h"
#include "Buffers.h"
#include "Plane.h"
#include "StuntPlane.h"


//! Static creation.
Plane * Plane::create(XFcGL *aGL, const CHAR *aModelFile)
{
    Plane *p = new Plane(aGL);
    XFCASSERT(p);

    // Create hash table for keeping track of nodes.
    p->mNodes = new XFcHashtable<UINT32, Node *>();

    // Create vertex buffer used for drawing the propellar.
    p->mVB = XFcGLVertexBuffer::create(XFCGL_LVERTEX, sizeof(XFcGLLVertex), 4);   

    XFCASSERT(p->mNodes && p->mVB);
    
    // Try to load plane mesh.
    if (!p->loadFromXFF(aModelFile)) 
    {
        delete p;
        return NULL;
    }
    return p;
}


Plane::Plane(XFcGL *aGL) : mGL(aGL), mNodes(NULL), mVB(NULL)
{
}


Plane::~Plane()
{
    // Delete all nodes.
    XFcHashtable<UINT32, Node *>::iterator itr = mNodes->begin();
    while (itr != mNodes->end())
    {
        delete itr.getValue();
        itr++;
    }
    delete mNodes;
    delete mVB;
}


//! Finds a node by its id.
Node * Plane::getNodeById(UINT32 aId)
{
    if (aId == 0xffffffff)
        return NULL;

    XFcHashtable<UINT32, Node *>::iterator itr = mNodes->find(aId);

    if (itr == mNodes->end())
        return NULL;
    
    return itr.getValue();
}


//! Add node to node hash.
void Plane::addNode(Node *aNode)
{
    mNodes->put(aNode->getId(), aNode);
}


//! Render plane mesh and rotating propellar.
void Plane::render()
{
    // Render Plane meshes as defined in the XFF file.

    XFcHashtable<UINT32, Node *>::iterator itr = mNodes->begin();
    while (itr != mNodes->end())
    {
        Node *n = itr.getValue(); 
        if (n->getType() == NT_MESH) n->render();
        itr++;
    }

    // Render rotating propeller.
    
    // Lock vertex buffer.
    XFcGLLVertex *v;
    v = (XFcGLLVertex *)mVB->lock(0);
    
    XFCASSERT(v && "Vertex buffer locking failed.");
    

    // Hardcoded propeller vertices. This is a triangle fan.

    // Upper right.
    v[0].mX = REALf(1.4f * 4);           
    v[0].mY = REALf(0.15f * 4);
    v[0].mZ = REALf(1.23f * 4);
    v[0].mDiffuseColor = 0xff302010;
    
    // Upper left.
    v[1].mX = REALf(-1.4f * 4);
    v[1].mY = REALf(0.15f * 4);
    v[1].mZ = REALf(1.23f * 4);
    v[1].mDiffuseColor = 0xff302010;
    
    // Lower left.
    v[2].mX = REALf(-1.4f * 4);
    v[2].mY = REALf(-0.15f * 4);
    v[2].mZ = REALf(1.23f * 4);
    v[2].mDiffuseColor = 0xff302010;

    // Lower right.
    v[3].mX = REALf(1.4f * 4);
    v[3].mY = REALf(-0.15f * 4);
    v[3].mZ = REALf(1.23f * 4);
    v[3].mDiffuseColor = 0xff302010;

    // Make the propeller rotate around the Z-axis at a constant rate.

    XFcMatrix4 planeMatrix;

    // First, get current plane rotation matrix.
    mGL->getMatrix(XFCGLMAT_WORLD, planeMatrix);

    // Because the plane model is rotated 90 degrees too much around the X axis
    // in the XFF file the planeMatrix was earlier compensated for this. Here we
    // just rotate back again because the above coordinates were defined with a
    // noncompensated plane matrix in mind. FUBAR, I know. Don't care.
    XFcMath::matrixRotateX(planeMatrix, PI / 2);

    // Apply Z rotation.
    XFcMath::matrixRotateZ(planeMatrix, 0.02f * (XFcCore::getTick() % 1000));

    mGL->setMatrix(XFCGLMAT_WORLD, planeMatrix);

    mGL->setTexture(NULL);    
    mGL->renderPrimitive(mVB, XFCGLPT_TRIANGLEFAN, 0, 4, 0, 3, NULL);
    
    // Unlock vertex buffer.
    mVB->unlock();  
}


//! Adjust plane color.
void Plane::colorize(REAL aRed, REAL aGreen, REAL aBlue)
{
    XFcGLTriangleInfoBuffer *tib = NULL;

    XFcHashtable<UINT32, Node *>::iterator itr = mNodes->begin();
    while (itr != mNodes->end())
    {
        if (itr.getValue()->getType() == NT_TRIANGLEINFOBUFFER)
        {

            tib = ((TriangleInfoBuffer *)itr.getValue())->getTIB();
        }
        itr++;
    }
    if (tib == NULL) return;

    if (tib->mDiffuseColorOffs == -1) return;

    UINT8 *data = (UINT8 *)tib->lock();

    data += tib->mDiffuseColorOffs;

    INT i, j;
    UINT32 shade;

    for (i = 0; i < tib->mNumTriangles; i++)
    {
        UINT32 *diffuse = (UINT32 *)data;
        for (j = 0; j < 3; j++)
        {
            shade = *diffuse;

            if (((shade >> 16) & 0xff) > ((shade & 0xff)))
            {
                shade = (shade >> 16) & 0xff;
                UINT32 r, g, b;
                r = aRed * REALi(shade);
                g = aGreen * REALi(shade);
                b = aBlue * REALi(shade);

                if (r > 0xff) r = 0xff;
                if (g > 0xff) g = 0xff;
                if (b > 0xff) b = 0xff;

                *diffuse = r << 16 | g << 8 | b;
            }
            diffuse++;
        }
        data += tib->mInfoSize;
    }
    tib->unlock();
}


//! Loads the plane graph from XFF file, skipping most of the info we don't need for this game.
INT Plane::loadFromXFF(const char *aFilename)
{
    INT loadSuccess = 1;

    XFcFile *file = XFcFile::open(aFilename, XFCSTR("rb"));
    if (file == NULL) return 0;
    
    file->seek(0, SEEK_END);
    INT32 fileLen = file->tell();
    
    file->seek(0, SEEK_SET);
    while (file->tell() < fileLen && loadSuccess)
    {
        
        // Read header.
        UINT16 chunkType = file->readUINT16();
        UINT16 chunkVersion = file->readUINT16();
        UINT32 chunkId = file->readUINT32();
        UINT32 chunkBlockLength = file->readUINT32();
        
        // Save position.
        INT32 pos = file->tell();
        
        // Load the chunks we need, skip the rest.
        switch (chunkType)
        {
            case CT_MESH:
            {          
                XFCASSERT(chunkVersion == 3);

                // Create a mesh.

                UINT32 id = file->readUINT32();
                getString(file);

                // Ok, this should be the plane mesh. Go get it.

                Mesh *mesh = Mesh::create(this, chunkId);
                XFCASSERT(mesh);

                UINT16 submeshes = file->readUINT16();

                INT i;    
                for (i = 0; i < submeshes; i++)
                {
                    // Read a submesh.
                    Submesh *sm = new Submesh();
                    XFCASSERT(sm);
                        
                    sm->mVertexBufferId = file->readUINT32();
                    sm->mFaceListId = file->readUINT32();
                    sm->mTriangleInfoBufferId = file->readUINT32();
                    sm->mMaterialId = file->readUINT32();
                    sm->mTextureId = file->readUINT32();
                    file->readUINT32();
                    sm->mVertexOffset = file->readUINT32();
                    sm->mVertexCount = file->readUINT32();
                    file->readUINT8();

                    mesh->addSubmesh(sm);    
                }
                break;
            }
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

                vertexBufferFlags |= XFCGLVF_DIFFUSECOLOR;
                if (hasUVCoords) vertexBufferFlags |= XFCGLVF_TEXTURE1;

                if (!hasDiffuseColor)
                    vertexSize += 4;
                
                XFcGLVertexBuffer *vertexBuffer = 
                    XFcGLVertexBuffer::create(vertexBufferFlags, vertexSize, vertexCount);
                
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
                        XFCASSERT(0);
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

                // Build the vertex buffer node.
                VertexBuffer *vb = new VertexBuffer(this, chunkId);
                XFCASSERT(vb);
                vb->setVB(vertexBuffer);
                break;
            }

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

                break;
            }

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
                
                XFcGLTriangleInfoBuffer *triangleInfoBuffer = 
                    XFcGLTriangleInfoBuffer::create(triangleInfoFlags, triangleInfoSize, triangleCount);

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
                
                break;
            }
            default:
                break;
        }
        // Set position.
        file->seek(pos + chunkBlockLength, SEEK_SET);
    }
    
    file->close();
    
    // Initload all nodes.
    XFcHashtable<UINT32, Node *>::iterator itr = mNodes->begin();
    while (itr != mNodes->end())
    {
        itr.getValue()->initLoad();
        ++itr;
    }
    
    return loadSuccess;
}


//! Get length initiated string.
CHAR *Plane::getString(XFcFile *aFile)
{
    UINT8 len = aFile->readUINT8();
    CHAR8 *val = new CHAR8[len + 1];
    aFile->read(val, sizeof(CHAR8), len);
    val[len] = '\0';
    return val;
}


//! Reads a 32-bit float and writes it as a REAL into the buffer and advances the buffer pointer.
void Plane::readREALToBuffer(XFcFile *aFile, UINT8 **aBuffer)
{
    UINT8 *buf = *aBuffer;
    *((REAL*)buf) = 4*aFile->readFLOAT32();
    *aBuffer += sizeof(REAL);
}


//! Reads an UINT32 into the buffer and advances the buffer pointer.
void Plane::readUINT32ToBuffer(XFcFile *aFile, UINT8 **aBuffer)
{
    UINT8 *buf = *aBuffer;
    *((UINT32*)buf) = aFile->readUINT32();
    *aBuffer += sizeof(UINT32);
}
