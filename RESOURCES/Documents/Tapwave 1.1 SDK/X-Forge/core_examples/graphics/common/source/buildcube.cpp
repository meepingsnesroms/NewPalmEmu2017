/*! \file 
 * X-Forge Core Example <br>
 * Copyright 2002,2003 Fathammer Ltd
 * 
 * \brief Code to build a cube vertex buffer.
 * 
 * $Id: buildcube.cpp,v 1.3 2003/01/17 08:50:25 jetro Exp $
 * $Date: 2003/01/17 08:50:25 $
 * $Revision: 1.3 $
 */

#include <xforge.h>


XFcGLVertexBuffer *xfBuildCube()
{
    // Create 36 LVERTEX vertices (2 triangles in every 6 sides of cube).
    XFcGLVertexBuffer *vb = XFcGLVertexBuffer::create(XFCGL_LVERTEX,
                                                      sizeof(XFcGLLVertex), 36);
    if (vb == NULL)
        return NULL;
    
    XFcGLLVertex *v;
    
    // Lock vertex buffer. Quit if the operation fails.
    v = (XFcGLLVertex *)vb->lock(0);
    if (v == NULL)
    {
        delete vb;
        return NULL;
    }
    
    /*
     * Vertices of the cube:
     * 
     * Cornerpoints are numbered 1 .. 8
     *   
     *     1-------2
     *     |     / |                                          7------8
     *     |   /   |                                        / |     /|
     *     | /     |                                      /   |   /  |
     *     1-------3-------4-------2-------1             1-------2   |
     *     | \     |     / |     / | \     |             |    5--|---6
     *     |   \   |   /   |   /   |   \   |     =>      |  /    |  /
     *     |     \ | /     | /     |     \ |             |/      |/
     *     7-------5-------6-------8-------7             3-------4
     *     | \     |
     *     |   \   |
     *     |     \ |
     *     7-------8
     *     
     *       
     * Texture coordinates U and V tell the position of the texture to be mapped 
     * to triangle's corner. U and V are between 0 and 1. (0,0) is the upper
     * left corner of the texture and (1,1) the lower right corner. If U or V are
     * > 1 the texture will be wrapped => 1.1 = 0.1.
     *         
     *     Texture:                Triangle:
     *     
     *     ---------                               1
     *     |A     B|        Vertex 1: U,V=0,0      |\
     *     |    F  |    =>  Vertex 2: U,V=1,0  =>  |A \
     *     |  G    |        Vertex 3: U,V=1,1      |   F\
     *     |C     D|                               |B    D\
     *     ---------                               2-------3
     *       
     * Textures width and height have to be power's of two. Maximum is 2^8 = 256.
     */
        
    // Vertex coordinates: mX mY mZ, 
    // Texture coordinates mU mV
    
    // Color is in INT32 = Alpha-R-G-B, in 8bit per color.
    // Alpha is set to 0x80 on every face to get 50% transparency when blending is enabled.
    
    //                                     Cornerpoint:
        
    v[0].mX = -5;                               // 5.
    v[0].mY = -5;
    v[0].mZ = -5;
    v[0].mDiffuseColor = 0x802222ff;
    v[0].mU = 0;
    v[0].mV = 1;
    
    v[1].mX = 5;                                // 6.
    v[1].mY = -5;
    v[1].mZ = -5;
    v[1].mDiffuseColor = 0x802222ff;
    v[1].mU = 0;
    v[1].mV = 0;
    
    v[2].mX = 5;                                // 8.
    v[2].mY = 5;
    v[2].mZ = -5;
    v[2].mDiffuseColor = 0x802222ff;
    v[2].mU = 1;
    v[2].mV = 0;
    
    
    v[3].mX = -5;                               // 5.
    v[3].mY = -5;
    v[3].mZ = -5;
    v[3].mDiffuseColor = 0x802222ff;
    v[3].mU = 0;
    v[3].mV = 1;
    
    v[4].mX = 5;                                // 8.
    v[4].mY = 5;
    v[4].mZ = -5;
    v[4].mDiffuseColor = 0x802222ff;
    v[4].mU = 1;
    v[4].mV = 0;
    
    v[5].mX = -5;                               // 7.
    v[5].mY = 5;
    v[5].mZ = -5;
    v[5].mDiffuseColor = 0x802222ff;
    v[5].mU = 1;
    v[5].mV = 1;
    
    
    v[6].mX = -5;                               // 3.
    v[6].mY = -5;
    v[6].mZ = 5;
    v[6].mDiffuseColor = 0x8022ff22;
    v[6].mU = 0;
    v[6].mV = 1;
    
    v[7].mX = 5;                                // 2.
    v[7].mY = 5;
    v[7].mZ = 5;
    v[7].mDiffuseColor = 0x8022ff22;
    v[7].mU = 1;
    v[7].mV = 0;
    
    v[8].mX = 5;                                // 4.
    v[8].mY = -5;
    v[8].mZ = 5;
    v[8].mDiffuseColor = 0x8022ff22;
    v[8].mU = 1;
    v[8].mV = 1;
    
    
    v[9].mX = -5;                               // 3.
    v[9].mY = -5;
    v[9].mZ = 5;
    v[9].mDiffuseColor = 0x8022ff22;
    v[9].mU = 0;
    v[9].mV = 1;
    
    v[10].mX = -5;                              // 1.
    v[10].mY = 5;
    v[10].mZ = 5;
    v[10].mDiffuseColor = 0x8022ff22;
    v[10].mU = 0;
    v[10].mV = 0;
    
    v[11].mX = 5;                               // 2.
    v[11].mY = 5;
    v[11].mZ = 5;
    v[11].mDiffuseColor = 0x8022ff22;
    v[11].mU = 1;
    v[11].mV = 0;
    
    
    v[12].mX = -5;                              // 5.
    v[12].mY = -5;
    v[12].mZ = -5;
    v[12].mDiffuseColor = 0x80ff22ff;
    v[12].mU = 1;
    v[12].mV = 1;
    
    v[13].mX = -5;                              // 1.
    v[13].mY = 5;
    v[13].mZ = 5;
    v[13].mDiffuseColor = 0x80ff22ff;
    v[13].mU = 0;
    v[13].mV = 0;
    
    v[14].mX = -5;                              // 3.
    v[14].mY = -5;
    v[14].mZ = 5;
    v[14].mDiffuseColor = 0x80ff22ff;
    v[14].mU = 1;
    v[14].mV = 0;
    
    
    v[15].mX = -5;                              // 5.
    v[15].mY = -5;
    v[15].mZ = -5;
    v[15].mDiffuseColor = 0x80ff22ff;
    v[15].mU = 1;
    v[15].mV = 1;
    
    v[16].mX = -5;                              // 7.
    v[16].mY = 5;
    v[16].mZ = -5;
    v[16].mDiffuseColor = 0x80ff22ff;
    v[16].mU = 0;
    v[16].mV = 1;
    
    v[17].mX = -5;                              // 1.
    v[17].mY = 5;
    v[17].mZ = 5;
    v[17].mDiffuseColor = 0x80ff22ff;
    v[17].mU = 0;
    v[17].mV = 0;
    
    
    v[18].mX = 5;                               // 2.
    v[18].mY = 5;
    v[18].mZ = 5;
    v[18].mDiffuseColor = 0x80ff2222;
    v[18].mU = 1;
    v[18].mV = 1;
    
    v[19].mX = 5;                               // 6.
    v[19].mY = -5;
    v[19].mZ = -5;
    v[19].mDiffuseColor = 0x80ff2222;
    v[19].mU = 0;
    v[19].mV = 0;
    
    v[20].mX = 5;                               // 4.
    v[20].mY = -5;
    v[20].mZ = 5;
    v[20].mDiffuseColor = 0x80ff2222;
    v[20].mU = 1;
    v[20].mV = 0;
    
    
    v[21].mX = 5;                               // 8.
    v[21].mY = 5;
    v[21].mZ = -5;
    v[21].mDiffuseColor = 0x80ff2222;
    v[21].mU = 0;
    v[21].mV = 1;
    
    v[22].mX = 5;                               // 6.
    v[22].mY = -5;
    v[22].mZ = -5;
    v[22].mDiffuseColor = 0x80ff2222;
    v[22].mU = 0;
    v[22].mV = 0;
    
    v[23].mX = 5;                               // 2.
    v[23].mY = 5;
    v[23].mZ = 5;
    v[23].mDiffuseColor = 0x80ff2222;
    v[23].mU = 1;
    v[23].mV = 1;
    
    
    v[24].mX = -5;                              // 1.
    v[24].mY = 5;
    v[24].mZ = 5;
    v[24].mDiffuseColor = 0x8022ffff;
    v[24].mU = 0;
    v[24].mV = 0;
    
    v[25].mX = -5;                              // 7.
    v[25].mY = 5;
    v[25].mZ = -5;
    v[25].mDiffuseColor = 0x8022ffff;
    v[25].mU = 1;
    v[25].mV = 0;
    
    v[26].mX = 5;                               // 2.
    v[26].mY = 5;
    v[26].mZ = 5;
    v[26].mDiffuseColor = 0x8022ffff;
    v[26].mU = 0;
    v[26].mV = 1;
    
    
    v[27].mX = 5;                               // 8.
    v[27].mY = 5;
    v[27].mZ = -5;
    v[27].mDiffuseColor = 0x8022ffff;
    v[27].mU = 1;
    v[27].mV = 1;
    
    v[28].mX = 5;                               // 2.
    v[28].mY = 5;
    v[28].mZ = 5;
    v[28].mDiffuseColor = 0x8022ffff;
    v[28].mU = 0;
    v[28].mV = 1;
    
    v[29].mX = -5;                              // 7.
    v[29].mY = 5;
    v[29].mZ = -5;
    v[29].mDiffuseColor = 0x8022ffff;
    v[29].mU = 1;
    v[29].mV = 0;
    
    
    v[30].mX = -5;                              // 3.
    v[30].mY = -5;
    v[30].mZ = 5;
    v[30].mDiffuseColor = 0x80ffff22;
    v[30].mU = 1;
    v[30].mV = 1;
    
    v[31].mX = 5;                               // 4.
    v[31].mY = -5;
    v[31].mZ = 5;
    v[31].mDiffuseColor = 0x80ffff22;
    v[31].mU = 0;
    v[31].mV = 1;
    
    v[32].mX = -5;                              // 5.
    v[32].mY = -5;
    v[32].mZ = -5;
    v[32].mDiffuseColor = 0x80ffff22;
    v[32].mU = 1;
    v[32].mV = 0;    
    
    v[33].mX = 5;                               // 6.
    v[33].mY = -5;
    v[33].mZ = -5;
    v[33].mDiffuseColor = 0x80ffff22;
    v[33].mU = 0;
    v[33].mV = 0;
    
    v[34].mX = -5;                              // 5.
    v[34].mY = -5;
    v[34].mZ = -5;
    v[34].mDiffuseColor = 0x80ffff22;
    v[34].mU = 1;
    v[34].mV = 0;
    
    v[35].mX = 5;                               // 4.
    v[35].mY = -5;
    v[35].mZ = 5;
    v[35].mDiffuseColor = 0x80ffff22;
    v[35].mU = 0;
    v[35].mV = 1;
    
    // Unlock vertex buffer
    vb->unlock();
    
    return vb;  
}
