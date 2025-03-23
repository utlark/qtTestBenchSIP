#pragma once

#include <QDebug>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQuickWindow>

#include <Extension/JsonConfig.h>
#include <Extension/LambdaRunnable.h>

#include <gst/gst.h>
#include <qqml.h>

class [[maybe_unused]] MainViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool flip READ getFlip CONSTANT FINAL)
    Q_PROPERTY(bool mirror READ getMirror CONSTANT FINAL)
    Q_PROPERTY(int windowWidth READ getWindowWidth CONSTANT FINAL)
    Q_PROPERTY(int windowHeight READ getWindowHeight CONSTANT FINAL)
    Q_PROPERTY(int containerWidth READ getContainerWidth CONSTANT FINAL)
    Q_PROPERTY(int containerHeight READ getContainerHeight CONSTANT FINAL)
    Q_PROPERTY(QString containerAlignment READ getContainerAlignment CONSTANT FINAL)
    Q_PROPERTY(int gridRows READ getGridRows CONSTANT FINAL)
    Q_PROPERTY(int gridCols READ getGridCols CONSTANT FINAL)

    QML_ELEMENT

public:
    [[maybe_unused]] explicit MainViewModel (QObject *parent = nullptr);

    [[nodiscard]] bool getFlip () const;

    [[nodiscard]] bool getMirror () const;

    [[nodiscard]] int getWindowWidth () const;

    [[nodiscard]] int getWindowHeight () const;

    [[nodiscard]] int getContainerWidth () const;

    [[nodiscard]] int getContainerHeight () const;

    [[nodiscard]] const QString &getContainerAlignment () const;

    [[nodiscard]] int getGridRows () const;

    [[nodiscard]] int getGridCols () const;

public slots:
    [[maybe_unused]] void populateVideoGrid (QQuickItem *videoGrid);

private:
    JsonConfig mJsonConfig;
};
