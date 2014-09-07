
layout (location = 0) in vec3 aPosition;
layout (location = 2) in float aSize;
layout (location = 3) in float aDistance;

out float gDistance;
out float gSize;

void main()
{
    gl_Position = vec4(aPosition, 1.0);
    gDistance = aDistance;
    gSize = aSize;
}


