//
//  FeedbackShader.cpp
//  NoiseBasedParticles
//
//  Created by James Milton on 18/06/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "FeedbackShader.h"

FeedbackShader::FeedbackShader() : BaseShader("feedback", NULL, NULL) {
    mDeltaTimeHandle = getUniformLocation("uDeltaTime");
    mMousePositionHandle = getUniformLocation("uMousePosition");
    mBirthRateHandle = getUniformLocation("uBirthRate");
    mVelocityTextureHandle = getUniformLocation("uVelocityTexture");
    mElapsedTimeHandle = getUniformLocation("uElapsedTime");
    mSizeHandle = getUniformLocation("uSize");
}