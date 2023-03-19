#ifndef _STRING_UITLS_H_
#define _STRING_UITLS_H_
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class stringutils
{
public:
    static int load_el_config(std::string fileUrl, vector<vector<string>>* target)
    {
        fstream fs = fstream();
        fs.open(fileUrl.c_str());
        // open fail
        if (!fs.is_open())
        {
            std::cerr << "err: open fail" << '\n';
            return -1;
        }
        int i = 0;
        vector<string> ss = vector<string>();
        string line = string();
        while (getline(fs, line))
        {
            try
            {
                if (line.empty())
                {
                    continue;
                }
                i++;
                ss.push_back(line);
                if (i % 2 == 0)
                {
                    target->push_back(ss);
                    ss = vector<string>();
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        fs.close();
        return 0;
    }

    static int load_el_vj(std::string fileUrl, vector<vector<string>>* target)
    {
        fstream fs = fstream();
        fs.open(fileUrl.c_str());
        // open fail
        if (!fs.is_open())
        {
            std::cerr << "err: open fail" << '\n';
            return -1;
        }
        string line = string();
        while (getline(fs, line))
        {
            try
            {
                if (line.empty())
                {
                    continue;
                }
                vector<string> t = vector<string>();
                splitSpace(line, &t);
                if (t.size() == 0)
                {
                    continue;
                }
                if (t[0].c_str()[0] < '0' || t[0].c_str()[0] > '9')
                {
                    continue;
                }
                target->push_back(t);
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        fs.close();
        return 0;
    }

    static int load_aul(std::string fileUrl, vector<vector<string>>* target)
    {
        fstream fs = fstream();
        fs.open(fileUrl.c_str());
        // open fail
        if (!fs.is_open())
        {
            std::cerr << "err: open fail" << '\n';
            return -1;
        }
        string line = string();
        while (getline(fs, line))
        {
            try
            {
                if (line.empty())
                {
                    continue;
                }
                vector<string> t = vector<string>();
                splitSpace(line, &t);
                if (t.size() == 0)
                {
                    continue;
                }
                if (t[0].c_str()[0] < '0' || t[0].c_str()[0] > '9')
                {
                    continue;
                }
                // v v PQR(n) Eevj Aul FCFs -> v j v j Aul Eevj FCFs
                vector<string> tt = vector<string>();
                string v1 = t[0];
                string v2 = t[1];
                long double j_sum = 0.0;
                if (t[2].c_str()[0] == 'R')
                {
                    j_sum = 1.0;
                }
                else if (t[2].c_str()[0] == 'Q')
                {
                    j_sum = 0.0;
                }
                else if (t[2].c_str()[0] == 'P')
                {
                    j_sum = -1.0;
                }
                string j = "";
                for (size_t i = 0; i < t[2].size(); i++)
                {
                    if (t[2].c_str()[i] >= '0' && t[2].c_str()[i] <= '9')
                    {
                        j += t[2].c_str()[i];
                    }
                }
                string j1 = std::to_string(stold(j) + j_sum);
                string j2 = std::to_string(stold(j));
                string Eevj = t[3];
                string aul = t[4];
                string fcfs = t[5];
                tt.push_back(v1);
                tt.push_back(j1);
                tt.push_back(v2);
                tt.push_back(j2);
                tt.push_back(aul);
                tt.push_back(Eevj);
                tt.push_back(fcfs);
                target->push_back(tt);
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        fs.close();
        return 0;
    }

    static int load_unhandle_aul(std::string fileUrl, vector<vector<string>>* target) {
        fstream fs = fstream();
        fs.open(fileUrl.c_str());
        // open fail
        if (!fs.is_open())
        {
            std::cerr << "err: open fail" << '\n';
            return -1;
        }
        string line = string();
        while (getline(fs, line))
        {
            try
            {
                //if startWith RQP
                bool startWidthRQP = false;
                for (size_t i = 0; i < line.size(); i++)
                {
                    if (line.at(i) == 'R' || line.at(i) == 'Q' || line.at(i) == 'P')
                    {
                        if (i + 1 < line.size())
                        {
                            if (line.at(i + 1) == '(')
                            {
                                startWidthRQP = true;
                                break;
                            }
                        }
                    }
                }
                if (!startWidthRQP)
                {
                    continue;
                }
                vector<string> vec_ss = vector<string>();
                string ss = string();
                for (size_t i = 0; i < line.size(); i++)
                {
                    char line_c = line.at(i);
                    //RQP
                    if (line_c == 'R' || line_c == 'Q' || line_c == 'P')
                    {
                        for (size_t j = i; j < line.size(); j++)
                        {
                            if (line.at(j) == '\t' || line.at(j) == ' ')
                            {
                                continue;
                            }
                            ss += line.at(j);
                            if (line.at(j) == ')')
                            {
                                i = j + 1;
                                break;
                            }
                        }
                        continue;
                    }
                    //Other
                    if (line_c == '\t' || line_c == ' ')
                    {
                        if (ss == "-")
                        {
                            ss = "";
                        }
                        else  if (!ss.empty())
                        {
                            vec_ss.push_back(ss);
                            ss = "";
                        }
                        continue;
                    }
                    if (line_c == 'D')
                    {
                        ss += "E";
                    }
                    else {
                        ss += line_c;
                    }

                }
                target->push_back(vec_ss);
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        return 0;
    }

    static void splitSpace(string spliter, vector<string>* target)
    {
        string s = string();
        for (size_t i = 0; i < spliter.size(); i++)
        {
            char c = spliter.at(i);
            if (c == '\t' || c == ' ')
            {
                if (!s.empty())
                {
                    target->push_back(s);
                    s = "";
                }
                continue;
            }
            s += c;
            if (i == spliter.size() - 1)
            {
                if (!s.empty())
                {
                    target->push_back(s);
                    s = "";
                }
            }
        }
    }
};
#endif