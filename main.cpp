#include <QDebug>
#include <QFile>
#include <QGuiApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

QJsonObject loadConfig (const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Couldn't open config.json";
        return QJsonObject();
    }
    QByteArray data = file.readAll();
    file.close();

    return QJsonDocument::fromJson(data).object();
}

int main (int argc, char *argv[])
{
    QGuiApplication       app(argc, argv);
    QQmlApplicationEngine engine;

    QJsonObject config = loadConfig("config.json");

    QStringList sources;
    for (const QJsonValue &value : config["sources"].toArray())
        sources.append(value.toString());


    engine.rootContext()->setContextProperty("windowWidth", config["windowWidth"].toInt(1920));
    engine.rootContext()->setContextProperty("windowHeight", config["windowHeight"].toInt(1080));
    engine.rootContext()->setContextProperty("containerWidth", config["containerWidth"].toInt(1920));
    engine.rootContext()->setContextProperty("containerHeight", config["containerHeight"].toInt(1080));
    engine.rootContext()->setContextProperty("containerAlignment", config["containerAlignment"].toString("center"));
    engine.rootContext()->setContextProperty("flip", config["flip"].toBool(false));
    engine.rootContext()->setContextProperty("mirror", config["mirror"].toBool(false));
    engine.rootContext()->setContextProperty("gridRows", config["rows"].toInt(1));
    engine.rootContext()->setContextProperty("gridCols", config["cols"].toInt(1));
    engine.rootContext()->setContextProperty("videoSources", sources);

    engine.loadFromModule("qtTestBenchSIP", "Main");

    return app.exec();
}
