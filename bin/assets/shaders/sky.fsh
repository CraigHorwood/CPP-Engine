uniform samplerCube textureSampler;

varying vec3 pos;

void main()
{
    gl_FragColor = texture(textureSampler, pos);
}