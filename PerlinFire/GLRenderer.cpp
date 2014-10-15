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
#include "EmitterShader.h"

void GLRenderer::initOpenGL() {
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    mViewWidth = 1200;
    mViewHeight = 800;
    reshape(1200, 800);
    
    mScreenQuadModel = new ScreenQuadModel;
    mScreenQuadModel->buildVAO();
    createParticleBuffers();
    createEmitters();
    mVelocityTexture = CreateNoise3D();
    
    initBillboardShader();
    initFeedbackShader();
    initEmitterShader();
    
    mTestShader = new TestShader;
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE);
   // glEnable(GL_DEPTH_TEST);
    
    render(0.0);
}

void GLRenderer::initBillboardShader() {
    mBillboardShader = new BillboardShader;
}

void GLRenderer::initFeedbackShader() {
    mFeedbackShader = new FeedbackShader;
    const GLchar* FeedbackVaryings[6] =
    {
        "vPosition",
        "vAge",
        "vType",
        "vWeight",
        "vLifespan",
        "vActive",
    };
    
    glTransformFeedbackVaryings(mFeedbackShader->getProgram(),countof(FeedbackVaryings),
                                FeedbackVaryings,GL_INTERLEAVED_ATTRIBS);
    mFeedbackShader->linkProgram();
}

void GLRenderer::initEmitterShader() {
    mEmitterShader = new EmitterShader;
    const GLchar* FeedbackVaryings[6] =
    {
        "vPosition",
        "vAge",
        "vType",
        "vWeight",
        "vLifespan",
        "vActive",
    };
    
    glTransformFeedbackVaryings(mEmitterShader->getProgram(),countof(FeedbackVaryings),
                                FeedbackVaryings,GL_INTERLEAVED_ATTRIBS);
    mEmitterShader->linkProgram();
}

void GLRenderer::createParticleBuffers() {    
    for (int i = 0; i < MAX_PARTICLES; i++){
        particles[i].position.x = 0;
        particles[i].position.y = 0;
        particles[i].position.z = 0;
        particles[i].age = 0;
        particles[i].type = 0;
        particles[i].weight = 0;
        particles[i].lifespan = 0;
        particles[i].active = 0;
    }
    
    glGenBuffers(BUFFER_COUNT, mVBO);
    glGenVertexArrays(BUFFER_COUNT, mVAO);
    for (int i = 0; i < BUFFER_COUNT; i++){
        glBindVertexArray(mVAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(particles), particles, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Particle), 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 1, GL_FLOAT, false, sizeof(Particle), (void*)(sizeof(GLfloat)*3));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 1, GL_FLOAT, false, sizeof(Particle), (void*)(sizeof(GLfloat)*4));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 1, GL_FLOAT, false, sizeof(Particle), (void*)(sizeof(GLfloat)*5));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 1, GL_FLOAT, false, sizeof(Particle), (void*)(sizeof(GLfloat)*6));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 1, GL_FLOAT, false, sizeof(Particle), (void*)(sizeof(GLfloat)*7));
    }
    
    glBindVertexArray(0);
}

void GLRenderer::createEmitters() {
    for (int i = 0; i < MAX_EMITTERS; i++){
        float x = BASE_WIDTH*((float)i/(MAX_EMITTERS)) - (BASE_WIDTH/2);
        if (i <= MAX_EMITTERS*0.4 || i >= MAX_EMITTERS*0.6){
            emitters[i].type = 1;
        } else {
            //x *= 0.25;
            emitters[i].type = 2;
        }
        emitters[i].position = glm::vec3(x,0,0);
        emitters[i].emit = 0;
        emitters[i].burstRate = ((rand() % MAX_BURST_RATE) / 1000.0) + (MAX_BURST_RATE / 4000.0);
        emitters[i].age = 0;
    }
    
    glGenBuffers(1, &mEmitterVBO);
    glGenVertexArrays(1, &mEmitterVAO);
    glBindVertexArray(mEmitterVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mEmitterVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(emitters), emitters, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Emitter), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_FLOAT, false, sizeof(Emitter), (void*)(sizeof(GLfloat)*3));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, false, sizeof(Emitter), (void*)(sizeof(GLfloat)*4));
    
    glBindVertexArray(0);
}

void GLRenderer::updateEmitters(float dt) {
    
    for (int i = 0; i < MAX_EMITTERS; i++){
        emitters[i].age += dt;
        emitters[i].emit = 0;
        if (emitters[i].age > emitters[i].burstRate){
            emitters[i].age = 0;
            emitters[i].emit = 1;
        }
    }
    
    glBindVertexArray(mEmitterVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mEmitterVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(emitters), emitters, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Emitter), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_FLOAT, false, sizeof(Emitter), (void*)(sizeof(GLfloat)*3));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, false, sizeof(Emitter), (void*)(sizeof(GLfloat)*4));
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
    
    updateEmitters(dt);
    
    GLuint query;
    glGenQueries(1, &query);
    glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, query);
    
    mEmitterShader->enable();
    glUniform1f(mEmitterShader->mDeltaTimeHandle, dt);
    glUniform1f(mEmitterShader->mElapsedTimeHandle, mElapsedTime);
    glUniform1f(mEmitterShader->mEmitCountHandle, EMIT_COUNT);
    glBindBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mVBO[mCurrentBuffer], sizeof(Particle)*mParticleCount,sizeof(Particle)*MAX_PARTICLES);
    glEnable(GL_RASTERIZER_DISCARD);
    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS,0, MAX_EMITTERS);
    glEndTransformFeedback();
    glDisable(GL_RASTERIZER_DISCARD);
    
    glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
    
    mFeedbackShader->enable();
    glUniform1f(mFeedbackShader->mDeltaTimeHandle, dt);
    glUniform1f(mFeedbackShader->mElapsedTimeHandle, mElapsedTime);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mVelocityTexture);
    glBindVertexArray(mVAO[mCurrentBuffer]);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mVBO[(mCurrentBuffer+1)%BUFFER_COUNT]);
    glEnable(GL_RASTERIZER_DISCARD);
    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS,0, MAX_PARTICLES);
    glEndTransformFeedback();
    glDisable(GL_RASTERIZER_DISCARD);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mBillboardShader->enable();
    glUniformMatrix4fv(mBillboardShader->mModelViewProjectionHandle, 1, GL_FALSE, glm::value_ptr(mvp));
    glUniform3f(mBillboardShader->mRightHandle, right.x, right.y, right.z);
    glUniform3f(mBillboardShader->mUpHandle, up.x, up.y, up.z);
    glUniform1f(mBillboardShader->mBillboardSizeHandle, BILLBOARD_SIZE);
    glBindVertexArray(mVAO[(mCurrentBuffer+1)%BUFFER_COUNT]);
    glDrawArrays(GL_POINTS, 0, MAX_PARTICLES);
    
//    mTestShader->enable();
//    glUniformMatrix4fv(mTestShader->mMVP, 1, GL_FALSE, glm::value_ptr(mvp));
//    glUniform1f(mTestShader->mElapsedTimeHandle, mElapsedTime);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, mVelocityTexture);
//    mScreenQuadModel->drawArrays();
//    mTestShader->disable();
    
    GLuint primitives;
    glGetQueryObjectuiv(query, GL_QUERY_RESULT, &primitives);
    
    mCurrentBuffer = (mCurrentBuffer + (BUFFER_COUNT-1)) % BUFFER_COUNT;
    mParticleCount+=primitives;
    if (mParticleCount >= MAX_PARTICLES)mParticleCount = 0;
}

void GLRenderer::reshape(int width, int height) {
    glViewport(0, 0, width, height);
    mViewWidth = width;
    mViewHeight = height;
    mProjectionMatrix = glm::perspective(45.0f, (float)width/(float)height, 0.1f, 10.0f);
    mViewMatrix = glm::lookAt(glm::vec3(0,0,0.5), glm::vec3(0,0,0), glm::vec3(0,1,0));
    
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