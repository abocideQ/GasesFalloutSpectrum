// #include "computefundation.h"

// std::mutex computefundation::m_mutex;

// void computefundation::compute_qevj(long double h, long double c, long double k,
//                                     long double Tex, long double Tvib, long double Trot,
//                                     std::vector<ConfigVJ> *vec_config_vj,
//                                     std::vector<std::vector<ModelVJ>> *ret_vec_vj_all)
// {
//     //1. 解析 v j e
//     for (size_t i = 0; i < vec_config_vj->size(); i++) {
//         std::vector<ModelVJ> vec_vj = std::vector<ModelVJ>();
//         std::vector<std::vector<long double>> vec_vj_tmp = std::vector<std::vector<long double>>();
//         ConfigVJ *config = &vec_config_vj->at(i);
//         m_fileUtils.LoadVJ(config->url.data(), &vec_vj_tmp);
//         for (size_t j = 0; j<vec_vj_tmp.size(); j++) {
//             std::vector<long double> data = vec_vj_tmp[j];
//             ModelVJ model = ModelVJ();
//             model.configVJ = config;
//             model.v = data[0];
//             model.j = data[1];
//             model.Eevj = data[2];
//             vec_vj.push_back(model);
//         }
//         ret_vec_vj_all->push_back(vec_vj);
//     }
//     //2. 计算Qevj
//     for (size_t i = 0; i < ret_vec_vj_all->size(); i++) {
//         std::vector<ModelVJ> *vec_vj = &ret_vec_vj_all->at(i);
//         long double Gvnj0 = 0;
//         long double Fv0j0 = 0;
//         for (size_t j = 0; j< vec_vj->size(); j++) {
//             ModelVJ *model = &vec_vj->at(j);
//             ConfigVJ *config = model->configVJ;
//             if(model->j == 0) {
//                 Gvnj0 = model->Eevj;
//             }
//             if(model->v == 0 && model->j == 0) {
//                 Fv0j0 = model->Eevj;
//             }
//             long double Fj = model->Eevj - Gvnj0;//Eevj - G(VnJ0)
//             long double Gv = Gvnj0 - Fv0j0;//G(VnJ0) - F(V0J0)
//             long double gj = sumgj(model->j, config->gne, config->gno, config->gbase);
//             long double Qevj = gj * DecimalUtils::exp_((-1 * (h * c * pow(10, 2) / k)) * ((config->Te / Tex) + (Gv / Tvib) + (Fj / Trot)));
//             model->gj = gj;
//             model->Qevj = Qevj;
//         }
//     }
// }

// void computefundation::compute_y(int type, std::vector<int> _vec_v_diff, long double Tgas, long double h, long double c,
//                                  int _low_index, int _up_index, std::vector<std::vector<ModelVJ>> *vec_vj_all, string _aul_url,
//                                  vector<ModelXY> *ret_vec_xy)
// {
//     bool reset_x_by_aul_file = true;
//     //1. 计算 x
//     vector<ModelVJ> vec_vj_low = vec_vj_all->at(_low_index);
//     vector<ModelVJ> vec_vj_up = vec_vj_all->at(_up_index);
//     for (size_t i = 0; i < vec_vj_low.size(); i++) {
//         ModelVJ *vj_low = &vec_vj_low[i];
//         for (size_t j = 0; j < vec_vj_up.size(); j++) {
//             ModelVJ *vj_up = &vec_vj_up[j];
//             for (size_t k = 0; k < _vec_v_diff.size(); k++) {
//                 int tmp = _vec_v_diff[k];
//                 if(vj_up->v - vj_low->v == tmp){
//                     if(vj_up->j - vj_low->j == 1 || vj_up->j - vj_low->j == -1){
//                         ModelXY model_xy = ModelXY();
//                         model_xy.model_vj_low = vj_low;
//                         model_xy.model_vj_up = vj_up;
//                         if(!reset_x_by_aul_file){
//                             model_xy.x = (vj_up->Eevj + vj_up->configVJ->Te) - (vj_low->Eevj + vj_low->configVJ->Te);
//                         }
//                         ret_vec_xy->push_back(model_xy);
//                     }
//                 }
//             }
//         }
//     }
//     //2. 解析Au -> 合并Aul x
//     std::vector<std::vector<long double>> vec_aul = std::vector<std::vector<long double>>();
//     m_fileUtils.LoadAul(_aul_url.data(), &vec_aul);
//     m_process_position = 0;
//     m_process_size = ret_vec_xy->size();
//     int RANGE = m_process_size / 4;
//     size_t loop = -RANGE;
//     size_t end = 0;
//     while (end < ret_vec_xy->size()) {
//         loop += RANGE;
//         end = loop + RANGE;
//         if(end > ret_vec_xy->size()){
//             end = ret_vec_xy->size();
//         }
//         std::thread t([=](){
//             for (size_t i = loop; i < end; i++) {
//                 try {
//                     ModelXY *model_xy = &ret_vec_xy->at(i);
//                     for (size_t j = 0; j < vec_aul.size(); j++) {
//                         //v1 j1 v2 j2 aul
//                         std::vector<long double> aul = vec_aul[j];
//                         int aul_low_v = aul[0];
//                         int aul_low_j = aul[1];
//                         int aul_up_v = aul[2];
//                         int aul_up_j = aul[3];
//                         long double Aul = aul[4];
//                         long double Eevj = aul[5];
//                         if(model_xy->model_vj_low->v == aul_low_v &&
//                                 model_xy->model_vj_low->j  == aul_low_j &&
//                                 model_xy->model_vj_up->v  == aul_up_v &&
//                                 model_xy->model_vj_up->j  == aul_up_j){
//                             model_xy->Aul = Aul;
//                             if(reset_x_by_aul_file){
//                                 model_xy->x = -1 * Eevj;
//                             }
//                             break;
//                         }
//                     }
//                     std::unique_lock<std::mutex> lock(m_mutex);
//                     m_process_position ++;
//                     lock.unlock();
//                 } catch (const char* msg) {
//                     std::unique_lock<std::mutex> lock(m_mutex);
//                     m_process_position++;
//                     lock.unlock();
//                     cerr << msg << endl;
//                 }
//             }
//         });
//         t.detach();
//     }
//     std::thread t([=](){
//         while(m_process_position < m_process_size - 1){
//             this_thread::sleep_for(std::chrono::milliseconds(1000));
//             std::cout << "sleep_for = " << m_process_position << ", " << m_process_size << std::endl;
//             continue;
//         }
//         this_thread::sleep_for(std::chrono::milliseconds(1000));
//     });
//     t.join();
//     //3. 计算y
//     long double Q = 0;
//     for (size_t i = 0; i < vec_vj_all->size(); i++) {
//         std::vector<ModelVJ> vec_vj = vec_vj_all->at(i);
//         for (size_t j = 0; j< vec_vj.size(); j++) {
//             ModelVJ *model_vj = &vec_vj[j];
//             Q += model_vj->Qevj;
//         }
//     }
//     long double pai = 3.1415926;
//     if(type == 1){//发射系数
//         for(size_t i = 0; i < ret_vec_xy->size(); i++){
//             ModelXY *model_xy = &ret_vec_xy->at(i);
//             long double Na = compute_na(Tgas);
//             long double nu = Na * (model_xy->model_vj_low->Qevj / Q);
//             model_xy->y = nu * ((h * c * model_xy->Aul * model_xy->x) / (4 * pai));
//         }
//     }else{//吸收系数
//         for(size_t i = 0; i < ret_vec_xy->size(); i++){
//             ModelXY *model_xy = &ret_vec_xy->at(i);
//             long double Na = compute_na(Tgas);
//             long double nu = Na * (model_xy->model_vj_up->Qevj / Q);
//             long double nl = Na * (model_xy->model_vj_low->Qevj / Q);
//             //            long double Bul = (model_xy->Aul * pow(model_xy->x, 3)) / (8 * pai * h);
//             //            long double Blu = Bul * (model_xy->model_vj_up->gj / model_xy->model_vj_low->gj);
//             //            long double tmp = (nl * Blu) - (nu * Bul);
//             model_xy->y = model_xy->Aul * ((nl * model_xy->model_vj_up->gj) - (nu * model_xy->model_vj_low->gj));
//             model_xy->y = model_xy->y / (8 * pai * c * model_xy->model_vj_low->gj * pow(model_xy->x, 4) * pow(10, 8));
//         }
//     }
// }

// long double computefundation::compute_na(long double _Tgas)
// {
//     long double P = 1.01 * pow(10, 5);
//     long double K = (1.38 * pow(10, -23));
//     long double Aa = 6.02 * pow(10, 23);
//     long double Na = P / (Aa * K * _Tgas);
//     Na = Na * Aa;
//     return Na;
// }

// long double computefundation::sumgj(int j, long double gne, long double gno, long double gbase)
// {
//     if (DecimalUtils::even_(j)){   //偶
//         return gne * gbase * ((2 * j) + 1);
//     }else{
//         return gno * gbase * ((2 * j) + 1);
//     }
// }
