
in float fAge;
in float fType;
out vec4 out_FragColor;

const vec3 colorOne = vec3(0,0,1.0);
const vec3 colorTwo = vec3(0.5,0.5,1.0);

void main()
{
    //out_FragColor = vec4(1,1,1,1.0);
    float ageMod = 0;
    if (fAge > 0.2)ageMod = fAge-0.2;
   // if (fType == 1){
    //    out_FragColor = vec4(colorOne.x-fAge,colorOne.y-fAge*0.5,colorOne.z-ageMod,1.0-fAge*1.2);
   // } else {
        out_FragColor = vec4(colorTwo.x-fAge,colorTwo.y-fAge*0.5,colorTwo.z-ageMod,1.0-fAge*1.2);
    //}
}