uniform mat4    u_mvp_matrix;
uniform float   u_time;
uniform vec3    u_cameraPosition;

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
    //float   intensity;
};

vec3 light(Light l)
{
    vec3 surfaceToLight = normalize(l.position - v_position.xyz);
    vec3 surfaceToCamera = normalize(u_cameraPosition - v_position.xyz);

    //l.intensity = dot(surfaceToLight, v_normal);

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
    vec3 linearColor = ambient + attenuation*(diffuse);// + specular);


    // Gamma Correction
    vec3 gamma = vec3(1.0/1.2);

    return pow(linearColor, gamma);
}


void main()
{
    normalize(v_normal);

    Light l;
    l.color = vec3(1.0,1.0,1.0);
    l.position = vec3(0, sin(u_time/1.0)*25.0, 20.0);
    l.ambientCoefficient = 0.95;
    l.diffuseCoefficient = max(0.0, dot(v_normal.xyz, normalize(l.position - v_position.xyz)));
    l.attenuationCoefficient = 0.001;
    l.materialShininess = 10.05;

    l.materialSpecularColor = vec3(1.0,1.0,1.0);

    gl_FragColor = vec4(light(l)*1.0, v_color.a);

    //gl_FragColor = v_color;
}

