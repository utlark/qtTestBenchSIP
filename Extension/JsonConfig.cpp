#include "JsonConfig.h"

JsonConfig::JsonConfig ()
{
    QFile file("config.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Couldn't open config.json";
        return;
    }

    QJsonDocument json = QJsonDocument::fromJson(file.readAll());

    if (const QJsonValue v = json["flip"]; v.isBool())
        mFlip = v.toBool();

    if (const QJsonValue v = json["mirror"]; v.isBool())
        mMirror = v.toBool();

    if (const QJsonValue v = json["windowWidth"]; v.isDouble())
        mWindowWidth = v.toInt();

    if (const QJsonValue v = json["windowHeight"]; v.isDouble())
        mWindowHeight = v.toInt();

    if (const QJsonValue v = json["containerWidth"]; v.isDouble())
        mContainerWidth = v.toInt();

    if (const QJsonValue v = json["containerHeight"]; v.isDouble())
        mContainerHeight = v.toInt();

    if (const QJsonValue v = json["containerAlignment"]; v.isString())
        mContainerAlignment = v.toString();

    if (const QJsonValue v = json["sources"]; v.isArray())
        mSources = v.toArray();

    if (const QJsonValue v = json["rows"]; v.isDouble())
        mGridRows = v.toInt();

    if (const QJsonValue v = json["cols"]; v.isDouble())
        mGridCols = v.toInt();
}

bool JsonConfig::getFlip () const
{
    return mFlip;
}

bool JsonConfig::getMirror () const
{
    return mMirror;
}

int JsonConfig::getWindowWidth () const
{
    return mWindowWidth;
}

int JsonConfig::getWindowHeight () const
{
    return mWindowHeight;
}

int JsonConfig::getContainerWidth () const
{
    return mContainerWidth;
}

int JsonConfig::getContainerHeight () const
{
    return mContainerHeight;
}

const QString &JsonConfig::getContainerAlignment () const
{
    return mContainerAlignment;
}

const QJsonArray &JsonConfig::getSources () const
{
    return mSources;
}

int JsonConfig::getGridRows () const
{
    return mGridRows;
}

int JsonConfig::getGridCols () const
{
    return mGridCols;
}
