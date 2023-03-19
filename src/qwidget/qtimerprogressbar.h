#include <QProgressBar>
#include <QTimer>
#include <QDebug>
#include <mutex>

class QTimerProgressBar: public QProgressBar
{
public:
    QTimerProgressBar();
    void set_value(float v);
    void start();
    void stop();

private:
    QTimer* m_timer = new QTimer(this);
    std::mutex m_mutex;
    int value = 0;

private slots:
    void update_progress();
};