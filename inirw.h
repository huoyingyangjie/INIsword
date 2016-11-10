//
// author:huoyingyangjie@163.com
//

#ifndef MOMPARE_SHFE_INIRW_H
#define MOMPARE_SHFE_INIRW_H
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <iostream>


using namespace std;


std::string &trim(std::string &s);

typedef enum SECTION_TYPE_t{
        INI_GLOBAL=0,
        INI_LOCAL=1,

}SECTION_TYPE;



typedef struct KeyValue_t{
    string key;
    string value;
}KeyValue;


typedef struct Section_t{
    string  section;
    vector<KeyValue> kv;
    SECTION_TYPE type;
}Section;



class INIsword{

public:
    INIsword(string file_name):file_name(file_name){
        int ret;
        ret=this->init();
        //add exception
        if(ret)
        {
        throw "ERROR:init failed!\n";
        }


    };
    vector<Section> getSection(string section_name);
    string getValue(Section &sc,string key);
    string getGlobalValue(string key);
    void release();
    ~INIsword(){
        release();

    };


private:
    int init();
    int readlines();
    void parse_ini();
private:

    string file_name;
    vector<string *> lines;
    vector<Section>  m_sc;

};











#endif //MOMPARE_SHFE_INIRW_H
