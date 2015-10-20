#version 150

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
out vec3 N;
out vec3 V;
out vec3 L;
out vec3 H; 

uniform mat4 uModelView;
uniform mat4 uProjection;
uniform vec4 uLightPosition;
uniform vec4 uLightColor;
uniform vec4 uAmbientLight;

void main()
{
	vec4 normal = uModelView * vec4(vNormal, 0);
	N = normalize(normal.xyz);

	vec4 vPosEye = uModelView * vPosition;
	V = normalize(-vPosEye.xyz);
	L = normalize(uLightPosition.xyz - vPosEye.xyz);
	H = normalize(L + V); // This is doing an average, cleverly enough

	ambientDiffuseColor = vAmbientDiffuseColor;
	specularColor = vSpecularColor;
    diffuseAmount = vDiffuseAmount;
    specularAmount = vSpecularAmount;
    specularExponent = vSpecularExponent;

	gl_Position = uProjection * vPosEye;
}
