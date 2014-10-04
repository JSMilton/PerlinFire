//
//  EmitterShader.h
//  PerlinFire
//
//  Created by James on 28/09/2014.
//  Copyright (c) 2014 James. All rights reserved.
//

#include "BaseShader.h"

class EmitterShader : public BaseShader {
public:
    EmitterShader();
    GLint mDeltaTimeHandle;
    GLint mElapsedTimeHandle;
    GLint mEmitCountHandle;
};