#version 330
in vec2 ftexCoord;

uniform sampler2D colorTexture;
uniform float slider;
uniform float controler;

// valor de gamma varia entre 2.0 e 2.4
// vou fazer variando de 1.5 -> 3.0 atraves do controler (slider vertcical)
uniform float gamma = 2.2;

out vec4 outColor;

void main(void) {
    float proportion = slider / 100;
    // x varia de 0 a 1
    if (ftexCoord.x <= proportion) {
        outColor = texture2D(colorTexture, ftexCoord);
    } else {
        // monitores possuem uma resposta nao linear para intensidade de pixels
        // P = I^G (Intensidade percebida = intensidade do pixel ^ gamma
        // correcao gamma envolve elevar a intensidade do pixel numa potencia que compense
        // a nao linearidade do monitor
        vec3 color = texture2D(colorTexture, ftexCoord).rgb;
        outColor =  vec4( pow (color, vec3(1.0 / (1.5 + controler * 0.015))), 1.0);
    }


}
