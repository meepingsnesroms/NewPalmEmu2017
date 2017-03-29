/*! \file
 * GameGraph.h <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: GameGraph.h,v 1.2 2003/09/04 12:26:31 toni Exp $
 * $Date: 2003/09/04 12:26:31 $
 * $Revision: 1.2 $
 */
#ifndef GAMEGRAPH_H_INCLUDED
#define GAMEGRAPH_H_INCLUDED

class Group;
class Node;
class Camera;
class XFcGL;
class XFcFile;
class XFcMatrix4;

template<class Key, class Value> class XFcHashtable;

//! Game graph class
class GameGraph
{
public:
    //! Static constructor.
    static GameGraph * create(XFcGL *aGL);
    
    //! Virtual destructor.
    virtual ~GameGraph();

    //! Root node accessor
    Group *getRoot() { return mRootNode; }
    void setRoot(Group *aSceneRoot) { mRootNode = aSceneRoot; }

    Camera *getActiveCamera() { return mActiveCamera; }
    void setActiveCamera(Camera *aCam) { mActiveCamera = aCam; }

    //! Finds a node from the hash table
    Node *getNodeById(UINT32 aId);

    //! Loads a scene from XFF
    INT loadFromXFF(char *aFilename);

    //! GL accessor
    XFcGL *getGL() { return mGL; }

    //! Render a frame
    void render();

    //! Adds a node to the hash. Nodes self-register themselves using this method
    void addNode(Node *aNode);

    //! Returns the approximated tick (assume 25fps)
    INT32 getTick() { return mLastFrame * 1000 / 25; }

protected:
    //! Protected constructor.
    GameGraph(XFcGL *aGL);

    //! Root group
    Group *mRootNode;

    //! Active camera
    Camera *mActiveCamera;

    //! XForge GL
    XFcGL *mGL;

    //! Hash table of all the nodes in memory
    XFcHashtable<UINT32, Node *> *mNodes;

    //! Last rendered frame
    UINT32 mLastFrame;

    //! Helper functions for xff loading
    CHAR *getString(XFcFile *aFile);
    void readPRS(XFcFile *aFile, XFcMatrix4 &aMat, bool aNoScale = false);
    //! Reads a 32-bit float and writes it as a REAL into the buffer and advances the buffer pointer.
    void readREALToBuffer(XFcFile *aFile, UINT8 **aBuffer);
    //! Reads an UINT32 into the buffer and advances the buffer pointer.
    void readUINT32ToBuffer(XFcFile *aFile, UINT8 **aBuffer);
    
};



#endif // !GAMEGRAPH_H_INCLUDED
