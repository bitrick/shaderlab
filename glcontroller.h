#ifndef GLCONTROLLER_H
#define GLCONTROLLER_H

#include <time.h>
#include <QOpenGLFunctions_3_3_Core>


class GLController: public QOpenGLFunctions_3_3_Core
{
public:
    GLController();

    ~GLController();

    void m_InitGL();

    void m_Update();

    void m_SetElapsed(clock_t elapsed);

    void m_SetViewport(int width, int height);

    void m_CreateProgram(const QString& vs, const QString& fs);

    GLint CreateProgram(const QString& vs, const QString& fs);

    GLint CreateVertexArray();

    GLint CreateBuffer();

    void DestroyProgram(GLuint program);

    void DestroyVertexArray(GLuint vertex_array);

    void DestroyBuffer(GLuint buffer);

private:
    void _m_UploadUniformData();

    void _m_QueryUniformDataLocation();

private:
    clock_t _m_Elapsed;
    GLint _m_ElapsedLoc;

    int _m_Width;
    GLint _m_WidthLoc;

    int _m_Height;
    GLint _m_HeightLoc;

    GLint _m_Program;

    GLint _m_VertexArray;

    GLint _m_Buffer;
};

#endif // GLCONTROLLER_H
