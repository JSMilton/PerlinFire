
layout (location = 0) in vec3 aPosition;
layout (location = 1) in float aAge;
layout (location = 2) in float aSize;
layout (location = 3) in float aWeight;
layout (location = 4) in float aLifespan;
layout (location = 5) in float aActive;

out vec3 vPosition;
out float vAge;
out float vSize;
out float vWeight;
out float vLifespan;
out float vActive;

uniform float uElapsedTime;
uniform float uDeltaTime;
uniform sampler3D uVelocityTexture;

void main()
{
    if (aActive){
        if (aAge > aLifespan){
            vActive = 0;
        } else {
            vec3 texCoord = vec3((aPosition.x / 2 + 0.5), (aPosition.y / 2 + 0.5), (aPosition.z / 2 + 0.5));
            texCoord.y = mod(texCoord.y+uElapsedTime*0.025, 1.0);
            vec3 velocity = ((vec3(texture(uVelocityTexture, texCoord).xyz) * 2 - 1.0) * uDeltaTime);
            velocity.y *= -1.0;
            velocity.z *= -1;
            vPosition = aPosition + (velocity*aWeight/2) + vec3(0,(0.5-(vAge*5)) * 0.0015,0);
            vAge = aAge+uDeltaTime;
            vWeight = aWeight;
            vSize = aSize / 1.015;
            vLifespan = aLifespan;
            vActive = aActive;
        }
    }
}