#ifndef SHADERLAB_H
#define SHADERLAB_H

#include <sys/time.h>
#include <QObject>
#include <QWindow>
#include <QTimer>
#include "glcontroller.h"

class QString;
class QOpenGLContext;
class QSurfaceFormat;


class ShaderLab: public QObject
{
    Q_OBJECT
public:
    ShaderLab();

    ~ShaderLab();

    void m_LoadFile(const QString& path);

    void m_SetFSCode(const QString& code);

    void m_Start();

    void m_Pause();

    void m_Stop();

    void m_InitWindow();

    void m_InitGLController();

    void m_SetWidth(int width);

    void m_SetHeight(int height);

    long m_Elapsed();

    long m_TimeGap();

public slots:
    void m_Update();

    void m_Shutdown();

private:
    static long _TimeDelta(struct timeval& t1, struct timeval& t2);

private:
    int _m_Width;

    int _m_Height;

    struct timeval _m_StartTime;

    struct timeval _m_LastTime;

    int _m_Active;

    QTimer _m_Timer;

private:
    GLController _m_GLController;

    QOpenGLContext _m_Context;

    QSurfaceFormat _m_Format;

    QWindow _m_Window;
};

#endif // SHADERLAB_H
