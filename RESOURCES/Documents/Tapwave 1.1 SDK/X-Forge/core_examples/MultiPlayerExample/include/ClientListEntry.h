/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: ClientListEntry.h,v 1.2 2003/10/13 12:46:30 peppe Exp $
 * $Date: 2003/10/13 12:46:30 $
 * $Revision: 1.2 $
 */

#ifndef CLIENTLISTENTRY_H_INCLUDED
#define CLIENTLISTENTRY_H_INCLUDED

#include <xfcore/net/socket/XFcHostEntry.h>
#include <xfcore/net/socket/XFcInetHostEntry.h>
#include <xfcore/net/socket/XFcBtHostEntry.h>

// The ClientListEntry is an entry in the client list in the ConnectingScreen
// It contains the information of one client that has been discovered, and is
// used to display the entry in the list, and then contact the client when the
// initiator starts the game.

class ClientListEntry
{

public:

    ClientListEntry(XFcInetHostEntry *aInetHostEntry)
    {
        mHostEntry = XFcInetHostEntry::create(*aInetHostEntry);
        initName();
    }

    ClientListEntry(XFcBtHostEntry *aBtHostEntry)
    {
        mHostEntry = XFcBtHostEntry::create(*aBtHostEntry);
        initName();
    }

    ~ClientListEntry()
    {
        delete[] mName;
        delete mHostEntry;
    }

    CHAR * getName() { return mName; }
    XFcHostEntry * getHostEntry() { return mHostEntry; }

protected:

    void initName()
    {
        INT32 len = mHostEntry->getName()->mLen;
        if (len == 0)
        {
            mName = NULL;
        }
        else
        {
            INT32 maxNameLen = 14;
            mName = new CHAR[maxNameLen + 4];
            INT32 i;
            for (i = 0; i < len && i < maxNameLen; i++)
            {
                mName[i] = mHostEntry->getName()->mName[i];
            }
            if (i == maxNameLen)
            {
                mName[i++] = '.';
                mName[i++] = '.';
                mName[i++] = '.';
            }
            mName[i] = '\0';
            XFcStringToolkit::toUpperCase(mName);
        }
    }

    CHAR *mName;
    XFcHostEntry *mHostEntry;

};

#endif // !CLIENTLISTENTRY_H_INCLUDED

