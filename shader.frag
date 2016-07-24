#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

in vec2 UV;
layout(location=0) uniform sampler2D tex;

void main() {
    gl_FragColor = texture(tex, UV).rgba;
}
