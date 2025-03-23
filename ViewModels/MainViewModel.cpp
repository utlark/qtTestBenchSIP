#include "MainViewModel.h"

[[maybe_unused]] MainViewModel::MainViewModel (QObject *parent) :
        QObject(parent),
        mJsonConfig()
{
}

[[maybe_unused]] void MainViewModel::populateVideoGrid (QQuickItem *videoGrid)
{
    QQmlComponent videoComponent(qmlEngine(videoGrid));
    videoComponent.loadFromModule("qtTestBenchSIP", "VideoItem");
    if (videoComponent.isError())
    {
        qWarning() << videoComponent.errors();
        return;
    }

    QJsonArray sources = mJsonConfig.getSources();
    for (int i = 0; i < sources.count(); ++i)
    {
        QObject *videoObject = videoComponent.create();
        if (!videoObject)
        {
            qWarning() << videoComponent.errorString();
            continue;
        }

        QQuickItem *videoItem = qobject_cast<QQuickItem *>(videoObject);
        if (!videoItem)
        {
            qWarning() << "Couldn't cast VideoItem to QQuickItem";
            continue;
        }

        videoItem->setWidth(1.0 * mJsonConfig.getContainerWidth() / mJsonConfig.getGridCols());
        videoItem->setHeight(1.0 * mJsonConfig.getContainerHeight() / mJsonConfig.getGridRows());

        videoItem->setParentItem(videoGrid);

        GstElement *pipeline = gst_parse_launch(sources.at(i).toString().toUtf8().constData(), nullptr);
        g_object_set(gst_bin_get_by_name(GST_BIN(pipeline), "sink"), "widget", videoItem, nullptr);
        videoItem->window()->scheduleRenderJob(
                new LambdaRunnable([pipeline] () {
                    gst_element_set_state(pipeline, GST_STATE_PLAYING);
                    gst_object_unref(pipeline);
                }),
                QQuickWindow::BeforeSynchronizingStage
        );
    }
}

bool MainViewModel::getFlip () const
{
    return mJsonConfig.getFlip();
}

bool MainViewModel::getMirror () const
{
    return mJsonConfig.getMirror();
}

int MainViewModel::getWindowWidth () const
{
    return mJsonConfig.getWindowWidth();
}

int MainViewModel::getWindowHeight () const
{
    return mJsonConfig.getWindowHeight();
}

int MainViewModel::getContainerWidth () const
{
    return mJsonConfig.getContainerWidth();
}

int MainViewModel::getContainerHeight () const
{
    return mJsonConfig.getContainerHeight();
}

const QString &MainViewModel::getContainerAlignment () const
{
    return mJsonConfig.getContainerAlignment();
}

int MainViewModel::getGridRows () const
{
    return mJsonConfig.getGridRows();
}

int MainViewModel::getGridCols () const
{
    return mJsonConfig.getGridCols();
}
