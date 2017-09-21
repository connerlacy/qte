
uniform mat4    u_mvp_matrix;
uniform float   u_time;
uniform vec3    u_cameraPosition;

uniform float   u_iter;
uniform float   u_layers;
uniform float   u_obj;

varying vec4    v_position;
varying vec4    v_color;
varying vec4    v_normal;

varying float   v_index;

uniform struct Light
{
    vec3    position;
    vec3    color;
    float   ambientCoefficient;
    float   diffuseCoefficient;
    float   attenuationCoefficient;
    float   materialShininess;
    vec3    materialSpecularColor;
};

vec3 light(Light l)
{
    vec3 surfaceToLight = normalize(l.position - v_position.xyz);
    vec3 surfaceToCamera = normalize(u_cameraPosition - v_position.xyz);

    // Ambient
    vec3 ambient =  l.ambientCoefficient * l.color * v_color.rgb;


    // Diffuse
    vec3 diffuse = l.diffuseCoefficient * l.color * v_color.rgb;


    // Specular
    float specularCoefficient = 0.0;

    if(l.diffuseCoefficient > 0.0)
    {
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, v_normal.xyz))), l.materialShininess);
    }

    vec3 specular = specularCoefficient * l.materialSpecularColor * l.color;


    // Attenuation
    float attenuation = 1.0 / (1.0 + l.attenuationCoefficient * pow(distance(v_position.xyz, l.position), 2.0));


    // Color
    vec3 linearColor = ambient + attenuation*(diffuse + specular);


    // Gamma Correction
    vec3 gamma = vec3(1.0/1.2);

    return pow(linearColor, gamma);
}

///////////////////////////////////////////////////////////////
int NUM_OCTAVES = 4;

float rand(vec2 n) {
    return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

/*float noise(vec2 p){
    vec2 ip = floor(p);
    vec2 u = fract(p);
    u = u*u*(3.0-2.0*u);

    float res = mix(
                mix(rand(ip),rand(ip+vec2(1.0,0.0)),u.x),
                mix(rand(ip+vec2(0.0,1.0)),rand(ip+vec2(1.0,1.0)),u.x),u.y);
    return res*res;
}
*/

float noise( in vec2 x )
{
    return sin(1.5*x.x)*sin(1.5*x.y);
}

float rand(float n){return fract(sin(n) * 43758.5453123);}

float noise(float p){
    float fl = floor(p);
    float fc = fract(p);
    return mix(rand(fl), rand(fl + 1.0), fc);
}

float mod289(float x){return x - floor(x * (1.0 / 289.0)) * 289.0;}
vec4 mod289(vec4 x){return x - floor(x * (1.0 / 289.0)) * 289.0;}
vec4 perm(vec4 x){return mod289(((x * 34.0) + 1.0) * x);}

float noise(vec3 p){
    vec3 a = floor(p);
    vec3 d = p - a;
    d = d * d * (3.0 - 2.0 * d);

    vec4 b = a.xxyy + vec4(0.0, 1.0, 0.0, 1.0);
    vec4 k1 = perm(b.xyxy);
    vec4 k2 = perm(k1.xyxy + b.zzww);

    vec4 c = k2 + a.zzzz;
    vec4 k3 = perm(c);
    vec4 k4 = perm(c + 1.0);

    vec4 o1 = fract(k3 * (1.0 / 41.0));
    vec4 o2 = fract(k4 * (1.0 / 41.0));

    vec4 o3 = o2 * d.z + o1 * (1.0 - d.z);
    vec2 o4 = o3.yw * d.x + o3.xz * (1.0 - d.x);

    return o4.y * d.y + o4.x * (1.0 - d.y);
}


float fbm(float x) {
    float v = 0.0;
    float a = 0.5;
    float shift = float(100);
    for (int i = 0; i < NUM_OCTAVES; ++i) {
        v += a * noise(x);
        x = x * 2.0 + shift;
        a *= 0.5;
    }
    return v;
}


float fbm(vec2 x) {
    float v = 0.0;
    float a = 0.5;
    vec2 shift = vec2(100);
    // Rotate to reduce axial bias
    mat2 rot = mat2(cos(0.5), sin(0.5), -sin(0.5), cos(0.50));
    for (int i = 0; i < NUM_OCTAVES; ++i) {
        v += a * noise(x);
        x = rot * x * 2.0 + shift;
        a *= 0.5;
    }
    return v;
}


float fbm(vec3 x) {
    float v = 0.0;
    float a = 0.5;
    vec3 shift = vec3(100);
    for (int i = 0; i < NUM_OCTAVES; ++i) {
        v += a * noise(x);
        x = x * 2.0 + shift;
        a *= 0.5;
    }
    return v;
}

const mat2 mtx = mat2( 0.80,  0.60, -0.60,  0.80 );

float fbm4( vec2 p )
{
    float f = 0.0;

    f += 0.5000*(-1.0+2.0*noise( p )); p = mtx*p*2.02;
    f += 0.2500*(-1.0+2.0*noise( p )); p = mtx*p*2.03;
    f += 0.1250*(-1.0+2.0*noise( p )); p = mtx*p*2.01;
    f += 0.0625*(-1.0+2.0*noise( p ));

    return f/0.9375;
}

float fbm6( vec2 p )
{
    float f = 0.0;

    f += 0.500000*noise( p ); p = mtx*p*2.02;
    f += 0.250000*noise( p ); p = mtx*p*2.03;
    f += 0.125000*noise( p ); p = mtx*p*2.01;
    f += 0.062500*noise( p ); p = mtx*p*2.04;
    f += 0.031250*noise( p ); p = mtx*p*2.01;
    f += 0.015625*noise( p );

    return f/0.96875;
}

void main()
{
    normalize(v_normal);

    Light l;
    l.color = vec3(1.0, 1.0, 1.0);
    l.position = vec3(1.0, 1.0, 10.0);
    l.ambientCoefficient = 0.5;
    l.diffuseCoefficient = max(0.0, dot(v_normal.xyz, normalize(l.position - v_position.xyz)));
    l.attenuationCoefficient = 0.01;
    l.materialShininess = 0.0;
    l.materialSpecularColor = vec3(1.0,1.0,1.0);

    gl_FragColor = vec4(light(l), v_color.a);
}

