
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aVelocity;
layout (location = 2) in float aAge;
layout (location = 3) in vec3 aStartPosition;

out vec3 vPosition;
out vec3 vVelocity;
out float vAge;
out vec3 vStartPosition;

uniform float uDeltaTime;
uniform vec3 uMousePosition;
uniform float uBirthRate;

void main()
{
    float x = aPosition.x;
    float y = aPosition.y;
    float forceX = 0;
    float forceY = 0;
    float force = 0;
    float distSquared = pow(x - uMousePosition.x, 2) + pow(y - uMousePosition.y, 2);
    force = 1.f / distSquared;
    forceX = (uMousePosition.x - x) * force;
    forceY = (uMousePosition.y - y) * force;

    vec3 accel = vec3(forceX, forceY, 0);
    vec3 oldVel = aVelocity;
    vec3 newVel = aVelocity + accel * uDeltaTime;
    if (uMousePosition.x == -1.0 && uMousePosition.y == -1.0 || distSquared < 0.025){
        newVel = aVelocity;
    }
    
    if (aAge > uBirthRate){
        vPosition = aStartPosition;
        vVelocity = vec3(0,0,0);
        vAge = 0;
    } else {
        vPosition = aPosition + (oldVel + newVel) * 0.5 * uDeltaTime;
        vVelocity = newVel;
        vVelocity *= 0.99;
        vAge = aAge+uDeltaTime;
    }

    vStartPosition = aStartPosition;
}