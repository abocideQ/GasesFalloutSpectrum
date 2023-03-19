// #ifndef COMPUTEFUNDATION_H
// #define COMPUTEFUNDATION_H

// #include <iostream>
// #include <stdio.h>
// #include <math.h>
// #include <thread>
// #include <vector>
// #include <mutex>
// #include "FileUtils.h"
// #include "DecimalUtils.h"
// #include "XYModel.h"

// class computefundation
// {
// public:
//    FileUtils m_fileUtils = FileUtils();
//    static std::mutex m_mutex;
//    float m_process_position = 0;
//    float m_process_size = 1;

//    void compute_qevj(long double h, long double c, long double k,
//                      long double Tex, long double Tvib, long double Trot,
//                      std::vector<ConfigVJ> *vec_config_vj,
//                      std::vector<std::vector<ModelVJ>> *ret_vec_vj);

//    void compute_y(int type, std::vector<int> _vec_v_diff, long double Tgas, long double h, long double c,
//                   int _low_index, int _up_index, std::vector<std::vector<ModelVJ>> *vec_vj_all, string _aul_url,
//                   vector<ModelXY> *ret_vec_xy);

//    long double compute_na(long double _Tgas);

//    long double sumgj(int j, long double gne, long double gno, long double gbase);
// };

// #endif // COMPUTEFUNDATION_H
