// #include "computecurve.h"

// std::mutex computecurve::m_mutex_thread;
// std::mutex computecurve::m_mutex;

// void computecurve::computeCurveVoigt(float min_x, float max_x, float step, float weight, float Trot, vector<ModelXY>* vec_x, vector<ModelCoordinate>* ret_vec_coordinate)
// {
//     long double min_x_real = 9993466.0f / max_x;
//     long double max_x_real = 9993466.0f / min_x;
//     long double step_real = step * 1;
//     if (step_real > 10) {
//         step_real = 10;
//     } else if (step_real < 0.0001) {
//         step_real = 0.0001;
//     }
//     //    long double step_real = 9993466.0f / step;
//     //1. 初始化 区间内 基准x vec_x_ranged
//     vector<ModelXY> vec_xy_ranged = vector<ModelXY>();
//     for (size_t i = 0; i < vec_x->size(); i++) {
//         ModelXY* mode_xy = &vec_x->at(i);
//         long double x_tmp = mode_xy->x;
//         if (x_tmp > min_x_real && x_tmp < max_x_real) {
//             vec_xy_ranged.push_back(*mode_xy);
//         }
//     }
//     if (vec_xy_ranged.size() == 0) {
//         return;
//     }
//     //2. 初始化 区间内 所有曲线横坐标点 -> step计算 -> x = minx + n*step
//     std::map<long double, ModelCoordinate> map_coordinate = std::map<long double, ModelCoordinate>();
//     for (long double x = min_x_real; x <= max_x_real; x += step_real) {
//         ModelCoordinate coordinate = ModelCoordinate();
//         long double step_x = x;
//         coordinate.x = step_x;
//         ret_vec_coordinate->push_back(coordinate);
//     }
//     if (ret_vec_coordinate->size() == 0) {
//         return;
//     }
//     //3. 计算
//     long double RANGE = 200.0;
//     m_process_position = 0;
//     m_process_size = vec_xy_ranged.size();
//     int CPU_t = 0;
//     try {
//         SYSTEM_INFO sysInfo;
//         GetSystemInfo(&sysInfo);
//         CPU_t = sysInfo.dwNumberOfProcessors;
//     } catch (const char* msg) {
//     }
//     if (CPU_t <= 0) {
//         CPU_t = 4;
//     }
//     //展宽
//     for (size_t i = 0; i < vec_xy_ranged.size(); i++) {
//         std::unique_lock<std::mutex> thread_lock(m_mutex_thread);
//         /*if (i % 10 == 0) {
//             this_thread::sleep_for(std::chrono::milliseconds(10));
//         }*/
//         while (m_thread_num > CPU_t) {
//             thread_lock.unlock();
//             this_thread::sleep_for(std::chrono::milliseconds(10));
//             thread_lock.lock();
//         }
//         m_thread_num++;
//         //std::cout << "11thread_num" << m_thread_num << std::endl;
//         thread_lock.unlock();
//         std::thread t([=](int value) {
//             try {
//                 for (size_t j = 0; j < ret_vec_coordinate->size(); j++) {
//                     long double step_x = ret_vec_coordinate->at(j).x;
//                     long double step_y = ret_vec_coordinate->at(j).y;
//                     long double center_x = vec_xy_ranged[value].x;
//                     long double center_y = vec_xy_ranged[value].y;
//                     if (step_x - center_x < -RANGE) {
//                         continue;
//                     } else if (step_x - center_x > RANGE) {
//                         break;
//                     }
//                     long double y = (center_y * coordinateVoigt(weight, Trot, center_x, step_x));
//                     ret_vec_coordinate->at(j).y = step_y + y;
//                 }
//                 std::unique_lock<std::mutex> lock(m_mutex);
//                 m_process_position++;
//                 lock.unlock();
//             } catch (const char* msg) {
//                 std::unique_lock<std::mutex> lock(m_mutex);
//                 m_process_position++;
//                 lock.unlock();
//                 cerr << msg << endl;
//             };
//             std::unique_lock<std::mutex> thread_lock(m_mutex_thread);
//             m_thread_num--;
//             thread_lock.unlock();
//         },
//             i);
//         t.detach();
//     }
//     std::thread t([=]() {
//         while (m_process_position < m_process_size - 1) {
//             this_thread::sleep_for(std::chrono::milliseconds(1000));
//             std::cout << "sleep_for = " << m_process_position << ", " << m_process_size << std::endl;
//             continue;
//         }
//         this_thread::sleep_for(std::chrono::milliseconds(1000));
//     });
//     t.join();
// }

// float computecurve::getProcess()
// {
//     return m_process_position / m_process_size;
// }

// long double computecurve::coordinateVoigt(float weight, float Trot, long double center_x, long double step_x)
// {
//     long double fWidth_D = 2 * (5.94 * pow(10, -6)) * center_x * sqrt(Trot / 296 / weight);
//     long double fWidth_L = 2 * 1 * 0.05 * pow((296 / Trot), 0.05) * 1;
//     long double fWidth_V = (0.5346 * fWidth_L) + sqrt((0.2166 * pow(fWidth_L, 2)) + pow(fWidth_D, 2));
//     fWidth_V = 100 * fWidth_V; //扩大展宽
//     long double CSPRD = step_x - center_x;
//     if (CSPRD < 0) {
//         CSPRD *= -1;
//     }
//     long double CSPRD1 = fWidth_L / fWidth_V;
//     long double CSPRD2 = CSPRD / fWidth_V;
//     long double GV = ((1.0 - CSPRD1) * DecimalUtils::exp_(-2.772 * pow(CSPRD2, 2))) + (CSPRD1 / (1 + (4 * pow(CSPRD2, 2)))) + ((0.016 * (1 - CSPRD1) * CSPRD1) * (DecimalUtils::exp_(-0.4 * pow(CSPRD2, 2.25)) - (10 / (10 + pow(CSPRD2, 2.25)))));
//     GV /= fWidth_V * (1.065 + (0.447 * CSPRD1) + (0.058 * pow(CSPRD1, 2)));
//     //Coordinate
//     return GV;
// }
