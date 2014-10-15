
layout(points)           in;
layout(triangle_strip)   out;
layout(max_vertices = 4) out;

in float gAge[];
in float gType[];
out float fAge;
out float fType;

uniform mat4  u_MVP;
uniform vec3  u_Right;
uniform vec3  u_Up;

uniform float uBillboardSize;

void simpleBillboard()
{
    float size = uBillboardSize - ((uBillboardSize * fAge) * 0.8);
    
    vec3 pos     = gl_in[0].gl_Position.xyz;
    vec3 up      = u_Up*size;
    vec3 right   = u_Right*size;

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
}

void main()
{
    fAge = gAge[0];
    fType = gType[0];
    simpleBillboard();
}
