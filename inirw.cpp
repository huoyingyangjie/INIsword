//author:huoyingyangjie@163.com

#include "inirw.h"
// trim from start
  std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
  std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
  std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

//split

  vector<string> split(const string &s,char delimiter){
    int size=s.size();
    string token="";
    vector<string> tokens;

    for(int i=0;i<size;i++){
        if(s[i]!=delimiter)
        {
            token+=s[i];
            continue;
        }
        tokens.push_back(trim(token));
        if(i+1<size) {
            string sTmp = s.substr(i + 1, size - i - 1);
            tokens.push_back(trim(sTmp));
        }
        else
            tokens.push_back("");
        return tokens;

    }

      tokens.push_back(trim(token));
      tokens.push_back("");
      return tokens;

  }


void INIsword::release(){
    vector<string *>::iterator iter;
    for(iter=lines.begin();iter!=lines.end();iter++)
    {
       delete *iter;
    }

}


int INIsword::readlines(){


    int ret;
    int  f=open(file_name.c_str(),O_RDONLY);
    if(f<0){
        printf("ERROR: open %s failed!\n",file_name.c_str());
        return -1;
    }
    string * line=new string("");
    char file_char=0;

    while(1){

        ret=read(f,&file_char,1);

        if(ret!=1){
            return 0;
        }

        if(file_char!='\n') {
            *line += file_char;
            continue;
        }

        this->lines.push_back(line);
        line=new string("");

    }




}
void INIsword::parse_ini(){
    //trim
    vector<string *>::iterator iter;
    Section current_sc;
    current_sc.type=INI_GLOBAL;
    current_sc.section="";
    for(iter=lines.begin();iter!=lines.end();iter++)
    {
        string &current_line=trim((**iter));

        if(current_line.empty())
            continue;



        //section
        if((**iter)[0]=='[' && (**iter)[(**iter).size()-1]==']'){

            current_sc.type=INI_LOCAL;
            if(current_line.size()>2) {
                current_sc.section = (**iter).substr(1, (**iter).size() - 2);
                current_sc.section = trim(current_sc.section);
            }
            else
                current_sc.section="";
            m_sc.push_back(current_sc);
            continue;

        }

        if(current_sc.type==INI_GLOBAL)
            m_sc.push_back(current_sc);

        //key=name
        vector<string> tokens=split(current_line,'=');
        KeyValue kv= {
                .key=tokens[0],
                .value=tokens[1]
        };


        m_sc[m_sc.size()-1].kv.push_back(kv);

    }





}

vector<Section> INIsword::getSection(string section_name){

    vector<Section>::iterator iter;
    vector<Section> tmp;
    for(iter=m_sc.begin();iter!=m_sc.end();iter++)
    {
        if((*iter).type==INI_GLOBAL)
            continue;

       if( (*iter).section.compare(section_name)==0 ){

            tmp.push_back(*iter);
       }

    }

    return tmp;

}

string INIsword::getValue(Section &sc,string key){
    vector<KeyValue>::iterator iter;
    for(iter=sc.kv.begin();iter!=sc.kv.end();iter++){


       if( (*iter).key.compare(key)==0)
           return (*iter).value;

    }
    return "";

}

string INIsword::getGlobalValue(string key){

    vector<Section>::iterator iter;

    for(iter=m_sc.begin();iter!=m_sc.end();iter++)
    {


        if((*iter).type==INI_LOCAL)
            continue;


        vector<KeyValue>::iterator iter_kv;

        for(iter_kv=(*iter).kv.begin();iter_kv!=(*iter).kv.end();iter_kv++){


            if( (*iter_kv).key.compare(key)==0)
                return (*iter_kv).value;

        }


    }

    return "";



}


int INIsword::init(){

    int ret;
    //read file by line
    ret=this->readlines();
    if(ret)
    {
        return ret;
    }


    parse_ini();


    return 0;
}
