/*! \file
 * Group.cpp <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Group.cpp,v 1.2 2003/09/04 12:26:31 toni Exp $
 * $Date: 2003/09/04 12:26:31 $
 * $Revision: 1.2 $
 */

#include <xforge.h>
#include <xfutil/XFuDynamicArray.h>
#include "Group.h"
#include "GameGraph.h"
#include "PRSAnimation.h"

Group * Group::create(GameGraph *aGameGraph, UINT32 aId)
{
    Group *g = new Group(aGameGraph, aId);
    if(g)
    {
        // Further initializations and memory allocations
        g->mType = NT_GROUP;
        g->mChildren = XFuDynamicArray<Group *>::create();
        if(!g->mChildren)
        {
            delete g;
            g = NULL;
        }
    }
    return g;
}

Group::Group(GameGraph *aGameGraph, UINT32 aId) : Node(aGameGraph, aId), mParent(NULL), mParentId(0xffffffff), mAlias(NULL), mAnim(NULL)
{
    mChildren = NULL;
    XFcMath::matrixIdentity(mTransformation);
    XFcMath::matrixIdentity(mWorldTransformation);
}

Group::~Group()
{
    delete mChildren;
    mChildren = NULL;
    delete mAlias;
    mAlias = NULL;
}

void Group::initLoad()
{
    // If this node has parent, connect it, otherwise make this sceneroot
    if(mParentId != 0xffffffff)
    {
        mParent = (Group *)mGameGraph->getNodeById(mParentId);
        XFCASSERT(mParent);
        mParent->addChild(this);
    }
    else
    {
        mGameGraph->setRoot(this);
    }
}

void Group::addChild(Group *aChild)
{
    mChildren->put(aChild);
}

void Group::prepare()
{
    // Run animation if found
    if(mAnim)
    {
        mAnim->getNextFrame(mTransformation);
    }

    // Update transformations
    if(mParent)
    {
        mWorldTransformation = mTransformation * mParent->mWorldTransformation;
    }
    else
        mWorldTransformation = mTransformation;

    // Propagate to children
    for(unsigned int i = 0; i < mChildren->size(); i++)
    {
        mChildren->get(i)->prepare();
    }
}

void Group::render()
{
    // Propagate to children
    for(unsigned int i = 0; i < mChildren->size(); i++)
    {
        mChildren->get(i)->render();
    }
}
