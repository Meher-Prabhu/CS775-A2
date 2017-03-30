varying vec3 position;
varying vec3 normal;
varying vec3 multipliedNormal;
varying vec3 multipliedlightDirection1;
varying vec3 multipliedlightDirection2;
uniform vec4 lightDirection1;
uniform vec4 lightDirection2;
void main()
{
  gl_Position = ftransform();
  gl_FrontColor = gl_Color;
  gl_BackColor = gl_Color;
  normal = normalize(vec3(gl_Normal));
  multipliedNormal = normalize(gl_NormalMatrix * vec3(gl_Normal));
  position = normalize(vec3(gl_ModelViewMatrix * gl_Vertex));
  multipliedlightDirection1	 = normalize(vec3(gl_ModelViewMatrix * lightDirection1));
  multipliedlightDirection2	 = normalize(vec3(gl_ModelViewMatrix * lightDirection2));
  gl_TexCoord[0] = gl_MultiTexCoord0;
}
