
layout (location = 0) in vec3 aPosition;
layout (location = 2) in float aSize;
layout (location = 1) in float aAge;

out float gAge;
out float gSize;

void main()
{
    gl_Position = vec4(aPosition, 1.0);
    gAge = aAge;
    gSize = aSize;
}


