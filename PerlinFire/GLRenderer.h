//
//  GLRenderer.h
//  GyroSquares
//
//  Created by James Milton on 28/05/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glUtil.h"
#include "Utils.h"
extern "C"{
    #include "perlin.h"
}

#define BUFFER_COUNT 2
#define MAX_PARTICLES 10000
#define BILLBOARD_SIZE 0.005f
#define MAX_BURST_RATE 1000//ms
#define EMIT_COUNT 20
#define MAX_EMITTERS 100
#define BASE_WIDTH 0.05

class BillboardShader;
class FeedbackShader;
class TestShader;
class ScreenQuadModel;
class EmitterShader;

class GLRenderer {
    struct Particle
    {
        glm::vec3 position;
        GLfloat age;
        GLfloat type;
        GLfloat weight;
        GLfloat lifespan;
        GLfloat active;
    };
    
    struct Emitter
    {
        glm::vec3 position;
        GLfloat emit;
        GLfloat type;
        GLfloat burstRate;
        GLfloat age;
    };
    
public:
    void initOpenGL();
    void render(float dt);
    void reshape(int width, int height);
    void destroy();
    void getMousePosition(float x, float y, float z);
    void getMouseAcceleration(float x, float y, float z);
    
private:
    void createFrameBuffers();
    void resetFramebuffers();
    void freeGLBindings() const;
    
    void initBillboardShader();
    void initFeedbackShader();
    void initEmitterShader();
    void createParticleBuffers();
    void createEmitters();
    void createVelocityTexture();
    
    void updateEmitters(float dt);
    
    glm::mat4 mProjectionMatrix;
    glm::mat4 mViewMatrix;
    glm::mat4 mPreviousViewMatrix;
    glm::mat4 mInverseMVPMatrix;
    
    int mViewWidth;
    int mViewHeight;
    float mMouseWidth;
    float mMouseHeight;
    
    glm::vec4 mMouseTransform;
    
    int mCurrentBuffer;
    
    GLuint mVAO[BUFFER_COUNT];
    GLuint mVBO[BUFFER_COUNT];
    
    GLuint mEmitterVAO;
    GLuint mEmitterVBO;
    
    GLuint mVelocityTexture;
    
    BillboardShader *mBillboardShader;
    FeedbackShader *mFeedbackShader;
    TestShader *mTestShader;
    EmitterShader *mEmitterShader;
    
    ScreenQuadModel *mScreenQuadModel;
    
    glm::vec3 mMousePosition;
    glm::vec3 mMouseAcceleration;
    
    Particle particles[MAX_PARTICLES];
    Emitter emitters[MAX_EMITTERS];
    
    int mParticleCount;
    
    float mElapsedTime;
};
