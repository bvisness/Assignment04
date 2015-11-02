#version 150

#define MAX_LIGHTS 6

#define LIGHT_DISABLED 0
#define LIGHT_POINT 1
#define LIGHT_SPOT 2
#define LIGHT_DIRECTIONAL 3

in vec4 posEye;
in vec3 normal;
in vec4 ambientDiffuseColor;
in vec4 specularColor;
in float diffuseAmount;
in float specularAmount;
in float specularExponent;

uniform int uLightType[MAX_LIGHTS];
uniform vec4 uLightPosition[MAX_LIGHTS];
uniform vec4 uLightDirection[MAX_LIGHTS];
uniform float uLightSpotAngleCos[MAX_LIGHTS];
uniform vec4 uLightColor[MAX_LIGHTS];
uniform vec4 uAmbientLight;

out vec4 fColor;

void main()
{
    vec4 amb = ambientDiffuseColor * uAmbientLight;
    vec4 diff = vec4(0, 0, 0, 0);
    vec4 spec = vec4(0, 0, 0, 0);
    
    for (int i = 0; i < MAX_LIGHTS; i++) {
        if (uLightType[i] == 0) {
            continue;
        }
        
        vec3 fN = normalize(normal);
		vec3 fL;
		if (uLightType[i] == LIGHT_DIRECTIONAL) {
			fL = -normalize(uLightDirection[i].xyz);
		} else {
			fL = normalize(uLightPosition[i].xyz - posEye.xyz);
		}
        vec3 fH = normalize(fL + normalize(-posEye.xyz));

		bool isLit = true;
		if (uLightType[i] == LIGHT_SPOT) {
			isLit = dot(normalize(uLightDirection[i].xyz), -fL) >= uLightSpotAngleCos[i];
		}

		if (isLit) {
			diff += max(0, dot(fN, fL)) * diffuseAmount * ambientDiffuseColor * uLightColor[i];
			spec += pow(max(0, dot(fN, fH)), specularExponent) * specularAmount * specularColor * uLightColor[i];
		}
	}
    
    fColor = amb + diff + spec;
    //fColor = amb;
    //fColor = diff;
    //fColor = spec;
    //fColor = vec4(fN, 1);
    //fColor = vec4(diffuseAmount, diffuseAmount, diffuseAmount, 1);
    //fColor = vec4(specularAmount, specularAmount, specularAmount, 1);
	//fColor = specularColor;
	//fColor = vec4(dot(N[0], H[0]), dot(N[0], H[0]), dot(N[0], H[0]), 1);
    //fColor = vec4(specularExponent, specularExponent, specularExponent, 1);
	//fColor = uLightColor[0];
	//fColor = vec4(uLightSpotAngleCos[0], uLightSpotAngleCos[0], uLightSpotAngleCos[0], 1);
	//fColor = vec4(dot(uLightDirection[0].xyz, -L[0]), dot(uLightDirection[0].xyz, -L[0]), dot(uLightDirection[0].xyz, -L[0]), 1);
	//fColor = vec4((L[0].r + 1) / 2, (L[0].g + 1) / 2, (L[0].b + 1) / 2, 1);
}
