#version 410

#define IOR 1.45

#define LIGHTOFFSET vec3(0.0,5.0,0.0)

#define PI 3.14159265359
//-----------------------------------------------------
//FROM THE VERT SHADER
in vec3 fragWorldPos;
in vec3 fragNormal;
in vec2 fragmentTexCoord;
//-----------------------------------------------------
//UNIFORMS
uniform samplerCube envMap;                   //Cubemap
uniform vec3 lightPos = vec3(1.0f,10.0f,2.0f);//Position of our light
uniform vec3 lightCol = vec3(1.0f,1.0f,1.0f); //Colour of the light
uniform float roughness  = 0.5f;              //BRDF Roughness
uniform float shineyness = 0.5f;              //BRDF shineyness
layout (location=0) out vec4 FragColor;       //Final Colour
//-----------------------------------------------------
//-------Prototyping functions
//General functions
float random(vec2 st);
float  noise(vec2 st);
//BRDF functions
float fresnel();
float roughnessnessDist();
float geoCalc(float k);
float NDF();
//-----------------------------------------------------
//Clamps between 0 and 1 (Basically HLSL now.)
float saturate(float i)
{
    return clamp(i, 0, 1);
}
//#PolymorphismIsCool
vec3 saturate(vec3 i)
{
    return clamp(i, 0, 1);
}
//-----------------------------------------------------
//=====================================================BEGIN DEFINING GLOBAL VALUES
struct inputVectors{
    vec3 n;// Unit surface normal
    vec3 s;// The light vector
    vec3 v;// Unit vector in direction of the viewer
    vec3 r;// Reflect the light about the surface normal
    vec3 h;// The half vector
};
inputVectors inVec = inputVectors(
            /*n*/normalize(fragNormal),
            /*s*/normalize( lightPos+LIGHTOFFSET - fragWorldPos ),
            /*v*/normalize(fragWorldPos),
            /*r*/reflect(normalize( lightPos+LIGHTOFFSET - fragWorldPos ),  normalize(fragNormal)),
            /*h*/normalize(normalize(fragWorldPos)+normalize( lightPos+LIGHTOFFSET - fragWorldPos ))
            );

struct iconicAngles{
    float NdotH;//Dot product of the surface normal and the half angle
    float NdotL;//Dot of the light and the normal vectors
    float NdotV;//Dot of the normal and the and the view vector
    float VdotH;//Dot of the vertex position and the half vector, used for fresnel
};
iconicAngles dotProds  = iconicAngles(
            /*NdotH*/saturate(dot(inVec.n, inVec.h)),
            /*NdotL*/saturate(dot(inVec.n,inVec.s)),
            /*NdotV*/saturate(dot(inVec.n,inVec.v)),
            /*VdotH*/saturate(dot(inVec.v,inVec.h))
            );
//=====================================================END DEFINING GLOBAL VALUES
//-----------------------------------------------------
//=====================================================BEGIN NOISE FUNCTIONS
// The following section is from :-
// Patricio Gonzalez Vivo (2015). The Book of Shaders : Random [online]. [Accessed 03/04/2017].
// Available from: "https://thebookofshaders.com/10/".
float random (vec2 st)
{
    return fract(sin(dot(st.xy,vec2(12.9898,78.233)))*43758.5453123);
}
float noise (vec2 st)
{
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec2 u = f*f*(3.0-2.0*f);
    // u = smoothstep(0.,1.,f);

    // Mix 4 coorners porcentages
    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}
// end of Citation
//=====================================================END NOISE FUNCTIONS
//-----------------------------------------------------
//=====================================================BEGIN BRDF FUNCTIONS
float fresnel()
{
    //Schlick approximation using spherical gaussian, as in UE4
    //https://de45xmedrsdbp.cloudfront.net/Resources/files/2013SiggraphPresentationsNotes-26915738.pdf
    float F0 = 0.8;
    return min(1.0, F0 + (1 - F0)*pow(2, ((-5.55473*dotProds.VdotH)-(-6.98316)*dotProds.VdotH)));
}
float roughnessnessDist()
{
    //The shininess squared
    float alpha  = roughness*roughness;
    float alpha2 = alpha*alpha;

    float r1 = dotProds.NdotH * dotProds.NdotH;
    float r2 = (alpha2 - 1.0) + 1.0;
    float r3 = r1*r2;
    return min(1.0, alpha2 / (PI * r3 * r3));
}
float geoCalc(float k)
{
    float geo1 = dotProds.NdotL / ((dotProds.NdotL*(1-k))+k);
    float geo2 = dotProds.NdotV / ((dotProds.NdotV*(1-k))+k);
    return min(geo1 * geo2, 1.0);
}
//normal distribution function GGX/Trowbridge-Reitz
float NDF()
{
    float _NdotH2 = dotProds.NdotH * dotProds.NdotH;
    float alpha2  = roughness*roughness;
    float denTerm = _NdotH2*(alpha2-1)+1;

    return alpha2/PI*(denTerm*denTerm);
}
//=====================================================END BRDF FUNCTIONS
//-----------------------------------------------------
//=====================================================BEGIN ENV FUNCTIONS
vec3 envColour()
{
    vec4 env        = texture(envMap, reflect(inVec.v, inVec.n));
    return vec3(env);
}
vec4 smudgedEnvColour()
{
    vec4 env        = textureLod(envMap, reflect(inVec.v, inVec.n), 6);
    vec4 smudgedEnv = textureLod(envMap, reflect(inVec.v, inVec.n), 8);
    return mix(smudgedEnv, env, noise(fragmentTexCoord.xx*1000)) * shineyness;
}
//=====================================================END ENV FUNCTIONS
//-----------------------------------------------------
//=====================================================BEGIN IMAGE BASED LIGHTING FUNCTIONS
// The following section is from :-
// Holger Dammertz (2012). Hammersley Points on the Hemisphere [online]. [Accessed 12/05/2017].
// Available from: "http://holger.dammertz.org/stuff/notes_HammersleyOnHemisphere.html".
float radicalInverse_VdC(uint bits)
{
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}
vec2 Hammersley(uint i, uint N)
{
    return vec2(float(i)/float(N), radicalInverse_VdC(i));
}
// end of Citation

// The following section is edited from :-
//  Brian Karis (2013). Real Shading in Unreal Engine 4 [online]. [Accessed 12/05/2017].
// Available from: "https://de45xmedrsdbp.cloudfront.net/Resources/files/2013SiggraphPresentationsNotes-26915738.pdf".
vec3 ImportanceSampleGGX(vec2 Xi)
{
    float a = roughness * roughness;
    float Phi = 2 * PI * Xi.x;
    float CosTheta = sqrt( (1 - Xi.y) / ( 1 + (a*a - 1) * Xi.y ) );
    float SinTheta = sqrt( 1 - CosTheta * CosTheta );
    vec3 H;
    H.x = SinTheta * cos( Phi );
    H.y = SinTheta * sin( Phi );
    H.z = CosTheta;
    vec3 N = inVec.n;
    vec3 UpVector = abs(N.z) < 0.999 ? vec3(0,0,1) : vec3(1,0,0);
    vec3 TangentX = normalize( cross( UpVector, N ) );
    vec3 TangentY = cross( N, TangentX );
    // Tangent to world space
    return TangentX * H.x + TangentY * H.y + N * H.z;
}
vec3 SpecularIBL( vec3 SpecularColor , float _k )
{
    vec3 SpecularLighting = vec3(0);
    const uint NumSamples = 1024;
    for( uint i = 0; i < NumSamples; i++ )
    {
        vec2 Xi = Hammersley( i, NumSamples );
        vec3 H = ImportanceSampleGGX(Xi);
        vec3 L = 2 * dotProds.VdotH * inVec.h - inVec.v;
        if( dotProds.NdotL > 0 )
        {
            vec3 SampleColor = envColour();
            float G = geoCalc(_k);
            float Fc = pow( 1 - dotProds.VdotH, 5 );
            vec3 F = (1 - Fc) * SpecularColor + Fc;

            SpecularLighting += SampleColor * F * G * dotProds.VdotH / (dotProds.NdotH * dotProds.NdotV);
        }
    }
    return (saturate(SpecularLighting) / NumSamples);
}
// end of Citation
//=====================================================END IMAGE BASED LIGHTING FUNCTIONS
//-----------------------------------------------------
//=====================================================BEGIN MAIN
void main()
{
    float k1 = (roughness+1)*(roughness+1);
    float k  = k1/8;

    vec3 diffuseColour  =  vec3(0.8);

    diffuseColour *= dotProds.NdotL;

    vec3 specular = vec3(0.0);

    if(dotProds.NdotL > 0)
    {
        vec3 specNum  = lightCol * vec3(fresnel() * geoCalc(k) * NDF());
        float specDen = 4*dotProds.NdotL*dotProds.NdotV;
        specular += saturate(specNum / specDen);
    }
    vec3 final =  SpecularIBL( specular, k ) + diffuseColour + (lightCol*(length(inVec.s)/10));

    if(fragmentTexCoord.x>0.5)//Sides of the fork
        FragColor = mix(vec4(final, 1.0f), smudgedEnvColour(), clamp(noise(fragmentTexCoord*1000), 0.5, 1.0));
    else
        FragColor = mix(vec4(final, 1.0f), smudgedEnvColour(), geoCalc(k));
}
