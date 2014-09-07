//
//  TestShader.cpp
//  PerlinFire
//
//  Created by James on 31/08/2014.
//  Copyright (c) 2014 James. All rights reserved.
//

#include "TestShader.h"

TestShader::TestShader() : BaseShader("test", "test", NULL) {
    mTextureHandle = getUniformLocation("uTex");
    mMVP = getUniformLocation("uMVP");
    mElapsedTimeHandle = getUniformLocation("uElapsedTime");
}