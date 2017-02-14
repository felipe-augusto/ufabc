#version 330

uniform sampler2D colorTexture;
uniform float slider;
uniform float controler;

uniform float width;
uniform float height;

in vec2 ftexCoord;

out vec4 outColor;

void main(void) {
        // slide tem um valor de um a cem
        float proportion = slider / 100;
        // x varia de 0 a 1
        if (ftexCoord.x <= proportion) {
            outColor = texture2D(colorTexture, ftexCoord);
        } else {
            // acha qual o minimo e o maximo
            float minimum = min(width, height);
            float maximum = max(width, height);
            //acha a escala para criar quadrados de pixel na mesma proporcao
            float scale = maximum / minimum;
            // 1.0 / width -> incremento em x que equivale a um pixel
            // mesmo para height
            // aqui estamos criando um retangulo de 10 pixels de width e 15 de height
            float dx = ((5 + controler * scale) / 5) * (1.0 / width);
            float dy = ((5 + controler) / 5) * (1.0 / height);
            // prenche todo o retangulo com os valores do pixel da esquerda inferior
            // se ftexCoord % dx == 0, estamos no pixel da esquerda inferior
            // se nao precisa pegar esse pixel para escolher a cor
            vec2 recCoords = vec2(dx * floor(ftexCoord.x/dx), dy * floor(ftexCoord.y / dy));
            // outColor e sempre o do pixel da esquerda inferior do retangulo
            outColor =  texture2D(colorTexture, recCoords);
        }
}
