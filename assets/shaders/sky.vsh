attribute vec3 position;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

varying vec3 pos;

void main()
{
    pos = position;
    gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0);
}