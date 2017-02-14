# version 330
in vec4 vPosition ;
in vec3 vNormals ;
in vec4 vColors;

uniform mat4 model ;
uniform mat4 view ;
uniform mat4 projection ;
uniform mat3 normalMatrix ;

uniform vec4 lightPosition ;

out vec3 fN ;
out vec3 fE ;
out vec3 fL ;
out vec4 v2fcolor;

void main () {
    vec4 eyePosition = view * model * vPosition ;
    fN = mat3 ( view ) * normalMatrix * vNormals ;
    fL = lightPosition.xyz - eyePosition.xyz ;
    fE = - eyePosition.xyz ;
    gl_Position = projection * eyePosition ;
    v2fcolor = vColors;
}
