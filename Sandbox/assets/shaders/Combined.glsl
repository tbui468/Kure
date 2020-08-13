#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;

out vec2 v_TexCoord;
out vec4 v_Color;

uniform mat4 u_ViewProjMatrix;
//uniform mat4 u_Transform;

void main() {
	gl_Position = u_ViewProjMatrix * vec4(a_Position, 1.0);
	v_TexCoord = a_TexCoord;
	v_Color = a_Color;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_Color;

uniform sampler2D u_Texture;
uniform float u_TexScale;
uniform vec4 u_Color;

void main() {
	//color = texture(u_Texture, v_TexCoord * u_TexScale) * u_Color;
	color = v_Color;
}
