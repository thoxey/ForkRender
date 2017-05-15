#include "fork.h"

forkObj::forkObj()
{
  m_mesh.reset(new ngl::Obj("fork.obj"));
  m_mesh->createVAO();
  initEnvironment();
  m_shader = ngl::ShaderLib::instance();
  m_shader->loadShader("ForkProgram","shaders/forkVert.glsl","shaders/forkFrag.glsl");
}
void forkObj::setTransform(ngl::Transformation *_TX, ngl::Mat4 _projection, ngl::Mat4 _view,
                           ngl::Vec3 col, ngl::Vec3 lightPos, float rough, float shine)
{
  m_TX = _TX;


  ngl::Mat4 MV = ngl::Mat4(1.0f);
  ngl::Mat4 MVP;
  ngl::Mat3 N;

  MV = _TX->getMatrix()*_view;
  MVP = MV * _projection;

  N = MV.transpose();
  N = N.inverse();

  m_shader->setRegisteredUniform("MVP", MVP);
  m_shader->setRegisteredUniform("MV", MV);
  m_shader->setRegisteredUniform("N", N);
  m_shader->setRegisteredUniform("invV", _view.inverse());
  m_shader->setRegisteredUniform("lightCol", col);
  m_shader->setRegisteredUniform("lightPos", lightPos);
  m_shader->setRegisteredUniform("roughness", rough);
  m_shader->setRegisteredUniform("shineyness", shine);
}

void forkObj::draw()
{
  ngl::ShaderLib *m_shader = ngl::ShaderLib::instance();
  (*m_shader)["ForkProgram"]->use();

  m_mesh->draw();
}

//Env map management, taken from Env Map Workshop and adapted
//Author: Richard Southern
//Accesed: 30/03/17
/**
 * @brief Scene::initEnvironmentSide
 * @param texture
 * @param target
 * @param filename
 * This function should only be called when we have the environment texture bound already
 * copy image data into 'target' side of cube map
 */
void forkObj::initEnvironmentSide(GLenum target, const char *filename) {
  // Load up the image using NGL routine
  ngl::Image img(filename);

  // Transfer image data onto the GPU using the teximage2D call
  glTexImage2D (
        target,           // The target (in this case, which side of the cube)
        0,                // Level of mipmap to load
        img.format(),     // Internal format (number of colour components)
        img.width(),      // Width in pixels
        img.height(),     // Height in pixels
        0,                // Border
        GL_RGBA,          // Format of the pixel data
        GL_UNSIGNED_BYTE, // Data type of pixel data
        img.getPixels()   // Pointer to image data in memory
        );
}
void forkObj::initTexture(const GLuint& texUnit, GLuint &texId, const char *filename)
{
  // Set our active texture unit
  glActiveTexture(GL_TEXTURE0 + texUnit);

  // Load up the image using NGL routine
  ngl::Image img(filename);

  // Create storage for our new texture
  glGenTextures(1, &texId);

  // Bind the current texture
  glBindTexture(GL_TEXTURE_2D, texId);

  // Transfer image data onto the GPU using the teximage2D call
  glTexImage2D (
        GL_TEXTURE_2D,    // The target (in this case, which side of the cube)
        0,                // Level of mipmap to load
        img.format(),     // Internal format (number of colour components)
        img.width(),      // Width in pixels
        img.height(),     // Height in pixels
        0,                // Border
        GL_RGB,           // Format of the pixel data
        GL_UNSIGNED_BYTE, // Data type of pixel data
        img.getPixels()); // Pointer to image data in memory

  // Set up parameters for our texture
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
/**
 * @brief Scene::initEnvironment in texture unit 0
 */
void forkObj::initEnvironment()
{
  // Enable seamless cube mapping
  glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

  // Placing our environment map texture in texture unit 0
  glActiveTexture (GL_TEXTURE0);

  // Generate storage and a reference for our environment map texture
  glGenTextures (1, &m_envTex);

  // Bind this texture to the active texture unit
  glBindTexture(GL_TEXTURE_CUBE_MAP, m_envTex);

  // Now load up the sides of the cube
  initEnvironmentSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, "images/sky_zneg.png");
  initEnvironmentSide(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, "images/sky_zpos.png");
  initEnvironmentSide(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, "images/sky_ypos.png");
  initEnvironmentSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, "images/sky_yneg.png");
  initEnvironmentSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, "images/sky_xneg.png");
  initEnvironmentSide(GL_TEXTURE_CUBE_MAP_POSITIVE_X, "images/sky_xpos.png");

  // Generate mipmap levels
  glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

  // Set the texture parameters for the cube map
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, GL_TRUE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  GLfloat anisotropy;
  glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropy);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);

  // Set our cube map texture to on the shader so we can use it
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  shader->use("ForkProgram");
  shader->setUniform("envMap", 0);
}
