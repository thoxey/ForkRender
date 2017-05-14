#include "NGLScene.h"
#include <ngl/Mat4.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Util.h>
#include <ngl/ShaderLib.h>
#include <ngl/NGLInit.h>
#include <ngl/Transformation.h>

#include <chrono>

#include "fork.h"

NGLScene::NGLScene(QWidget * _parent) : QOpenGLWidget(_parent), m_turnatable(false), m_Zoom(4.0f)
{

}
void NGLScene::initializeGL()
{
  ngl::NGLInit::instance();
  glClearColor(0.9f,0.9f,0.9f,1.0f);

  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  shader->use("ForkProgram");

  myFork.init();

  glEnable(GL_DEPTH_TEST);

}
void NGLScene::paintGL()
{
  std::chrono::high_resolution_clock timer;
  auto start = timer.now();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Our MVP matrices
  ngl::Mat4 projection,view;

  view = ngl::lookAt(ngl::Vec3(m_Zoom,m_Zoom,m_Zoom),ngl::Vec3::zero(), ngl::Vec3::up());
  projection = ngl::perspective(60.0f, 1.0, 0.1,100);

  //Spin
  if(m_turnatable)
    m_Rot.m_y += (m_deltaTime/10.0f);

  ngl::Transformation tx;

  tx.setRotation(m_Rot);
  tx.setPosition(m_Trn);

  myFork.setTransform(&tx, projection, view);
  myFork.draw();

//   ngl::ShaderLib *sceneshader = ngl::ShaderLib::instance();
//  (*sceneshader)["EnvProgram"]->use();
//  std::unique_ptr<ngl::Obj> mesh(new ngl::Obj("Box.obj"));
//  mesh->createVAO();
//  mesh->draw();

  auto stop = timer.now();
  m_deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() / 1000.0f;

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
  m_Zoom = change/2;
  update();
}

void NGLScene::swapSpin()
{
  m_turnatable = !m_turnatable;
}


