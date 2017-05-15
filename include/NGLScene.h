#ifndef NGLSCENE_H
#define NGLSCENE_H

// Includes for NGL
#include <ngl/NGLInit.h>
#include <ngl/Vec3.h>
#include <ngl/Obj.h>

// Includes for GLM
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#include <QOpenGLWidget>

#include "fork.h"

class NGLScene : public QOpenGLWidget
{
  Q_OBJECT
public :
  NGLScene(QWidget * _parent);
  void initializeGL() override;
  void paintGL() override;
public slots :

  void setXTrnSlider(int _v);
  void setYTrnSlider(int _v);
  void setZTrnSlider(int _v);

  void setXRot(int _v);
  void setYRot(int _v);
  void setZRot(int _v);

  void setLightX(int _v);
  void setLightY(int _v);
  void setLightZ(int _v);

  void setRough(int _v);
  void setShine(int _v);

  void setZoom(int _v);

  void swapSpin();

  void setColour();

private :
  ngl::Vec3 m_Trn;
  ngl::Vec3 m_Rot;
  ngl::Vec3 m_Col = {0.9, 0.9, 0.9};
  ngl::Vec3 m_LightPos = {5, 5, 5};

  bool m_turnatable;
  float m_deltaTime;

  float m_roughness  = 0.5f;
  float m_shineyness = 0.5f;

  std::unique_ptr<forkObj> m_Fork;

  std::unique_ptr<ngl::Obj> m_mesh;
  float m_Zoom;


};

#endif
