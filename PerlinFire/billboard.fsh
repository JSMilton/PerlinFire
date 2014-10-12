
in float fAge;
out vec4 out_FragColor;

void main()
{
    //out_FragColor = vec4(1,1,1,1.0);
    float ageMod = 0;
    if (fAge > 0.3)ageMod = fAge-0.3;
    out_FragColor = vec4(0.5-fAge,0.5-fAge*0.5,1.0-ageMod,1.0-fAge);
}