
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aVelocity;
layout (location = 2) in float aAge;
layout (location = 3) in vec3 aStartPosition;
layout (location = 4) in vec3 aStartVelocity;
layout (location = 5) in float aSize;

out vec3 vPosition;
out vec3 vVelocity;
out float vAge;
out vec3 vStartPosition;
out vec3 vStartVelocity;
out float vSize;

uniform float uDeltaTime;
uniform vec3 uMousePosition;
uniform float uBirthRate;

void main()
{
    float x = aPosition.x;
    float y = aPosition.y;
    
    if (aAge > uBirthRate){
        vPosition = aStartPosition;
        vVelocity = aStartVelocity;
        vAge = 0;
        vSize = 0.05;
    } else {
        vPosition = aPosition + (aVelocity * uDeltaTime * 0.5);
        vVelocity = aVelocity;// * 0.99;
        vAge = aAge+uDeltaTime;
        vSize = aSize / 1.015;
        //if (vSize < 0.01)vSize = 0.01;
    }

    vStartPosition = aStartPosition;
    vStartVelocity = aStartVelocity;
}