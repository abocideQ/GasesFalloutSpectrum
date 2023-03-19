#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent)
{
  setWindowTitle("Spectrum");
  setWindowIcon(QIcon(":/ic/icon.png"));
  setMinimumWidth(QDesktopWidget().width() * 0.6);
  setMinimumHeight(QDesktopWidget().height() * 0.6);
  setWindowState(Qt::WindowState::WindowActive);
  initMenuBarView();
  initCenterView();
}

void MainWindow::initMenuBarView()
{
  // setWindowFlags(Qt::FramelessWindowHint);
  QString style_menubar = QString("QMenuBar { padding: 5px; }");
  QString style_menu_normal = QString("QMenu { background-color: rgba(252, 252, 252, 1); }");
  QString style_menu_selected = QString("QMenu::selected { color: black; background-color: rgba(0, 125, 255, 0.6); }");
  QMenuBar* p_menuBar = menuBar();
  p_menuBar->setStyleSheet(style_menubar);
  QAction* p_action_open_elConfig_file = new QAction("    打开能级配置文件");
  QAction* p_action_open_el_file = new QAction("    打开Aul文件");
  QAction* p_action_draw_shoot_base = new QAction("    基准(发射)");
  QAction* p_action_draw_intake_base = new QAction("    基准(吸收)");
  QAction* p_action_draw_shoot = new QAction("    发射谱");
  QAction* p_action_draw_intake = new QAction("    吸收谱");
  QAction* p_action_export_current = new QAction("    导出当前数据");
  QAction* p_action_AUL = new QAction("    解析原始Aul文件");
  connect(p_action_open_elConfig_file, &QAction::triggered, this, [=]() { this->QActionEvent(OPEN_CONFIG); });
  connect(p_action_open_el_file, &QAction::triggered, this, [=]() { this->QActionEvent(OPEN_EL); });
  connect(p_action_draw_shoot_base, &QAction::triggered, this, [=]() { this->QActionEvent(DRAW_SHOOT_BASE); });
  connect(p_action_draw_intake_base, &QAction::triggered, this, [=]() { this->QActionEvent(DRAW_INTAKE_BASE); });
  connect(p_action_draw_shoot, &QAction::triggered, this, [=]() { this->QActionEvent(DRAW_SHOOT); });
  connect(p_action_draw_intake, &QAction::triggered, this, [=]() { this->QActionEvent(DRAW_INTAKE); });
  connect(p_action_export_current, &QAction::triggered, this, [=]() { this->QActionEvent(EXPORT_DATA); });
  connect(p_action_AUL, &QAction::triggered, this, [=]() { this->QActionEvent(PARSE_AUL); });
  QMenu* p_menue_file = new QMenu("文件(F)");
  p_menue_file->setStyleSheet(style_menu_normal + style_menu_selected);
  p_menue_file->addAction(p_action_open_elConfig_file);
  p_menue_file->addAction(p_action_open_el_file);
  QMenu* p_menue_run = new QMenu("运行(R)");
  p_menue_run->setStyleSheet(style_menu_normal + style_menu_selected);
  p_menue_run->addAction(p_action_draw_shoot_base);
  p_menue_run->addAction(p_action_draw_intake_base);
  p_menue_run->addAction(p_action_draw_shoot);
  p_menue_run->addAction(p_action_draw_intake);
  QMenu* p_menue_export = new QMenu("导出(E)");
  p_menue_export->setStyleSheet(style_menu_normal + style_menu_selected);
  p_menue_export->addAction(p_action_export_current);
  QMenu* p_menue_AUL = new QMenu("其他(E)");
  p_menue_AUL->setStyleSheet(style_menu_normal + style_menu_selected);
  p_menue_AUL->addAction(p_action_AUL);
  p_menuBar->addMenu(p_menue_file);
  p_menuBar->addMenu(p_menue_run);
  p_menuBar->addMenu(p_menue_export);
  p_menuBar->addMenu(p_menue_AUL);
}

void MainWindow::initCenterView()
{
  /*
   * CenterRoot
   */
  setCentralWidget(mp_QRootWidget = new QFrame());
  centralWidget()->setLayout(mp_QRootLayout = new QVBoxLayout());
  centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
  centralWidget()->layout()->addWidget(mp_QRootSplitter = new QSplitter());
  mp_QRootSplitter->setContentsMargins(0, 0, 0, 0);
  mp_QRootSplitter->setHandleWidth(0);
  mp_QRootSplitter->setLineWidth(0);
  mp_QRootSplitter->addWidget(mp_QTreeView = new QTreeView());
  mp_QRootSplitter->addWidget(mp_QTabWidget = new QTabWidget());
  mp_QRootSplitter->addWidget(mp_QProgressBar = new QTimerProgressBar());
  /*
   * QTreeView LeftView
   */
  connect(mp_QTreeView, &QTreeView::doubleClicked, this, [=]() {
    QModelIndex model_index = mp_QTreeView->currentIndex();
    QString qstr_name = model_index.data().toString();
    QString qstr_data = model_index.data(Qt::UserRole + 1).toString();
    if (qstr_data.isEmpty())
    {
      return;
    }
    mp_QTabWidget->setCurrentIndex(mp_QTabWidget->indexOf(mp_QTabWidget_Map->value(qstr_name))); });
  mp_QTreeView->setContentsMargins(0, 0, 0, 0);
  mp_QTreeView->setStyleSheet("QTreeView { border: 0px; background-color: rgba(246,246,246,1); }");
  mp_QTreeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  QStandardItemModel* p_itemModel = new QStandardItemModel();
  p_itemModel->setHorizontalHeaderLabels(QStringList(QStringLiteral("资源管理器")));
  QStandardItem* p_itemRoot = p_itemModel->invisibleRootItem();
  mp_QTreeView_Map->insert(FOLDERS[0], new QStandardItem(QIcon(":/ic/ic_folder"), FOLDERS[0]));
  mp_QTreeView_Map->insert(FOLDERS[1], new QStandardItem(QIcon(":/ic/ic_folder"), FOLDERS[1]));
  mp_QTreeView_Map->insert(FOLDERS[2], new QStandardItem(QIcon(":/ic/ic_folder"), FOLDERS[2]));
  p_itemRoot->appendRow(mp_QTreeView_Map->value(FOLDERS[0]));
  p_itemRoot->appendRow(mp_QTreeView_Map->value(FOLDERS[1]));
  p_itemRoot->appendRow(mp_QTreeView_Map->value(FOLDERS[2]));
  QList<QStandardItem*> list_params = QList<QStandardItem*>();
  list_params.append(new QStandardItem(FILES[0]));
  list_params[0]->setData(QVariant(QDir::currentPath().toStdString().c_str()), Qt::UserRole + 1);
  mp_QTreeView_Map->value(FOLDERS[0])->appendRow(list_params);
  QList<QStandardItem*> list_config = QList<QStandardItem*>();
  list_config.append(new QStandardItem(FILES[1]));
  list_config[0]->setData(QVariant(QDir::currentPath().toStdString().c_str()), Qt::UserRole + 1);
  mp_QTreeView_Map->value(FOLDERS[1])->appendRow(list_config);
  QList<QStandardItem*> list_El = QList<QStandardItem*>();
  list_El.append(new QStandardItem(FILES[2]));
  list_El[0]->setData(QVariant(QDir::currentPath().toStdString().c_str()), Qt::UserRole + 1);
  mp_QTreeView_Map->value(FOLDERS[2])->appendRow(list_El);
  mp_QTreeView->setModel(p_itemModel);
  mp_QTreeView->expandAll();
  /*
   * QTabWidget CenterView-TextEdit
   */
  mp_QTabWidget_Map->insert(FILES[0], new QPlainTextEdit());
  mp_QTabWidget_Map->insert(FILES[1], new QPlainTextEdit());
  mp_QTabWidget_Map->insert(FILES[2], new QPlainTextEdit());
  mp_QTabWidget_Map->value(FILES[0])->setContentsMargins(0, 0, 0, 0);
  mp_QTabWidget_Map->value(FILES[1])->setContentsMargins(0, 0, 0, 0);
  mp_QTabWidget_Map->value(FILES[2])->setContentsMargins(0, 0, 0, 0);
  mp_QTabWidget_Map->value(FILES[0])->setStyleSheet("QPlainTextEdit { border: 0px; background-color: rgba(252,252,242,1); }");
  mp_QTabWidget_Map->value(FILES[1])->setStyleSheet("QPlainTextEdit { border: 0px; background-color: rgba(252,252,242,1); }");
  mp_QTabWidget_Map->value(FILES[2])->setStyleSheet("QPlainTextEdit { border: 0px; background-color: rgba(252,252,242,1); }");
  ((QPlainTextEdit*)mp_QTabWidget_Map->value(FILES[0]))->document()->setMaximumBlockCount(INT_MAX);
  ((QPlainTextEdit*)mp_QTabWidget_Map->value(FILES[1]))->document()->setMaximumBlockCount(INT_MAX);
  ((QPlainTextEdit*)mp_QTabWidget_Map->value(FILES[2]))->document()->setMaximumBlockCount(INT_MAX);
  mp_QTabWidget->addTab(mp_QTabWidget_Map->value(FILES[0]), FILES[0]);
  mp_QTabWidget->addTab(mp_QTabWidget_Map->value(FILES[1]), FILES[1]);
  mp_QTabWidget->addTab(mp_QTabWidget_Map->value(FILES[2]), FILES[2]);
  QTextCharFormat fmt = QTextCharFormat();
  fmt.setFontFamily("Microsoft YaHei");
  fmt.setForeground(QBrush(qRgb(0, 120, 120)));
  ((QPlainTextEdit*)mp_QTabWidget_Map->value(FILES[0]))->setCurrentCharFormat(fmt);
  ((QPlainTextEdit*)mp_QTabWidget_Map->value(FILES[1]))->setCurrentCharFormat(fmt);
  ((QPlainTextEdit*)mp_QTabWidget_Map->value(FILES[2]))->setCurrentCharFormat(fmt);
  ((QPlainTextEdit*)mp_QTabWidget_Map->value(FILES[0]))->setPlainText(QString(QJsonDocument(mp_qinterface->getArgs()).toJson()));
  ((QPlainTextEdit*)mp_QTabWidget_Map->value(FILES[1]))->setPlainText("未打开el配置文件");
  ((QPlainTextEdit*)mp_QTabWidget_Map->value(FILES[2]))->setPlainText("未打开Aul文件");
  /*
   * QTabWidget CenterView-Charts
   */
  mp_QTabWidget_Map->insert(CHARTS[0], new QCustomPlot());
  mp_QTabWidget_Map->value(CHARTS[0])->setContentsMargins(0, 0, 0, 0);
  mp_QTabWidget_Map->value(CHARTS[0])->setStyleSheet("QCustomPlot { border: 0px; background-color: rgba(252,252,242,1); }");
  // connect(m_pQCumstomPlot, &QCustomPlot::selectionChangedByUser, this, &MainWindow::on_qcustomplot_selection);
  ((QCustomPlot*)mp_QTabWidget_Map->value(CHARTS[0]))->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables); // 1拖动2缩放3可选
  ((QCustomPlot*)mp_QTabWidget_Map->value(CHARTS[0]))->xAxis->setLabel("x");
  ((QCustomPlot*)mp_QTabWidget_Map->value(CHARTS[0]))->yAxis->setLabel("y");
  ((QCustomPlot*)mp_QTabWidget_Map->value(CHARTS[0]))->clearGraphs();
  ((QCustomPlot*)mp_QTabWidget_Map->value(CHARTS[0]))->addGraph();
  // ((QCustomPlot*)mp_QTabWidget_Map->value(CHARTS[0]))->setOpenGl(true);
  ((QCustomPlot*)mp_QTabWidget_Map->value(CHARTS[0]))->graph(0)->setAdaptiveSampling(true);
  ((QCustomPlot*)mp_QTabWidget_Map->value(CHARTS[0]))->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssDisc, 1));
  ((QCustomPlot*)mp_QTabWidget_Map->value(CHARTS[0]))->graph(0)->setSelectable(QCP::SelectionType::stMultipleDataRanges);
  QPen* pen = new QPen();
  pen->setWidth(1);
  pen->setColor(Qt::black);
  ((QCustomPlot*)mp_QTabWidget_Map->value(CHARTS[0]))->graph(0)->setPen(*pen);
  mp_QTabWidget->addTab(mp_QTabWidget_Map->value(CHARTS[0]), CHARTS[0]);
  /*
   * QProgressBar RightView
   */
  mp_QProgressBar->setContentsMargins(0, 0, 0, 0);
  mp_QProgressBar->setStyleSheet("QTreeView { border: 0px; background-color: rgba(246,246,246,1); }");
  mp_QProgressBar->setOrientation(Qt::Vertical);
  /*
   * QSplitter
   */
  mp_QRootSplitter->setStretchFactor(0, 1);
  mp_QRootSplitter->setStretchFactor(1, 3);
}

void MainWindow::QActionEvent(CLICKEVENT event)
{
  Qt::WindowFlags windowFlags = Qt::WindowFlags();
  windowFlags.setFlag(Qt::WindowMaximizeButtonHint);
  windowFlags.setFlag(Qt::WindowMinimizeButtonHint);
  windowFlags.setFlag(Qt::WindowCloseButtonHint);
  if (event == OPEN_CONFIG)
  { // el配置文件
    QString url_elconfig = QFileDialog::getOpenFileName(this, "####!!!!>>>> 选择 能级配置 文件 <<<<!!!!####============================", "", "All files(*.*)");
    if (url_elconfig.isEmpty())
    {
      return;
    }
    // 1.数据解析
    int err = mp_qinterface->init_config(QTextCodec::codecForName("gbk")->fromUnicode(url_elconfig).toStdString());
    if (err < 0)
    {
      QMessageBox::about(this, tr("Spectrum"), QString("------elConfig文件解析失败------\n err: " + QString::number(err)));
    }
    // 2.View选项卡
    QFile file(url_elconfig);
    file.open(QFile::ReadWrite);
    QByteArray bytes = file.read(file.size());
    file.close();
    ((QPlainTextEdit*)mp_QTabWidget_Map->value(FILES[1]))->setPlainText(bytes);
    mp_QTabWidget->setCurrentIndex(1);
  }
  else if (event == OPEN_EL)
  { // 打开Aul文件
    QString url_aul = QFileDialog::getOpenFileName(this, "####!!!!>>>> 选择 AUL 文件 <<<<!!!!####============================", "", "All files(*.*)");
    if (url_aul.isEmpty())
    {
      return;
    }
    // 1.数据解析
    int err = mp_qinterface->init_aul(QTextCodec::codecForName("gbk")->fromUnicode(url_aul).toStdString());
    if (err < 0)
    {
      QMessageBox::about(this, tr("Spectrum"), QString("------Aul文件解析失败------\n err: " + QString::number(err)));
      return;
    }
    // 2.View选项卡
    QFile file(url_aul);
    file.open(QFile::ReadWrite);
    QByteArray bytes = file.read(file.size());
    file.close();
    ((QPlainTextEdit*)mp_QTabWidget_Map->value(FILES[2]))->setPlainText(bytes);
    mp_QTabWidget->setCurrentIndex(2);
  }
  else if (event == DRAW_SHOOT_BASE || event == DRAW_INTAKE_BASE)
  {
    if (m_working)
    {
      QMessageBox::about(this, tr("Spectrum"), QString("------有任务在进行------"));
      return;
    }
    m_working = true;
    // 计算基准
    QString jsonStr = ((QPlainTextEdit*)mp_QTabWidget_Map->value(FILES[0]))->toPlainText();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8().data());
    // 1. 计算基准
    int err = 0;
    QFutureWatcher<void>* futureWatcher = new QFutureWatcher<void>();
    connect(futureWatcher, &QFutureWatcher<void>::finished, this, [=]() {
      m_working = false;
      if (err == 0)
      {
        QCustomPlot* p_QCustomPlot = ((QCustomPlot*)mp_QTabWidget_Map->value(CHARTS[0]));
        p_QCustomPlot->graph(0)->setData(mp_qinterface->m_x, mp_qinterface->m_y);
        p_QCustomPlot->graph(0)->rescaleAxes();
        p_QCustomPlot->replot();
        mp_QTabWidget->setCurrentIndex(3);
      }
      else if (err < 0)
      {
        QMessageBox::about(this, tr("Spectrum"), QString("------基准计算失败------\n err: " + QString::number(err)));
      } });
    futureWatcher->setFuture(QtConcurrent::run([=](int* err_ptr) {
      int type = 1;
      if (event == DRAW_INTAKE_BASE)
      {
        type = 2;
      }
      *err_ptr = mp_qinterface->cp_fundation(type, jsonDoc.object());
      }, &err));
    //进度
    mp_QProgressBar->start();
    QtConcurrent::run([=]() {
      float process = 0.0;
      while (process < 1)
      {
        this_thread::sleep_for(std::chrono::milliseconds(1000));
        process = mp_qinterface->get_process(1);
        mp_QProgressBar->set_value(process);
      }
      });
  }
  else if (event == DRAW_SHOOT || event == DRAW_INTAKE)
  {
    if (m_working)
    {
      QMessageBox::about(this, tr("Spectrum"), QString("------有任务在进行------"));
      return;
    }
    m_working = true;
    // 展宽
    QString jsonStr = ((QPlainTextEdit*)mp_QTabWidget_Map->value(FILES[0]))->toPlainText();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8().data());
    // 1. 计算展宽
    QFutureWatcher<void>* futureWatcher = new QFutureWatcher<void>();
    int err = 0;
    connect(futureWatcher, &QFutureWatcher<void>::finished, this, [=]() {
      m_working = false;
      if (err == 0)
      {
        QCustomPlot* p_QCustomPlot = ((QCustomPlot*)mp_QTabWidget_Map->value(CHARTS[0]));
        p_QCustomPlot->graph(0)->setData(mp_qinterface->m_x, mp_qinterface->m_y);
        p_QCustomPlot->graph(0)->rescaleAxes();
        p_QCustomPlot->replot();
        mp_QTabWidget->setCurrentIndex(3);
      }
      else if (err < 0)
      {
        QMessageBox::about(this, tr("Spectrum"), QString("------展宽计算失败------\n err: " + QString::number(err)));
      } });
    futureWatcher->setFuture(QtConcurrent::run([=](int* err_ptr) {
      int type = 1;
      if (event == DRAW_INTAKE)
      {
        type = 2;
      }
      *err_ptr = mp_qinterface->cp_extend(type, jsonDoc.object());
      }, &err));
    //进度
    mp_QProgressBar->start();
    QtConcurrent::run([=]() {
      float process = 0.0;
      while (process < 1)
      {
        this_thread::sleep_for(std::chrono::milliseconds(1000));
        process = mp_qinterface->get_process(2);
        mp_QProgressBar->set_value(process);
      }
      });
  }
  else if (event == EXPORT_DATA)
  { // 数据导出
    QString path = QFileDialog::getExistingDirectory(this, "####!!!!>>>> 选择导出位置 <<<<!!!!####============================", nullptr, QFileDialog::ShowDirsOnly);
    if (path.isEmpty()) {
      return;
    }
    try {
      QFile file(path + "/数据.txt");
      file.open(QIODevice::ReadWrite);
      for (size_t i = 0; i < mp_qinterface->m_x.size(); i++) {
        std::stringstream stream_x = std::stringstream();
        stream_x << mp_qinterface->m_x[i];
        std::stringstream stream_y = std::stringstream();
        stream_y << mp_qinterface->m_y[i];
        std::string tmp = "x=" + stream_x.str() + "  "
          + "y=" + stream_y.str() + "  "
          + "\n";
        file.write(tmp.c_str());
      }
      file.close();
    }
    catch (QException& e)
    {
      std::cerr << e.what() << '\n';
    }
  }
  else if (event == PARSE_AUL)
  { // AUL原始文件解析
    QString file_url = QFileDialog::getOpenFileName(this, "####!!!!>>>> 文件选择 <<<<!!!!####============================", "", "All files(*.*)");
    vector<vector<string>> target = vector<vector<string>>();
    //R(n) v' v'' El Eevj Aul Fc vjMvj
    mp_qinterface->ex_unhandle_aul(QTextCodec::codecForName("gbk")->fromUnicode(file_url).toStdString(), &target);
    QString out_url = QFileDialog::getExistingDirectory(this, "####!!!!>>>> 选择导出位置 <<<<!!!!####============================", nullptr, QFileDialog::ShowDirsOnly);
    if (out_url.isEmpty()) {
      return;
    }
    try {
      QFile file(out_url + "/Aul.txt");
      file.open(QIODevice::ReadWrite);
      for (size_t i = 0; i < target.size(); i++) {
        std::string tmp = target[i][1] + "  "
          + target[i][2] + "  "
          + target[i][0] + "  "
          + target[i][4] + "  "
          + target[i][5] + "  "
          + target[i][6] + "  "
          + "\n";
        file.write(tmp.c_str());
      }
      file.close();
    }
    catch (QException& e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  //  同步计算基准
  //  int type = 1;
  //  if (event == DRAW_INTAKE_BASE)
  //  {
  //    type = 2;
  //  }
  //  int err = mp_qinterface->cp_fundation(type, jsonDoc.object());
  //  if (err == 0)
  //  {
  //    QCustomPlot *p_QCustomPlot = ((QCustomPlot *)mp_QTabWidget_Map->value(CHARTS[0]));
  //    p_QCustomPlot->graph(0)->setData(mp_qinterface->m_x, mp_qinterface->m_y);
  //    p_QCustomPlot->graph(0)->rescaleAxes();
  //    p_QCustomPlot->replot();
  //    mp_QTabWidget->setCurrentIndex(3);
  //  }
  //  else if (err < 0)
  //  {
  //    QMessageBox::about(this, tr("Spectrum"), QString("------基准计算失败------\n err: " + QString::number(err)));
  //  }
}