/*! \file
* Texture.h <br>
* Copyright 2003 Fathammer Ltd
*
* $Id: Texture.h,v 1.1 2003/05/20 11:40:46 mikko Exp $
* $Date: 2003/05/20 11:40:46 $
* $Revision: 1.1 $
*/

#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include "Node.h"

//! Texture class, just a node wrapper for XFcGLTexture
class Texture : public Node
{
public:
    //! Constructor.
    Texture(GameGraph *aGameGraph, UINT32 aId) : Node(aGameGraph, aId), mTex(NULL)
    {
        mType = NT_TEXTURE;
    }
    
    //! Virtual destructor.
    virtual ~Texture()
    {
        delete mTex;
        mTex = NULL;
    }
    
    XFcGLTexture *getTex() { return mTex; }
    void setTex(XFcGLTexture *aTex) { mTex = aTex; }
    
protected:
    XFcGLTexture *mTex;
    
};




#endif // !TEXTURE_H_INCLUDED
