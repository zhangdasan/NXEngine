#version 410 core


in vec2 Position;

out vec4 FragColor;


const vec2  BrickSize   = vec2(90, 90);


vec4 CaculateColor();

void main() {
    FragColor = vec4(1.0);
    FragColor = CaculateColor();
}

vec4 CaculateColor(){
    vec2 position = Position / BrickSize;
    float u = fract(position.x);
    float v = fract(position.y);

    FragColor = vec4(u, v, u * v, 1.0f);
    FragColor = vec4(0.7);
    return vec4(1.0f , 0, 0, 1);
}