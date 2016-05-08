#ifndef GLWINDOW_H
#define GLWINDOW_H

#include "typedefs.h"
#include <QWindow>
#include <QOpenGLFunctions_3_3_Core>

class GLWIndow: public QWindow,
                public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
protected:
    void destroy();
private:
    // 不允许复制
    GLWindow(const GLWindow&);
public:
    GLWIndow(GLRenderer* gl_renderer);
    ~GLWindow();

    void obsolete();

    void setRenderer(GLRenderer* gl_renderer);
    const GLRenderer* getRenderer();

    void render();
    void swap_buffers();

private:
    QOpenGLContext *gl_context;
    GLRenderer *gl_renderer;
};

#endif // GLWINDOW_H
