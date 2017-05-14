#version 410

#define IOR 1.45

#define ROUGH 1

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

// The following section is edited from :-
// Patricio Gonzalez Vivo (2015). The Book of Shaders : Random [online]. [Accessed 03/04/2017].
// Available from: "https://thebookofshaders.com/10/".
float random (vec2 st)
{
    return fract(sin(dot(st.xy,vec2(12.9898,78.233)))*43758.5453123);
    //return max(ret, 0.85);
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

float roughnessDist(float _NdotH)
{
    //The shininess squared
    float alpha  = ROUGH*ROUGH;
    float alpha2 = alpha*alpha;

    float r1 = _NdotH * _NdotH;
    float r2 = (alpha2 - 1.0) + 1.0;
    float r3 = r1*r2;
    return min(1.0, alpha2 / (PI * r3 * r3));
}

float geoCalc(float _Ndot, float k)
{
    return _Ndot / ((_Ndot*(1-k))+k);
}
//normal distribution function GGX/Trowbridge-Reitz
float NDF(float _NdotH)
{
    float _NdotH2 = _NdotH * _NdotH;
    float alpha2  = ROUGH*ROUGH;
    float denTerm = _NdotH2*(alpha2-1)+1;

    return alpha2/PI*(denTerm*denTerm);
}

vec4 envColour(vec3 _v, vec3 _n)
{
    vec4 env        = textureLod(envMap, reflect(_v, _n), 0);
    vec4 smudgedEnv = textureLod(envMap, reflect(_v, _n), 6);
    return mix(smudgedEnv, env, noise(fragmentTexCoord.xx*1000));
}

void main()
{
    //Position of the light
    vec3 lightPos = vec3(2.0f,8.0f,2.0f);
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
    float NdotH = saturate(dot(n, h));
    //Dot of the light and the normal vectors
    float NdotL = saturate(dot(n,s));
    //Dot of the normal and the and the view vector
    float NdotV = saturate(dot(n,v));
    //Dot of the vertex position and the half vector, used for fresnel
    float VdotH = saturate(dot(v,h));

    float k1 = (ROUGH+1)*(ROUGH+1);
    float k  = k1/8;

    vec3 diffuseColour  =  vec3(0.8);

    float geoTerm = min(geoCalc(NdotV, k), geoCalc(NdotL, k));

    vec3 specular = vec3(0.0);

    if(NdotL > 0)
    {
        vec3 specNum  = lightCol * vec3(fresnel(VdotH) * geoTerm * NDF(NdotH));
        float specDen = 4*NdotL*NdotV;
        specular += saturate(specNum / specDen);
    }

    vec3 final =  NdotL * (k + specular * (1.0 - k));

    //    vec3 final =  specular + (diffuseColour * (1-fresnel(NdotH)));

    FragColor = mix(vec4(final, 1.0f), envColour(v,n), geoTerm);
//        FragColor = vec4(final, 1.0f);
//    FragColor = vec4(vec3(noise(fragmentTexCoord*50)),1.0);
}

