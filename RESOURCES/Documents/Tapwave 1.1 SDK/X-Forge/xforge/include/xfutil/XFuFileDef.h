/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief This is a helper hack header file to turn sources using
 *        FILE * into our XFuFile class friendly ones.
 * 
 * $Id: XFuFileDef.h,v 1.6 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.6 $
 */

#ifndef XFUFILEDEF_H_INCLUDED
#define XFUFILEDEF_H_INCLUDED


//! Turns fopen() call into XFcFile::open() call.
#define fopen(a, b) XFcFile::open((const CHAR *)(a), XFCSTR(b))
//! Turns fseek() call into XFcFile::seek() call.
#define fseek(f, a, b) (f) ? f->seek(a, b) : 0
//! Turns ftell() call into XFcFile::tell() call.
#define ftell(f) (f) ? f->tell() : 0
//! Turns fgetc() call into XFcFile::getChar() call.
#define fgetc(f) (f) ? f->getChar() : 0
//! Turns fputc() call into XFcFile::putChar() call.
#define fputc(c, f) (f) ? f->putChar(c) : 0
//! Turns fread() call into XFcFile::read() call.
#define fread(bf, a, b, f) (f) ? f->read(bf, a, b) : 0
//! Turns fwrite() call into XFcFile::write() call.
#define fwrite(bf, a, b, f) (f) ? f->write(bf, a, b) : 0
//! Turns fclose() call into XFcFile::close() call.
#define fclose(f) (f) ? f->close() : 0
//! Turns FILE variable into a XFcFile call.
#define FILE XFcFile


#endif // !XFUFILEDEF_H_INCLUDED

