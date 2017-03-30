uniform sampler2D texture;
uniform float ma;
uniform float ml;
uniform float ms;
uniform float msm;
uniform float msp;
uniform vec4 ambientColor;
uniform vec4 lightColor1;
uniform vec4 lightColor2;
uniform vec4 lightDirection1;
uniform vec4 lightDirection2;
varying vec3 normal;
varying vec3 position;
varying vec3 multipliedNormal;
varying vec3 multipliedlightDirection1;
varying vec3 multipliedlightDirection2;

void main()
{
  vec3 lightNormalized1 = -normalize(vec3(lightDirection1));
  vec3 lightNormalized2 = -normalize(vec3(lightDirection2));

  vec3 reflectedDirection1 = -lightNormalized1 + 2.0 * dot(lightNormalized1,multipliedNormal) * multipliedNormal;
  vec3 reflectedDirection2 = -lightNormalized2 + 2.0 * dot(lightNormalized2,multipliedNormal) * multipliedNormal;

  vec4 ambientPart = ma * gl_Color * ambientColor;

  vec4 lambertianPart = ml * gl_Color * (lightColor1 * max(-dot(multipliedlightDirection1,normal),0.0));
  lambertianPart += ml * gl_Color * (lightColor2 * max(-dot(multipliedlightDirection2,normal),0.0));

  vec4 S = msm * gl_Color + (1.0 - msm) * vec4(1.0,1.0,1.0,1.0);
  vec4 specularPart = ms * S * (lightColor1 * pow(max(-dot(reflectedDirection1,position),0.0),msp));
  specularPart += ms * S * (lightColor2 * pow(max(-dot(reflectedDirection2,position),0.0),msp));

  gl_FragColor = texture2D(texture,gl_TexCoord[0].st) * (ambientPart + lambertianPart + specularPart);
}
