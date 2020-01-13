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
    }mat;

uniform sampler2D diffuseTexture;

uniform sampler2D cubetex;
uniform sampler2D cubetexSpec;

uniform sampler2D cubeNormalTex;
in mat3 tbnMatrix;

uniform vec3 camPos;

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
	//color = vec3 (1,0,0);
	//color  = vertexNormal;
	//return;
	vec3 lightDir = normalize(vec3(normalize(lights[0].position - worldPos)));
	//color = lightDir;
	float diffDot = max(dot(vertexNormal, lightDir), 0.0);
	//color = vec3(diffDot,0,0);
	vec3 diffuseColor = diffDot * lights[0].diffuse;
	float ambientFactor = 0.1f;
	vec3 ambientColor = (lights[0].ambient.xyz * ambientFactor);
	vec3 colorMap = vec3 (0.7,0.5,0.5);
	if (mat.ifTextureColor){
		//color = vec3(1,1,0);
		//return;
		//color = vec3(1,0,0);
		//return;
		colorMap = vec3(texture(diffuseTexture,texCoord));
	}else{
		//color = vec3(1,0,0);
		//return;
		colorMap = vertexColor;
	}

	vec3 viewDir = vec3(normalize(camPos - worldPos));
	//vec3 reflectDir = reflect(-lightDir, vertexNormal);
	//float specDot = max(dot(viewDir, reflectDir), 0.0);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float specDot = max(dot(vertexNormal, halfwayDir), 0.0);
	float spec = pow(specDot, 32);
	float specStrength = 1.0;
	//float specStrength = 0.5; // tweeking the specular strength a bit
	vec3 specularColor = specStrength * spec * lights[0].specular;


	//color = (ambientColor2 + diffuseColor2) * colorMap2.rgb;
	color = vec4((ambientColor + diffuseColor) * colorMap.rgb + (specularColor), 1.0);


	
}
