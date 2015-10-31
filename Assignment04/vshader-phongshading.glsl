#version 150

#define MAX_LIGHTS 6

in vec4 vPosition;
in vec4 vAmbientDiffuseColor;
in vec3 vNormal;
in float vDiffuseAmount;
in float vSpecularAmount;
in float vSpecularExponent;

vec4 vSpecularColor = vec4(1, 1, 1, 1);

out vec4 ambientDiffuseColor;
out vec4 specularColor;
out float diffuseAmount;
out float specularAmount;
out float specularExponent;
out vec3 N[MAX_LIGHTS];
out vec3 L[MAX_LIGHTS];
out vec3 H[MAX_LIGHTS];

uniform mat4 uModelView;
uniform mat4 uProjection;

uniform int uLightType[MAX_LIGHTS];
uniform vec4 uLightPosition[MAX_LIGHTS];
uniform vec4 uLightDirection[MAX_LIGHTS];
uniform vec4 uAmbientLight;

void main()
{
	vec4 normal = uModelView * vec4(vNormal, 0);
	vec4 vPosEye = uModelView * vPosition;
    
    for (int i = 0; i < MAX_LIGHTS; i++) {
        if (uLightType[i] == 0) {
            continue;
        }
        
        vec3 V = normalize(-vPosEye.xyz);
        
        N[i] = normalize(normal.xyz);
        L[i] = normalize(uLightPosition[i].xyz - vPosEye.xyz);
        H[i] = normalize(L[i] + V);
    }

	ambientDiffuseColor = vAmbientDiffuseColor;
	specularColor = vSpecularColor;
    diffuseAmount = vDiffuseAmount;
    specularAmount = vSpecularAmount;
    specularExponent = vSpecularExponent;

	gl_Position = uProjection * vPosEye;
}
