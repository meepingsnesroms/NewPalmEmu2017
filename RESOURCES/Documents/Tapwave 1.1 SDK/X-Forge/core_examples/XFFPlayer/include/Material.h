/*! \file
 * Material.h <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Material.h,v 1.1 2003/05/20 11:40:46 mikko Exp $
 * $Date: 2003/05/20 11:40:46 $
 * $Revision: 1.1 $
 */
#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED


#include "Node.h"

//! Material class
class Material : public Node
{
public:
    //! Constructor.
    Material(GameGraph *aGameGraph, UINT32 aId) : Node(aGameGraph, aId)
    {
        mType = NT_MATERIAL;
    }
    
    //! Virtual destructor.
    virtual ~Material()
    {

    }

    //! Shading mode; see XFCGLSHADINGMODES.
    /*! \sa XFCGLSHADINGMODES
    */
    INT32 mShadingMode;
    
    //! Alpha blending. Values 0 and 1.
    INT32 mAlphaBlend;
    
    //! Source blend.
    INT32 mSourceBlend;
    
    //! Target blend.
    INT32 mTargetBlend;
    
    //! Perspective correction. Values 0 and 1.
    INT32 mPerspectiveCorrection;
    
    //! Wireframe mode. Values 0 and 1. Mainly meant for debugging.
    INT32 mWireframeMode;
    
    //! Non-zero if this material is double sided.
    INT32 mDoubleSided;
    
    //! Polygon offset (for sort).
    REAL mPolygonOffset;
    
};




#endif // !MATERIAL_H_INCLUDED
