//
// Created by root on 11/10/16.
//

//author huoyingyangjie@163.com
#include "inirw.h"
#include <iostream>




int main(){

    INIsword is("./democonfig.ini");


    cout<<is.getGlobalValue("hello")<<endl;

    vector<Section> vs=is.getSection("feiona");
    cout<<is.getValue(vs[0],"name")<<endl;
    cout<<is.getValue(vs[1],"name")<<endl;

    vs=is.getSection("sun");

    cout<<is.getValue(vs[0],"up")<<endl;

    cout<<is.getValue(vs[0],"xxx")<<endl;


}
