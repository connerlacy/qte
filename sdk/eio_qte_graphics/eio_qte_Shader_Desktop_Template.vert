uniform mat4    u_mvp_matrix;
uniform float   u_time;

attribute vec4  a_position;
attribute vec4  a_color;
attribute vec4  a_normal;
attribute vec2  a_texoord;

varying vec4    v_position;
varying vec4    v_color;

void main(void)
{
    v_position = a_position;
    v_color = a_color;

    gl_Position = u_mvp_matrix * v_position;
}
