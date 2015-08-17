uniform mat4    u_mvp_matrix;
uniform float   u_time;

attribute vec4  a_position;
attribute vec4  a_color;

varying vec4    v_position;
varying vec4    v_color;

void main(void)
{
    v_position = a_position;
    v_color = a_color;

    v_position.z = sin( distance(vec2(0,0), v_position.xy)*0.5 + u_time/1000.0);
    gl_Position = u_mvp_matrix * v_position;
}
