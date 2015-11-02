//
//  Light.h
//  Assignment02
//
//  Created by Benjamin Visness on 9/30/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment02__Light__
#define __Assignment02__Light__

#include "GameObject.h"

#define LIGHT_DISABLED 0
#define LIGHT_POINT 1
#define LIGHT_SPOT 2
#define LIGHT_DIRECTIONAL 3

class Light : public GameObject {
private:
	int lightId = -1;
protected:
	void customInitGameObject();
public:
	Vector4 color = Vector4(0, 0, 0, 1);
	int type = LIGHT_DISABLED;

	void updateInMiddleman();
};

#endif /* defined(__Assignment02__Light__) */
