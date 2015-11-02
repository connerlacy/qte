vec3 gradient(float position)
{
    //Color: vec4(r, g, b, location)
    vec4 color0 = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 color1 = vec4(0.01, 0.34, 0.71, 0.2);
    vec4 color2 = vec4(0.95, 0.15, 0.15, 0.69);
    vec4 color3 = vec4(0.95, 1.0, 0.15, 1.0);

    vec3 color = color0.xyz;

    color = mix(color.xyz, color1.xyz, smoothstep(color0.w, color1.w, position));
    color = mix(color.xyz, color2.xyz, smoothstep(color1.w, color2.w, position));
    color = mix(color.xyz, color3.xyz, smoothstep(color2.w, color3.w, position));

    return color;
}

float rand(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}
