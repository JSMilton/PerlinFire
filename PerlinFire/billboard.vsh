
layout (location = 0) in vec3 aPosition;
layout (location = 1) in float aAge;
layout (location = 2) in float aType;

out float gAge;
out float gType;

void main()
{
    gl_Position = vec4(aPosition, 1.0);
    gAge = aAge;
    gType = aType;
}


