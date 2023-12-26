#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

out vec4 vCor;
out vec2 texCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 visao;

void main(){
	gl_Position = proj * visao * model * vec4(pos, 1.0);
	vCor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);

	texCoord = tex;

	Normal = mat3(transpose(inverse(model))) * norm;

	FragPos = (model * vec4(pos, 1.0)).xyz;
}