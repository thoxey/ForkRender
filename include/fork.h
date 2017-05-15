#ifndef FORK_H
#define FORK_H
#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>
#include <ngl/Mat4.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Util.h>
#include <ngl/Obj.h>

class forkObj
{
public:
    forkObj();
    void setTransform(ngl::Transformation *_TX, ngl::Mat4 _projection, ngl::Mat4 _view, ngl::Vec3 col, ngl::Vec3 lightPos, float rough, float shine);
    void draw();
private:

    std::unique_ptr<ngl::Obj> m_mesh;

    ngl::ShaderLib *m_shader;
    ngl::Transformation *m_TX;
    //Env map management, taken from Env Map Workshop and adapted
    //Author: Richard Southern
    //Accesed: 30/03/17
    /// The ID of our environment texture
    GLuint m_envTex, m_glossMapTex;

    /// Initialise the entire environment map
    void initEnvironment();

    /// Utility function for loading up a 2D texture
    void initTexture(const GLuint&, GLuint &, const char *);

    /// Initialise a single side of the environment map
    void initEnvironmentSide(GLenum /*target*/, const char* /*filename*/);
};

#endif // FORK_H
