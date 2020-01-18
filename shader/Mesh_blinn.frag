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
uniform int lightIndex;

layout(location = 0) out vec4 color;

uniform struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform int lightCount;
uniform Light lights[100];

void main()
{
	color = vec4(0,0,0,1);

	//point lights
	for (int i = 0; i < lightCount; i++){
            
		vec3 lightDir = normalize(lights[i].position - worldPos);
            
		//diffuse
		float diff = max(dot(vertexNormal, lightDir), 0.0f);
		vec3 diffuse = lights[i].diffuse * diff * mat.kd;
            
            
		//specular
		vec3 viewDir = normalize(camPos - worldPos);
		vec3 halfwayDir = normalize(lightDir + viewDir);
		float spec = pow(max(dot(vertexNormal, halfwayDir), 0.0), mat.ns);
		vec3 specular = lights[i].specular * spec * mat.ks;

		color += vec4(diffuse + specular, 1);
    }

	if (isLight){
		color = vec4(lights[lightIndex].diffuse, 1);
	}
}
