// #ifndef COMPUTECURVE_H
// #define COMPUTECURVE_H

// #include <windows.h>
// #include <vector>
// #include <math.h>
// #include <map>
// #include <iostream>
// #include <iomanip>
// #include <string>
// #include <future>
// #include <mutex>
// #include "XYModel.h"
// #include "DecimalUtils.h"

// class computecurve
// {
// public:
//     int m_thread_num;
//     static std::mutex m_mutex_thread;
//     //进度
//     static std::mutex m_mutex;
//     float m_process_position = 0;
//     float m_process_size = 1;
//     //voigt展宽数据
//     void computeCurveVoigt(float min_x, float max_x, float step, float weight, float Trot, vector<ModelXY> *vec_x, vector<ModelCoordinate> *ret_vec_coordinate);

//     float getProcess();
// private:
//     //voigt线性计算
//     long double coordinateVoigt(float weight, float Trot, long double center_x, long double step_x);
// };
// #endif // COMPUTECURVE_H
