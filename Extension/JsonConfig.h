#pragma once

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

class JsonConfig
{
public:
    explicit JsonConfig ();

    [[nodiscard]] bool getFlip () const;

    [[nodiscard]] bool getMirror () const;

    [[nodiscard]] int getWindowWidth () const;

    [[nodiscard]] int getWindowHeight () const;

    [[nodiscard]] int getContainerWidth () const;

    [[nodiscard]] int getContainerHeight () const;

    [[nodiscard]] const QString &getContainerAlignment () const;

    [[nodiscard]] const QJsonArray &getSources () const;

    [[nodiscard]] int getGridRows () const;

    [[nodiscard]] int getGridCols () const;

private:
    bool       mFlip;
    bool       mMirror;
    int        mWindowWidth;
    int        mWindowHeight;
    int        mContainerWidth;
    int        mContainerHeight;
    QString    mContainerAlignment;
    QJsonArray mSources;
    int        mGridRows;
    int        mGridCols;
};
