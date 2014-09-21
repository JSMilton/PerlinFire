
layout(points)           in;
layout(triangle_strip)   out;
layout(max_vertices = 4) out;

in float gAge[];
in float gSize[];
out float fAge;

uniform mat4  u_MVP;
uniform vec3  u_Right;
uniform vec3  u_Up;
uniform float u_BillboardSize;

void simpleBillboard()
{
    vec3 pos     = gl_in[0].gl_Position.xyz;
    vec3 up      = u_Up*gSize[0];
    vec3 right   = u_Right*gSize[0];

    pos         -= right;
    gl_Position  = u_MVP*vec4(pos, 1.0);
    EmitVertex();

    pos         += up;
    gl_Position  = u_MVP*vec4(pos, 1.0);
    EmitVertex();

    pos         -= up;
    pos         += right;
    gl_Position  = u_MVP*vec4(pos, 1.0);
    EmitVertex();

    pos         += up;
    gl_Position  = u_MVP*vec4(pos, 1.0);
    EmitVertex();

    EndPrimitive();
    
    pos.x = u_BillboardSize;
}

void main()
{
    fAge = gAge[0];
    simpleBillboard();
}
