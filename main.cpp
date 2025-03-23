#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>

#include <gst/gst.h>

int main (int argc, char *argv[])
{
    gst_init(&argc, &argv);

    QGuiApplication app(argc, argv);
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    // A crutch to register GstGLQt6VideoItem in qml
    gst_element_factory_make("qml6glsink", nullptr);

    QQmlApplicationEngine engine;
    engine.loadFromModule("qtTestBenchSIP", "Main");

    int ret = QGuiApplication::exec();
    gst_deinit();
    return ret;
}
