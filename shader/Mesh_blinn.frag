#version 330 core

in vec3 vertexColor;
in vec3 vertexNormal;
in vec3 worldPos;
in vec2 texCoord;

uniform struct Material{
        vec3 ka;
        vec3 kd;
        vec3 ks;
        float ns;
        bool ifTextureColor;
        bool hasNormalTexture;
        bool hasSpecTexture;
        bool hasObjectColor;
        vec3 color;
        float illumination;
}mat;

in mat3 tbnMatrix;

uniform vec3 camPos;
uniform bool isLight;
uniform vec3 lightColor;

layout(location = 0) out vec4 color;

uniform struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform struct DirLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform int lightCount;
uniform Light lights[100];

uniform int dirLightCount;
uniform DirLight dirLights[100];

vec3 specularCalc(vec3 lightDir, vec3 lightColor){
	vec3 viewDir = normalize(camPos - worldPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(vertexNormal, halfwayDir), 0.0), mat.ns);
	return lightColor * spec * mat.ks;
}

void main()
{
	color = vec4(0,0,0,1);

	//dir lights
	for (int i = 0; i < dirLightCount; i++){
		//diffuse
		float diff = max(dot(vertexNormal, -dirLights[i].direction), 0.0);
		vec3 diffuse = dirLights[i].diffuse * diff * mat.kd;

		//specular
		vec3 specular = specularCalc(-dirLights[i].direction, dirLights[i].specular);

		color += vec4(diffuse + specular, 1);
	}

	//point lights
	for (int i = 0; i < lightCount; i++){
            
		vec3 lightDir = normalize(lights[i].position - worldPos);
            
		//diffuse
		float diff = max(dot(vertexNormal, lightDir), 0.0f);
		vec3 diffuse = lights[i].diffuse * diff * mat.kd;
            
            
		//specular
		vec3 specular = specularCalc(lightDir, lights[i].specular);

		color += vec4(diffuse + specular, 1);
    }

	if (isLight){
		color = vec4(lightColor, 1);
	}
}
