//
//  Empty.h
//  Assignment02
//
//  Created by Benjamin Visness on 9/30/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment02__Empty__
#define __Assignment02__Empty__

#include "GameObject.h"

class Empty: public GameObject {
protected:
    int getNumberOfVertices();
    Vector4* getVertices();
    Vector4* getVertexColors();
};

#endif /* defined(__Assignment02__Empty__) */
