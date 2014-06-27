#ifndef __PROTO_PLUG_H__
#define __PROTO_PLUG_H__

#ifndef STDCALL
#if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
	#define STDCALL __stdcall
#else
	#define STDCALL __attribute__((__stdcall__))
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

//void  STDCALL OnRecvLoginReq(void* obj,unsigned char* inData, const int inLen);
void OnRecvLoginReq(void* obj,const unsigned char* inData, const int inLen);

#ifdef __cplusplus
}
#endif

#endif // PROTO_PLUG
