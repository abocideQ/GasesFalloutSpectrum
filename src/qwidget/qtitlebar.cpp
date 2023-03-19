#include "qtitlebar.h"

qtitlebar::qtitlebar(QMainWindow *window, QIcon icon_min, QIcon icon_max, QIcon icon_close)
{
    // MainWindow
    m_window = window;
    // Button
    mp_tb_min = new QToolButton(this);
    mp_tb_min->setAutoRaise(true);
    mp_tb_min->setIcon(icon_min);
    mp_tb_min->setIconSize(QSize(25, 25));
    mp_tb_min->setFixedSize(QSize(60, 40));
    connect(mp_tb_min, SIGNAL(clicked()), this, SLOT(m_window->showMinimized()));
    mp_tb_max = new QToolButton(this);
    mp_tb_max->setAutoRaise(true);
    mp_tb_max->setIcon(icon_max);
    mp_tb_max->setIconSize(QSize(25, 25));
    mp_tb_max->setFixedSize(QSize(60, 40));
    connect(mp_tb_max, SIGNAL(clicked()), this, SLOT(m_window->showMaximized()));
    mp_tb_close = new QToolButton(this);
    mp_tb_close->setAutoRaise(true);
    mp_tb_close->setIcon(icon_close);
    mp_tb_close->setIconSize(QSize(25, 25));
    mp_tb_close->setFixedSize(QSize(60, 40));
    connect(mp_tb_close, SIGNAL(clicked()), this, SLOT(m_window->close()));
    // Root
    setLayout(new QHBoxLayout());
    layout()->addWidget(mp_tb_min);
    layout()->addWidget(mp_tb_max);
    layout()->addWidget(mp_tb_close);
}

void qtitlebar::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::MouseButton::LeftButton)
    {
        m_move_enable = true;
        m_move_point = frameGeometry().topLeft();
        m_move_last_Point = ev->screenPos().toPoint();
        qDebug("movePoint x=%d y=%d", m_move_point.x(), m_move_point.y());
        qDebug("lastPoint x=%d y=%d", m_move_last_Point.x(), m_move_last_Point.y());
    }
}

void qtitlebar::mouseReleaseEvent(QMouseEvent *ev)
{
}

void qtitlebar::mouseMoveEvent(QMouseEvent *ev)
{
    m_move_enable = false;
}
