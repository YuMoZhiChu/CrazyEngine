#version 150

in vec3 fragmColor;
in vec2 fragmtexCord;

out vec4 outColor;

uniform sampler2D tex1;
//uniform sampler2D tex2;

//uniform float weight;

void main()
{
    outColor = texture(tex1, fragmtexCord) * vec4(fragmColor, 1.0);
	
}