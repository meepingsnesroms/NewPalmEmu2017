/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Particle system utility
 * 
 * $Id: XFuParticleSystem.h,v 1.12 2003/10/01 08:10:05 peppe Exp $
 * $Date: 2003/10/01 08:10:05 $
 * $Revision: 1.12 $
 */
#ifndef XFUPARTICLESYSTEM_H_INCLUDED
#define XFUPARTICLESYSTEM_H_INCLUDED


class XFuParticleSystem;


//! Noise controller for the XFuParticleSystem class.
class XFuNoiseController
{
public:
    INT32 mType;    //!< Type of particle system.
    XFcFixed mValue;    //!< Noise 'value' - strenght of the particle system.
    XFcFixed mPeriod;   //!< Noise 'period' - time in which the noise loops, or changes.
    XFcFixed noise(INT32 aTick, XFuParticleSystem * ps); //!< Generate noise.
    void write(XFcFile * aFile);    //!< Write the noise controller data into a file.
    void read(XFcFile * aFile);     //!< Read the noise controller data from a file.
};


//! Flags for the particle system.
enum XFUPARTICLESYSTEM_FLAGBITS
{
    //! X min is a collider.
    XFUPSF_COLLIDER_XMIN = 1,
    //! Y min is a collider.
    XFUPSF_COLLIDER_YMIN = 2,
    //! Z min is a collider.
    XFUPSF_COLLIDER_ZMIN = 4,
    //! X max is a collider.
    XFUPSF_COLLIDER_XMAX = 8,
    //! Y max is a collider.
    XFUPSF_COLLIDER_YMAX = 16,
    //! Z max is a collider.
    XFUPSF_COLLIDER_ZMAX = 32,
    //! Does N iterations per second (and not FPS iterations).
    XFUPSF_FORCEITERATIONS = 64,
    //! Not implemented at the moment (world vs object space).
    XFUPSF_WORLDSPACE_PARTICLES = 128,
    //! Flag set in the editor, used in high-level x-forge.
    XFUPSF_TICK_ONLY_WHEN_SEEN = 256  
};


//! Particle system class.
/*!
 *  This particle system class runs and renders particle systems made with the
 *  'thingamajig' particle system editor.
 */
class XFuParticleSystem  
{
    // Everything is made public for the editor.
public:
    UINT32 mFlags;      //!< Flags (see XFUPARTICLESYSTEM_FLAGBITS enum).

    //! Launch velocity.
    XFcFixed mLaunchVelocity[3];
    //! Noise controllers for launch velocity.
    XFuNoiseController mLaunchVelocityVar[3];

    //! Damping (emulates friction).
    XFcFixed mDamping[3];

    //! Weight (or gravity, wind, whatever).
    XFcFixed mWeight[3];
    //! Noise contollers for weight.
    XFuNoiseController mNoise[3];

    //! Launch rate (particles per second).
    XFcFixed mLaunchRate;
    //! Maximum age (in msec).
    INT32 mMaxAge;
    //! Maximum age noise controller.
    XFuNoiseController mAgeVariation;
    //! Maximum number of particles for all time.
    INT32 mMaxTotal;
    //! Maximum number of particles visible at any time. DO NOT CHANGE DIRECTLY.
    INT32 mMaxVisible;

    //! All sizes are scaled by this value.
    XFcFixed mSizeScale;
    //! Scaling value for the rendering billboards.
    /*! This is inverse of the camera scale in ViewMatrix.
     */
    XFcFixed mViewScale;
    //! Time is scaled by this value (for 'bullet-time'ish things) - unfinished.
    XFcFixed mTimeScale;
    //! Maximum iterations per second.
    XFcFixed mDesiredFPS;

    //! Alpha mode (none, alpha, add, mul, invmul).
    INT32 mAlphaMode;
    //! Alpha value at the beginning of the lifespan.
    XFcFixed mAlphaStart;
    //! Alpha value at the end of the lifespan.
    XFcFixed mAlphaEnd;
    //! Noise controller for alpha.
    XFuNoiseController mAlphaVariation;

    //! Particle size at the beginning of the lifespan.
    XFcFixed mParticleSizeStart;
    //! Particle size at the end of the lifespan.
    XFcFixed mParticleSizeEnd;
    //! Noise controller for particle size.
    XFuNoiseController mParticleSizeVariation;
    //! Base z-rotation.
    XFcFixed mRotation;
    //! Noise controller for rotation.
    XFuNoiseController mRotationVariation;
    //! Noise controller for original z-position.
    XFuNoiseController mRotationNoise;

    //! Noise controller for particle animation frames.
    XFuNoiseController mFrameVariation;

    //! Emitter size (0 for point).
    XFcFixed mEmitterSize[3];
    //! Maximum limits from the center of the particle system (0 for infinite).
    XFcFixed mAABB[3];

    //! How many frames to pre-tick the particle system on restart.
    INT32 mPreTick;

    //! File names for animation frames.
    CHAR **mTexture;

    //////////////////////////////////////////////////////////////////////
    // Rest are not meant to be saved in a file
    //////////////////////////////////////////////////////////////////////

    //! Single particle structure.
    struct Particle 
    {
        XFcFixed mX, mY, mZ;    //!< Current position.
        XFcFixed mXi, mYi, mZi; //!< Current motion vector.
        XFcFixed mAngle;        //!< Current z-rotation angle.
        XFcFixed mBaseRotation; //!< Base rotation.
        XFcFixed mSize;         //!< Current size.
        XFcFixed mAge;          //!< Current age.
        XFcFixed mMaxAge;       //!< Maximum age.
        INT32 mUniqueSeed;  //!< For noise controller(s).
    } *mParticle; //!< Array of particles.

    INT32 mActive;          //!< Number of currently active particles.
    INT32 mFrames;          //!< Number of frames of animation for this system.
    XFcGLTexture **mFrame;  //!< Particle animation frames.
    XFcFixed mStartTick;        //!< Start tick.
    XFcFixed mLastTick;         //!< Last tick the particle system was updated.
    XFcFixed mCurrentTick;      //!< Current tick .
    INT32 mPeakActive;      //!< Peak active particles.
    INT32 mEmitted;         //!< Number of particles emitted so far.
    XFcFixed mEmitQueue;        //!< Number of particles in queue to be emitted.

    INT32 mRandSeed1;       //!< First seed for rol'n'xor noise function.
    INT32 mRandSeed2;       //!< Second seed for rol'n'xor noise function.

    //! Are textures shared? (otherwise owned by this particle system)
    INT mSharedTextures;

    // Methods

    //! Constructor.
    XFuParticleSystem();
    //! Destructor.
    virtual ~XFuParticleSystem();
    //! Restarts the particle system.
    void restart();
    //! Called to update the particle system.
    void tick(XFcFixed aTime);
    
    //! Used internally.
    /*! \internal
     */
    void tickOnce(XFcFixed aTimeSlice);
    //! Renders the particle system using 3D sprites.
    void render(XFcGL * mGL);
    //! Sets maximum number of visible particles.
    void setMaxVisible(INT32 value);
    //! Saves particle system to disk.
    void save(const CHAR *aFname);
    //! Loads particle system from disk.
    void load(XFcFile *f);
    //! Loads particle system from disk.
    void load(const CHAR *aFname);
    //! Loads textures.
    /*! \param aFilenamePrefix filename prefix to use for each texture filename.
     */
    void loadTextures(const CHAR *aFilenamePrefix = NULL);

    // Internal methods

    //! Creates a new particle.
    /*! \internal
     */
    void newParticle(struct Particle &aParticle);
    //! Seeds the noise function.
    /*! \internal
     */
    void PSSeed(INT32 aValue);
    //! Noise function.
    /*! \internal
     */
    INT32 PSRand();
    //! Seeds the noise function and returns the next value.
    /*! \internal
     */
    static INT32 PSRandInPlace(INT32 aSeed);
};


#endif // !XFUPARTICLESYSTEM_H_INCLUDED

