
// #include <fstream>
// #include <iostream>
// #include <math.h>
// #include <string>
// #include <vector>

// #ifndef _BASESFILEUTILS_H_
// #define _BASESFILEUTILS_H_
// class FileUtils {
// public:
//     std::string erro;

//     void LoadConfigFile(const char* pUrl, std::vector<std::vector<std::string>>* ret_)
//     {
//         //url (Te ge go gbase)
//         std::ifstream ifs;
//         ifs.open(pUrl);
//         if (!ifs.is_open()) {
//             erro += "congif open err " + std::string(pUrl) + "\n\n";
//             printf("err open err \n");
//         }
//         int index = 1; //每2行为一个循环(path) (Te ge go base)
//         std::vector<std::string> vec_str = std::vector<std::string>();
//         std::string str_buffer;
//         while (getline(ifs, str_buffer)) {
//             if (str_buffer.empty()) {
//                 continue;
//             }
//             vec_str.push_back(str_buffer);
//             index++;
//             if (index > 2) {
//                 ret_->push_back(vec_str);
//                 vec_str = std::vector<std::string>();
//                 index = 1;
//             }
//         }
//         ifs.close();
//     }

//     void LoadVJ(const char* pUrl, std::vector<std::vector<long double>>* ret_)
//     {
//         //v j e
//         std::ifstream ifs;
//         ifs.open(pUrl);
//         if (!ifs.is_open()) {
//             erro += "vj open err " + std::string(pUrl);
//             printf("err open err \n");
//         }
//         std::string str_buffer;
//         while (getline(ifs, str_buffer)) {
//             ret_->push_back(VJObtain((char*)str_buffer.data()));
//         }
//         ifs.close();
//     }

//     void LoadAul(const char* pUrl, std::vector<std::vector<long double>>* ret_)
//     {
//         std::ifstream ifs;
//         ifs.open(pUrl);
//         if (!ifs.is_open()) {
//             erro += "aul open err " + std::string(pUrl);
//             printf("err open err \n");
//         }
//         std::string str_buffer;
//         while (getline(ifs, str_buffer)) {
//             char* data = (char*)str_buffer.data();
//             if ((data[0] < '0' || data[0] > '9')) {
//                 continue;
//             }
//             ret_->push_back(AulObtain(data));
//         }
//         ifs.close();
//     }

//     void LoadUnHandleAul(const char* pUrl, std::vector<std::vector<long double>>* ret_)
//     {
//         std::ifstream ifs;
//         ifs.open(pUrl);
//         if (!ifs.is_open()) {
//             erro += "aul open err " + std::string(pUrl);
//             printf("err open err \n");
//         }
//         std::string str_buffer;
//         while (getline(ifs, str_buffer)) {
//             char* data = (char*)str_buffer.data();
//             if (data[0] == ' ') {
//                 if (data[1] != 'R' && data[1] != 'Q' && data[1] != 'P' && data[1] != '(') {
//                     continue;
//                 }
//             } else if (data[0] != 'R' && data[0] != 'Q' && data[0] != 'P' && data[0] != '(') {
//                 continue;
//             }
//             ret_->push_back(UnHandleAulObtain(data));
//         }
//         ifs.close();
//     }

// private:
//     std::vector<long double> VJObtain(char* content)
//     {
//         std::vector<long double> ret_;
//         std::string tmp_str = "";
//         int i = 0;
//         while (1) {
//             char tmp_c = content[i];
//             if (tmp_c == '\0') { //行结尾
//                 if (!tmp_str.empty()) { //Eevj
//                     // std::cout << tmp_str << " ";
//                     long double tmp_float = std::stof(tmp_str);
//                     ret_.push_back(tmp_float);
//                     tmp_str = "";
//                 }
//                 goto __Exit;
//             } else if ((tmp_c >= '0' && tmp_c <= '9') || tmp_c == '.' || tmp_c == '-' || tmp_c == '+') { //数值
//                 tmp_str += tmp_c;
//             } else if (!tmp_str.empty()) { //V或J
//                 // std::cout << tmp_str << " ";
//                 long double tmp_float = std::stof(tmp_str);
//                 ret_.push_back(tmp_float);
//                 tmp_str = "";
//             }
//             i++;
//             continue;
//         }
//     __Exit:
//         return ret_;
//     }

//     std::vector<long double> AulObtain(char* line)
//     {
//         std::vector<long double> ret_ = std::vector<long double>(7);
//         int ret_index = 0;
//         std::string tmp_str = "";
//         int i = 0;
//         while (1) {
//             char tmp_c = line[i];
//             if (tmp_c == 'R' || tmp_c == 'Q' || tmp_c == 'P') {
//                 tmp_str = "";
//                 float diff = 0.0;
//                 if (tmp_c == 'R') {
//                     diff = 1.0;
//                 } else if (tmp_c == 'Q') {
//                     diff = 0.0;
//                 } else if (tmp_c == 'P') {
//                     diff = -1.0;
//                 }
//                 while (1) {
//                     tmp_c = line[i];
//                     if (tmp_c == ')') {
//                         long double tmp_float = std::stold(tmp_str); //v'v''j'j''
//                         ret_[ret_index] = tmp_float + diff; //j'
//                         ret_index++;
//                         ret_[ret_index] = tmp_float; //j''
//                         ret_index++;
//                         tmp_str = "";
//                         if (line[i + 1] == '\t' || line[i + 1] == ' ') {
//                             i++;
//                         }
//                         goto __CONN;
//                     } else if (tmp_c >= '0' && tmp_c <= '9') {
//                         tmp_str += tmp_c;
//                     }
//                     i++;
//                 }
//             } else if ((tmp_c >= '0' && tmp_c <= '9') || tmp_c == '.' || tmp_c == 'E' || tmp_c == '+' || tmp_c == '-') {
//                 tmp_str += tmp_c;
//             } else if (tmp_c == '\t' || tmp_c == ' ' || tmp_c == '\0') { //空格/tab
//                 if (tmp_str.empty()) {
//                     goto __CONN;
//                 }
//                 if (tmp_str.find("E") != std::string::npos && tmp_str.find("+") != std::string::npos) {
//                     long double tmp_float1 = std::stold(tmp_str.substr(0, tmp_str.find("E")));
//                     long double tmp_float2 = std::stold(tmp_str.substr(tmp_str.find("+")));
//                     long double tmp_float3 = tmp_float1 * pow(10, tmp_float2);
//                     ret_[ret_index] = tmp_float3;
//                 } else if (tmp_str.find("E") != std::string::npos && tmp_str.find("-") != std::string::npos) {
//                     long double tmp_float1 = std::stold(tmp_str.substr(0, tmp_str.find("E")));
//                     long double tmp_float2 = std::stold(tmp_str.substr(tmp_str.find("-")));
//                     long double tmp_float3 = tmp_float1 * pow(10, tmp_float2);
//                     ret_[ret_index] = tmp_float3;
//                 } else {
//                     long double tmp_float = std::stold(tmp_str);
//                     ret_[ret_index] = tmp_float;
//                 }
//                 ret_index++;
//                 tmp_str = "";
//                 if (tmp_c == '\0') {
//                     goto __Exit;
//                 }
//                 goto __CONN;
//             }
//         __CONN:
//             i++;
//             continue;
//         }
//     __Exit:
//         long double v1 = ret_[0];
//         long double v2 = ret_[1];
//         long double j1 = ret_[2];
//         long double j2 = ret_[3];
//         long double eevj = ret_[4];
//         long double aul = ret_[5];
//         //v''v'j''j' -> v'j'v''j''
//         //Eevj Aul FCFs -> Aul Eevj FCFs
//         ret_[0] = v2;
//         ret_[1] = j2;
//         ret_[2] = v1;
//         ret_[3] = j1;
//         ret_[4] = aul;
//         ret_[5] = eevj;
//         return ret_;
//     }

//     std::vector<long double> UnHandleAulObtain(char* line)
//     {
//         std::vector<long double> ret_ = std::vector<long double>(12);
//         int ret_index = 0;
//         std::string tmp_str = "";
//         int i = 0;
//         while (1) {
//             char tmp_c = line[i];
//             if (tmp_c == 'R' || tmp_c == 'Q' || tmp_c == 'P') {
//                 tmp_str = "";
//                 float diff = 0.0;
//                 if (tmp_c == 'R') {
//                     diff = 1.0;
//                 } else if (tmp_c == 'Q') {
//                     diff = 0.0;
//                 } else if (tmp_c == 'P') {
//                     diff = -1.0;
//                 }
//                 while (1) {
//                     tmp_c = line[i];
//                     if (tmp_c == ')') {
//                         long double tmp_float = std::stold(tmp_str); //v'v''j'j''
//                         ret_[ret_index] = tmp_float + diff; //j'
//                         ret_index++;
//                         ret_[ret_index] = tmp_float; //j''
//                         ret_index++;
//                         tmp_str = "";
//                         if (line[i + 1] == '\t' || line[i + 1] == ' ') {
//                             i++;
//                         }
//                         goto __CONN;
//                     } else if (tmp_c >= '0' && tmp_c <= '9') {
//                         tmp_str += tmp_c;
//                     }
//                     i++;
//                 }
//             } else if ((tmp_c >= '0' && tmp_c <= '9') || tmp_c == '.' || tmp_c == 'D' || tmp_c == '+' || tmp_c == '-') {
//                 tmp_str += tmp_c;
//             } else if (tmp_c == '\t' || tmp_c == ' ' || tmp_c == '\0') { //空格/tab
//                 if (tmp_str.empty()) {
//                     goto __CONN;
//                 }
//                 if (tmp_str.find("D") != std::string::npos && tmp_str.find("+") != std::string::npos) {
//                     long double tmp_float1 = std::stold(tmp_str.substr(0, tmp_str.find("D")));
//                     long double tmp_float2 = std::stold(tmp_str.substr(tmp_str.find("+")));
//                     long double tmp_float3 = tmp_float1 * pow(10, tmp_float2);
//                     ret_[ret_index] = tmp_float3;
//                 } else if (tmp_str.find("D") != std::string::npos && tmp_str.find("-") != std::string::npos) {
//                     long double tmp_float1 = std::stold(tmp_str.substr(0, tmp_str.find("D")));
//                     long double tmp_float2 = std::stold(tmp_str.substr(tmp_str.find("-")));
//                     long double tmp_float3 = tmp_float1 * pow(10, tmp_float2);
//                     ret_[ret_index] = tmp_float3;
//                 } else if (tmp_str == "-") {

//                 } else {
//                     long double tmp_float = std::stold(tmp_str);
//                     ret_[ret_index] = tmp_float;
//                 }
//                 ret_index++;
//                 tmp_str = "";
//                 if (tmp_c == '\0') {
//                     goto __Exit;
//                 }
//                 goto __CONN;
//             }
//         __CONN:
//             i++;
//             continue;
//         }
//     __Exit:
//         //j' j'' v' 0 v'' El Eevj Aul Fc M
//         return ret_;
//     }
// };
// #endif
