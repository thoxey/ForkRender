#ifndef NGLSCENE_H
#define NGLSCENE_H

#include <ngl/NGLInit.h>
#include <ngl/Vec3.h>
#include <ngl/Obj.h>

#include <QOpenGLWidget>

class NGLScene : public QOpenGLWidget
{
  Q_OBJECT
public :
  NGLScene(QWidget * _parent);
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int _w, int _h) override;
public slots :

  void setXTrnSlider(int _v);
  void setYTrnSlider(int _v);
  void setZTrnSlider(int _v);

  void setXRot(int _v);
  void setYRot(int _v);
  void setZRot(int _v);

  void setZoom(int _v);

  void setColour();

  void swapSpin();

private :
  ngl::Vec3 m_Trn;
  ngl::Vec3 m_Rot;
  ngl::Vec3 m_Col = {0.2, 0.4, 0.8};

  bool m_turnatable;
  float m_deltaTime;

  std::unique_ptr<ngl::Obj> m_mesh;
  float m_Zoom = 1.0f;

};

#endif
