uniform mat4    u_mvp_matrix;
uniform float   u_time;

varying vec4    v_position;
varying vec4    v_color;

void main()
{
    //gl_FragColor = vec4(1,1,1,1);
    gl_FragColor = v_color;
}
