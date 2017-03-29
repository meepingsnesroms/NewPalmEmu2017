/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Static link 'use' interface for code parts to discard unused parts at link time
 * 
 * $Id: XFcUse.h,v 1.17 2003/10/15 09:32:45 kkallio Exp $
 * $Date: 2003/10/15 09:32:45 $
 * $Revision: 1.17 $
 */

#ifndef XFC_CORE_XFCUSE_H_INCLUDED
#define XFC_CORE_XFCUSE_H_INCLUDED


//! Includes default set of features in the core. Meant to be called from xfcAppInit(). 
/*! Default set includes: 
 *  CFLFilterZlib
 *  GLDefault
 *  ImageFilterPCX
 *  ImageFilterTGA 
 *  AudioDefault
 */
extern void XFCDLLEXPORT XFCIMPORT xfcUseDefaults();

//! Includes default audio system in the core. Meant to be called from xfcAppInit().
extern void XFCDLLEXPORT XFCIMPORT xfcUseAudioDefault();

//! Includes ZLib filter in the core. Meant to be called from xfcAppInit().
extern void XFCDLLEXPORT XFCIMPORT xfcUseCFLFilterZlib();

//! Includes default GL device in the core. Meant to be called from xfcAppInit(). 
extern void XFCDLLEXPORT XFCIMPORT xfcUseGLDefault();

//! Includes PCX loader filter in the core. Meant to be called from xfcAppInit(). 
extern void XFCDLLEXPORT XFCIMPORT xfcUseImageFilterPCX();

//! Includes TGA loader filter in the core. Meant to be called from xfcAppInit(). 
extern void XFCDLLEXPORT XFCIMPORT xfcUseImageFilterTGA();

//! Includes 2D vector drawing functionality to the core. Meant to be called from xfcAppInit().
extern void XFCDLLEXPORT XFCIMPORT xfcUse2DVectorGraphics();

//! FSAA output device (4x screen size, real-time downsampling). Meant to be called from xfcAppInit(). 
extern void XFCDLLEXPORT XFCIMPORT xfcUseGLDefaultFSAA();

//! Upsample output device (1/4 screen size, real-time upsampling). Meant to be called from xfcAppInit(). 
extern void XFCDLLEXPORT XFCIMPORT xfcUseGLDefaultUpsample();

//! ZBuffer output device. Meant to be called from xfcAppInit(). 
extern void XFCDLLEXPORT XFCIMPORT xfcUseGLZBuffer();

//! Default rasterizer with binary log output. Meant to be called from xfcAppInit(). 
extern void XFCDLLEXPORT XFCIMPORT xfcUseGLDefaultProfiler();

//! Includes network communication device in the core. Meant to be called from xfcAppInit().
extern void XFCDLLEXPORT XFCIMPORT xfcUseNetwork();

//! Tells GL to use all default fillers. Should be called after GL creation. GLDefault calls this automatically.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseDefaults();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerFlat();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerFlatAdd();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerFlatAlpha();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerFlatInvmul();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerGouraud();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerGouraudAdd();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerGouraudAlpha();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerGouraudInvmul();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerGreyscaleGouraud();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerGreyscaleGouraudAdd();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerGreyscaleGouraudAlpha();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerGreyscaleGouraudInvmul();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexture();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureAdd();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureAlpha();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureInvmul();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexture5515();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureAdd5515();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureAlpha5515();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureInvmul5515();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureFlat();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureFlatAdd();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureFlatAlpha();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureFlatInvmul();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureGouraud();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureGouraudAdd();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureGouraudAlpha();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureGouraudInvmul();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureGreyscaleGouraud();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureGreyscaleGouraudAdd();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureGreyscaleGouraudAlpha();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureGreyscaleGouraudInvmul();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspective();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspective5515();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveAdd();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveAdd5515();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveAlpha();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveInvmul();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveAlpha5515();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveInvmul5515();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveFlat();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveFlatAdd();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveFlatAlpha();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveFlatInvmul();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveGouraud();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveGouraudAdd();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveGouraudAlpha();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveGouraudInvmul();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveGreyscaleGouraud();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveGreyscaleGouraudAdd();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveGreyscaleGouraudAlpha();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveGreyscaleGouraudInvmul();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureAddPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureAlphaPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureInvmulPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureFlatPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureFlatAddPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureFlatAlphaPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureFlatInvmulPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureGouraudPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureGouraudAddPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureGouraudAlphaPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureGouraudInvmulPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureGreyscaleGouraudPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureGreyscaleGouraudAddPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureGreyscaleGouraudAlphaPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTextureGreyscaleGouraudInvmulPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectivePal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveAddPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveAlphaPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveInvmulPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveFlatPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveFlatAddPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveFlatAlphaPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveFlatInvmulPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveGouraudPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveGouraudAddPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveGouraudAlphaPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveGouraudInvmulPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveGreyscaleGouraudPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveGreyscaleGouraudAddPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveGreyscaleGouraudAlphaPal55X5();

//! Tells GL to use this filler. Should be called after GL creation. Not needed for GLDefault.
extern void XFCDLLEXPORT XFCIMPORT xfcGLUseFillerTexturePerspectiveGreyscaleGouraudInvmulPal55X5();

#endif // !XFC_CORE_XFCUSE_H_INCLUDED

