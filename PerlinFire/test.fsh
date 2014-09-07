
in vec2 st;

out vec4 out_FragColor;
uniform sampler3D uTex;
uniform float uElapsedTime;

void main()
{
    vec3 v = texture(uTex, vec3(st.x, mod((st.y + uElapsedTime*0.5),1.0),1)).xyz;
    out_FragColor = vec4(v,1);
}