#version 330

uniform sampler2D colorTexture;

uniform float slider;
uniform float controler;
uniform float width;
uniform float height;

in vec2 ftexCoord;

out vec4 outColor;

uniform float PixOffset[5] = float[](0.0,1.0,2.0,3.0,4.0);

float gauss(int x, float sigma2) {
    // 1-D funcao de gauss
    return (1 / sqrt(2 * 3.14159265358979323846 * sigma2)) * pow(2.71828182845904523536, -(pow(x,2)/(2 * sigma2)));
}

void main(void) {
        // sigma2 eh a variancia, e determina o comprimento da curva gaussiana
        // slide tem um valor de um a cem
        float proportion = slider / 100;
        // x varia de 0 a 1
        if (ftexCoord.x <= proportion) {
            outColor = texture2D(colorTexture, ftexCoord);
        } else {
            // pesos de gauss
            float pesos[5];
            float sigma2 = pow(controler / 10 + 1, 2);

            //calcula os pesos (!?)
            pesos[0] = gauss(0, sigma2);

            float weight_sum;
            weight_sum = pesos[0];

            // muito eneficiente deixar isso aqui, deveria ficar fora
            // os valores sao constantes
            for (int i = 0; i < 4; i++) {
                pesos[i] = gauss(i, sigma2);
                // vezes dois para os positivos e negativos (o x na equacao esta ao quadrado
                // economiza uns lacos fazendo isso
                weight_sum += 2.0 * pesos[i];
            }

            // primeiro fazemos a soma em y
            // armazena numa textura temporária
            // proximo pixel
            float dx = 1.0 / width;
            float dy = 1.0 / height;

            vec4 sum = texture2D(colorTexture, ftexCoord) * (pesos[0] / weight_sum);

            for (int i = 1; i < 3; i++) {
                // em y
                // float(i - 1) * dy
                sum += texture2D(colorTexture, ftexCoord + vec2(0.0, PixOffset[i] * dy)) * (pesos[i] / weight_sum);
                sum += texture2D(colorTexture, ftexCoord - vec2(0.0, PixOffset[i] * dy)) * (pesos[i] / weight_sum);
                // em x
                sum += texture2D(colorTexture, ftexCoord + vec2(PixOffset[i] * dx), 0.0) * (pesos[i] / weight_sum);
                sum += texture2D(colorTexture, ftexCoord - vec2(PixOffset[i] * dx), 0.0) * (pesos[i] / weight_sum);
            }

            // divide por weight_sum (!?)
            outColor = sum;
        }
}
