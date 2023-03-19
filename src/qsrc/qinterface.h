#include <QJsonObject>
#include <QMessageBox>
#include <QStringList>
#include <QTextCodec>
#include <QVector>
#include <QException>
#include <QDebug>
#include <QString>
#include "src/csrc/cpfundation.h"
#include "src/csrc/cpextend.h"

class qinterface
{
public:
    int init_config(string url);
    int init_aul(string url);
    int cp_fundation(int type, QJsonObject jsonObject);
    int cp_extend(int type, QJsonObject jsonObject);
    QJsonObject getArgs();
    float get_process(int type);
    int ex_unhandle_aul(string url, vector<vector<string>>* target);

    QVector<double> m_x = QVector<double>();
    QVector<double> m_y = QVector<double>();

    int erro = 0;
private:
    // Source
    QJsonObject m_src_json_params = QJsonObject();
    vector<vector<string>> m_src_vec_elConfig = vector<vector<string>>();
    vector<vector<string>> m_src_vec_aul = vector<vector<string>>();
    // Model
    ModelArgs m_modelArgs = ModelArgs();
    vector<ModelElConfig> m_vec_elConfig = vector<ModelElConfig>();
    vector<vector<ModelVJ>> m_vec_vj_all = vector<vector<ModelVJ>>();
    vector<ModelAul> m_vec_aul = vector<ModelAul>();
    // cp
    cpfundation* mp_cpfundation = new cpfundation();
    vector<ModelXY> m_out_vec_xy = vector<ModelXY>();
    cpextend* mp_extend = new cpextend();
    vector<ModelExtend> m_out_vec_extd = vector<ModelExtend>();
};