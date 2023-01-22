attribute vec3 position;
attribute vec2 texCoords;
attribute vec3 normal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

varying vec3 pos;
varying vec2 uvs;
varying vec3 nml;

void main()
{
    pos = position;
    uvs = texCoords;
    nml = normal;
    gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0);
}