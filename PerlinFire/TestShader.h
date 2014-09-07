//
//  TestShader.h
//  PerlinFire
//
//  Created by James on 31/08/2014.
//  Copyright (c) 2014 James. All rights reserved.
//

#include "BaseShader.h"

class TestShader : public BaseShader {
public:
    TestShader();
    
    GLint mTextureHandle;
    GLint mElapsedTimeHandle;
    GLint mMVP;
};