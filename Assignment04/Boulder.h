//
//  Boulder.h
//  Assignment02
//
//  Created by Benjamin Visness on 9/28/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment02__Boulder__
#define __Assignment02__Boulder__

#include "PLYGameObject.h"

class Boulder : public PLYGameObject {
public:
	Boulder() : PLYGameObject("Boulder.ply") {
		material.specularAmount = 0.2;
		material.specularExponent = 2;
	}
};

#endif /* defined(__Assignment02__Boulder__) */
