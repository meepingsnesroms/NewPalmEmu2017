/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Application class.
 * \note Only one of these should be instantiated in the whole program.
 * 
 * $Id: XFcApp.h,v 1.15 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.15 $
 */

#ifndef XFC_CORE_XFCAPP_H_INCLUDED
#define XFC_CORE_XFCAPP_H_INCLUDED


//! Defines an X-Forge application.
/*! Each X-Forge application has exactly one copy of an application class.
 * This object is owned by the core. The XFcApp-extended class is usually
 * instantiated in the xfcAppInit() function. Since the default constructor
 * stores a pointer to the class within the core, the application does not
 * need to keep track of the object. (And since static global data is 
 * illegal, the application couldn't keep track of the object even if it
 * wanted).
 */
class XFCDLLEXPORT XFcApp
{

public:

    //! Constructor; sets application to be found with XFcCore::getApp().
    /*!
     * This constructor registers the application instance into the core.
     * If more than one instance of XFcApp-extended classes are created,
     * the application quits.
     */
    XFCIMPORT XFcApp();
    
    //! Virtual destructor.
    /*! The destructor is called by the core when application quits. 
     */
    XFCIMPORT virtual ~XFcApp();
    
    //! Called upon application init.
    /*! Once the core has been initialized, the application onAppInit()
     * method is called.
     */
    XFCIMPORT virtual void onAppInit();
    
    //! Called every frame (before rendering).
    /*! This is a good candidate for events that must occur everywhere in the
     * application, regardless of the current renderer. 
     */
    XFCIMPORT virtual void onTick();
    
    //! Called on application quit (cleanup).
    /*! You should do most of your clean-up in this function. The core
     * calls this function when it is shutting down.
     */
    XFCIMPORT virtual void onAppDeinit();
    
    //! Called when the device state changes in a way that affects the application.
    /*!
     * It is highly recommended that the application overrides this method and acts
     * according to the events. If severity is medium, it is recommended that the application
     * goes to pause mode, and it is especially critical that all audio is paused. If severity
     * is critical, the application should shut down its threads and quit.
     * \param aEvent See XFCDEVICESTATEEVENTS enumerated type.
     * \param aSeverity See XFCDEVICESTATEEVENTSEVERITY enumerated type.
     * \param aMoreInfo More information of the event; depends on the event type and platform.
     * \return Undefined, should return 0.
     * <table><tr><td colspan=2>Platform specific behavior</td></tr>

     * <tr><td colspan=2>&nbsp;</td></tr>
     * <tr><td></td><td>XFCDSE_FOCUSLOST</td></tr>
     * <tr><td>DesktopWindows</td><td>Supported, XFCDSE_SEVERITY_MODERATE</td></tr>
     * <tr><td>PocketPC</td><td>Supported, XFCDSE_SEVERITY_MODERATE</td></tr>
     * <tr><td>Smartphone2002</td><td>Supported, XFCDSE_SEVERITY_MODERATE</td></tr>
     * <tr><td>Series60</td><td>Supported, XFCDSE_SEVERITY_MODERATE</td></tr>
     * <tr><td>UIQ</td><td>Supported, XFCDSE_SEVERITY_MODERATE</td></tr>     
     * <tr><td>Palm</td><td>Supported, XFCDSE_SEVERITY_MODERATE</td></tr>     
     *
     * <tr><td colspan=2>&nbsp;</td></tr>
     * <tr><td></td><td>XFCDSE_FOCUSGAIN</td></tr>  
     * <tr><td>DesktopWindows</td><td>Supported, XFCDSE_SEVERITY_NOTE</td></tr>
     * <tr><td>PocketPC</td><td>Supported, XFCDSE_SEVERITY_NOTE</td></tr>
     * <tr><td>Smartphone2002</td><td>Supported, XFCDSE_SEVERITY_NOTE</td></tr>
     * <tr><td>Series60</td><td>Supported, XFCDSE_SEVERITY_NOTE</td></tr>
     * <tr><td>UIQ</td><td>Supported, XFCDSE_SEVERITY_NOTE</td></tr>     
     * <tr><td>Palm</td><td>Supported, XFCDSE_SEVERITY_NOTE</td></tr>     
     *
     * <tr><td colspan=2>&nbsp;</td></tr>
     * <tr><td></td><td>XFCDSE_AUDIOLOST</td></tr>
     * <tr><td>DesktopWindows</td><td>Unsupported</td></tr>
     * <tr><td>PocketPC</td><td>Unsupported</td></tr>
     * <tr><td>Smartphone2002</td><td>Unsupported</td></tr>
     * <tr><td>Series60</td><td>Supported, XFCDSE_SEVERITY_MODERATE</td></tr>
     * <tr><td>UIQ</td><td>Supported, XFCDSE_SEVERITY_MODERATE</td></tr>     
     * <tr><td>Palm</td><td>Unsupported</td></tr>     
     *
     * <tr><td colspan=2>&nbsp;</td></tr>
     * <tr><td></td><td>XFCDSE_KILLSIGNAL</td></tr>
     * <tr><td>DesktopWindows</td><td>Supported, XFCDSE_SEVERITY_CRITICAL</td></tr>
     * <tr><td>PocketPC</td><td>Supported, XFCDSE_SEVERITY_CRITICAL</td></tr>
     * <tr><td>Smartphone2002</td><td>Supported, XFCDSE_SEVERITY_CRITICAL</td></tr>
     * <tr><td>Series60</td><td>Supported, XFCDSE_SEVERITY_CRITICAL</td></tr>
     * <tr><td>UIQ</td><td>Supported, XFCDSE_SEVERITY_CRITICAL</td></tr>     
     * <tr><td>Palm</td><td>Supported, XFCDSE_SEVERITY_CRITICAL</td></tr>     
     *
     * <tr><td colspan=2>&nbsp;</td></tr>
     * <tr><td></td><td>XFCDSE_MEDIACHANGED</td></tr>
     * <tr><td>DesktopWindows</td><td>Unsupported</td></tr>
     * <tr><td>PocketPC</td><td>Unsupported</td></tr>
     * <tr><td>Smartphone2002</td><td>Unsupported</td></tr>
     * <tr><td>Series60</td><td>Unsupported</td></tr>
     * <tr><td>UIQ</td><td>Unsupported</td></tr>     
     * <tr><td>Palm</td><td>Supported, XFCDSE_SEVERITY_NOTE</td></tr>     
     *
     * <tr><td colspan=2>&nbsp;</td></tr>
     * <tr><td></td><td>XFCDSE_LOWMEMORY</td></tr>
     * <tr><td>DesktopWindows</td><td>Unsupported</td></tr>
     * <tr><td>PocketPC</td><td>Unsupported</td></tr>
     * <tr><td>Smartphone2002</td><td>Unsupported</td></tr>
     * <tr><td>Series60</td><td>Unsupported</td></tr>
     * <tr><td>UIQ</td><td>Unsupported</td></tr>     
     * <tr><td>Palm</td><td>Unsupported</td></tr>     
     *
     * <tr><td colspan=2>&nbsp;</td></tr>
     * <tr><td></td><td>XFCDSE_PHONEEVENT</td></tr>
     * <tr><td>DesktopWindows</td><td>Unsupported</td></tr>
     * <tr><td>PocketPC</td><td>Unsupported</td></tr>
     * <tr><td>Smartphone2002</td><td>Unsupported</td></tr>
     * <tr><td>Series60</td><td>Unsupported</td></tr>
     * <tr><td>UIQ</td><td>Unsupported</td></tr>     
     * <tr><td>Palm</td><td>Unsupported</td></tr>     
     * </table>
     */
    XFCIMPORT virtual INT onDeviceStateEvent(INT32 aEvent, INT32 aSeverity, void *aMoreInfo);

};


#endif // !XFC_CORE_XFCAPP_H_INCLUDED

