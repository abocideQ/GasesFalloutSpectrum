#include <QWidget>
#include <QToolButton>
#include <QIcon>
#include <QHBoxLayout>
#include <QPoint>
#include <QMouseEvent>
#include <QMainWindow>

class qtitlebar : public QWidget
{
public:
    qtitlebar(QMainWindow *, QIcon, QIcon, QIcon);

    QMainWindow *m_window = nullptr;

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

    bool m_move_enable;
    QPoint m_move_point;
    QPoint m_move_last_Point;

private:
    QToolButton *mp_tb_min;
    QToolButton *mp_tb_max;
    QToolButton *mp_tb_close;
};