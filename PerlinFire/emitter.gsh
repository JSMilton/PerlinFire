
layout(points)             in;
layout(points)             out;
layout(max_vertices = 120) out;

in vec3 gPosition[];
in float gAge[];
in float gBurstRate[];

layout (location = 0) out vec3 vPosition;
layout (location = 1) out float vAge;
layout (location = 2) out float vSize;
layout (location = 3) out float vWeight;
layout (location = 4) out float vLifespan;
layout (location = 5) out float vActive;

layout (location = 6) out float vEmitterAge;

uniform float uDeltaTime;
uniform float uEmitCount;
uniform float uSize;

void main()
{
    if (gAge[0] > gBurstRate[0]){
        vAge = 0;
        for (int i = 0; i < uEmitCount; i++){
            vPosition = gPosition[0];
            vAge = 0;
            vSize = uSize;
            vWeight = 0.5;
            vLifespan = 2.0;
            vActive = 1;
        }
    } else {
        vEmitterAge = gAge[0] + uDeltaTime;
    }
}