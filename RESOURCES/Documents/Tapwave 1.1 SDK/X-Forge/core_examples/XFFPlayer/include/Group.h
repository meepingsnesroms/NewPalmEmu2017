/*! \file
 * Group.h <br>
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Group.h,v 1.3 2003/09/04 12:26:31 toni Exp $
 * $Date: 2003/09/04 12:26:31 $
 * $Revision: 1.3 $
 */

#ifndef GROUP_H_INCLUDED
#define GROUP_H_INCLUDED

#include "Node.h"
template<class T> class XFuDynamicArray;
class PRSAnimation;

//! Gamegraph object. A Group has a transformation matrix and it can have other groups as children.
class Group : public Node
{
public:
    //! Static creation    
    static Group * create(GameGraph *aGameGraph, UINT32 aId);

    //! Virtual destructor.
    virtual ~Group();

    //! Prepare the group (and all its children) for rendering (Updates transformations)
    virtual void prepare();

    //! Render the group and all it's children
    virtual void render();

    //! This gets called after all nodes have been loaded
    virtual void initLoad();

    //! Adds a child to the group
    virtual void addChild(Group *aChild);

    //! Group alias accessor
    CHAR *getAlias() { return mAlias; }
    //! Transfers ownership
    void setAlias(CHAR *aAlias) { mAlias = aAlias; }

    //! Parent/child -relation
    void setParentId(UINT32 aId) { mParentId = aId; }
    Group *getParent() { return mParent; }

    //! This is used to set the local transformation matrix
    void setTransformation(const XFcMatrix4 &aMat) { mTransformation = aMat; }

    void setAnimation(PRSAnimation *aPRS) { mAnim = aPRS; }

protected:
    //! Protected constructor.
    Group(GameGraph *aGameGraph, UINT32 aId);

    // These are valid only after the call to initLoad()
    Group *mParent;
    XFuDynamicArray<Group *> *mChildren;

    //! Parent Id
    UINT32 mParentId;

    //! Group name
    CHAR *mAlias;

    //! Possible animation
    PRSAnimation *mAnim;

    //! Local and world transformations
    XFcMatrix4 mTransformation;
    XFcMatrix4 mWorldTransformation;

};

#endif // !GROUP_H_INCLUDED
