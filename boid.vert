attribute vec3 pos;
varying vec4 f_color;
 
void main()
{
  // Treat the normal (x, y, z) values as (r, g, b) color components.
 
  gl_Position = ftransform();
  f_color = clamp(gl_Color, 0.0, 1.0);
}
