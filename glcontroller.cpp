#include <stdio.h>
#include <QDebug>
#include "glcontroller.h"


GLController::GLController():
    _m_Elapsed(0.0),
    _m_Width(0),
    _m_Height(0),
    _m_Program(0),
    _m_VertexArray(0),
    _m_Buffer(0)
{}

GLController::~GLController()
{
    glDisableVertexAttribArray(0);
    DestroyBuffer(_m_Buffer);
    DestroyVertexArray(_m_VertexArray);
    DestroyProgram(_m_Program);
}

void GLController::m_InitGL()
{
    initializeOpenGLFunctions();

    static const GLfloat vertex_data[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
    };

    _m_VertexArray = CreateVertexArray();
    glBindVertexArray(_m_VertexArray);

    _m_Buffer = CreateBuffer();
    glBindBuffer(GL_ARRAY_BUFFER, _m_Buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
    glUseProgram(_m_Program);
}

void GLController::m_CreateProgram(const QString &vs, const QString &fs)
{
    if (_m_Program) {
        DestroyProgram(_m_Program);
    }

    _m_Program = CreateProgram(vs, fs);
    glUseProgram(_m_Program);
    _m_QueryUniformDataLocation();
}

void GLController::m_Update()
{
    _m_UploadUniformData();

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

GLint GLController::CreateVertexArray()
{
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);

    return vao;
}

GLint GLController::CreateBuffer()
{
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);

    return vbo;
}

GLint GLController::CreateProgram(const QString &vs, const QString &fs)
{
    GLuint  vs_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint  fs_id = glCreateShader(GL_FRAGMENT_SHADER);

    QByteArray vs_ba = vs.toUtf8();
    GLint vs_size = vs_ba.size();
    const char* vs_byte = vs_ba.constData();
    glShaderSource(vs_id, 1, &vs_byte, &vs_size);
    glCompileShader(vs_id);

    GLint is_compiled = 0;
    glGetShaderiv(vs_id, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled == GL_FALSE) {
        GLint max_length = 0;
        glGetShaderiv(vs_id, GL_INFO_LOG_LENGTH, &max_length);
        char info[max_length];
        glGetShaderInfoLog(vs_id, max_length, &max_length, info);
        qDebug() << info;
    }

    QByteArray fs_ba = fs.toUtf8();
    GLint fs_size = fs_ba.size();
    const char* fs_byte = fs_ba.constData();
    glShaderSource(fs_id, 1, &fs_byte, &fs_size);
    glCompileShader(fs_id);

    glGetShaderiv(fs_id, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled == GL_FALSE) {
        GLint max_length = 0;
        glGetShaderiv(fs_id, GL_INFO_LOG_LENGTH, &max_length);
        char info[max_length];
        glGetShaderInfoLog(fs_id, max_length, &max_length, info);
        qDebug() << info;
    }

    GLint program = glCreateProgram();
    glAttachShader(program, vs_id);
    glAttachShader(program, fs_id);
    glLinkProgram(program);
    glDeleteShader(vs_id);
    glDeleteShader(fs_id);

    return program;
}

void GLController::DestroyVertexArray(GLuint vertex_array)
{
    glDeleteVertexArrays(1, &vertex_array);
}

void GLController::DestroyBuffer(GLuint buffer)
{
    glDeleteBuffers(1, &buffer);
}

void GLController::DestroyProgram(GLuint program)
{
    glDeleteProgram(program);
}

void GLController::_m_UploadUniformData()
{
    glUniform1i(_m_ElapsedLoc, _m_Elapsed);
    glUniform1i(_m_WidthLoc, _m_Width);
    glUniform1i(_m_HeightLoc, _m_Height);

//    qDebug() << "eloc" << _m_ElapsedLoc << "elapsed" << _m_Elapsed
//             << "wloc" << _m_WidthLoc << "width" << _m_Width
//             << "hloc" << _m_HeightLoc << "height" << _m_Height;
}

void GLController::_m_QueryUniformDataLocation()
{
    _m_WidthLoc = glGetUniformLocation(_m_Program, "width");
    _m_HeightLoc = glGetUniformLocation(_m_Program, "height");
    _m_ElapsedLoc = glGetUniformLocation(_m_Program, "elapsed");
}

void GLController::m_SetViewport(int width, int height)
{
    _m_Width = width;
    _m_Height = height;

    glViewport(0, 0, _m_Width, _m_Height);
}

void GLController::m_SetElapsed(clock_t elapsed)
{
    _m_Elapsed = elapsed;
}




