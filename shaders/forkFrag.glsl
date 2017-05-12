#version 410

#define IOR 1.45

#define SHINEY 0.3

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
    return F1 * F2;
#else
    //Schlick approximation
    float F0 = 0.8;
    return pow(1.0f - _VdotH, 5.0) * (1.0f - F0) + F0;
#endif
}
//The beckman distribution funtion simulates microfacets on the surface
float beckmanRoughness(float _NdotH)
{
    //The shininess squared
    float mSquared = SHINEY * SHINEY;

    //Beckman distribution funcion
    float r1 = 1.0f / (4.0f * mSquared * pow(_NdotH, 4.0f));
    float r2 = _NdotH * _NdotH - 1.0f;
    float r3 = mSquared * _NdotH * _NdotH;
    return r1 * exp(r2/r3);
}

//Cook Paper page 5
float geoTerm(float _NdotH, float _VdotH, float _NdotL, float _NdotV)
{
    float geo_numerator = 2.0 * _NdotH;
    float geo_denominator = _VdotH;

    float geo_b = (geo_numerator * _NdotV) / geo_denominator;
    float geo_c = (geo_numerator * _NdotL) / geo_denominator;
    return min(1.0, min(geo_b, geo_c));
}

vec4 envColour(vec3 _v, vec3 _n)
{

    float smudge     = texture(glossMap, fragmentTexCoord).r * 8;
    float roughness  = clamp(smudge,0,8);
    vec4 smudgedEnv = textureLod(envMap, reflect(_v, _n), roughness);
    return smudgedEnv * 0.1f;

}

void main()
{
    //Position of the light
    vec3 lightPos = vec3(5.0f,5.0f,5.0f);
    //Colour of the light
    vec3 lightCol = vec3(1.0f,1.0f,1.0f);

    // Transform your input normal
    vec3 n = normalize(fragNormal);
    // Calculate the light vector
    vec3 s = normalize( lightPos - fragWorldPos );
    // Calculate the vertex position
    vec3 v = normalize(-fragWorldPos);
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

    vec3 specularColour = vec3(envColour(v, n)) * vec3(0.7) * lightCol;

    vec3 diffuseColour  =  vec3(1.0);

    //https://github.com/kamil-kolaczynski/synthclipse-demos/blob/master/src/jsx-demos/lighting-models/shaders/model/cook-torrance.glsl
    vec3 Rs_numerator = vec3(fresnel(VdotH) * geoTerm(NdotH, VdotH, NdotL, NdotV) * beckmanRoughness(NdotH));
    float Rs_denominator = NdotV * NdotL;
    vec3 Rs = clamp(Rs_numerator / Rs_denominator, 0.0, 1.0);


    vec3 final =  (specularColour * Rs) + (diffuseColour * (1-fresnel(NdotH)));

    FragColor = (vec4(final, 1.0) + envColour(v, n))/2;
}

