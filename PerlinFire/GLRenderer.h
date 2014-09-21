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
#define MAX_PARTICLES 1000
#define BILLBOARD_SIZE 0.01f
#define BIRTH_RATE 0.5

class BillboardShader;
class FeedbackShader;
class TestShader;
class ScreenQuadModel;

class GLRenderer {
    struct Particle
    {
        glm::vec3 position;
        GLfloat age;
        float size;
        float weight;
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
    void createParticleBuffers();
    void createVelocityTexture();
    
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
    
    GLuint mVelocityTexture;
    
    BillboardShader *mBillboardShader;
    FeedbackShader *mFeedbackShader;
    TestShader *mTestShader;
    
    ScreenQuadModel *mScreenQuadModel;
    
    glm::vec3 mMousePosition;
    glm::vec3 mMouseAcceleration;
    
    Particle particles[MAX_PARTICLES];
    
    float mElapsedTime;
};
