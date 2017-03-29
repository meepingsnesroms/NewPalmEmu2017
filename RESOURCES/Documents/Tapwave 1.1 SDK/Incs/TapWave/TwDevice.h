/* Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved. */

#ifndef __TWDEVICE_H__
#define __TWDEVICE_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef NON_PORTABLE

typedef struct TwDeviceType TwDeviceType;

typedef TwDeviceType* TwDeviceHandle;

struct TwDeviceType {
    // public fields to device provider
    Err    (*init)(TwDeviceHandle handle, const char* name, const char* mode);
    Err   (*close)(TwDeviceHandle handle);
    Err    (*read)(TwDeviceHandle handle, void* buf, Int32* len);
    Err   (*write)(TwDeviceHandle handle, const void* buf, Int32* len);
    Err  (*getter)(TwDeviceHandle handle, Int32 property, void* buf, Int32* len);
    Err  (*setter)(TwDeviceHandle handle, Int32 property, const void* buf, Int32 len);
    Err (*control)(TwDeviceHandle handle, Int32 cmd, void* buf, Int32 len);

    void* data;
    void* data1;
    void* data2;
    void* data3;

    // private fields to device manager
    struct TwDeviceEntry* devTableEntryP;
    struct TwDeviceType* next;
    struct TwDeviceType* prev;
};

#else // NON_PORTABLE

typedef Int32 TwDeviceHandle;

#endif // NON_PORTABLE

/*
 * Register a virtual device driver. The `name' uses convention
 * similar to UNIX /dev/name, for example "vibrator0", "mixer0".
 * The `init' function will be called when the device is opened,
 * and the `data' pointer will be used to initialize `data' field
 * of TwDeviceType, see above. The return value is POSIX error code.
 *
 * NOTE: this is 32-bit only API, which can't be accessed by 68K code.
 */
Err TwDeviceRegister(const char* name, Err (*init)(TwDeviceHandle, const char*, const char*), void* data);

/*
 * Unregister a virtual device driver. The arguments must exactly
 * match what were used for TwDeviceRegister(). The return value is
 * POSIX error code.
 *
 * NOTE: this is 32-bit only API, which can't be accessed by 68K code.
 */
Err TwDeviceUnregister(const char* name, Err (*init)(TwDeviceHandle, const char*, const char*), void* data);

/*
 * Open a virtual device. The `name' specifies the virtual device to
 * open, for example "vibrator0" denotes the default vibrator on
 * current system. The `mode' specifies the desired access, such as
 * "r" for read, "w" for write, and "rw" for read/write. The return
 * value is POSIX error code.
 */
Err TwDeviceOpen(TwDeviceHandle* handle, const char* name, const char* mode)
    TAL_TRAP(trapTwDeviceOpen);

/*
 * Close the virtual device. The return value is POSIX error code.
 */
Err TwDeviceClose(TwDeviceHandle handle)
    TAL_TRAP(trapTwDeviceClose);

/*
 * Read data from the virtual device. `buf' points to data buffer, and
 * `len' specifies the buffer size in bytes. On return, the `len'
 * gives the actual number of bytes read. The return value is POSIX
 * error code.
 */
Err TwDeviceRead(TwDeviceHandle handle, void* buf, Int32* len)
    TAL_TRAP(trapTwDeviceRead);

/*
 * Write data to the virtual device. `buf' points to data buffer, and
 * `len' specifies the buffer size in bytes. On return, the `len'
 * gives the actual number of bytes written. The return value is POSIX
 * error code.
 */
Err TwDeviceWrite(TwDeviceHandle handle, const void* buf, Int32* len)
    TAL_TRAP(trapTwDeviceWrite);

/*
 * Get the specified property value from the virtual device. The
 * return value is the error code. The `property' is typically
 * specified using multi-character integer, such as 'size', 'port'.
 * `buf' points a buffer that will receives the value, and `len' gives
 * the buffer size. On return, `len' always contains the actual size
 * of the actual property value. If the size of property value is
 * larger than the buffer size, the buffer will be filled with partial
 * value and ENOMEM error code will be returned.
 */
Err TwDeviceGetProperty(TwDeviceHandle handle, Int32 property, void* buf, Int32* len)
    TAL_TRAP(trapTwDeviceGetProperty);

/*
 * Set the specified property value for the virtual device. The return
 * value is POSIX error code. The `property' is typically specified
 * using multi-character integers, such as 'size'. `buf' points to the
 * property value, and `len' gives the size of value.
 */
Err TwDeviceSetProperty(TwDeviceHandle handle, Int32 property, const void* buf, Int32 len)
    TAL_TRAP(trapTwDeviceSetProperty);

/*
 * Send arbitary control command to virtual device. The `cmd' argument
 * is a device specific selector, the `buf' points to the command
 * parameter block, `len' is the size of parameter block in bytes. The
 * parameter block may be used as input, ouput, or both. If the
 * parameter block is not needed, both `buf' and `len' should be set
 * to 0. The return value is the error code. The `cmd' is typically
 * specified using multi-character integers, such as 'peek', 'poll',
 * 'push', 'pop'.
 */
Err TwDeviceControl(TwDeviceHandle handle, Int32 cmd, void* buf, Int32 len)
    TAL_TRAP(trapTwDeviceControl);

#ifdef __cplusplus
}
#endif

#endif /* __TWDEVICE_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
