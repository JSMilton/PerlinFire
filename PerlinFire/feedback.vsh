
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aVelocity;
layout (location = 2) in float aAge;
layout (location = 3) in vec3 aStartPosition;
layout (location = 4) in float aSize;

out vec3 vPosition;
out vec3 vVelocity;
out float vAge;
out vec3 vStartPosition;
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
        vVelocity = vec3(0,0.2,0);
        vAge = 0;
        vSize = 0.01;
    } else {
        vPosition = aPosition;// ((aPosition + aVelocity) * 0.5 * uDeltaTime) / 100;
        vPosition.y += 0.005;
        vVelocity = aVelocity;
        vVelocity *= 0.99;
        vAge = aAge+uDeltaTime;
        vSize = aSize / 1.05;
    }

    vStartPosition = aStartPosition;
}