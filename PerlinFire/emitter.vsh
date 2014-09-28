layout (location = 0) in vec3 aPosition;
layout (location = 1) in float aAge;
layout (location = 2) in float aBurstRate;

out vec3 gPosition;
out float gAge;
out float gBurstRate;

void main()
{
    gPosition = aPosition;
    gAge = aAge;
    gBurstRate = aBurstRate;
}