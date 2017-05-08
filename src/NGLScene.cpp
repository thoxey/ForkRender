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


    ngl::ShaderLib *sceneshader = ngl::ShaderLib::instance();
    sceneshader->use(ngl::nglColourShader);
    sceneshader->setUniform("Colour",0.5,0.5,0.5, 1.0f);
    // Initialise our environment map here
    initEnvironment();

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

    myFork.setTransform(tx, projection, view);
    myFork.draw();


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
    m_Zoom = change/2;
    update();
}

void NGLScene::swapSpin()
{
    m_turnatable = !m_turnatable;
}
void NGLScene::setEnvToggle(bool _v)
{
    m_useEnvTex = _v;
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
void NGLScene::initEnvironmentSide(GLenum target, const char *filename) {
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
void NGLScene::initTexture(const GLuint& texUnit, GLuint &texId, const char *filename)
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
void NGLScene::initEnvironment()
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
    shader->setRegisteredUniform("envMap", 0);
}
