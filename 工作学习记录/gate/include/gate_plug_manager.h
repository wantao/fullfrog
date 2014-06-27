#ifndef __GATE_PLUG_MANAGER_H__
#define __GATE_PLUG_MANAGER_H__

#include "sh_common.h"
#include "sh_type.h"

namespace MPlug{

struct plugStruct{	
	plugStruct() : id(0),isLoad(0),path(""),desc("") {}
	INT16 id;//plug id
	INT16 isLoad; //plug isLoad to memory
	string path; //plug path
	string desc; //plug description
};

class CPlugMgr: public share::CSingleton<CPlugMgr>
{
public:
protected:
private:
};
}

#endif
