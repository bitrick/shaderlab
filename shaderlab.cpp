#include <QFile>
#include <QString>
#include "shaderlab.h"
#include <QDebug>

ShaderLab::ShaderLab():
    _m_Width(640),
    _m_Height(480),
    _m_StartTime(),
    _m_LastTime(),
    _m_Active(0),
    _m_Timer(this),
    _m_GLController(),
    _m_Context(),
    _m_Format(),
    _m_Window()
{
    m_InitWindow();
    m_InitGLController();
}

ShaderLab::~ShaderLab()
{}

void ShaderLab::m_Start()
{
    _m_Window.show();
    connect(&_m_Timer, SIGNAL(timeout()), this, SLOT(m_Update()));
    _m_Active = 1;

    // 60fps
    _m_Timer.start(17);
    gettimeofday(&_m_StartTime, NULL);
}

void ShaderLab::m_Pause()
{
    _m_Active = 0;
}

void ShaderLab::m_Stop()
{
    _m_Timer.stop();
    disconnect(&_m_Timer, SIGNAL(timeout()), this, SLOT(m_Update()));
    _m_Active = 0;
}

long ShaderLab::m_Elapsed()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return _TimeDelta(now, _m_StartTime);
}

long ShaderLab::m_TimeGap()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return _TimeDelta(now, _m_LastTime);
}

void ShaderLab::m_SetWidth(int width)
{
    _m_Width = width;
    _m_Window.setWidth(width);
    _m_GLController.m_SetViewport(width, _m_Height);
}

void ShaderLab::m_SetHeight(int height)
{
    _m_Height = height;
    _m_Window.setHeight(height);
    _m_GLController.m_SetViewport(_m_Width, height);
}

void ShaderLab::m_Update()
{
    if (_m_Active) {
        _m_Context.makeCurrent(&_m_Window);

        _m_GLController.m_SetElapsed(m_Elapsed());
        _m_GLController.m_Update();

        _m_Context.swapBuffers(&_m_Window);
        gettimeofday(&_m_LastTime, NULL);
    }
}

void ShaderLab::m_InitWindow()
{
    _m_Format.setRenderableType(QSurfaceFormat::OpenGL);
    _m_Format.setVersion(3, 3);
    _m_Format.setProfile(QSurfaceFormat::CoreProfile);

    _m_Window.resize(_m_Width, _m_Height);
    _m_Window.setSurfaceType(QWindow::OpenGLSurface);
    _m_Window.setFormat(_m_Format);
    _m_Window.create();

    _m_Context.setFormat(_m_Format);
    _m_Context.create();

    connect(&_m_Window, SIGNAL(destroyed()), this, SLOT(m_Shutdown()));
}

void ShaderLab::m_InitGLController()
{
    _m_Context.makeCurrent(&_m_Window);
    _m_GLController.m_InitGL();
    _m_GLController.m_SetViewport(_m_Width, _m_Height);
}

void ShaderLab::m_SetFSCode(const QString &code)
{
    static QString vs = "#version 330 core\n"
                        "layout(location = 0) in vec3 vertex;"
                        "out vec3 position;"
                        "void main() {"
                            "gl_Position.xyz = vertex;"
                            "gl_Position.w = 1.0;"
                            "position = vertex;"
                        "}";
    _m_GLController.m_CreateProgram(vs, code);
}

void ShaderLab::m_LoadFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString fs;
    while (!file.atEnd()) {
        fs.append(file.readLine());
    }

    m_SetFSCode(fs);
}

void ShaderLab::m_Shutdown()
{
    exit(0);
}

long ShaderLab::_TimeDelta(timeval &t1, timeval &t2)
{
    return (t1.tv_sec - t2.tv_sec) * 1000 + (t1.tv_usec - t2.tv_usec) / 1000;
}



