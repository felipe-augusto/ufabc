#version 330

uniform sampler2D colorTexture;
uniform float slider;

in vec2 ftexCoord;

out vec4 outColor;

void main(void) {
        // slide tem um valor de um a cem
        float proportion = slider / 100;
        // x varia de 0 a 1
        if (ftexCoord.x <= proportion) {
            outColor = texture2D(colorTexture, ftexCoord);
        } else {
            vec4 color = texture2D(colorTexture, ftexCoord);
            color.rgb = 1. - color.rgb;
            outColor =  color;
        }
}
