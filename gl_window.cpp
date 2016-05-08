#include "gl_window.h"

GLWIndow::GLWIndow(GLRenderer *gl_renderer)
    : QWindow(this)
    , gl_renderer(gl_renderer)
    , m_gl_context(0)
{
    this->setSurfaceType(QWindow::OpenGLSurface);
}

GLWindow::~GLWindow()
{
    destroy();
}

GLWindow::destroy()
{
    if (gl_renderer) {
        gl_renderer->obsolete();
        gl_renderer = 0;
    }

    if (gl_context) {
        delete gl_context;
        gl_context = 0;
    }
}

GLWindow::obsolete()
{
    // do nothing
}

GLWindow::setRenderer(GLRenderer* gl_renderer)
{
    if (this->gl_renderer) {
        this->gl_renderer->obsolete();
    }
    this->gl_renderer = gl_renderer;
}

GLWindow::render()
{
    bool need_initialize = false;

    if (!gl_context) {
        gl_context = new QOpenGLContext(this);
        gl_context->setFormat(requestedFormat());
        gl_context->create();
    }

    gl_context->makeCurrent(this);

    if (need_initialize) {
        initializeOpenGLFunctions();
        gl_renderer->initialize();
    }

    gl_renderer->render(this);
}

GLWindow::swap_buffers()
{
    gl_context->swapBuffers();
}
