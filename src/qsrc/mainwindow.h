#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QIcon>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QFileDialog>
#include <QSplitter>
#include <QTreeView>
#include <QStandardItemModel>
#include <QTabWidget>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QRgb>
#include <QTextCharFormat>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QByteArray>
#include <QTextCodec>
#include <QtConcurrent/QtConcurrent>
#include <vector>
#include "src/qwidget/qcustomplot.h"
#include "src/qwidget/qtimerprogressbar.h"
#include "src/qwidget/qtitlebar.h"
#include "src/qsrc/qinterface.h"

class MainWindow: public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);

private:
  void initMenuBarView();

  void initCenterView();

  enum CLICKEVENT
  {
    OPEN_CONFIG,
    OPEN_EL,
    DRAW_SHOOT_BASE,
    DRAW_INTAKE_BASE,
    DRAW_SHOOT,
    DRAW_INTAKE,
    EXPORT_DATA,
    PARSE_AUL,
  };
  QString FOLDERS[3] = {
      "args",
      "cfig",
      "aul",
  };
  QString FILES[3] = {
      "args.txt",
      "config.txt",
      "aul.txt",
  };
  QString CHARTS[1] = {
      "QCharts" };
  // ContainerLayout
  QFrame* mp_QRootWidget;
  QVBoxLayout* mp_QRootLayout;
  QSplitter* mp_QRootSplitter;
  // ContentView
  QTreeView* mp_QTreeView; // TreeView
  QMap<QString, QStandardItem*>* mp_QTreeView_Map = new QMap<QString, QStandardItem*>;
  QTabWidget* mp_QTabWidget; // TabView
  QMap<QString, QWidget*>* mp_QTabWidget_Map = new QMap<QString, QWidget*>;
  QTimerProgressBar* mp_QProgressBar; // Progressbar
  // interface
  bool m_working = false;
  qinterface* mp_qinterface = new qinterface();
private slots:
  void QActionEvent(CLICKEVENT);
};
#endif // MAINWINDOW_H
