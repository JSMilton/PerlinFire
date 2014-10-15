
layout (location = 0) in vec3 aPosition;
layout (location = 1) in float aAge;
layout (location = 2) in float aType;
layout (location = 3) in float aWeight;
layout (location = 4) in float aLifespan;
layout (location = 5) in float aActive;

out vec3 vPosition;
out float vAge;
out float vType;
out float vWeight;
out float vLifespan;
out float vActive;

uniform float uElapsedTime;
uniform float uDeltaTime;
uniform sampler3D uVelocityTexture;

void reset()
{
    vPosition = vec3(0,0,0);
    vActive = 0;
    vType = 0;
    vAge = 0;
    vWeight = 0;
    vLifespan = 0;
}

void main()
{
    if (aActive == 1){
        if (aAge > aLifespan){
            reset();
        } else {
            vec3 texCoord = vec3((aPosition.x), (aPosition.y), (aPosition.z));
            texCoord.z = mod(texCoord.z+uElapsedTime*0.075, 1.0);
            vec3 velocity = ((vec3(texture(uVelocityTexture, texCoord).xyz) * 2 - 1.0) * uDeltaTime);
            velocity.y *= -1.0;
            vPosition = aPosition + (velocity*aWeight/2);
            vAge = aAge+uDeltaTime;
            vWeight = aWeight;
            vType = aType;
            vLifespan = aLifespan;
            vActive = aActive;
        }
    } else {
        reset();
    }
}