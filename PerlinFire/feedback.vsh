
layout (location = 0) in vec3 aPosition;
layout (location = 1) in float aAge;
layout (location = 2) in float aSize;
layout (location = 3) in float aDistance;

out vec3 vPosition;
out float vAge;
out float vSize;
out float vDistance;

uniform float uElapsedTime;
uniform float uDeltaTime;
uniform vec3 uMousePosition;
uniform float uBirthRate;
uniform float uSize;

uniform float TimeStep = 5.0;
uniform float InitialBand = 0.05;
uniform float SeedRadius = 0.25;
uniform float PlumeCeiling = 3.0;
uniform float PlumeBase = -1.0;

uniform sampler3D uVelocityTexture;

const float TwoPi = 6.28318530718;
const float UINT_MAX = 4294967295.0;

uint randhash(uint seed)
{
    uint i=(seed^12345391u)*2654435769u;
    i^=(i<<6u)^(i>>26u);
    i*=2654435769u;
    i+=(i<<5u)^(i>>12u);
    return i;
}

float randhashf(uint seed, float b)
{
    return float(b * randhash(seed)) / UINT_MAX;
}

void main()
{
    float x = aPosition.x;
    float y = aPosition.y;
    
    if (aAge > uBirthRate){
        vAge = 0;
        vSize = uSize;
        
        uint seed = uint(uDeltaTime * 1000.0) + uint(gl_VertexID);
        float theta = randhashf(seed++, TwoPi);
        float r = randhashf(seed++, SeedRadius);
        float y = randhashf(seed++, InitialBand);
        vPosition.x = r * cos(theta);
        vPosition.y = PlumeBase + y;
        vPosition.z = 0;
    } else {
        vec3 texCoord = vec3((aPosition.x / 2 + 0.5), (aPosition.y / 2 + 0.5), (aPosition.z / 2 + 0.5));
        texCoord.y = mod(texCoord.y+uElapsedTime*0.15, 1.0);
        vec3 velocity = ((vec3(texture(uVelocityTexture, texCoord).xyz) * 2 - 1.0) * uDeltaTime);
        velocity.y *= -1.0;
        //velocity.x *= vAge+1;
        velocity.z *= -1;
        vPosition = aPosition + (velocity);// + vec3(0, 0.005,0);
        vAge = aAge+uDeltaTime;
    }
    
    vDistance = 1;
}