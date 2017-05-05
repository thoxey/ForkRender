#include "NGLScene.h"
#include <ngl/Mat4.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Util.h>
#include <ngl/ShaderLib.h>
#include <ngl/NGLInit.h>
#include <ngl/Transformation.h>

#include <chrono>

#include <QColorDialog>

NGLScene::NGLScene(QWidget * _parent) : QOpenGLWidget(_parent), m_turnatable(false)
{

}
void NGLScene::initializeGL()
{
  ngl::NGLInit::instance();
  glClearColor(0.8f,0.8f,0.8f,1.0f);
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  shader->use(ngl::nglColourShader);
  shader->setUniform("Colour",m_Col.m_x,m_Col.m_y,m_Col.m_z, 1.0f);
}
void NGLScene::paintGL()
{
  std::chrono::high_resolution_clock timer;
  auto start = timer.now();


  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  ngl::Mat4 projection,view;

  shader->setRegisteredUniform("Colour",m_Col.m_x,m_Col.m_y,m_Col.m_z, 1.0f);

  view = ngl::lookAt(ngl::Vec3(m_Zoom,m_Zoom,m_Zoom),ngl::Vec3::zero(), ngl::Vec3::up());
  projection = ngl::perspective(45.0f, 1.0, 0.1,100);

  ngl::Transformation tx;

  //Spin
  std::cerr<<m_turnatable<<"\n";
  if(m_turnatable)
    m_Rot.m_y = m_Rot.m_y + (m_deltaTime/2.0f);


  tx.setRotation(m_Rot);
  tx.setPosition(m_Trn);

  shader->setRegisteredUniform("MVP", tx.getMatrix()*view*projection);

  ngl::VAOPrimitives* prim = ngl::VAOPrimitives::instance();
   prim->draw( "teapot" );


  auto stop = timer.now();
  m_deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000.0f;;

  update();
}
void NGLScene::resizeGL(int _w, int _h)
{

}
void NGLScene::setXRot(int _v)
{
  m_Rot.m_x = _v;
  update();
}
void NGLScene::setYRot(int _v)
{
  m_Rot.m_y = _v;
  update();
}
void NGLScene::setZRot(int _v)
{
  m_Rot.m_z = _v;
  update();
}

void NGLScene::setXTrnSlider(int _v)
{
  double change = _v;
  m_Trn.m_x = change/10;
  update();
}
void NGLScene::setYTrnSlider(int _v)
{
  double change = _v;
  m_Trn.m_y = change/10;
  update();
}
void NGLScene::setZTrnSlider(int _v)
{
  double change = _v;
  m_Trn.m_z = change/10;
  update();
}

void NGLScene::setZoom(int _v)
{
  float change = _v;
  m_Zoom = change;
  update();
}

void NGLScene::setColour()
{
  QColor colour = QColorDialog::getColor();
  if(colour.isValid())
    {
      m_Col.m_x = colour.redF();
      m_Col.m_y = colour.greenF();
      m_Col.m_z = colour.blueF();
    }
  update();
}
void NGLScene::swapSpin()
{
  m_turnatable = !m_turnatable;
}
