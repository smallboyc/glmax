#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
//
uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float Ns;

uniform bool useTexture;
uniform sampler2D map_Kd;

void main() {

    vec3 diffuseColor = useTexture ? texture(map_Kd, TexCoords).rgb : Kd;

    // Ambient
    vec3 ambient = Ka * (lightColor * 0.25);

    // Diffuse
    vec3 L = normalize(lightPos - FragPos);
    vec3 N = normalize(Normal);
    float diff = max(dot(L, N), 0.0);
    vec3 diffuse = diff * diffuseColor * lightColor;

    // Specular
    vec3 V = normalize(viewPos - FragPos);
    vec3 H = normalize(L + V);
    float spec = pow(max(dot(N, H), 0.0), Ns);
    vec3 specular = spec * Ks * lightColor;

    // => Blinn-Phong
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
