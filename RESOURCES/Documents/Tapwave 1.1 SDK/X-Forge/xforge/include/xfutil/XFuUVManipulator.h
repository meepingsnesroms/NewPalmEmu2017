/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief UV Coordinate manipulation routines
 * 
 * $Id: XFuUVManipulator.h,v 1.7 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.7 $
 */

#ifndef XFUUVMANIPULATOR_H_INCLUDED
#define XFUUVMANIPULATOR_H_INCLUDED




//! Collection of UV coordinate generation routines.
class XFuUVManipulator
{
public:
    //! Generates environment mapping coordinates.
    /*!
     * Overwrites the UV coordinates of the vertex buffer for 'environment mapping'
     * effect. Fetches current matrices from the GL. The vertex buffer must be of
     * type (XFCGLVF_XYZ | XFCGLVF_NORMAL | XFCGLVF_DIFFUSECOLOR | XFCGLVF_TEXTURE1).
     * If the type is not correct or locking fails, the function doesn't do anything.    
     */
    static void generateEnvmapCoordinates(XFcGLVertexBuffer *aVertexBuffer, XFcGL *aGL);
};


#endif // !XFUUVMANIPULATOR_H_INCLUDED

