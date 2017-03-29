/*! \file
 * Plane.h <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Plane.h,v 1.5 2003/08/06 11:42:45 jari Exp $
 * $Date: 2003/08/06 11:42:45 $
 * $Revision: 1.5 $
 */

#ifndef PLANE_H_INCLUDED
#define PLANE_H_INCLUDED

class Mesh;
class Node;
class XFcGL;
class XFcFile;
class XFcMatrix4;

template<class Key, class Value> class XFcHashtable;

//! XFF chunk type codes. We only use a few of theese here.
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


//! Happy little airplane class. Mainly used for loading and rendering the plane mesh.
class Plane
{
public:
    //! Static constructor.
    static Plane * create(XFcGL *aGL, const CHAR *aModelFile);
    
    //! Virtual destructor.
    virtual ~Plane();

    //! Loads a scene from an XFF file.
    INT loadFromXFF(const char *aFilename);

    //! GL accessor.
    XFcGL *getGL() { return mGL; }

    //! Adds a node to plane node hash. Nodes self-register themselves using this method.
    void addNode(Node *aNode);

    //! Get node by id from hashtable.
    Node * getNodeById(UINT32 aId);        

    void colorize(REAL aRed, REAL aGreen, REAL aBlue);

    //! Render the plane using current world, camera and projection transforms.
    void render();

protected:
    //! Protected constructor.
    Plane(XFcGL *aGL);

    //! XForge GL.
    XFcGL *mGL;

    // Vertex buffer used for drawing the propeller.
    XFcGLVertexBuffer *mVB; 

    //! Hash table of all the nodes in memory.
    XFcHashtable<UINT32, Node *> *mNodes;

    //! Last rendered frame.
    UINT32 mLastFrame;

    //! Helper functions for xff loading.
    CHAR *getString(XFcFile *aFile);

    //! Reads a 32-bit float and writes it as a REAL into the buffer and advances the buffer pointer.
    void readREALToBuffer(XFcFile *aFile, UINT8 **aBuffer);

    //! Reads an UINT32 into the buffer and advances the buffer pointer.
    void readUINT32ToBuffer(XFcFile *aFile, UINT8 **aBuffer);
};


#endif // !PLANE_H_INCLUDED
