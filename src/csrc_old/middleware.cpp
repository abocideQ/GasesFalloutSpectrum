// #include "middleware.h"

// void middleware::init_temperature(long double _Tex, long double _Tvib, long double _Trot, long double _Tgas)
// {
//     this->config_Tex = _Tex;
//     this->config_Tvib = _Tvib;
//     this->config_Trot = _Trot;
//     this->config_Tgas = _Tgas;
// }

// void middleware::init_vj_all(std::string _config_url)
// {
//     std::vector<std::vector<std::string>> configs_str = std::vector<std::vector<std::string>>();
//     FileUtils().LoadConfigFile(_config_url.c_str(), &configs_str);
//     std::vector<ConfigVJ>().swap(config_vec_VJ);
//     for (size_t i = 0; i < configs_str.size(); i++) {
//         //path (Te ge go gbase)
//         std::vector<std::string> file_info = configs_str[i];
//         //编码转换 中文路径打不开问题
//         QTextCodec *txCodec = QTextCodec::codecForName("gb2312");
//         //file
//         string url = txCodec->fromUnicode(QString::fromStdString(file_info[0])).toStdString();
// //        QFileInfo fileInfo(url.c_str());
//         string name = file_info[0];
//         //data
//         QStringList data_list = QString::fromStdString(file_info[1]).split(" ");
//         float Te = data_list[0].trimmed().toFloat();
//         int gne = data_list[1].trimmed().toInt();
//         int gno = data_list[2].trimmed().toInt();
//         int gbase = data_list[3].trimmed().toInt();
//         ConfigVJ configVJ = ConfigVJ();
//         configVJ.url = url;//地址
//         configVJ.name = name;//名称
//         configVJ.Te = Te;//跃迁
//         configVJ.gne = gne;//偶值
//         configVJ.gno = gno;//奇值
//         configVJ.gbase = gbase;//倍数
//         config_vec_VJ.push_back(configVJ);
//     }
// }

// void middleware::compute_vj_all_Qevj()
// {
//     std::vector<std::vector<ModelVJ>>().swap(m_data_vj_all);
//     std:: vector<ModelXY>().swap(m_data_vec_xmodel);
// //    std::vector<ModelAul>().swap(m_data_vec_aul);
//     std::vector<ModelCoordinate>().swap(m_data_coordinate);
//     m_data_Q = 0;
//     m_pComputefundation->compute_qevj(config_CONST_H, config_CONST_C, config_CONST_K,
//                                       config_Tex, config_Tvib, config_Trot, &config_vec_VJ, &m_data_vj_all);
// }

// void middleware::compute_xmodel(int type, std::vector<int> _vec_v_diff, int _low_index, int _up_index, string _aul_url)
// {
//     m_pComputefundation->compute_y(type, _vec_v_diff, config_Tgas, config_CONST_H, config_CONST_C,
//                                    _low_index, _up_index, &m_data_vj_all, _aul_url, &m_data_vec_xmodel);
// }

// void middleware::compute_curve(float min_x, float max_x, float step, float weight)
// {
//     m_pComputecurve->computeCurveVoigt(min_x, max_x, step, weight, config_Trot, &m_data_vec_xmodel, &m_data_coordinate);
// }
