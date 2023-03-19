// #ifndef MAINWINDOW2_H
// #define MAINWINDOW2_H

// #include <QMainWindow>
// #include "qclickqlabel.h"
// #include "qcustomplot.h"
// #include "brigde.h"
// #include "qhandler.h"
// #include <thread>
// #include <QApplication>
// #include <QtConcurrent/QtConcurrent>
// #include "middleware.h"
// QT_BEGIN_NAMESPACE
// namespace Ui { class MainWindow; }
// QT_END_NAMESPACE

// class MainWindow2 : public QMainWindow
// {
//     Q_OBJECT

// public:
//     MainWindow2(QWidget *parent = nullptr);
//     ~MainWindow2();
// protected:
//     void initWidgetTop();
//     void initWidgetCenter();
//     void initWidgetBottom();

// private:
//     Ui::MainWindow *ui;
//     //top
//     QWidget *m_pWidget_top;
//     QClickQLabel *m_pLabel_file_Temperature;
//     QClickQLabel *m_pLabel_file_Q;
//     QClickQLabel *m_pLabel_file_Xul_Aul;
//     QClickQLabel *m_pLabel_plots_baisc_shoot_build;
//     QClickQLabel *m_pLabel_plots_baisc_absorb_build;
//     QClickQLabel *m_pLabel_plots_voigt_build_test;
//     QClickQLabel *m_pLabel_plots_voigt_shoot_build;
//     QClickQLabel *m_pLabel_plots_voigt_absorb_build;
//     QClickQLabel *m_pLabel_baisc_shoot_export;
//     QClickQLabel *m_pLabel_baisc_absorb_export;
//     QClickQLabel *m_pLabel_aul_file_handle;
//     //center
//     QWidget *m_pWidget_center;
//     QCustomPlot *m_pQCumstomPlot;
//     QVector<double> m_x = QVector<double>(0);
//     QVector<double> m_y = QVector<double>(0);
//     //bottom
//     QWidget *m_pWidget_bottom;
//     QLabel *m_pLabel_data;
//     //core
//     middleware *m_pMiddleWare = new middleware();
//     computecurve *m_pComputeCurve = new computecurve();
//     std::string m_err;

//     long double ENumber(std::string num_str);

// private slots:
//     void on_qcustomplot_selection();//qcustomplot selection
//     void on_menu_file_Temperature();
//     void on_menu_file_Q();
//     void on_menu_plots_basic_shoot_build();
//     void on_menu_plots_basic_absorb_build();
//     void on_menu_plots_voigt_shoot_build();
//     void on_menu_plots_voigt_absorb_build();
//     void on_menu_basic_shoot_export();
//     void on_menu_basic_absorb_export();
//     void on_menu_aul_file_handle();
//     void on_menu_erro_show();
// };
// #endif // MAINWINDOW2_H
