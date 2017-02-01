#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDebug>
#include "shaderlab.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("shaderlab");
    QApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    QCommandLineOption source_option("f", "fragment shader source file", ".");
    parser.addOption(source_option);
    parser.process(app);

    QString src = parser.value(source_option);

    ShaderLab lab;
    lab.m_LoadFile(src);
    lab.m_Start();

    return app.exec();
}
