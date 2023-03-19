#include <mutex>
#include <cmath>
#include <thread>
#include "src/csrc/stringutils.h"
#include "src/csrc/modelspec.h"

using namespace std;
class cpfundation
{
public:
    void process_reload();
    int cp_fundation(int type, ModelArgs*, vector<vector<ModelVJ>>*, vector<ModelAul>*, vector<ModelXY>*);

    int PROCESS_POS = 0;
    int PROCESS_TOTAL = 3;

private:
    std::mutex m_mutex;

    long double cp_na(long double Tgas);

    long double cp_gj(int j, long double ge, long double go, long double g_times);
};