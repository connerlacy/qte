
uniform mat4    u_mvp_matrix;
uniform float   u_time;
uniform vec3    u_cameraPosition;

varying vec4    v_position;
varying vec4    v_color;
varying vec4    v_normal;

varying float   v_index;
varying float   v_noise;

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
/////////////////////////////////////

float func( vec2 q, out vec2 o, out vec2 n )
{
    float ql = length( q );
    q.x += 0.05*sin(0.11*u_time+ql*4.0);
    q.y += 0.05*sin(0.13*u_time+ql*4.0);
    q *= 0.7 + 0.2*cos(0.05*u_time);

    q = (q+1.0)*0.5;

    o.x = 0.5 + 0.5*fbm4( vec2(2.0*q*vec2(1.0,1.0)          )  );
    o.y = 0.5 + 0.5*fbm4( vec2(2.0*q*vec2(1.0,1.0)+vec2(5.2))  );

    float ol = length( o );
    o.x += 0.02*sin(0.11*u_time*ol)/ol;
    o.y += 0.02*sin(0.13*u_time*ol)/ol;


    n.x = fbm6( vec2(4.0*o*vec2(1.0,1.0)+vec2(9.2))  );
    n.y = fbm6( vec2(4.0*o*vec2(1.0,1.0)+vec2(5.7))  );

    vec2 p = 4.0*q + 4.0*n;

    float f = 0.5 + 0.5*fbm4( p );

    f = mix( f, f*f*f*3.5, f*abs(n.x) );

    float g = 0.5+0.5*sin(4.0*p.x)*sin(4.0*p.y);
    f *= 1.0-0.5*pow( g, 8.0 );

    return f;
}



vec3 doMagic(vec2 p)
{
    vec2 q = p*0.3;

    vec4 on = vec4(0.0);
    float f = func(q, on.xy, on.zw);

    vec3 col = vec3(0.0);
    col = mix( vec3(0.9,0.1,0.4), vec3(0.3,0.05,0.05), f );
    col = mix( col, vec3(0.9,0.9,0.9), dot(on.zw,on.zw) );
    col = mix( col, vec3(0.4,0.3,0.3), 0.5*on.y*on.y );
    col = mix( col, vec3(0.0,0.2,0.4), 0.5*smoothstep(1.2,1.3,abs(on.z)+abs(on.w)) );
    col = clamp( col*f*2.0, 0.0, 1.0 );


    return 1.1*col*col;
}

float pattern(in vec3 p, in float c, out vec3 q, out vec3 r)
{
    q = vec3( fbm( p + vec3(0.4,0.05,0.2) ),
              fbm( p + vec3(5.2,1.3, 2.8) ),
              fbm( p + vec3(1.5, 5.4,2.0)) );

    r = vec3( fbm( p + c*q + vec3(1.7,9.2, 3.4) ),
              fbm( p + c*q + vec3(8.3,2.8, 9.9) ),
              fbm( p + c*q + vec3(3.3,1.8,0.3)));

    return fbm( p + c*r );
}

vec3 makeColor(vec3 p, vec3 q, vec3 r)
{
    vec3 col = vec3(0.0);


    //r.g *= 0.1;
    //q = smoothstep(q, vec3(0.8), vec3(0.9));
    //q.rg *= 0.5;

    //col = smoothstep(mix(q, r, p), p, r);
    col = mix(q,r,p);


    return col;
}


void main()
{
    normalize(v_normal);

    Light l;
    l.color = vec3(1.0,1.0,1.0);
    l.position = vec3(0, 0, 1.0);
    l.ambientCoefficient = 0.1;
    l.diffuseCoefficient = max(0.0, dot(v_normal.xyz, normalize(l.position - v_position.xyz)));
    l.attenuationCoefficient = 0.0;
    l.materialShininess = 100.0;
    l.materialSpecularColor = vec3(0.0,0.0,0.0);

    vec3 q = vec3(0.0);
    vec3 r = vec3(0.0);
    vec3 p = vec3(pattern(vec3(v_position.xy, u_time), 2.0, q, r));

    vec3 col = makeColor(p, q, r);

    gl_FragColor = vec4(1,1,1, 0.05);
}

