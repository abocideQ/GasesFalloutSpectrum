#include <mutex>
#include <cmath>
#include <vector>
#include <thread>
#include "src/csrc/stringutils.h"
#include "src/csrc/modelspec.h"

using namespace std;
class cpextend
{
public:
    void process_reload();
    int cp_extend(ModelArgs*, vector<ModelXY>*, vector<ModelExtend>*);

    int PROCESS_POS = 0;
    int PROCESS_TOTAL = 100000;

private:
    std::mutex m_mutex_process;
    std::mutex m_mutex_thread;
    int m_thread_num;

    long double cp_voigt(float, float, long double, long double);
};
