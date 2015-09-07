#version 150

in highp vec3 vert;
in highp vec3 vertNormal;

uniform highp vec3 lightPos;

out highp vec4 fragColor;

void main() {
    highp vec3 normal = normalize(vertNormal);
    highp vec3 s = normalize(lightPos - vert);
    highp vec3 di = vec3(max(dot(s, normal), 0.0));

    // Final color
    fragColor = vec4(clamp(di, 0.0, 1.0), 1.0); //vec4(1.0, 1.0, 1.0, 1.0);
}
