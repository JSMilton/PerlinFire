
layout(points)             in;
layout(points)             out;
layout(max_vertices = 120) out;

in vec3 gPosition[];
in float gBurstRate[];

out vec3 vPosition;
out float vAge;
out float vSize;
out float vWeight;
out float vLifespan;
out float vActive;

uniform float uEmitCount;
uniform float uElapsedTime;
uniform float uDeltaTime;

const float lifespan = 2.0;
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
    //if (mod(uElapsedTime, gBurstRate[0]) > gBurstRate[0]*0.5){
        //for (int i = 0; i < uEmitCount; i++){
            uint seed = uint(uDeltaTime * 1000.0) + uint(gl_PrimitiveIDIn);
            vPosition = gPosition[0];
            vAge = 0;
            vSize = billboardSize;
            vWeight = randhashf(seed++, 0.75);
            vLifespan = lifespan;
            vActive = 1;
            EmitVertex();
            EndPrimitive();
        //}
   // }
}