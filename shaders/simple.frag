#version 150

in highp vec3 vert;
in highp vec3 vertNormal;

uniform highp vec3 lightPos;
uniform highp vec3 frontColor;
uniform highp vec3 backColor;

out highp vec4 fragColor;

void main() {
    highp vec3 normal = normalize(vertNormal);
    highp vec3 viewDir = normalize(-vert);

    highp float normalViewCos = dot(normal, viewDir);
    highp float fronted = sign(clamp(normalViewCos, 0.0, 1.0));
    highp float backed = sign(clamp(-normalViewCos, 0.0, 1.0));
    highp vec3 facedColor = fronted * frontColor + backed * backColor;

    highp vec3 s = normalize(lightPos - vert);
    highp float normalLightCos = dot(s, normal);
    highp float di = fronted * max(normalLightCos, 0.0) + backed * max(-normalLightCos, 0.0);

    fragColor = vec4(clamp(di, 0.2, 1.0) * facedColor, 1.0);
}
