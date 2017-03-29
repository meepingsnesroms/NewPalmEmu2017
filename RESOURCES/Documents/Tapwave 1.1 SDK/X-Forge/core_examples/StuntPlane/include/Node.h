/*! \file
 * Node.h <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Node.h,v 1.2 2003/07/02 06:54:38 lars Exp $
 * $Date: 2003/07/02 06:54:38 $
 * $Revision: 1.2 $
 */

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "Plane.h"

class Plane;

//! Node type enumeration. Only the types we will use in this game.
enum NODE_TYPE 
{  
    NT_NA, 
    NT_MESH, 
    NT_VERTEXBUFFER, 
    NT_FACELIST, 
    NT_TRIANGLEINFOBUFFER, 
};


//! Plane model node base class.
class Node
{
public:    
    //! Virtual destructor.
    virtual ~Node() { }

    //! Get node id.
    UINT32 getId() { return mId; }

    //! Return node type.
    NODE_TYPE getType() { return mType; }

    //! This gets called for each node after all nodes have been loaded.
    virtual void initLoad() { };

    //! Render this node.
    virtual void render() { };
    
protected:
    //! Protected constructor.
    Node(Plane *aPlane, UINT32 aId) : mPlane(aPlane), mId(aId), mType(NT_NA)
    { 
        // Self-register
        mPlane->addNode(this);
    }

    //! Pointer to the plane.
    Plane *mPlane;

    //! Unique Id of this gamegraph node.
    UINT32 mId;

    //! Type of this node.
    NODE_TYPE mType;
};


#endif // !NODE_H_INCLUDED
