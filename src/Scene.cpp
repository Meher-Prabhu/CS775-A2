#include "Scene.hpp"

bool
Scene::load(string const & filename, Material const & m, double  & x,double  & y,double  & z)
{
  material = m;
  OBJParser parser;
  bool didParse = parser.parseOBJ(filename, &myMesh);
  if (!didParse)
  {
    cerr << "Since we couldnt parse the OBJ file, we will now quit" << endl;
    exit(1);
  }

  myMesh.calculateBBox();
  x = (myMesh.max[0] + myMesh.min[0])/2;
  y = (myMesh.max[1] + myMesh.min[1])/2;
  z = max(myMesh.max[2],myMesh.min[2])+1500;
  // TODO: Replace these lines with more of your own code to process the loaded scene if necessary.
  // TODO: Hint - texture maps are only on the CPU at this point.
  for(int i = 0; i < myMesh.materials.size(); i++){
    myMesh.materials[i]->textureId = createGLTexture(myMesh.materials[i]->textureImage);
  }
  return didParse;
}

bool
Scene::draw()
{
  SaveGLState save_gl_state;  // will restore state upon destruction

  // Load the shader if it hasn't been loaded yet
  if (!shader.isLoaded())
    if (!shader.load("vert.glsl", "frag.glsl"))
      return false;
  // Use the shader
  shader.enable();
  shader.setUniform("ma", (float)material.getMA()); 
  shader.setUniform("ml", (float)material.getML()); 
  shader.setUniform("ms", (float)material.getMS());
  shader.setUniform("msm", (float)material.getMSM());
  shader.setUniform("msp", (float)material.getMSP());
  shader.setUniform("ambientColor", Vec4(0.9,0.0,0.9,1.0));
  shader.setUniform("lightColor1", Vec4(1.0,0.0,1.0,1.0));
  shader.setUniform("lightColor2", Vec4(0.0,1.0,0.0,1.0));
  shader.setUniform("lightDirection1", Vec4(0.0,0.0,1.0,0.0));    
  shader.setUniform("lightDirection2", Vec4(0.0,0.0,-1.0,0.0));
  for (size_t fid = 0; fid < myMesh.faces.size(); ++fid)
  {
    OBJFace* f = myMesh.faces[fid];
    RGB faceColor = myMesh.materials[f->materialId]->C;
    shader.setUniform("texture", myMesh.materials[f->materialId]->textureId); 
    glBegin(GL_POLYGON);
    glColor3f(faceColor[0],faceColor[1],faceColor[2]);
    for (size_t vi = 0; vi < f->v.size(); ++vi)
    {
      OBJVertexTexCoord const & vertexTextureCoordinate = myMesh.vertexTexCoords[f->vt[vi]];
      glTexCoord2f(vertexTextureCoordinate.coord.x(),1 - vertexTextureCoordinate.coord.y());
      OBJVertex const & vertex = myMesh.vertices[f->v[vi]];
      glVertex3f(vertex.pos[0],vertex.pos[1],vertex.pos[2]);
    }
    glEnd();
  }

  // Don't replace this line!
  return true;
}
