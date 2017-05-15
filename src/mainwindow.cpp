#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_gl = new NGLScene(this);
  ui->s_gridLayout->addWidget(m_gl,0,0,2,1);

  connect(ui->m_x_trn_slider,SIGNAL(valueChanged(int)), m_gl,SLOT(setXTrnSlider(int)));
  connect(ui->m_y_trn_slider,SIGNAL(valueChanged(int)), m_gl,SLOT(setYTrnSlider(int)));
  connect(ui->m_z_trn_slider,SIGNAL(valueChanged(int)), m_gl,SLOT(setZTrnSlider(int)));

  connect(ui->m_x_rotation,SIGNAL(valueChanged(int)), m_gl,SLOT(setXRot(int)));
  connect(ui->m_y_rotation,SIGNAL(valueChanged(int)), m_gl,SLOT(setYRot(int)));
  connect(ui->m_z_rotation,SIGNAL(valueChanged(int)), m_gl,SLOT(setZRot(int)));

  connect(ui->m_Zoom,SIGNAL(valueChanged(int)), m_gl,SLOT(setZoom(int)));

  connect(ui->m_Spin_Button,SIGNAL(clicked(bool)),m_gl,SLOT(swapSpin()));


  connect(ui->m_lightX,SIGNAL(valueChanged(int)),m_gl,SLOT(setLightX(int)));
  connect(ui->m_lightY,SIGNAL(valueChanged(int)),m_gl,SLOT(setLightY(int)));
  connect(ui->m_lightZ,SIGNAL(valueChanged(int)),m_gl,SLOT(setLightZ(int)));

  connect(ui->m_roughSlider,SIGNAL(valueChanged(int)),m_gl,SLOT(setRough(int)));
  connect(ui->m_shineySlider,SIGNAL(valueChanged(int)),m_gl,SLOT(setShine(int)));

  connect(ui->m_colourButton,SIGNAL(clicked(bool)),m_gl,SLOT(setColour()));


}

MainWindow::~MainWindow()
{
  delete ui;
}
