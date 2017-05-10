#include "fork.h"

forkObj::forkObj()
{

}
void forkObj::init()
{
  m_shader = ngl::ShaderLib::instance();
  m_shader->loadShader("ForkProgram","shaders/forkVert.glsl","shaders/forkFrag.glsl");
}
void forkObj::setTransform(ngl::Transformation *_TX, ngl::Mat4 _projection, ngl::Mat4 _view)
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
}
const ngl::Transformation forkObj::getTransform() const noexcept
{
  //return m_TX;
}

void forkObj::draw()
{
  ngl::ShaderLib *m_shader = ngl::ShaderLib::instance();
  (*m_shader)["ForkProgram"]->use();
//#define TEAPOT
#ifdef TEAPOT
  ngl::VAOPrimitives* prim = ngl::VAOPrimitives::instance();
  prim->draw( "teapot" );
#else
  std::unique_ptr<ngl::Obj> mesh(new ngl::Obj("fork.obj"));
  mesh->createVAO();
  mesh->draw();
#endif
}
