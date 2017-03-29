/*! \file
 * Node.h <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Node.h,v 1.1 2003/05/20 11:40:46 mikko Exp $
 * $Date: 2003/05/20 11:40:46 $
 * $Revision: 1.1 $
 */

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "GameGraph.h"

//! Node type enumeration
enum NODE_TYPE { NT_NA, NT_GROUP, NT_MESH, NT_CAMERA, NT_VERTEXBUFFER, NT_FACELIST, NT_TRIANGLEINFOBUFFER, NT_MATERIAL, NT_TEXTURE, NT_PARTICLESYSTEM };

//! Gamegraph node base class
class Node
{
public:    
    //! Virtual destructor.
    virtual ~Node() { }

    UINT32 getId() { return mId; }
    NODE_TYPE getType() { return mType; }

    //! This gets called for each node after all nodes have been loaded
    virtual void initLoad() { };
    
protected:
    //! Protected constructor.
    Node(GameGraph *aGameGraph, UINT32 aId) : mGameGraph(aGameGraph), mId(aId), mType(NT_NA)
    { 
        // Self-register
        mGameGraph->addNode(this);
    }

    //! Pointer to the gamegraph this node is attached to.
    GameGraph *mGameGraph;
    //! Unique Id of this gamegraph node
    UINT32 mId;

    //! Type of this node
    NODE_TYPE mType;
};



#endif // !NODE_H_INCLUDED
