#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4   mvp_matrix; // Model-view-projection matrix

attribute vec4 position;
attribute vec2 texcoord;

varying vec2   v_texcoord;

void main()
{
    gl_PointSize = 5.0;

    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * position;

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = texcoord;
}
