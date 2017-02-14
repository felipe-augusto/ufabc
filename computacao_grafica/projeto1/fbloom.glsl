#version 330

uniform sampler2D colorTexture;
uniform float threshold = 0.75;

uniform float slider;
uniform float controler;

in vec2 ftexCoord;

out vec4 outColor;

// aproxima a iluminacao (!?) de um valor RGB
float luma( vec3 color ) {
    return 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
}

void main(void) {

        float proportion = slider / 100;

        if (ftexCoord.x <= proportion) {
            outColor = texture2D(colorTexture, ftexCoord);
        } else {
            vec4 color = texture2D(colorTexture, ftexCoord);
            // clamp — constrain a value to lie between two further values
            // tem como ser maior que um (!?) o clamp (acho que nao)
            // se luma(color.rgb) - threshold <= 0 -> retorna (0,0,0,0)
            // se > 0 eh escalado pela quantidade de iluminacao acima do threshold
            outColor = color * clamp(luma(color.rgb) - (controler / 100), 0.0, 1.0) * (1.0 / (1.0 - (controler / 100)));
        }


}
