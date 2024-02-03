#include "qinterface.h"

/**
 * -1.erro: file load fail
 * -2.erro: model init fail
 * -3.erro: compute fail
 */
int ERRO_CODE[3]{ -1, -2, -3 };

int qinterface::init_config(string url)
{
    //clear
    vector<vector<string>>().swap(m_src_vec_elConfig);
    vector<ModelElConfig>().swap(m_vec_elConfig);
    vector<vector<ModelVJ>>().swap(m_vec_vj_all);
    //load
    int err = stringutils::load_el_config(url, &m_src_vec_elConfig);
    if (err < 0)
    {
        return ERRO_CODE[0];
    }
    try
    {
        // init Model(elConfigs)
        for (size_t i = 0; i < m_src_vec_elConfig.size(); i++)
        {
            ModelElConfig config = ModelElConfig();
            config.url = QTextCodec::codecForName("gbk")->fromUnicode(QString::fromStdString(m_src_vec_elConfig[i][0])).toStdString();
            config.name = config.url;
            vector<string> sp = vector<string>();
            stringutils::splitSpace(m_src_vec_elConfig[i][1], &sp);
            config.Te = std::stold(sp[0]);
            config.ge = std::stold(sp[1]);
            config.go = std::stold(sp[2]);
            config.gtimes = std::stold(sp[3]);
            m_vec_elConfig.push_back(config);
        }
        // init Model(VJ ALL)
        for (size_t i = 0; i < m_vec_elConfig.size(); i++)
        {
            ModelElConfig* config = &m_vec_elConfig[i];
            vector<vector<string>> vec_src_vjs_tmp = vector<vector<string>>();
            int err = stringutils::load_el_vj(config->url, &vec_src_vjs_tmp);
            if (err < 0)
            {
                return ERRO_CODE[0];
            }
            vector<ModelVJ> vec_vjs_tmp = vector<ModelVJ>();
            for (size_t j = 0; j < vec_src_vjs_tmp.size(); j++)
            {
                vector<string> vj = vec_src_vjs_tmp[j];
                ModelVJ modeVJ = ModelVJ();
                modeVJ.el_config = config;
                modeVJ.v = std::stoi(vj[0]);
                modeVJ.j = std::stoi(vj[1]);
                modeVJ.Eevj = std::stold(vj[2]);
                vec_vjs_tmp.push_back(modeVJ);
            }
            m_vec_vj_all.push_back(vec_vjs_tmp);
        }
    }
    catch (QException& e)
    {
        std::cerr << e.what() << '\n';
        return ERRO_CODE[1];
    }
    return 0;
}

int qinterface::init_aul(string url)
{
    //clear
    vector<vector<string>>().swap(m_src_vec_aul);
    vector<ModelAul>().swap(m_vec_aul);
    //load
    int err = stringutils::load_aul(url, &m_src_vec_aul);
    if (err < 0)
    {
        return ERRO_CODE[0];
    }
    try
    {
        // init Model(Aul)
        for (size_t i = 0; i < m_src_vec_aul.size(); i++)
        {
            ModelAul modelAul = ModelAul();
            // modelAul.v_up = std::stoi(m_src_vec_aul[i][0]);
            // modelAul.j_up = std::stoi(m_src_vec_aul[i][1]);
            // modelAul.v_low = std::stoi(m_src_vec_aul[i][2]);
            // modelAul.j_low = std::stoi(m_src_vec_aul[i][3]);
            modelAul.v_low = std::stoi(m_src_vec_aul[i][0]);
            modelAul.j_low = std::stoi(m_src_vec_aul[i][1]);
            modelAul.v_up = std::stoi(m_src_vec_aul[i][2]);
            modelAul.j_up = std::stoi(m_src_vec_aul[i][3]);
            modelAul.Aul = std::stold(m_src_vec_aul[i][4]);
            modelAul.Eevj = std::stold(m_src_vec_aul[i][5]);
            m_vec_aul.push_back(modelAul);
        }
    }
    catch (QException& e)
    {
        std::cerr << e.what() << '\n';
        return ERRO_CODE[1];
    }
    return 0;
}

int qinterface::cp_fundation(int type, QJsonObject jsonObject)
{
    if (m_src_vec_elConfig.size() == 0 || m_src_vec_aul.size() == 0)
    {
        return ERRO_CODE[0];
    }
    try
    {
        //clear
        mp_cpfundation->process_reload();
        vector<ModelXY>().swap(m_out_vec_xy);
        // init args
        m_src_json_params = QJsonObject(jsonObject);
        m_modelArgs.Tex = m_src_json_params.value("Tex").toDouble();
        m_modelArgs.Tvib = m_src_json_params.value("Tvib").toDouble();
        m_modelArgs.Trot = m_src_json_params.value("Trot").toDouble();
        m_modelArgs.Tgas = m_src_json_params.value("Tgas").toDouble();
        m_modelArgs.el_up_index = m_src_json_params.value("el_up_index").toInt();
        m_modelArgs.el_low_index = m_src_json_params.value("el_low_index").toInt();
        vector<int>().swap(m_modelArgs.v_differences);
        QStringList v_differences = m_src_json_params.value("v_differences").toString().split(",");
        for (size_t i = 0; i < v_differences.size(); i++)
        {
            m_modelArgs.v_differences.push_back(v_differences[i].toInt());
        }
        m_modelArgs.range_min = m_src_json_params.value("range_min").toDouble();
        m_modelArgs.range_max = m_src_json_params.value("range_max").toDouble();
        m_modelArgs.weight = m_src_json_params.value("weight").toDouble();
        m_modelArgs.step = m_src_json_params.value("step").toDouble();
        m_modelArgs.h = 6.626 * pow(10, -34);
        m_modelArgs.c = 3 * pow(10, 10);
        m_modelArgs.k = (1.38 * pow(10, -23));
        // cp
        int err = mp_cpfundation->cp_fundation(type, &m_modelArgs, &m_vec_vj_all, &m_vec_aul, &m_out_vec_xy);
        if (err < 0)
        {
            return ERRO_CODE[2];
        }
        // insert to vec_x vec_y
        QVector<double>().swap(m_x);
        QVector<double>().swap(m_y);
        m_x = QVector<double>(m_out_vec_xy.size());
        m_y = QVector<double>(m_out_vec_xy.size());
        for (size_t i = 0; i < m_out_vec_xy.size(); i++)
        {
            if (m_out_vec_xy[i].x == 0)
            {
                m_x[i] = 0;
            }
            else
            {
                m_x[i] = 9993466.0f / m_out_vec_xy[i].x;
                // m_x[i] = m_out_vec_xy[i].x
            }
            m_y[i] = m_out_vec_xy[i].y;
        }
    }
    catch (QException& e)
    {
        std::cerr << e.what() << '\n';
        return ERRO_CODE[1];
    }
    return 0;
}

int qinterface::cp_extend(int type, QJsonObject jsonObject)
{
    if (m_src_vec_elConfig.size() == 0 || m_src_vec_aul.size() == 0)
    {
        return ERRO_CODE[0];
    }
    try
    {
        //clear
        mp_cpfundation->process_reload();
        mp_extend->process_reload();
        vector<ModelXY>().swap(m_out_vec_xy);
        vector<ModelExtend>().swap(m_out_vec_extd);
        // init args
        m_src_json_params = QJsonObject(jsonObject);
        m_modelArgs.Tex = m_src_json_params.value("Tex").toDouble();
        m_modelArgs.Tvib = m_src_json_params.value("Tvib").toDouble();
        m_modelArgs.Trot = m_src_json_params.value("Trot").toDouble();
        m_modelArgs.Tgas = m_src_json_params.value("Tgas").toDouble();
        m_modelArgs.el_up_index = m_src_json_params.value("el_up_index").toInt();
        m_modelArgs.el_low_index = m_src_json_params.value("el_low_index").toInt();
        vector<int>().swap(m_modelArgs.v_differences);
        QStringList v_differences = m_src_json_params.value("v_differences").toString().split(",");
        for (size_t i = 0; i < v_differences.size(); i++)
        {
            m_modelArgs.v_differences.push_back(v_differences[i].toInt());
        }
        m_modelArgs.range_min = m_src_json_params.value("range_min").toDouble();
        m_modelArgs.range_max = m_src_json_params.value("range_max").toDouble();
        m_modelArgs.weight = m_src_json_params.value("weight").toDouble();
        m_modelArgs.step = m_src_json_params.value("step").toDouble();
        m_modelArgs.h = 6.626 * pow(10, -34);
        m_modelArgs.c = 3 * pow(10, 10);
        m_modelArgs.k = (1.38 * pow(10, -23));
        // cp fundation
        int err = mp_cpfundation->cp_fundation(type, &m_modelArgs, &m_vec_vj_all, &m_vec_aul, &m_out_vec_xy);
        if (err < 0)
        {
            return ERRO_CODE[2];
        }
        // cp extend
        err = mp_extend->cp_extend(&m_modelArgs, &m_out_vec_xy, &m_out_vec_extd);
        if (err < 0)
        {
            return ERRO_CODE[2];
        }
        // insert to vec_x vec_y
        QVector<double>().swap(m_x);
        QVector<double>().swap(m_y);
        m_x = QVector<double>(m_out_vec_extd.size());
        m_y = QVector<double>(m_out_vec_extd.size());
        for (size_t i = 0; i < m_out_vec_extd.size(); i++)
        {
            if (m_out_vec_extd[i].x == 0)
            {
                m_x[i] = 0;
            }
            else
            {
                m_x[i] = 9993466.0f / m_out_vec_extd[i].x;
                // m_x[i] = m_out_vec_xy[i].x
            }
            m_y[i] = m_out_vec_extd[i].y;
        }
    }
    catch (QException& e)
    {
        std::cerr << e.what() << '\n';
        return ERRO_CODE[1];
    }
    return 0;
}

QJsonObject qinterface::getArgs()
{
    if (m_src_json_params.isEmpty())
    {
        m_src_json_params.insert("Tex", 1000);
        m_src_json_params.insert("Tvib", 8500);
        m_src_json_params.insert("Trot", 1500);
        m_src_json_params.insert("Tgas", 8500);
        m_src_json_params.insert("el_low_index", 1);
        m_src_json_params.insert("el_up_index", 2);
        m_src_json_params.insert("v_differences", "0,1,2,3,4,5");
        m_src_json_params.insert("range_min", 500);
        m_src_json_params.insert("range_max", 1100);
        m_src_json_params.insert("weight", 28);
        m_src_json_params.insert("step", 0.1);
    }
    return m_src_json_params;
}

float qinterface::get_process(int type)
{
    float numerator = 0.0;
    float denominator = 0.0;
    if (type == 1)
    {
        numerator = mp_cpfundation->PROCESS_POS + 0.0;
        denominator = mp_cpfundation->PROCESS_TOTAL + 0.0;
    }
    else
    {
        numerator = mp_cpfundation->PROCESS_POS + 0.0 + mp_extend->PROCESS_POS + 0.0;
        denominator = mp_cpfundation->PROCESS_TOTAL + 0.0 + mp_extend->PROCESS_TOTAL + 0.0;
    }
    return numerator / denominator;
}

int qinterface::ex_unhandle_aul(string fileUrl, vector<vector<string>>* target) {
    return stringutils::load_unhandle_aul(fileUrl, target);
}
