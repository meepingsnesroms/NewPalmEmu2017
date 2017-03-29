/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Input library.
 *
 * This class provides device control event listening interface. Events
 * include pointer events (mouse, stylus), key events (direct keycodes)
 * and "control" events (predefined button control codes).
 * 
 * $Id: XFcInput.h,v 1.10 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.10 $
 */

#ifndef XFC_CORE_XFCCL_H_INCLUDED
#define XFC_CORE_XFCCL_H_INCLUDED


//! Control codes.
enum XFCCL_KEYCODE
{
    XFCCL_LEFT = 500,    //!< Motion control.
    XFCCL_RIGHT,         //!< Motion control.
    XFCCL_UP,            //!< Motion control.
    XFCCL_DOWN,          //!< Motion control.
    XFCCL_FIRE1,         //!< Most accessible fire.
    XFCCL_FIRE2,         //!< Fire button 2.
    XFCCL_FIRE3,         //!< Fire button 3.
    XFCCL_FIRE4,         //!< Fire button 4.
    XFCCL_FIRE5,         //!< Fire button 5.
    XFCCL_FIRE6,         //!< Fire button 6.
    XFCCL_FIRE7,         //!< Fire button 7.
    XFCCL_FIRE8,         //!< Least accessible fire.
    XFCCL_WHEELDOWN,     //!< Wheel down.
    XFCCL_WHEELUP,       //!< Wheel up.
    XFCCL_TAB,           //!< "tab" forward
    XFCCL_RTAB,          //!< "tab" backwards
    XFCCL_CLEAR,         //!< "clear" or "backspace"
    XFCCL_UNMAPPED = -1  //!< Unmap control
};


//! Input interface class.
/*! The active input listener is set by calling the static
 *  XFcCore::setController() method. Only one class may be the active
 *  input receiver at any time.
 */
class XFCDLLEXPORT XFcInput
{

public:

    //! Called when pointer is down.
    /*!
     * This call is only supported on devices with a touchscreen (or mouse)
     * \param aX X-coordinate for event.
     * \param aY Y-coordinate for event.
     */
    XFCIMPORT virtual void onPointerDown(INT32 aX, INT32 aY);
    
    //! Called when pointer moves.
    /*!     
     * This call is only supported on devices with a touchscreen (or mouse)
     * \param aX X-coordinate for event.
     * \param aY Y-coordinate for event.
     */
    XFCIMPORT virtual void onPointerMove(INT32 aX, INT32 aY);
    
    //! Called when pointer is released.
    /*!
     * This call is only supported on devices with a touchscreen (or mouse)
     * \param aX X-coordinate for event.
     * \param aY Y-coordinate for event.
     */
    XFCIMPORT virtual void onPointerUp(INT32 aX, INT32 aY);
    
    //! Called when key is pressed.
    /*!
     * \param aCode Direct hardware keycode for event.
     */
    XFCIMPORT virtual void onKeyDown(INT32 aCode);
    
    //! Called when key is released.
    /*!
     * \param aCode Direct hardware keycode for event.
     */
    XFCIMPORT virtual void onKeyUp(INT32 aCode);
    
    //! Called when a "control" is pressed.
    /*!
     * \param aCode XFCCL_KEYCODE control code for event.
     * \sa XFCCL_KEYCODE
     */
    XFCIMPORT virtual void onControlDown(INT32 aCode);
    
    //! Called when a "control" is released.
    /*!
     * \param aCode XFCCL_KEYCODE control code for event.
     * \sa XFCCL_KEYCODE
     */
    XFCIMPORT virtual void onControlUp(INT32 aCode); 

    //! Called when a character is entered.
    /*!
     * On systems where character input is supported (via keyboard for instance),
     * in addition to onKeyDown, onKeyUp, and possibly onControlDown and 
     * onControlUp, the core calls this function to report what character the
     * operating system feels should be inputted. Theoretically some devices
     * may call this function even without any key events if the input mechanism
     * does not use any keys.
     * \param aChar entered character.
     */
    XFCIMPORT virtual void onCharEntered(CHAR aChar);
    
    //! Called when the analog joystick has moved.
    /*!
     * This call is only supported on devices with an analog joystick.
     * The coordinates range from -32767 to 32768.
     * \param aX joystick position along the X-axis.
     * \param aY joystick position along the Y-axis.
     */
    XFCIMPORT virtual void onJoystickMoved(INT32 aX, INT32 aY);
    
};


#endif // !XFC_CORE_XFCCL_H_INCLUDED

