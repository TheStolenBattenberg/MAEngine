attribute vec3 in_Position;
attribute vec3 in_Normal;
attribute vec4 in_Colour;

varying vec3 v_Position;
varying vec3 v_Normal;
varying vec4 v_Colour;

uniform mat3 u_NormalMat;

void main() {
    v_Position = vec3(gm_Matrices[MATRIX_WORLD_VIEW] * vec4(in_Position, 1.0));
    v_Normal   = normalize(u_NormalMat * in_Normal);
    v_Colour   = in_Colour;
    
    gl_Position = gm_Matrices[MATRIX_WORLD_VIEW_PROJECTION] * vec4(in_Position, 1.0);
}

//######################_==_YOYO_SHADER_MARKER_==_######################@~varying vec3 v_Position;
varying vec3 v_Normal;
varying vec4 v_Colour;

uniform vec3 u_LightPos;
uniform vec3 u_AmbientColour;
uniform vec3 u_SpecColour;

void main() {
    vec4 diffuseColour = v_Colour;
    
    vec3 lightDir = normalize(u_LightPos - v_Position);
    vec3 viewDir  = normalize(-v_Position);
    
    float lamb = max(dot(lightDir, v_Normal), 0.0);
    float spec = pow(max(dot(normalize(lightDir + viewDir), v_Normal), 0.0), 16.0);
    
    gl_FragColor = vec4(u_AmbientColour + lamb * diffuseColour.rgb + spec * u_SpecColour, diffuseColour.a);
}

