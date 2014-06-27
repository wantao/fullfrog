#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <linux/string.h>
#include "MarkupSTL.h"
#include "sh_common.h"

using namespace std;

int main()
{
	CMarkupSTL oXml;
	if(!oXml.Load("./config/srlib_config.xml")) {
		cerr<<"Load error"<<endl;
		return -1;
	}
	if (!oXml.FindElem("root")){
		cerr<<"find root failure"<<endl;
        	return -1;
    	}

    	if (!oXml.IntoElem()){
		cerr<<"into elem faliure"<<endl;	
        	return -1;
    	}
	
	while (oXml.FindElem("plugSet")) {
		if (!oXml.IntoElem()) {
			cerr<<"into plugSet elem error"<<endl;
			return -1;
		}
		while(oXml.FindElem("item")) {
			int id = share::a2i(oXml.GetAttrib("id"));
			int isLoad = share::a2i(oXml.GetAttrib("isLoad"));
			string path = oXml.GetAttrib("path");
			string desc = oXml.GetAttrib("desc");
			cout<<"id:"<<id<<" isLoad:"<<isLoad<<" path:"<<path<<"desc:"<<desc<<endl;
		}
		oXml.OutOfElem();
	}
	oXml.OutOfElem();
}

