uniform sampler2D textureSampler;

varying vec3 pos;
varying vec2 uvs;
varying vec3 nml;

const vec3 testLight = vec3(1.0, 4.0, 2.0);

void main()
{
    float dotLight = dot(nml, normalize(testLight));
    float diffuse = clamp(dotLight, 0.25, 1.0);
    gl_FragColor = vec4(texture2D(textureSampler, uvs).xyz * diffuse, 1.0);
}