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
    void init();
    void setTransform(ngl::Transformation *_TX, ngl::Mat4 _projection, ngl::Mat4 _view);
    const ngl::Transformation getTransform() const noexcept;
    void draw();
private:
    ngl::ShaderLib *m_shader;
    ngl::Transformation *m_TX;
};

#endif // FORK_H
