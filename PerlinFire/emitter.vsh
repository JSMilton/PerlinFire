layout (location = 0) in vec3 aPosition;
layout (location = 1) in float aBurstRate;

out vec3 gPosition;
out float gBurstRate;

void main()
{
    gPosition = aPosition;
    gBurstRate = aBurstRate;
}