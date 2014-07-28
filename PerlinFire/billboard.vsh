
layout (location = 0) in vec3 aPosition;
layout (location = 4) in float aSize;

out float gSize;

void main()
{
    gl_Position = vec4(aPosition, 1.0);
    gSize = aSize;
}


