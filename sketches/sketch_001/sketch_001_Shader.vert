uniform mat4    u_mvp_matrix;
uniform float   u_time;
uniform vec3    u_cameraPosition;

attribute vec4  a_position;
attribute vec4  a_normal;
attribute vec4  a_color;
attribute vec2  a_texoord;
attribute float a_index;

varying vec4    v_position;
varying vec4    v_normal;
varying vec4    v_color;

void main(void)
{
    v_position = a_position;
    v_normal = a_normal;
    v_color = a_color;

    gl_Position = u_mvp_matrix * v_position;
}
