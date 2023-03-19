#include "qtimerprogressbar.h"

QTimerProgressBar::QTimerProgressBar() {
    setValue(0);
    setRange(0, 100);
    connect(m_timer, &QTimer::timeout, this, &QTimerProgressBar::update_progress);
}

void QTimerProgressBar::set_value(float v)
{
    value = (int)(v * 100);
}

void QTimerProgressBar::start()
{
    value = 0;
    setValue(0);
    m_timer->stop();
    m_timer->start(1000);
}

void QTimerProgressBar::stop()
{
    m_timer->stop();
}

void QTimerProgressBar::update_progress()
{
    if (value < 1)
    {
        setValue(1);
    }
    else if (value > 100)
    {
        setValue(99);
    }
    else
    {
        setValue(value);
    }
    if (value >= 100)
    {
        stop();
    }
}