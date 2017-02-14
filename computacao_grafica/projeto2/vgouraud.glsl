# version 330
in vec4 vPosition ;
in vec3 vNormals ;

// gouraud usa as equacoes nos vertices

// olhar nas contas exatamente qual eh qual
// nas variaveis

uniform mat4 model ;
// camera
uniform mat4 view ;
uniform mat4 projection ;
// matrix reponsavei para aplicar as transformacoes
// inversa da normal
uniform mat3 normalMatrix ;

uniform vec4 ambientProduct ;
uniform vec4 diffuseProduct ;
uniform vec4 specularProduct ;
uniform float shininess ;
uniform vec4 lightPosition ;

out vec4 inoutColor ;

void main () {
    // calcular o ponto que a luz sera calculada a partir do observador
    vec4 eyePosition = view * model * vPosition;
    // NORMAL
    vec3 N = normalize ( mat3 ( view ) * normalMatrix * vNormals ) ;
    // calcula o vertor iluminacao
    vec3 L = normalize ( lightPosition.xyz - eyePosition.xyz ) ;
    // vetor E (0,0,0) , eh o centro
    vec3 E = normalize ( - eyePosition.xyz ) ;

    // produto usa algumas vezes
    float NdotL = dot (N , L ) ;

    // o que acontece quando tira o max (PERGUNTA DE PROVA)

    // calcula o vetor reflexao - comando do glsl (reflect
    vec3 R = normalize (2.0 * NdotL * N - L ) ;
    // agora entra na equacao propriamente dita
    // ou a parte de dentro ou de tras se for negativa (!?) -> nao quer negativos
    float Kd = max ( NdotL , 0.0) ;

    // se for menor que zero ou esta na parte de dentro ou na parte de tras
    // aqui ta preocupado com a parte de dentro
    float Ks = ( NdotL < 0.0) ? 0.0 : pow ( max ( dot (R , E ) , 0.0) , shininess ) ;

    vec4 diffuse = Kd * diffuseProduct ;
    vec4 specular = Ks * specularProduct ;
    vec4 ambient = ambientProduct ;

    inoutColor = vec4 (( ambient + diffuse + specular ).rgb , 1.0) ;

    // nao pode esquecer de multiplicar pela projecao
    gl_Position = projection * eyePosition ;
}
