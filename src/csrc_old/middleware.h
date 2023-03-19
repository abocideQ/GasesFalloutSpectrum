// #ifndef MIDDLEWARE_H
// #define MIDDLEWARE_H

// #include <vector>
// #include <math.h>
// #include <string>
// #include <QFile>
// #include <QFileInfo>
// #include <QString>
// #include <QStringList>
// #include <QTextCodec>
// #include "core/computefundation.h"
// #include "core/computecurve.h"

// class middleware
// {
// public:
//     //REQUEST
//     long double config_CONST_H = 6.626 * pow(10, -34);//常量
//     long double config_CONST_C = 3 * pow(10,8);//常量
//     long double config_CONST_K = (1.38 * pow(10, -23));//常量
//     long double config_Tex = 0;
//     long double config_Tvib = 0;
//     long double config_Trot = 0;
//     long double config_Tgas = 0;//气体温度
//     std::vector<ConfigVJ> config_vec_VJ= std::vector<ConfigVJ>();

//     //RESULT
//     std::vector<std::vector<ModelVJ>> m_data_vj_all = std::vector<std::vector<ModelVJ>>();//vj all
//     std::vector<ModelXY> m_data_vec_xmodel = std:: vector<ModelXY>();//xmodels
// //    std::vector<ModelAul> m_data_vec_aul = std::vector<ModelAul>();//Aul
//     std::vector<ModelCoordinate> m_data_coordinate = std::vector<ModelCoordinate>();//Coordinate
//     long double m_data_Q = 0;

//     //初始化
//     void init_temperature(long double _Tex, long double _Tvib, long double _Trot, long double _Tgas);
//     void init_vj_all(std::string _config_ur);
//     void init_aul(int _low_index, int _up_index, std::string _aul_url);

//     //计算
//     //1. 解析所有VJ数据 + 计算VJ配分函数
//     void compute_vj_all_Qevj();
//     //2. 计算基准值
//     void compute_xmodel(int type, std::vector<int> _vec_v_diff, int _low_index, int _up_index, string _aul_url);
//     //3. 计算曲线值(voigt曲线展开基准值)
//     void compute_curve(float min_x, float max_x, float step, float weight);

//     //工具
//     computefundation *m_pComputefundation = new computefundation();
//     computecurve *m_pComputecurve = new computecurve();
// };

// #endif // MIDDLEWARE_H
