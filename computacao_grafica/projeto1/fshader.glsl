#version 330
in vec2 ftexCoord;
uniform sampler2D colorTexture;

uniform float width;
uniform float slider;

out vec4 outColor;

void main(void) {
    outColor = texture2D(colorTexture, ftexCoord);
}
