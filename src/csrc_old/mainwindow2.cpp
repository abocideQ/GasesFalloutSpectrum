// #include "MainWindow2.h"
// #include "ui_mainwindow.h"

// MainWindow2::MainWindow2(QWidget* parent)
//     : QMainWindow(parent)
//     , ui(new Ui::MainWindow)
// {
//     //ui
//     ui->setupUi(this);
//     this->setWindowTitle("? Chart");
//     ui->menubar->setPalette(QPalette(Qt::white));
//     ui->menubar->setAutoFillBackground(true);
//     ui->statusbar->setPalette(QPalette(Qt::white));
//     ui->statusbar->setAutoFillBackground(true);
//     ui->centralwidget->setPalette(QPalette(Qt::white));
//     ui->centralwidget->setAutoFillBackground(true);
//     //widget
//     initWidgetTop();
//     initWidgetCenter();
//     initWidgetBottom();
//     //    initWidgetMenu();
//     //addwidget
//     QGridLayout* layout_root = new QGridLayout();
//     ui->centralwidget->setLayout(layout_root);
//     layout_root->addWidget(m_pWidget_top, 0, 0);
//     layout_root->addWidget(m_pWidget_center, 1, 0);
//     layout_root->addWidget(m_pWidget_bottom, 2, 0);
// }

// void MainWindow2::initWidgetTop()
// {
//     m_pWidget_top = new QWidget();
//     m_pWidget_top->setMaximumHeight(36);
//     QHBoxLayout* layout_top = new QHBoxLayout(m_pWidget_top);
//     //    layout_top->setSizeConstraint(QLayout::SetMaximumSize);
//     //    layout_top->setMargin(10);
//     //    layout_top->setSpacing(0);
//     m_pLabel_file_Temperature = new QClickQLabel("温度");
//     m_pLabel_file_Temperature->setMinimumWidth(80);
//     m_pLabel_file_Temperature->setMaximumHeight(36);
//     m_pLabel_file_Temperature->setAlignment(Qt::AlignmentFlag::AlignCenter);
//     m_pLabel_file_Q = new QClickQLabel("Q");
//     m_pLabel_file_Q->setMinimumWidth(80);
//     m_pLabel_file_Q->setMaximumHeight(36);
//     m_pLabel_file_Q->setAlignment(Qt::AlignmentFlag::AlignCenter);
//     m_pLabel_file_Xul_Aul = new QClickQLabel("λ & A");
//     m_pLabel_file_Xul_Aul->setMinimumWidth(80);
//     m_pLabel_file_Xul_Aul->setMaximumHeight(36);
//     m_pLabel_file_Xul_Aul->setAlignment(Qt::AlignmentFlag::AlignCenter);
//     m_pLabel_plots_baisc_shoot_build = new QClickQLabel("发射基准");
//     m_pLabel_plots_baisc_shoot_build->setMinimumWidth(80);
//     m_pLabel_plots_baisc_shoot_build->setMaximumHeight(36);
//     m_pLabel_plots_baisc_shoot_build->setAlignment(Qt::AlignmentFlag::AlignCenter);
//     m_pLabel_plots_baisc_absorb_build = new QClickQLabel("吸收基准");
//     m_pLabel_plots_baisc_absorb_build->setMinimumWidth(80);
//     m_pLabel_plots_baisc_absorb_build->setMaximumHeight(36);
//     m_pLabel_plots_baisc_absorb_build->setAlignment(Qt::AlignmentFlag::AlignCenter);
//     m_pLabel_plots_voigt_build_test = new QClickQLabel("VOIGT测试");
//     m_pLabel_plots_voigt_build_test->setMinimumWidth(80);
//     m_pLabel_plots_voigt_build_test->setMaximumHeight(36);
//     m_pLabel_plots_voigt_build_test->setAlignment(Qt::AlignmentFlag::AlignCenter);
//     m_pLabel_plots_voigt_shoot_build = new QClickQLabel("发射展宽");
//     m_pLabel_plots_voigt_shoot_build->setMinimumWidth(80);
//     m_pLabel_plots_voigt_shoot_build->setMaximumHeight(36);
//     m_pLabel_plots_voigt_shoot_build->setAlignment(Qt::AlignmentFlag::AlignCenter);
//     m_pLabel_plots_voigt_absorb_build = new QClickQLabel("吸收展宽");
//     m_pLabel_plots_voigt_absorb_build->setMinimumWidth(80);
//     m_pLabel_plots_voigt_absorb_build->setMaximumHeight(36);
//     m_pLabel_plots_voigt_absorb_build->setAlignment(Qt::AlignmentFlag::AlignCenter);
//     m_pLabel_baisc_shoot_export = new QClickQLabel("数据导出");
//     m_pLabel_baisc_shoot_export->setMinimumWidth(80);
//     m_pLabel_baisc_shoot_export->setMaximumHeight(36);
//     m_pLabel_baisc_shoot_export->setAlignment(Qt::AlignmentFlag::AlignCenter);
//     m_pLabel_baisc_absorb_export = new QClickQLabel("吸收导出");
//     m_pLabel_baisc_absorb_export->setMinimumWidth(80);
//     m_pLabel_baisc_absorb_export->setMaximumHeight(36);
//     m_pLabel_baisc_absorb_export->setAlignment(Qt::AlignmentFlag::AlignCenter);
//     m_pLabel_aul_file_handle = new QClickQLabel("Aul文件处理");
//     m_pLabel_aul_file_handle->setMinimumWidth(80);
//     m_pLabel_aul_file_handle->setMaximumHeight(36);
//     m_pLabel_aul_file_handle->setAlignment(Qt::AlignmentFlag::AlignCenter);
//     layout_top->addWidget(m_pLabel_file_Temperature);
//     layout_top->addWidget(m_pLabel_file_Q);
//     layout_top->addWidget(m_pLabel_plots_baisc_shoot_build);
//     layout_top->addWidget(m_pLabel_plots_baisc_absorb_build);
//     layout_top->addWidget(m_pLabel_plots_voigt_shoot_build);
//     layout_top->addWidget(m_pLabel_plots_voigt_absorb_build);
//     layout_top->addWidget(m_pLabel_baisc_shoot_export);
//     //    layout_top->addWidget(m_pLabel_baisc_absorb_export);
//     layout_top->addWidget(m_pLabel_aul_file_handle);
//     layout_top->addSpacerItem(new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
//     //信号槽
//     connect(m_pLabel_file_Temperature, &QClickQLabel::clicked, this, &MainWindow2::on_menu_file_Temperature);
//     connect(m_pLabel_file_Q, &QClickQLabel::clicked, this, &MainWindow2::on_menu_file_Q);
//     connect(m_pLabel_plots_baisc_shoot_build, &QClickQLabel::clicked, this, &MainWindow2::on_menu_plots_basic_shoot_build);
//     connect(m_pLabel_plots_baisc_absorb_build, &QClickQLabel::clicked, this, &MainWindow2::on_menu_plots_basic_absorb_build);
//     connect(m_pLabel_plots_voigt_shoot_build, &QClickQLabel::clicked, this, &MainWindow2::on_menu_plots_voigt_shoot_build);
//     connect(m_pLabel_plots_voigt_absorb_build, &QClickQLabel::clicked, this, &MainWindow2::on_menu_plots_voigt_absorb_build);
//     connect(m_pLabel_baisc_shoot_export, &QClickQLabel::clicked, this, &MainWindow2::on_menu_basic_shoot_export);
//     connect(m_pLabel_baisc_absorb_export, &QClickQLabel::clicked, this, &MainWindow2::on_menu_basic_absorb_export);
//     connect(m_pLabel_aul_file_handle, &QClickQLabel::clicked, this, &MainWindow2::on_menu_aul_file_handle);
// }

// void MainWindow2::initWidgetCenter()
// {
//     m_pWidget_center = new QWidget();
//     QGridLayout* layout_center = new QGridLayout(m_pWidget_center);
//     m_pQCumstomPlot = new QCustomPlot;
//     m_pQCumstomPlot->clearGraphs();
//     m_pQCumstomPlot->addGraph();
//     // 1、轴拖动 2、轴缩放 3、图可选 4、 多选
//     m_pQCumstomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
//     // 数据点显示图案
//     m_pQCumstomPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssDisc, 1));
//     m_pQCumstomPlot->graph(0)->setSelectable(QCP::SelectionType::stMultipleDataRanges);
//     // 设置颜色/宽度等
//     QPen* pen = new QPen;
//     pen->setWidth(1);
//     pen->setColor(Qt::black);
//     m_pQCumstomPlot->graph(0)->setPen(*pen);
//     m_pQCumstomPlot->graph(0)->setAdaptiveSampling(true);
//     // 设置x轴，y轴 label
//     m_pQCumstomPlot->xAxis->setLabel("x");
//     m_pQCumstomPlot->yAxis->setLabel("y");
//     layout_center->addWidget(m_pQCumstomPlot, 0, 0);
//     //信号槽
//     connect(m_pQCumstomPlot, &QCustomPlot::selectionChangedByUser, this, &MainWindow2::on_qcustomplot_selection);
// }

// void MainWindow2::initWidgetBottom()
// {
//     m_pWidget_bottom = new QWidget();
//     m_pWidget_bottom->setMaximumHeight(40);
//     QGridLayout* layout_bottom = new QGridLayout(m_pWidget_bottom);
//     m_pLabel_data = new QLabel("g:g, x:x, y:y, t:t, e,e, .....数据");
//     m_pLabel_data->setMaximumHeight(40);
//     m_pLabel_data->setAlignment(Qt::AlignmentFlag::AlignCenter);
//     layout_bottom->addWidget(m_pLabel_data, 0, 0);
// }

// //qcustomplot 数据点选择回调
// void MainWindow2::on_qcustomplot_selection()
// {
//     for (int i = 0; i < m_pQCumstomPlot->graphCount(); i++) {
//         //遍历有被选中的graph
//         if (m_pQCumstomPlot->graph(i)->selected()) {
//             QCPDataSelection selection = m_pQCumstomPlot->graph(i)->selection();
//             //遍历选中范围
//             for (int j = 0; j < selection.dataRangeCount(); j++) {
//                 QCPDataRange dataRange = selection.dataRange(j);
//                 //遍历数据
//                 for (int k = dataRange.begin(); k < dataRange.end(); k++) {
//                     QString str_key = QString::number(m_pQCumstomPlot->graph(i)->data()->at(k)->key);
//                     QString str_value = QString::number(m_pQCumstomPlot->graph(i)->data()->at(k)->value);
//                     QString str_at = QString::number(i);
//                     //text
//                     m_pLabel_data->setText("x=" + str_key + ", y=" + str_value);
//                 }
//             }
//         }
//     }
// }

// void MainWindow2::on_menu_file_Temperature()
// {
//     Qt::WindowFlags windowFlags = Qt::WindowFlags();
//     windowFlags.setFlag(Qt::WindowMaximizeButtonHint);
//     windowFlags.setFlag(Qt::WindowMinimizeButtonHint);
//     windowFlags.setFlag(Qt::WindowCloseButtonHint);
//     bool ret_ok;
//     //Tex Tvib Trot
//     float const_Tex = QInputDialog::getText(this, "温度Tex", tr("请输入温度Tex"), QLineEdit::Normal, 0, &ret_ok, windowFlags).toFloat();
//     if (!ret_ok || const_Tex < 0) {
//         return;
//     }
//     float const_Tvib = QInputDialog::getText(this, "温度Tvib", tr("请输入温度Tvib"), QLineEdit::Normal, 0, &ret_ok, windowFlags).toFloat();
//     if (!ret_ok || const_Tvib < 0) {
//         return;
//     }
//     float const_Trot = QInputDialog::getText(this, "温度Trot", tr("请输入温度Trot"), QLineEdit::Normal, 0, &ret_ok, windowFlags).toFloat();
//     if (!ret_ok || const_Trot < 0) {
//         return;
//     }
//     float const_Tgas = QInputDialog::getText(this, "气体温度", tr("请输入气体温度"), QLineEdit::Normal, 0, &ret_ok, windowFlags).toFloat();
//     if (!ret_ok || const_Tgas < 0) {
//         return;
//     }
//     //    m_pBrigde->set_other_info(const_h, const_c, const_K, const_Tex, const_Tvib, const_Trot, const_Tgas);
//     m_pMiddleWare->init_temperature(const_Tex, const_Tvib, const_Trot, const_Tgas);
// }

// void MainWindow2::on_menu_file_Q()
// {
//     try {
//         Qt::WindowFlags windowFlags = Qt::WindowFlags();
//         windowFlags.setFlag(Qt::WindowMaximizeButtonHint);
//         windowFlags.setFlag(Qt::WindowMinimizeButtonHint);
//         windowFlags.setFlag(Qt::WindowCloseButtonHint);
//         QString file_config_url = QFileDialog::getOpenFileName(this, "态配置文件选择", "", "All files(*.*)");
//         if (file_config_url.isEmpty()) {
//             return;
//         }
//         QByteArray bytes = file_config_url.toLocal8Bit(); //.toLatin1().data() 无效
//         char* file_url_char = new char[1024];
//         strcpy(file_url_char, bytes.data());
//         //        m_pBrigde->set_q_info(file_url_char);
//         m_pMiddleWare->init_vj_all(file_url_char);
//     } catch (QException e) {
//         qDebug("%s", e.what());
//     }
// }

// void MainWindow2::on_menu_plots_basic_shoot_build()
// {
//     Qt::WindowFlags windowFlags = Qt::WindowFlags();
//     windowFlags.setFlag(Qt::WindowMaximizeButtonHint);
//     windowFlags.setFlag(Qt::WindowMinimizeButtonHint);
//     windowFlags.setFlag(Qt::WindowCloseButtonHint);
//     bool ret_ok;
//     QString file_names = "";
//     for (size_t i = 0; i < m_pMiddleWare->config_vec_VJ.size(); i++) {
//         int index = i;
//         file_names += "id:";
//         file_names += std::to_string(index).c_str();
//         file_names += "\n";
//         file_names += "file:";
//         file_names += QString::fromStdString(m_pMiddleWare->config_vec_VJ[i].name).toStdString().c_str();
//         file_names += "\n\n";
//     }
//     file_names += "输入 低能态 高能态 文件id\n格式：0 1";
//     QString file_index = QInputDialog::getText(this,
//         "文件选择",
//         file_names,
//         QLineEdit::Normal,
//         0,
//         &ret_ok,
//         windowFlags);
//     QStringList file_index_list = file_index.split(" ");
//     if (file_index_list.size() < 2) {
//         return;
//     }
//     int low_index = file_index_list[0].trimmed().toInt();
//     int up_index = file_index_list[1].trimmed().toInt();
//     QString v_index = QInputDialog::getText(this,
//         "输入v'-v''差值",
//         "输入v'-v''差值\n格式: -1 0 1",
//         QLineEdit::Normal,
//         0,
//         &ret_ok,
//         windowFlags);
//     QStringList v_index_list = v_index.split(" ");
//     std::vector<int> v_index_vec = std::vector<int>();
//     for (int i = 0; i < v_index_list.size(); i++) {
//         v_index_vec.push_back(v_index_list[i].trimmed().toInt());
//     }
//     QString file_aul = QFileDialog::getOpenFileName(this, "Aul文件", "", "All files(*.*)");
//     if (file_aul.isEmpty()) {
//         return;
//     }
//     // plot
//     try {
//         m_pMiddleWare->compute_vj_all_Qevj();
//         m_pMiddleWare->compute_xmodel(1, v_index_vec, low_index, up_index, file_aul.toStdString());
//         QVector<double> m_x(m_pMiddleWare->m_data_vec_xmodel.size()), m_y(m_pMiddleWare->m_data_vec_xmodel.size());
//         for (size_t i = 0; i < m_pMiddleWare->m_data_vec_xmodel.size(); i++) {
//             m_x[i] = m_pMiddleWare->m_data_vec_xmodel[i].x;
//             if (m_x[i] != 0) {
//                 m_x[i] = 9993466.0f / m_x[i];
//             }
//             m_y[i] = m_pMiddleWare->m_data_vec_xmodel[i].y;
//         }
//         m_pQCumstomPlot->graph(0)->setData(m_x, m_y);
//         m_pQCumstomPlot->graph(0)->rescaleAxes();
//         m_pQCumstomPlot->replot();
//     } catch (std::exception e) {
//         m_err = "";
//         m_err = std::string(e.what());
//     }
// }

// void MainWindow2::on_menu_plots_basic_absorb_build()
// {
//     Qt::WindowFlags windowFlags = Qt::WindowFlags();
//     windowFlags.setFlag(Qt::WindowMaximizeButtonHint);
//     windowFlags.setFlag(Qt::WindowMinimizeButtonHint);
//     windowFlags.setFlag(Qt::WindowCloseButtonHint);
//     bool ret_ok;
//     QString file_names = "";
//     for (size_t i = 0; i < m_pMiddleWare->config_vec_VJ.size(); i++) {
//         int index = i;
//         file_names += "id:";
//         file_names += std::to_string(index).c_str();
//         file_names += "\n";
//         file_names += "file:";
//         file_names += QString::fromStdString(m_pMiddleWare->config_vec_VJ[i].name).toStdString().c_str();
//         file_names += "\n\n";
//     }
//     file_names += "输入 低能态 高能态 文件id\n格式：0 1";
//     QString file_index = QInputDialog::getText(this,
//         "文件选择",
//         file_names,
//         QLineEdit::Normal,
//         0,
//         &ret_ok,
//         windowFlags);
//     QStringList file_index_list = file_index.split(" ");
//     if (file_index_list.size() < 2) {
//         return;
//     }
//     int low_index = file_index_list[0].trimmed().toInt();
//     int up_index = file_index_list[1].trimmed().toInt();
//     QString v_index = QInputDialog::getText(this,
//         "输入v'-v''差值",
//         "输入v'-v''差值\n格式: -1 0 1",
//         QLineEdit::Normal,
//         0,
//         &ret_ok,
//         windowFlags);
//     QStringList v_index_list = v_index.split(" ");
//     std::vector<int> v_index_vec = std::vector<int>();
//     for (int i = 0; i < v_index_list.size(); i++) {
//         v_index_vec.push_back(v_index_list[i].trimmed().toInt());
//     }
//     QString file_aul = QFileDialog::getOpenFileName(this, "Aul文件", "", "All files(*.*)");
//     if (file_aul.isEmpty()) {
//         return;
//     }
//     // plot
//     try {
//         m_pMiddleWare->compute_vj_all_Qevj();
//         m_pMiddleWare->compute_xmodel(2, v_index_vec, low_index, up_index, file_aul.toStdString());
//         QVector<double> m_x(m_pMiddleWare->m_data_vec_xmodel.size()), m_y(m_pMiddleWare->m_data_vec_xmodel.size());
//         for (size_t i = 0; i < m_pMiddleWare->m_data_vec_xmodel.size(); i++) {
//             m_x[i] = m_pMiddleWare->m_data_vec_xmodel[i].x;
//             if (m_x[i] != 0) {
//                 m_x[i] = 9993466.0f / m_x[i];
//             }
//             m_y[i] = m_pMiddleWare->m_data_vec_xmodel[i].y;
//         }
//         m_pQCumstomPlot->graph(0)->setData(m_x, m_y);
//         m_pQCumstomPlot->graph(0)->rescaleAxes();
//         m_pQCumstomPlot->replot();
//     } catch (std::exception e) {
//         m_err = "";
//         m_err = std::string(e.what());
//     }
// }

// void MainWindow2::on_menu_plots_voigt_shoot_build()
// {
//     Qt::WindowFlags windowFlags = Qt::WindowFlags();
//     windowFlags.setFlag(Qt::WindowMaximizeButtonHint);
//     windowFlags.setFlag(Qt::WindowMinimizeButtonHint);
//     windowFlags.setFlag(Qt::WindowCloseButtonHint);
//     bool ret_ok;
//     QString file_names = "";
//     for (size_t i = 0; i < m_pMiddleWare->config_vec_VJ.size(); i++) {
//         int index = i;
//         file_names += "id:";
//         file_names += std::to_string(index).c_str();
//         file_names += "\n";
//         file_names += "file:";
//         file_names += QString::fromStdString(m_pMiddleWare->config_vec_VJ[i].name).toStdString().c_str();
//         file_names += "\n\n";
//     }
//     file_names += "输入 低能态 高能态 文件id\n格式：0 1";
//     QString file_index = QInputDialog::getText(this,
//         "文件选择",
//         file_names,
//         QLineEdit::Normal,
//         0,
//         &ret_ok,
//         windowFlags);
//     QStringList file_index_list = file_index.split(" ");
//     if (file_index_list.size() < 2) {
//         return;
//     }
//     int low_index = file_index_list[0].trimmed().toInt();
//     int up_index = file_index_list[1].trimmed().toInt();
//     QString v_index = QInputDialog::getText(this,
//         "输入v'-v''差值",
//         "输入v'-v''差值\n格式: -1 0 1",
//         QLineEdit::Normal,
//         0,
//         &ret_ok,
//         windowFlags);
//     QStringList v_index_list = v_index.split(" ");
//     std::vector<int> v_index_vec = std::vector<int>();
//     for (int i = 0; i < v_index_list.size(); i++) {
//         v_index_vec.push_back(v_index_list[i].trimmed().toInt());
//     }
//     QString file_aul = QFileDialog::getOpenFileName(this, "Aul文件", "", "All files(*.*)");
//     if (file_aul.isEmpty()) {
//         return;
//     }
//     float min = QInputDialog::getText(this, tr("min"), tr("min"), QLineEdit::Normal, 0, &ret_ok).toFloat();
//     if (!ret_ok || min < 0) {
//         return;
//     }
//     float max = QInputDialog::getText(this, tr("max"), tr("max"), QLineEdit::Normal, 0, &ret_ok).toFloat();
//     if (!ret_ok || max < 0) {
//         return;
//     }
//     float weight = QInputDialog::getText(this, tr("weight"), tr("weight"), QLineEdit::Normal, 0, &ret_ok).toFloat();
//     if (!ret_ok || weight < 0) {
//         return;
//     }
//     float step = QInputDialog::getText(this, tr("step"), tr("step"), QLineEdit::Normal, 0, &ret_ok).toFloat();
//     if (!ret_ok || weight < 0) {
//         return;
//     }
//     try {
//         vector<ModelCoordinate>* vec_coordinate = new vector<ModelCoordinate>();
//         //基准计算
//         m_pMiddleWare->compute_vj_all_Qevj();
//         m_pMiddleWare->compute_xmodel(1, v_index_vec, low_index, up_index, file_aul.toStdString());
//         QFutureWatcher<void>* pwatcher = new QFutureWatcher<void>;
//         pwatcher->setFuture(QtConcurrent::run([=]() {
//             //curve
//             m_pComputeCurve->computeCurveVoigt(min, max, step, weight,
//                 m_pMiddleWare->config_Trot,
//                 &m_pMiddleWare->m_data_vec_xmodel,
//                 vec_coordinate);
//         }));
//         connect(pwatcher, &QFutureWatcher<void>::finished, this, [=]() {
//             qDebug("QFutureWatcher finished");
//             m_x.clear();
//             m_y.clear();
//             m_x = QVector<double>(vec_coordinate->size());
//             m_y = QVector<double>(vec_coordinate->size());
//             for (size_t i = 0; i < vec_coordinate->size(); i++) {
//                 m_x[i] = 9993466.0f / vec_coordinate->at(i).x;
//                 m_y[i] = vec_coordinate->at(i).y;
//             }
//             m_pQCumstomPlot->graph(0)->setData(m_x, m_y);
//             m_pQCumstomPlot->graph(0)->rescaleAxes();
//             m_pQCumstomPlot->replot();
//         });
//         //===================== 进度条
//         QFutureWatcher<void>().setFuture(QtConcurrent::run([=]() {
//             float process = 0;
//             while (1) {
//                 this_thread::sleep_for(std::chrono::milliseconds(1000));
//                 process = m_pComputeCurve->getProcess();
//                 m_pLabel_data->setText("process = " + QString::fromStdString(std::to_string(process * 100)) + "%");
//                 if (process == 1) {
//                     break;
//                 }
//             }
//         }));
//     } catch (std::exception e) {
//         m_err = "";
//         m_err = std::string(e.what());
//     }
// }

// void MainWindow2::on_menu_plots_voigt_absorb_build()
// {
//     Qt::WindowFlags windowFlags = Qt::WindowFlags();
//     windowFlags.setFlag(Qt::WindowMaximizeButtonHint);
//     windowFlags.setFlag(Qt::WindowMinimizeButtonHint);
//     windowFlags.setFlag(Qt::WindowCloseButtonHint);
//     bool ret_ok;
//     QString file_names = "";
//     for (size_t i = 0; i < m_pMiddleWare->config_vec_VJ.size(); i++) {
//         int index = i;
//         file_names += "id:";
//         file_names += std::to_string(index).c_str();
//         file_names += "\n";
//         file_names += "file:";
//         file_names += QString::fromStdString(m_pMiddleWare->config_vec_VJ[i].name).toStdString().c_str();
//         file_names += "\n\n";
//     }
//     file_names += "输入 低能态 高能态 文件id\n格式：0 1";
//     QString file_index = QInputDialog::getText(this,
//         "文件选择",
//         file_names,
//         QLineEdit::Normal,
//         0,
//         &ret_ok,
//         windowFlags);
//     QStringList file_index_list = file_index.split(" ");
//     if (file_index_list.size() < 2) {
//         return;
//     }
//     int low_index = file_index_list[0].trimmed().toInt();
//     int up_index = file_index_list[1].trimmed().toInt();
//     QString v_index = QInputDialog::getText(this,
//         "输入v'-v''差值",
//         "输入v'-v''差值\n格式: -1 0 1",
//         QLineEdit::Normal,
//         0,
//         &ret_ok,
//         windowFlags);
//     QStringList v_index_list = v_index.split(" ");
//     std::vector<int> v_index_vec = std::vector<int>();
//     for (int i = 0; i < v_index_list.size(); i++) {
//         v_index_vec.push_back(v_index_list[i].trimmed().toInt());
//     }
//     QString file_aul = QFileDialog::getOpenFileName(this, "Aul文件", "", "All files(*.*)");
//     if (file_aul.isEmpty()) {
//         return;
//     }
//     float min = QInputDialog::getText(this, tr("min"), tr("min"), QLineEdit::Normal, 0, &ret_ok).toFloat();
//     if (!ret_ok || min < 0) {
//         return;
//     }
//     float max = QInputDialog::getText(this, tr("max"), tr("max"), QLineEdit::Normal, 0, &ret_ok).toFloat();
//     if (!ret_ok || max < 0) {
//         return;
//     }
//     float weight = QInputDialog::getText(this, tr("weight"), tr("weight"), QLineEdit::Normal, 0, &ret_ok).toFloat();
//     if (!ret_ok || weight < 0) {
//         return;
//     }
//     float step = QInputDialog::getText(this, tr("step"), tr("step"), QLineEdit::Normal, 0, &ret_ok).toFloat();
//     if (!ret_ok || weight < 0) {
//         return;
//     }
//     try {
//         vector<ModelCoordinate>* vec_coordinate = new vector<ModelCoordinate>();
//         //基准计算
//         m_pMiddleWare->compute_vj_all_Qevj();
//         m_pMiddleWare->compute_xmodel(2, v_index_vec, low_index, up_index, file_aul.toStdString());
//         QFutureWatcher<void>* pwatcher = new QFutureWatcher<void>;
//         pwatcher->setFuture(QtConcurrent::run([=]() {
//             //curve
//             m_pComputeCurve->computeCurveVoigt(min, max, step, weight,
//                 m_pMiddleWare->config_Trot,
//                 &m_pMiddleWare->m_data_vec_xmodel,
//                 vec_coordinate);
//         }));
//         connect(pwatcher, &QFutureWatcher<void>::finished, this, [=]() {
//             std::cout << "QFutureWatcher finished";
//             m_x.clear();
//             m_y.clear();
//             m_x = QVector<double>(vec_coordinate->size());
//             m_y = QVector<double>(vec_coordinate->size());
//             for (size_t i = 0; i < vec_coordinate->size(); i++) {
//                 m_x[i] = 9993466.0f / vec_coordinate->at(i).x;
//                 m_y[i] = vec_coordinate->at(i).y;
//             }
//             m_pQCumstomPlot->graph(0)->setData(m_x, m_y);
//             m_pQCumstomPlot->graph(0)->rescaleAxes();
//             m_pQCumstomPlot->replot();
//         });
//         //===================== 进度条
//         QFutureWatcher<void>().setFuture(QtConcurrent::run([=]() {
//             float process = 0;
//             while (1) {
//                 this_thread::sleep_for(std::chrono::milliseconds(1000));
//                 process = m_pComputeCurve->getProcess();
//                 m_pLabel_data->setText("process = " + QString::fromStdString(std::to_string(process * 100)) + "%");
//                 if (process == 1) {
//                     break;
//                 }
//             }
//         }));
//     } catch (std::exception e) {
//         m_err = "";
//         m_err = std::string(e.what());
//     }
// }

// void MainWindow2::on_menu_aul_file_handle()
// {
//     QString file_url = QFileDialog::getOpenFileName(this, "文件选择", "", "All files(*.*)");
//     std::vector<std::vector<long double>>* result = new std::vector<std::vector<long double>>();
//     FileUtils fileUtils = FileUtils();
//     fileUtils.LoadUnHandleAul(file_url.toStdString().c_str(), result);
//     //j' j'' v' 0 v'' El Eevj Aul Fc M
//     QString path = QFileDialog::getExistingDirectory(this, "选择导出位置", nullptr, QFileDialog::ShowDirsOnly);
//     if (path.isEmpty()) {
//         return;
//     }
//     QFile file(path + "/Aul.txt");
//     file.open(QIODevice::ReadWrite);
//     for (size_t i = 0; i < result->size(); i++) {
//         std::vector<long double> value = result->at(i);
//         int j1 = value[0];
//         int j2 = value[1];
//         int v1 = value[2];
//         int v2 = value[4];
//         long double Eevj = value[6];
//         long double Aul = value[7];
//         long double Fc = value[8];
//         if (Eevj > 0) {
//             continue;
//         }
//         std::string RPQ = "";
//         if (j2 - j1 == 1) {
//             RPQ = "P(" + std::to_string(j2) + ")";
//         } else if (j2 - j1 == 0) {
//             RPQ = "Q(" + std::to_string(j2) + ")";
//         } else if (j2 - j1 == -1) {
//             RPQ = "R(" + std::to_string(j2) + ")";
//         }
//         ostringstream os1;
//         ostringstream os2;
//         os1 << v1;
//         os2 << v2;
//         std::string tmp = os1.str() + " \t " + os2.str() + " \t ";
//         ostringstream osEevj;
//         osEevj << Eevj;
//         tmp += RPQ + " \t " + osEevj.str() + " \t ";
//         ostringstream osAul;
//         ostringstream osFc;
//         osAul << Aul;
//         osFc << Fc;
//         tmp += osAul.str() + " \t " + osFc.str() + "\n";
//         file.write(tmp.c_str());
//     }
//     file.close();
// }

// void MainWindow2::on_menu_basic_shoot_export()
// {
//     QString path = QFileDialog::getExistingDirectory(this, "选择导出位置", nullptr, QFileDialog::ShowDirsOnly);
//     if (path.isEmpty()) {
//         return;
//     }
//     try {
//         QFile file_base(path + "/基准数据.txt");
//         file_base.open(QIODevice::ReadWrite);
//         std::string tmp_str = "";
//         for (size_t i = 0; i < m_pMiddleWare->m_data_vec_xmodel.size(); i++) {
//             ModelXY model_xy = m_pMiddleWare->m_data_vec_xmodel[i];
//             tmp_str = "x=" + DecimalUtils::to_string(model_xy.x) + "  "
//                 + "y=" + DecimalUtils::to_string(model_xy.y) + "  "
//                 + "\n";
//             file_base.write(tmp_str.c_str());
//         }
//         file_base.close();
//         QFile file_vigt(path + "/展宽数据.txt");
//         file_vigt.open(QIODevice::ReadWrite);
//         for (int i = 0; i < m_x.size(); i++) {
//             double x = m_x[i];
//             double y = m_y[i];
//             tmp_str = "x=" + DecimalUtils::to_string(x) + "  "
//                 + "y=" + DecimalUtils::to_string(y) + "  "
//                 + "       "
//                 + "\n";
//             file_vigt.write(tmp_str.c_str());
//         }

//         file_vigt.close();
//     } catch (QException e) {
//         m_err = "";
//         m_err = std::string(e.what());
//     }
//     //    Qt::WindowFlags windowFlags = Qt::WindowFlags();
//     //    windowFlags.setFlag(Qt::WindowMaximizeButtonHint);
//     //    windowFlags.setFlag(Qt::WindowMinimizeButtonHint);
//     //    windowFlags.setFlag(Qt::WindowCloseButtonHint);
//     //    bool ret_ok;
//     //    QString file_names = "";
//     //    for(size_t i = 0; i < m_pMiddleWare->config_vec_VJ.size(); i++){
//     //        int index =  i;
//     //        file_names += "id:";
//     //        file_names += std::to_string(index).c_str();
//     //        file_names += "\n";
//     //        file_names += "file:";
//     //        file_names += QString::fromStdString(m_pMiddleWare->config_vec_VJ[i].name).toStdString().c_str();
//     //        file_names += "\n\n";
//     //    }
//     //    file_names += "输入 低能态 高能态 文件id\n格式：0 1";
//     //    QString file_index = QInputDialog::getText(this,
//     //                                               "文件选择" ,
//     //                                               file_names,
//     //                                               QLineEdit::Normal,
//     //                                               0,
//     //                                               &ret_ok,
//     //                                               windowFlags);
//     //    QStringList file_index_list = file_index.split(" ");
//     //    if(file_index_list.size() < 2){
//     //        return;
//     //    }
//     //    int low_index = file_index_list[0].trimmed().toInt();
//     //    int up_index = file_index_list[1].trimmed().toInt();
//     //    QString v_index = QInputDialog::getText(this,
//     //                                            "输入v'-v''差值",
//     //                                            "输入v'-v''差值\n格式: -1 0 1",
//     //                                            QLineEdit::Normal,
//     //                                            0,
//     //                                            &ret_ok,
//     //                                            windowFlags);
//     //    QStringList v_index_list = v_index.split(" ");
//     //    std::vector<int> v_index_vec = std::vector<int>();
//     //    for(int i = 0; i < v_index_list.size(); i++){
//     //        v_index_vec.push_back(v_index_list[i].trimmed().toInt());
//     //    }
//     //    QString file_aul = QFileDialog::getOpenFileName(this, "Aul文件", "", "All files(*.*)");
//     //    if (file_aul.isEmpty()){
//     //        return;
//     //    }
//     //    QString path = QFileDialog::getExistingDirectory(this, "选择导出位置", nullptr, QFileDialog::ShowDirsOnly);
//     //    if (path.isEmpty()){
//     //        return;
//     //    }
//     //    QFile file1(path + "/发射数据-+1=j1-j2.txt");
//     //    file1.open(QIODevice::ReadWrite);
//     //    // plot
//     //    try {
//     //        m_pMiddleWare->compute_vj_all_Qevj();
//     //        m_pMiddleWare->compute_xmodel(1, v_index_vec, low_index, up_index, file_aul.toStdString());
//     //        //file io
//     //        std::string tmp_str = "";
//     //        for(size_t i = 0; i < m_pMiddleWare->m_data_vec_xmodel.size(); i++){
//     //            ModelXY model_xy = m_pMiddleWare->m_data_vec_xmodel[i];
//     //            tmp_str +=
//     //                    //                "g'=" + x_model.g1 + ", "
//     //                    "v'=" + DecimalUtils::to_string(model_xy.model_vj_low->v) + "  "
//     //                    + "j'=" + DecimalUtils::to_string(model_xy.model_vj_low->j) + "  "
//     ////                    + "e'=" + DecimalUtils::to_string(model_xy.model_vj_low->Eevj) + "  "
//     //                    //                    + "t'=" + DecimalUtils::to_string(model_xy.model_vj_low->configVJ->Te) + "  "
//     //                    + "       "
//     //                    //                + "g''=" + x_model.g2 + ", "
//     //                    + "v''=" + DecimalUtils::to_string(model_xy.model_vj_up->v) + "  "
//     //                    + "j''=" + DecimalUtils::to_string(model_xy.model_vj_up->j) + "  "
//     ////                    + "e''=" + DecimalUtils::to_string(model_xy.model_vj_up->Eevj) + "  "
//     //                    //                    + "t''=" + DecimalUtils::to_string(model_xy.model_vj_up->configVJ->Te) + "  "
//     //                    + "       "
//     //                    + "λul=" + DecimalUtils::to_string(model_xy.x) + "  "
//     ////                    + "y= " + DecimalUtils::to_string(model_xy.y)
//     //                    + "Aul=" + DecimalUtils::to_string(model_xy.Aul) + "  "
//     //                    //                    + "Qevjup=" + DecimalUtils::to_string(model_xy.model_vj_low->Qevj) + "  "
//     //                    //                    + "Qevjlow= " + DecimalUtils::to_string(model_xy.model_vj_up->Qevj) + "  "
//     //                    + "\n";
//     //        }
//     //        file1.write(tmp_str.c_str());
//     //        file1.close();
//     //    } catch (QException e) {
//     //        m_err = "";
//     //        m_err = std::string(e.what());
//     //    }
// }

// void MainWindow2::on_menu_basic_absorb_export()
// {
// }

// void MainWindow2::on_menu_erro_show()
// {
//     Qt::WindowFlags windowFlags = Qt::WindowFlags();
//     windowFlags.setFlag(Qt::WindowMaximizeButtonHint);
//     windowFlags.setFlag(Qt::WindowMinimizeButtonHint);
//     windowFlags.setFlag(Qt::WindowCloseButtonHint);
//     bool ret_ok;
//     if (m_err.empty()) {
//         m_err = "NULL";
//     }
//     QString err_string = "ERRO: " + QString::fromStdString(m_err);
//     QString file_index = QInputDialog::getText(this,
//         "ERRO",
//         err_string,
//         QLineEdit::Normal,
//         0,
//         &ret_ok,
//         windowFlags);
// }

// //科学计数法
// long double MainWindow2::ENumber(std::string num_str)
// {
//     long double ret_ = 0;
//     int index_E_base = 1;
//     int index_E = -1;
//     if (num_str.find("E-") != num_str.npos) {
//         index_E_base = -1;
//         index_E = num_str.find("E-");
//     } else if (num_str.find("E+") != num_str.npos) {
//         index_E_base = 1;
//         index_E = num_str.find("E+");
//     }
//     if (index_E == -1) {
//         ret_ = std::stold(num_str);
//         return ret_;
//     }
//     std::string num_a = num_str.substr(0, index_E);
//     std::string num_b = num_str.substr(index_E + 2, num_str.length() - (index_E + 2));
//     ret_ = std::stold(num_a) * (std::pow(10, index_E_base * std::stoi(num_b)));
//     return ret_;
// }

// MainWindow2::~MainWindow2()
// {
//     delete ui;
// }
