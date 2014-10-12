
layout(points)             in;
layout(points)             out;
layout(max_vertices = 120) out;

in vec3 gPosition[];
in float gEmit[];

out vec3 vPosition;
out float vAge;
out float vSize;
out float vWeight;
out float vLifespan;
out float vActive;

uniform float uEmitCount;
uniform float uElapsedTime;
uniform float uDeltaTime;

const float lifespan = 3.0;
const float billboardSize = 0.0075;

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
    if (gEmit[0] == 1){
        uint seed = uint(uDeltaTime * 1000.0) + uint(gl_PrimitiveIDIn);
        for (int i = 0; i < uEmitCount; i++){
            vPosition = gPosition[0];
            //vPosition.x += randhashf(seed++, 0.005);
            //vPosition.y += randhashf(seed++, 0.005);
            vAge = 0;
            vSize = billboardSize;
            vWeight = 0.15 + randhashf(seed++, 0.5);
            vLifespan = lifespan;
            vActive = 1;
            EmitVertex();
            EndPrimitive();
        }
    }
}