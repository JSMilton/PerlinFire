layout (location = 0) in vec3 aPosition;
layout (location = 1) in float aEmit;
layout (location = 2) in float aType;

out vec3 gPosition;
out float gEmit;
out float gType;

void main()
{
    gPosition = aPosition;
    gEmit = aEmit;
    gType = aType;
}