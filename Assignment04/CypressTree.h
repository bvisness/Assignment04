//
//  CypressTree.h
//  Assignment02
//
//  Created by Benjamin Visness on 9/28/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment02__CypressTree__
#define __Assignment02__CypressTree__

#include "PLYGameObject.h"

class CypressTree : public PLYGameObject {
public:
	CypressTree() : PLYGameObject("CypressTree.ply") {
		material.specularAmount = 0.2;
		material.specularExponent = 1;
	}
};

#endif /* defined(__Assignment02__CypressTree__) */
