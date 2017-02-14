
#version 330
uniform sampler2D colorTexture;

uniform float slider;
uniform float controler;
uniform float width;
uniform float height;

in vec2 ftexCoord;

out vec4 outColor;

float pixel_intensity(in vec2 pix_coords, in float dx, in float dy) {
    vec4 pix_pos = texture2D(colorTexture, pix_coords + vec2(dx, dy));
    // luma do livro - o que isso faz?
    // isso representa a iluminacao da imagem
    return (0.2126 * pix_pos.r + 0.7152 * pix_pos.g + 0.0722 * pix_pos.b);
    // return (pix_pos.r + pix_pos.g + pix_pos.b)/3;
}

void main(void) {
        // slide tem um valor de um a cem
        float proportion = slider / 100;
        // x varia de 0 a 1
        if (ftexCoord.x <= proportion) {
            outColor = texture2D(colorTexture, ftexCoord);
        } else {
            vec4 color = texture2D(colorTexture, ftexCoord);

            // pega cordenadas x, y do pixel
            vec2 pix_coords = ftexCoord;

            // ve qual o incremento para pegar o proximo pixel
            float dx = 1.0 / width;
            float dy = 1.0 / height;

            // operador SOBEL hardcoded
            float pix[9];

            pix[0] = pixel_intensity(pix_coords, -dx, dy); // s00
            pix[1] = pixel_intensity(pix_coords, -dx, 0.0); // s10
            pix[2] = pixel_intensity(pix_coords, -dx, -dy); // s20
            pix[3] = pixel_intensity(pix_coords, 0.0, dy); // s01
            pix[4] = pixel_intensity(pix_coords, 0.0, -dy); // s21
            pix[5] = pixel_intensity(pix_coords, dx, dy); // s02
            pix[6] = pixel_intensity(pix_coords, dx, 0.0); // s12
            pix[7] = pixel_intensity(pix_coords, dx, -dy); // s22

            // sobel operator usado para aproximar o gradiente da imagem em cada pixel
            // componente horizontal
            float sx = pix[0] + 2 * pix[1] + pix[2] - (pix[5] + 2 * pix[6] + pix[7]);
            // componente vertical
            float sy = pix[0] + 2 * pix[3] + pix[5] - (pix[2] + 2 * pix[4] + pix[7]);

            // magnitude do gradiente do pixel
            float dist = sx * sx + sy * sy;

            // se for maior que o threshold retorna pintado de vermelho
            // como calcula o threshold ??
            if (dist > controler / 100) {
                outColor = vec4 (1.0, 0.0, 0.0, 1.0);
            } else {
                outColor = vec4 (0.0, 0.0, 0.0, 1.0);
            }
        }
}
