//
//  LilyPads.h
//  Assignment02
//
//  Created by Benjamin Visness on 9/28/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment02__LilyPads__
#define __Assignment02__LilyPads__

#include "PLYGameObject.h"

class LilyPads : public PLYGameObject {
public:
	LilyPads() : PLYGameObject("LilyPads.ply") {
		material.specularAmount = 0.2;
		material.specularExponent = 1;
	}
};

#endif /* defined(__Assignment02__LilyPads__) */
