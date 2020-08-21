#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_ViewProjMatrix;
uniform mat4 u_Transform;

void main() {
	gl_Position = u_ViewProjMatrix * u_Transform * vec4(a_Position, 1.0);
	v_TexCoord = a_TexCoord;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main() {
	color = texture(u_Texture, v_TexCoord * 10) * vec4(1.0, 0.5, 0.5, 1.0);
}