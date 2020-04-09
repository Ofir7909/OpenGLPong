#shader vertex

#version 330 core

uniform mat4 u_MVP;

layout(location = 0) in vec4 position;

varying vec2 vPos;

void main()
{
	vPos		= position.xy;
	gl_Position = u_MVP * position;
};

#shader fragment

#version 330 core

layout(location = 0) out vec4 fragColor;

uniform vec4 u_Color;

float CircleShape(vec2 position, float radius, float smoothing)
{
	return 1 - smoothstep(radius - smoothing, radius, length(position));
}

varying vec2 vPos;

void main()
{
	float alpha = CircleShape(vPos, 0.5, 0.05);
	fragColor	= vec4(u_Color.xyz, alpha);
}