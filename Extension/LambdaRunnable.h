#pragma once

#include <QRunnable>

class LambdaRunnable : public QRunnable
{
public:
    explicit LambdaRunnable (std::function<void()> func) :
            func_(std::move(func)) { }

    void run () override { func_(); }

private:
    std::function<void()> func_;
};
