#include "cpfundation.h"

void cpfundation::process_reload() {
    PROCESS_POS = 0;
    PROCESS_TOTAL = 3;
}

int cpfundation::cp_fundation(int type, ModelArgs* args, vector<vector<ModelVJ>>* vec_vj_all, vector<ModelAul>* vec_aul, vector<ModelXY>* target)
{
    {
        //std::cout 日志输出
        std::remove("log_fundation.log");
        static std::ofstream g_log("log_fundation.log");
        std::cout.rdbuf(g_log.rdbuf());
    }
    std::thread thd_main([=]() {
        try
        {
            //START
            std::unique_lock<std::mutex> lock(m_mutex);
            PROCESS_POS = 0;
            lock.unlock();
            // 1.计算Qevj & Q
            long double Q = 0;
            for (size_t i = 0; i < vec_vj_all->size(); i++)
            {
                vector<ModelVJ>* vec_vj = &vec_vj_all->at(i);
                long double Gvnj0 = 0;
                long double Fv0j0 = 0;
                for (size_t j = 0; j < vec_vj->size(); j++)
                {
                    ModelVJ* model_vj = &vec_vj->at(j);
                    if (model_vj->j == 0)
                    {
                        Gvnj0 = model_vj->Eevj;
                        if (model_vj->v == 0)
                        {
                            Fv0j0 = model_vj->Eevj;
                            break;
                        }
                    }
                }
                for (size_t j = 0; j < vec_vj->size(); j++)
                {
                    ModelVJ* model_vj = &vec_vj->at(j);
                    ModelElConfig* cfig = model_vj->el_config;
                    if (model_vj->j == 0)
                    {
                        Gvnj0 = model_vj->Eevj;
                        if (model_vj->v == 0)
                        {
                            Fv0j0 = model_vj->Eevj;
                        }
                    }
                    long double Fj = model_vj->Eevj - Gvnj0; // Eevj - G(VnJ0)
                    long double Gv = Gvnj0 - Fv0j0;          // G(VnJ0) - F(V0J0)
                    long double gj = cp_gj(model_vj->j, cfig->ge, cfig->go, cfig->gtimes);
                    long double Qevj = gj * exp((-1 * (args->h * args->c * pow(10, 2) / args->k)) * ((cfig->Te / args->Tex) + (Gv / args->Tvib) + (Fj / args->Trot)));
                    model_vj->gj = gj;
                    model_vj->Qevj = Qevj;
                    Q += Qevj;
                    std::cout
                        << "v=" << model_vj->v << " "
                        << "j=" << model_vj->j << " "
                        << "Gvnj0=" << Gvnj0 << " "
                        << "Fv0j0=" << Fv0j0 << " "
                        << "Fj=" << Fj << " "
                        << "Gv=" << Gv << " "
                        << "gj=" << gj << " "
                        << "Qevj=" << Qevj << " "
                        << std::endl;
                }
            }
            lock.lock();
            PROCESS_POS++;
            lock.unlock();
            // 2.计算x
            vector<ModelVJ> vec_vj_low = vec_vj_all->at(args->el_low_index);
            vector<ModelVJ> vec_vj_up = vec_vj_all->at(args->el_up_index);
            for (size_t i = 0; i < vec_vj_low.size(); i++)
            {
                ModelVJ* model_vj_low = &vec_vj_low[i];
                for (size_t j = 0; j < vec_vj_up.size(); j++)
                {
                    ModelVJ* model_vj_up = &vec_vj_up[j];
                    for (size_t k = 0; k < args->v_differences.size(); k++)
                    {
                        int difference = args->v_differences[k];
                        if (model_vj_low->v - model_vj_up->v == difference)
                        {
                            if (model_vj_low->j - model_vj_up->j == 1 || model_vj_low->j - model_vj_up->j == -1)
                            {
                                // 2.1 对应的vj计算出x
                                ModelXY model_xy = ModelXY();
                                model_xy.model_vj_low = model_vj_low;
                                model_xy.model_vj_up = model_vj_up;
                                // model_xy.x = (model_vj_up->Eevj + model_vj_up->el_config->Te) - (model_vj_low->Eevj + model_vj_low->el_config->Te);
                                // 2.2 合并Aul
                                for (size_t z = 0; z < vec_aul->size(); z++)
                                {
                                    ModelAul* model_aul = &vec_aul->at(z);
                                    if (model_xy.model_vj_low->v == model_aul->v_low &&
                                        model_xy.model_vj_low->j == model_aul->j_low &&
                                        model_xy.model_vj_up->v == model_aul->v_up &&
                                        model_xy.model_vj_up->j == model_aul->j_up)
                                    {
                                        model_xy.Aul = model_aul->Aul;
                                        model_xy.x = -1 * model_aul->Eevj;
                                        // 2.3 进组push_back
                                        target->push_back(model_xy);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            lock.lock();
            PROCESS_POS++;
            lock.unlock();
            // 3.计算y
            long double pai = 3.1415926;
            if (type == 1)
            { // 发射系数
                for (size_t i = 0; i < target->size(); i++)
                {
                    ModelXY* model_xy = &target->at(i);
                    long double Na = cp_na(args->Tgas);
                    long double nu = Na * (model_xy->model_vj_low->Qevj / Q);
                    model_xy->y = nu * ((args->h * args->c * model_xy->Aul * model_xy->x) / (4 * pai));
                    std::cout
                        << "lowQevj=" << model_xy->model_vj_low->Qevj << " "
                        << "Q=" << Q << " "
                        << "nu=" << nu << " "
                        << "aul=" << model_xy->Aul << " "
                        << "x=" << model_xy->x << " "
                        << "y=" << model_xy->y << " "
                        << std::endl;
                }
            }
            else
            { // 吸收系数
                for (size_t i = 0; i < target->size(); i++)
                {
                    ModelXY* model_xy = &target->at(i);
                    long double Na = cp_na(args->Tgas);
                    long double nu = Na * (model_xy->model_vj_up->Qevj / Q);
                    long double nl = Na * (model_xy->model_vj_low->Qevj / Q);
                    model_xy->y = model_xy->Aul * ((nl * model_xy->model_vj_up->gj) - (nu * model_xy->model_vj_low->gj));
                    model_xy->y = model_xy->y / (8 * pai * args->c * model_xy->model_vj_low->gj * pow(model_xy->x, 4) * pow(10, 8));
                    // long double nu = Na * (model_xy->model_vj_up->Qevj / Q);
                    // long double nl = Na * (model_xy->model_vj_low->Qevj / Q);
                    // model_xy->y = model_xy->Aul * ((nl * model_xy->model_vj_low->gj) - (nu * model_xy->model_vj_up->gj));
                    // model_xy->y = model_xy->y / (8 * pai * args->c * model_xy->model_vj_up->gj * pow(model_xy->x, 4) * pow(10, 8));
                }
            }
            lock.lock();
            PROCESS_POS++;
            lock.unlock();
            //END
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return -1;
        }
        return 0;
        });
    thd_main.detach();
    std::thread thd_spleep([=]() {
        // std::unique_lock<std::mutex> lock(m_mutex);
        while (PROCESS_POS != PROCESS_TOTAL) {
            // lock.unlock();
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            // lock.lock();
        }
        // lock.unlock();
        this_thread::sleep_for(std::chrono::milliseconds(1000));
        });
    thd_spleep.join();
    return 0;
}

long double cpfundation::cp_na(long double Tgas)
{
    long double P = 1.01 * pow(10, 5);
    long double K = (1.38 * pow(10, -23));
    long double Aa = 6.02 * pow(10, 23);
    long double Na = P / (Aa * K * Tgas);
    Na = Na * Aa;
    return Na;
}

long double cpfundation::cp_gj(int j, long double ge, long double go, long double gtimes)
{
    if (j % 2 == 0)
    {
        return ge * gtimes * ((2 * j) + 1);
    }
    return go * gtimes * ((2 * j) + 1);
}