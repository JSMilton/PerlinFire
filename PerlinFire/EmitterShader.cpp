//
//  EmitterShader.cpp
//  PerlinFire
//
//  Created by James on 28/09/2014.
//  Copyright (c) 2014 James. All rights reserved.
//

#include "EmitterShader.h"

EmitterShader::EmitterShader() : BaseShader("emitter", NULL, "emitter") {
    mDeltaTimeHandle = getUniformLocation("uDeltaTime");
    mElapsedTimeHandle = getUniformLocation("uElapsedTime");
    mEmitCountHandle = getUniformLocation("uEmitCount");
}