#include "cpextend.h"

void cpextend::process_reload() {
    PROCESS_POS = 0;
    PROCESS_TOTAL = 100000;
}

int cpextend::cp_extend(ModelArgs* args, vector<ModelXY>* vec_xy_all, vector<ModelExtend>* target)
{
    {
        //std::cout 日志输出
        std::remove("log_extend.log");
        static std::ofstream g_log("log_extend.log");
        std::cout.rdbuf(g_log.rdbuf());
    }
    std::thread thd_main([=]() {
        try
        {
            //开始
            std::unique_lock<std::mutex> lock_process(m_mutex_process);
            PROCESS_POS = 0;
            lock_process.unlock();
            //转化区间
            long double range_min = 9993466.0f / args->range_max;
            long double range_max = 9993466.0f / args->range_min;
            long double step = args->step * 10;
            if (step > 10) {
                step = 10;
            }
            else if (step < 0.0001) {
                step = 0.0001;
            }
            // 1.初始化区间内model_xy
            vector<ModelXY> vec_xy = vector<ModelXY>();
            for (size_t i = 0; i < vec_xy_all->size(); i++) {
                ModelXY* mode_xy = &vec_xy_all->at(i);
                if (mode_xy->x < range_min || range_max >  range_max)
                {
                    continue;
                }
                vec_xy.push_back(*mode_xy);
            }
            if (vec_xy.size() == 0) {
                std::cout
                    << "vec_xy.size() == 0"
                    << std::endl;
                return -1;
            }
            std::cout
                << "vec_xy.size() == " << vec_xy.size()
                << std::endl;
            // 2.初始化区间内展宽坐标点
            for (long double x = range_min; x <= range_max; x += step) {
                ModelExtend model_extd = ModelExtend();
                model_extd.x = x;
                target->push_back(model_extd);
            }
            if (target->size() == 0) {
                std::cout
                    << "target->size() == 0"
                    << std::endl;
                return -1;
            }
            std::cout
                << "target->size() == " << target->size()
                << std::endl;
            // 3.计算展宽&y
            lock_process.lock();
            PROCESS_TOTAL = vec_xy.size();
            lock_process.unlock();
            long double RANGE = 200.0;
            uint8_t CPU_t = 8;
            for (size_t i = 0; i < vec_xy.size(); i++)
            {
                std::unique_lock<std::mutex> lock_thd(m_mutex_thread);
                while (m_thread_num > CPU_t) {
                    lock_thd.unlock();
                    this_thread::sleep_for(std::chrono::milliseconds(10));
                    lock_thd.lock();
                }
                m_thread_num++;
                lock_thd.unlock();
                std::thread t([=](int index) {
                    try
                    {
                        for (size_t j = 0; j < target->size(); j++) {
                            long double step_x = target->at(j).x;
                            long double step_y = target->at(j).y;
                            long double center_x = vec_xy[index].x;
                            long double center_y = vec_xy[index].y;
                            if (step_x - center_x < -RANGE) {
                                continue;
                            }
                            else if (step_x - center_x > RANGE) {
                                break;
                            }
                            long double y = (center_y * cp_voigt(args->weight, args->Trot, center_x, step_x));
                            target->at(j).y = step_y + y;
                        }
                    }
                    catch (const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    std::unique_lock<std::mutex> lock_process2(m_mutex_process);
                    PROCESS_POS++;
                    lock_process2.unlock();
                    std::unique_lock<std::mutex> lock_thd2(m_mutex_thread);
                    m_thread_num--;
                    lock_thd2.unlock();
                    }, i);
                t.detach();
            }
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
        while (PROCESS_POS != PROCESS_TOTAL) {
            this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        this_thread::sleep_for(std::chrono::milliseconds(1000));
        });
    thd_spleep.join();
    return 0;
}

long double cpextend::cp_voigt(float weight, float Trot, long double center_x, long double step_x)
{
    long double fWidth_D = 2 * (5.94 * pow(10, -6)) * center_x * sqrt(Trot / 296 / weight);
    long double fWidth_L = 2 * 1 * 0.05 * pow((296 / Trot), 0.05) * 1;
    long double fWidth_V = (0.5346 * fWidth_L) + sqrt((0.2166 * pow(fWidth_L, 2)) + pow(fWidth_D, 2));
    // 倍数*n
    fWidth_V = 30 * fWidth_V;
    long double CSPRD = step_x - center_x;
    if (CSPRD < 0) {
        CSPRD *= -1;
    }
    long double CSPRD1 = fWidth_L / fWidth_V;
    long double CSPRD2 = CSPRD / fWidth_V;
    long double GV = ((1.0 - CSPRD1) * exp(-2.772 * pow(CSPRD2, 2))) + (CSPRD1 / (1 + (4 * pow(CSPRD2, 2)))) + ((0.016 * (1 - CSPRD1) * CSPRD1) * (exp(-0.4 * pow(CSPRD2, 2.25)) - (10 / (10 + pow(CSPRD2, 2.25)))));
    GV /= fWidth_V * (1.065 + (0.447 * CSPRD1) + (0.058 * pow(CSPRD1, 2)));
    return GV;
}