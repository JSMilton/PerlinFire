
in float fAge;
in float fType;
out vec4 out_FragColor;

const vec3 colorOne = vec3(0,0,1.0);
const vec3 colorTwo = vec3(0.85,0.65,0.45);

void main()
{
    //out_FragColor = vec4(1,1,1,1.0);
    float ageMod = 1;
    if (fAge > 0.8) ageMod = 1.25;
   // if (fType == 1){
    //    out_FragColor = vec4(colorOne.x-fAge,colorOne.y-fAge*0.5,colorOne.z-ageMod,1.0-fAge*1.2);
   // } else {
        out_FragColor = vec4(colorTwo.x-fAge * ageMod,colorTwo.y-fAge*ageMod,colorTwo.z-fAge*ageMod,1.0-fAge*1.2);
    //}
}