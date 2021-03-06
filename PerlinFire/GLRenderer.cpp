//
//  GLRenderer.cpp
//  GyroSquares
//
//  Created by James Milton on 28/05/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "GLRenderer.h"
#include "BillboardShader.h"
#include "FeedbackShader.h"
#include "TestShader.h"
#include "ScreenQuadModel.h"

void GLRenderer::initOpenGL() {
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    mViewWidth = 1200;
    mViewHeight = 800;
    reshape(1200, 800);
    
    mScreenQuadModel = new ScreenQuadModel;
    mScreenQuadModel->buildVAO();
    createParticleBuffers();
    mVelocityTexture = CreateNoise3D();
    //createVelocityTexture();
    
    initBillboardShader();
    initFeedbackShader();
    mTestShader = new TestShader;
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_DEPTH_TEST);
    
    render(0.0);
}

void GLRenderer::initBillboardShader() {
    mBillboardShader = new BillboardShader;
}

void GLRenderer::initFeedbackShader() {
    mFeedbackShader = new FeedbackShader;
    const GLchar* FeedbackVaryings[4] =
    {
        "vPosition",
        "vAge",
        "vSize",
        "vDistance",
    };
    
    glTransformFeedbackVaryings(mFeedbackShader->getProgram(),countof(FeedbackVaryings),
                                FeedbackVaryings,GL_INTERLEAVED_ATTRIBS);
    mFeedbackShader->linkProgram();
}

void GLRenderer::createParticleBuffers() {    
    for (int i = 0; i < MAX_PARTICLES; i++){
        
        float randomX, randomY, randomVelX, randomVelY;
        randomX = ((rand() % 1000) / 500.0) - 0.5;
        randomY = ((rand() % 2000) / 1000.0) - 1.0;
        randomVelX = ((rand() % 2000) / 1000.0) - 1.0;
        randomVelY = ((rand() % 1000) / 1000.0);
        
        particles[i].position.x = randomX;
        particles[i].position.y = randomY/10;
        particles[i].position.z = 0;
        particles[i].age = (rand() % (int)(BIRTH_RATE * 1000)) / 1000.0;
        particles[i].size = BILLBOARD_SIZE;
        particles[i].distance = 0.0;
    }
    
    glGenBuffers(BUFFER_COUNT, mVBO);
    glGenVertexArrays(BUFFER_COUNT, mVAO);
    for (int i = 0; i < BUFFER_COUNT; i++){
        glBindVertexArray(mVAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(particles), particles, GL_STATIC_DRAW);
        // position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Particle), 0);
        // age
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 1, GL_FLOAT, false, sizeof(Particle), (void*)(sizeof(GLfloat)*3));
        // size
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 1, GL_FLOAT, false, sizeof(Particle), (void*)(sizeof(GLfloat)*4));
        // distance
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 1, GL_FLOAT, false, sizeof(Particle), (void*)(sizeof(GLfloat)*5));
    }
    
    glBindVertexArray(0);
}

void GLRenderer::createVelocityTexture() {
    static const int elements = mViewWidth * mViewHeight;
    GLfloat data[elements*2];
    int index = 0;
    for (int row = 0; row < mViewWidth; row++){
        for (int col = 0; col < mViewHeight; col++){
            float f = (float)col / mViewHeight;;
            data[index++] = f;
            data[index++] = f;
        }
    }
    
    GLuint handle;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, mViewWidth, mViewHeight, 0, GL_RG, GL_FLOAT, &data[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    mVelocityTexture = handle;
}

void GLRenderer::render(float dt) {
    const float FPS_CLAMP = 1.0f / 15.0f;
    if (dt > FPS_CLAMP)
        dt = FPS_CLAMP;
    
    mElapsedTime += dt;
    
    freeGLBindings();
    
    glm::mat4 mvp = mProjectionMatrix * mViewMatrix;
    glm::vec4 right = mViewMatrix[0];
    glm::vec4 up = mViewMatrix[1];
    
    mFeedbackShader->enable();
    glUniform1f(mFeedbackShader->mDeltaTimeHandle, dt);
    glUniform1f(mFeedbackShader->mBirthRateHandle, BIRTH_RATE);
    glUniform3f(mFeedbackShader->mMousePositionHandle, mMousePosition.x, mMousePosition.y, mMousePosition.z);
    glUniform1f(mFeedbackShader->mElapsedTimeHandle, mElapsedTime);
    glUniform1f(mFeedbackShader->mSizeHandle, BILLBOARD_SIZE);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mVelocityTexture);
    glBindVertexArray(mVAO[(mCurrentBuffer+1)%BUFFER_COUNT]);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mVBO[mCurrentBuffer]);
    glEnable(GL_RASTERIZER_DISCARD);
    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS, 0, MAX_PARTICLES);
    glEndTransformFeedback();
    glDisable(GL_RASTERIZER_DISCARD);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mBillboardShader->enable();
    glUniformMatrix4fv(mBillboardShader->mModelViewProjectionHandle, 1, GL_FALSE, glm::value_ptr(mvp));
    glUniform3f(mBillboardShader->mRightHandle, right.x, right.y, right.z);
    glUniform3f(mBillboardShader->mUpHandle, up.x, up.y, up.z);
    glUniform1f(mBillboardShader->mBillboardSizeHandle, BILLBOARD_SIZE);
    glBindVertexArray(mVAO[mCurrentBuffer]);
    glDrawArrays(GL_POINTS, 0, MAX_PARTICLES);
    
//    mTestShader->enable();
//    glUniformMatrix4fv(mTestShader->mMVP, 1, GL_FALSE, glm::value_ptr(mvp));
//    glUniform1f(mTestShader->mElapsedTimeHandle, mElapsedTime);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, mVelocityTexture);
//    mScreenQuadModel->drawArrays();
//    mTestShader->disable();
    
    mCurrentBuffer = (mCurrentBuffer + 1) % BUFFER_COUNT;
}

void GLRenderer::reshape(int width, int height) {
    glViewport(0, 0, width, height);
    mViewWidth = width;
    mViewHeight = height;
    mProjectionMatrix = glm::perspective(45.0f, (float)width/(float)height, 0.1f, 100.0f);
    mViewMatrix = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
    
    glm::vec4 fwidth;
    fwidth = mProjectionMatrix * mViewMatrix * glm::vec4(mViewWidth, mViewHeight, 0, 1);
    mMouseWidth = fwidth.x /= fwidth.w;
    mMouseHeight = fwidth.y /= fwidth.w;
    createFrameBuffers();
}

void GLRenderer::freeGLBindings(void) const
{
    glBindFramebuffer(GL_FRAMEBUFFER,     0);
    glBindRenderbuffer(GL_RENDERBUFFER,   0);
    glBindBuffer(GL_ARRAY_BUFFER,         0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D,          0);
    glBindTexture(GL_TEXTURE_CUBE_MAP,    0);
}

void GLRenderer::getMousePosition(float x, float y, float z) {
    if (z == INT32_MAX){
        mMousePosition = glm::vec3(-1.0,-1.0,0);
    } else {
        float w = ((x - (mViewWidth/2)) /mMouseWidth) * 2.0;
        float h = ((y - (mViewHeight/2)) /mMouseHeight) * 2.0;
        mMousePosition = glm::vec3(w,h,z);
    }
}

void GLRenderer::getMouseAcceleration(float x, float y, float z) {
    mMouseAcceleration = glm::vec3(x,y,z);
}

void GLRenderer::resetFramebuffers() {
}

void GLRenderer::createFrameBuffers() {
    resetFramebuffers();
}

void GLRenderer::destroy() {
}