#version 410

#define IOR 1.45

#define ROUGH 0.1

#define SHINEY 0.5

#define PI 3.14159265359

// This is passed on from the vertex shader

in vec3 fragWorldPos;

in vec3 fragNormal;

in vec2 fragmentTexCoord;

uniform samplerCube envMap;

uniform sampler2D glossMap;

// This is no longer a built-in variable
layout (location=0) out vec4 FragColor;

float fresnel(float _VdotH)
{
#define FULLFRESNEL
#ifdef FULLFRESNEL
    float g = sqrt((IOR*IOR)+(_VdotH*_VdotH)-1);
    //Fresnel term one
    float F1 = ((g-_VdotH)*(g-_VdotH))/
            (2*((g+_VdotH)+(g+_VdotH)));
    //Fresnel term two
    float F2 = 1+((_VdotH*(g+_VdotH)-1)*(_VdotH*(g+_VdotH)-1))
            /    ((_VdotH*(g-_VdotH)-1)*(_VdotH*(g-_VdotH)+1));
    //full fresnel
    return min(1.0, F1 * F2);
#else
    //Schlick approximation
    float F0 = 0.8;
    //https://de45xmedrsdbp.cloudfront.net/Resources/files/2013SiggraphPresentationsNotes-26915738.pdf
    return min(1.0, F0 + (1 - F0)*pow(2, ((-5.55473*_VdotH)-(-6.98316)*_VdotH));
    //return min(1.0, pow(1.0f - _VdotH, 5.0) * (1.0f - F0) + F0);
#endif
}
//The beckman distribution funtion simulates microfacets on the surface
float roughnessDist(float _NdotH)
{
#define GGX
    //The shininess squared
    float alpha  = ROUGH*ROUGH;
    float alpha2 = alpha*alpha;
#ifdef GGX
    float r1 = _NdotH * _NdotH;
    float r2 = (alpha2 - 1.0) + 1.0;
    float r3 = r1*r2;
    return min(1.0, alpha2 / (PI * r3 * r3));
#else
    //Beckman distribution funcion
    float r1 = 1.0f / (4.0f * mSquared * pow(_NdotH, 4.0f));
    float r2 = _NdotH * _NdotH - 1.0f;
    float r3 = alpha * _NdotH * _NdotH;
    return min(1.0, r1 * exp(r2/r3));
#endif
}

//Cook Paper page 5
//float geoTerm(float _NdotH, float _VdotH, float _NdotL, float _NdotV)
//{
//    float geoNum = 2.0 * _NdotH;
//    float geoDen = _VdotH;

//    float geo_b = (geoNum * _NdotV) / geoDen;
//    float geo_c = (geoNum * _NdotL) / geoDen;
//    return min(1.0, min(geo_b, geo_c));
//}

float geoCalc(float _Ndot, float k)
{
    return _Ndot / ((_Ndot*(1-k))+k);
}

float NDF(float _NdotH)
{
    float _NdotH2 = _NdotH * _NdotH;
    float alpha2  = ROUGH*ROUGH;
    float denTerm = _NdotH2*(alpha2-1)+1;

    return alpha2/PI*(denTerm*denTerm);
}

vec4 envColour(vec3 _v, vec3 _n)
{
    float smudge     = texture(glossMap, fragmentTexCoord).r * 8;
    float roughness  = clamp(smudge,0,8);
    vec4 smudgedEnv = textureLod(envMap, reflect(_v, _n), roughness);
    return smudgedEnv * 0.5f;
}

// The following section is from :-
// Patricio Gonzalez Vivo (2015). The Book of Shaders : Random [online]. [Accessed 03/04/2017].
// Available from: "https://thebookofshaders.com/10/".
float random (vec2 st)
{
    float ret = fract(sin(dot(st.xy,vec2(12.9898,78.233)))*43758.5453123);
    return max(ret, 0.8);
}
// end of Citation

void main()
{
    //Position of the light
    vec3 lightPos = vec3(2.0f,2.0f,2.0f);
    //Colour of the light
    vec3 lightCol = vec3(1.0f,1.0f,1.0f);

    // Transform your input normal
    vec3 n = normalize(fragNormal);
    // Calculate the light vector
    vec3 s = normalize( lightPos - fragWorldPos );
    // Calculate the vertex position
    vec3 v = normalize(fragWorldPos);
    // Reflect the light about the surface normal
    vec3 r = reflect(s, n);
    //The half vector
    vec3 h = normalize(v+s);

    //Dot product of the surface normal and the half angle
    float NdotH = clamp(dot(n, h), 0.0, 1.0);
    //Dot of the light and the normal vectors
    float NdotL = clamp(dot(n,s), 0.0,1.0);
    //Dot of the normal and the and the view vector
    float NdotV = clamp(dot(n,v),0.0,1.0);
    //Dot of the vertex position and the half vector, used for fresnel
    float VdotH = clamp(dot(v,h), 0.0, 1.0);

    float k1 = (ROUGH+1)*(ROUGH+1);
    float k  = k1/8;

    vec3 diffuseColour  =  vec3(0.8, 0.5, 0.1);

    float geoTerm = min(geoCalc(NdotV, k), geoCalc(NdotL, k));

    //https://github.com/kamil-kolaczynski/synthclipse-demos/blob/master/src/jsx-demos/lighting-models/shaders/model/cook-torrance.glsl
//    vec3 specNum  = vec3(fresnel(VdotH) * geoTerm * roughnessDist(NdotH));
//    float specDen = PI * NdotV * NdotL;
//    vec3 specular = clamp(specNum / specDen, 0.0, 1.0);

    vec3 specNum  = vec3(fresnel(VdotH) * geoTerm * NDF(NdotH));
    float specDen = 4*NdotL*NdotV;
    vec3 specular = clamp(specNum / specDen, 0.0, 1.0);



    vec3 final = diffuseColour * NdotL * (k + specular * (1.0 - k));

//    vec3 final =  specular + (diffuseColour * (1-fresnel(NdotH)));

    FragColor = mix(vec4(final, 1.0f), envColour(v,n), random(fragmentTexCoord));

}

