/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Renderer interface class
 * 
 * $Id: XFcRenderer.h,v 1.7 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.7 $
 */

#ifndef XFC_CORE_XFCRENDERER_H_INCLUDED
#define XFC_CORE_XFCRENDERER_H_INCLUDED


//! Renderer base class. Used as an interface for core callback.
class XFCDLLEXPORT XFcRenderer 
{
public:

    //! Called every time in the rendering loop.
    XFCIMPORT virtual void render();

    //! Called before back buffer is displayed on screen.
    /*!
     *  The function should return 1 if it has handled the screen update,
     *  or for some other reason doesn't want the core to update the screen,
     *  or 0 to let core carry on. aMoreInfo parameter points to platform-
     *  specific information, and is currently reserved.
     */
    XFCIMPORT virtual INT updateScreen(void *aMoreInfo);

    //! Called when this renderer is activated.
    XFCIMPORT virtual void initRenderer();

    //! Called when this renderer is deactivated.
    XFCIMPORT virtual void deinitRenderer();

};


#endif // !XFC_CORE_XFCRENDERER_H_INCLUDED

