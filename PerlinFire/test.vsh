layout (location = 0) in vec4 inPosition;
layout (location = 2) in vec2 inTexture;

uniform mat4 uMVP;

out vec2 st;

void main()
{
    st = inTexture;
    gl_Position = inPosition;
}