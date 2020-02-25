#version 430

layout(std140, binding = 0) uniform Matrices
{
	mat4 projection;
	mat4 view;
};

layout (location = 0) in vec3 aPos;

out vec3 TexCoord;

void main(){
    mat4 n_view = mat4(mat3(view));
	gl_Position = projection * n_view * vec4(aPos, 1.0);
	TexCoord = aPos;
}