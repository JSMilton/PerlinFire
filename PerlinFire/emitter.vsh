layout (location = 0) in vec3 aPosition;
layout (location = 1) in float aEmit;

out vec3 gPosition;
out float gEmit;

void main()
{
    gPosition = aPosition;
    gEmit = aEmit;
}