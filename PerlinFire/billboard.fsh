
in float fAge;
out vec4 out_FragColor;

void main()
{
    out_FragColor = vec4(0.3-fAge*0.5,0.5-fAge*0.7,1.0-fAge,1.0);
}