#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexSlot;
layout(location = 4) in float a_TexScale;

out vec2 v_TexCoord;
out vec4 v_Color;
out float v_TexSlot;
out float v_TexScale;

uniform mat4 u_ViewProjMatrix;
//uniform mat4 u_Transform;

void main() {
	gl_Position = u_ViewProjMatrix * vec4(a_Position, 1.0);
	v_TexCoord = a_TexCoord;
	v_Color = a_Color;
	v_TexSlot = a_TexSlot;
	v_TexScale = a_TexScale;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_Color;
in float v_TexSlot;
in float v_TexScale;

uniform float u_TexScale;
uniform sampler2D u_Textures[32];

void main() {
	color = texture(u_Textures[int(v_TexSlot)], v_TexCoord * v_TexScale) * v_Color;
}
