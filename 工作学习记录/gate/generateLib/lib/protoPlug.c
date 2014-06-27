#include <errno.h>
#include "protoPlug.h"
#include "gate_client_session.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void OnRecvLoginReq(void* obj,const unsigned char* inData, const INT32 inLen)
{
    unsigned char * retData = (unsigned char*)malloc(inLen+MSG_HEADER_SIZE+MSG_TYPE_SIZE+1);
    if (NULL == retData) {
        printf("retData malloc error:%s\n",strerror(errno));
        return;
    } 
    INT32 len = MSG_HEADER_SIZE+MSG_TYPE_SIZE+inLen;
    memcpy(retData,&len,sizeof(len));
    INT32 msgType = E_GAET_LOGIN_ACK;
    memcpy(retData+MSG_HEADER_SIZE,&msgType,MSG_TYPE_SIZE);
    memcpy(retData+MSG_HEADER_SIZE+MSG_TYPE_SIZE,inData,inLen);

    CGateClientSession* p_gateClientSession = (CGateClientSession*)obj;
    p_gateClientSession->SendToClient(retData,len);
    if (NULL != retData) {
        free(retData);
        retData = NULL;
    }
}
