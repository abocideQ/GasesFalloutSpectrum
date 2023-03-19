#ifndef XYMODEL
#define XYMODEL
#include <string>
#include <vector>

using namespace std;

typedef struct model_args
{
    long double h;
    long double c;
    long double k;
    long double Tex;
    long double Tvib;
    long double Trot;
    long double Tgas;
    int el_low_index;
    int el_up_index;
    vector<int> v_differences = vector<int>();
    long double range_min;
    long double range_max;
    long double weight;
    long double step;
} ModelArgs;

typedef struct model_el_config
{
    string url;
    string name;        // 名称
    long double Te;     // 跃迁
    long double ge;     // 偶值
    long double go;     // 奇值
    long double gtimes; // 倍数
} ModelElConfig;

typedef struct model_vj
{
    ModelElConfig *el_config;
    int v;
    int j;
    long double Eevj; // 势能
    long double gj;
    long double Qevj; // 配分函数
} ModelVJ;

typedef struct model_aul // Aul
{
    int v_low;
    int j_low;
    int v_up;
    int j_up;
    long double Aul;
    long double Eevj;
} ModelAul;

typedef struct model_xy
{
    ModelVJ *model_vj_low;
    ModelVJ *model_vj_up;
    long double Aul;
    long double x;
    long double y;
} ModelXY;

typedef struct model_extend
{
    long double x = 0;
    long double y = 0;
} ModelExtend;

#endif
