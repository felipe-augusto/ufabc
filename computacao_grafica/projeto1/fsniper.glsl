#version 330
in vec2 ftexCoord;

uniform sampler2D colorTexture;

// como pega isso dinamicamente?
// tem que passar no buffer (!!!)

//uniform float width = 594.0; // x
//uniform float height = 437.0; // y

uniform float width;
uniform float height;
uniform float gamma = 2.2;
uniform float slider;

// valor maximo da visao norturno
// varia conforme a intensidade
const vec3 proportion = vec3(0.30, 0.59, 0.11);

out vec4 outColor;

float luma( vec3 color ) {
    return 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
}

void main(void) {
    // slide tem um valor de um a cem
    float proportion = slider / 100;
    // x varia de 0 a 1
    if (ftexCoord.x <= proportion) {
        outColor = texture2D(colorTexture, ftexCoord);
    } else {
        vec4 color =  texture2D(colorTexture, ftexCoord);
        // verifica qual o limite
        float minimum = min(width, height);
        float maximum = max(width, height);

        float proportion = maximum / minimum;
        // remove 10% para nao comer a borda de imagem
        // encontra os centros do sistema de cordenadas

        // o centro eh o (-0.5 , -0.5)
        // tem que usar a formula da elipse
        if (0.4 <=  sqrt(pow((ftexCoord.x - 0.5) , 2) / (pow(1 / proportion, 2)) + pow(ftexCoord.y - 0.5, 2))) {
            outColor = vec4 (0.0 , 0.0, 0.0, 1.0);
        } else {
            // desenha a mira
            if (0.5025 > ftexCoord.x && ftexCoord.x > 0.4975) {
                outColor = vec4 (0.0, 0.0, 0.0, 1.0);
                if (0.5005 > ftexCoord.y && ftexCoord.y > 0.4995) {
                    outColor = vec4 (1.0, 0.0, 0.0, 1.0);
                }
            } else if (0.5025 > ftexCoord.y && ftexCoord.y > 0.4975) {
                outColor = vec4 (0.0, 0.0, 0.0, 1.0);
                if (0.5005 > ftexCoord.x && ftexCoord.x > 0.4995) {
                    outColor = vec4 (1.0, 0.0, 0.0, 1.0);
                }
            } else {
                //estamos dentro da visao do cidadao
                vec4 intensity = vec4 (luma(color.rgb) * proportion);
                vec4 finalColor = color * vec3(0.0, intensity.g, 0.0);
                // faz correcao gamma
                outColor =  vec4( pow (finalColor.rgb, vec3(1.0 / gamma)), 1.0);
            }

        }
    }

}
