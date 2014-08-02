#include "curl/curl.h"
#include "curl/easy.h"
#include "serverInternal.pb.h"
int curlWriteCallback(char *data, size_t size, size_t nmemb, string *writerData)
{
    if (writerData == NULL)
        return 0;
    int len = size*nmemb;
    writerData->append(data, len);

    return len;
}

int main(void)
{

    CURL *curl = curl_easy_init();
    if (!curl) {
        USER_FAST_LOG_FATAL("curl init failure!!!!!");
        return;
    }
    CURLcode res;
    std::string logAuthUrl = "http://127.0.0.1/91jieru/CheckUserLoginDemo.php";
    protoc::serverInternal::NineOneLoginAuthReq la;
    la.set_uin(req.account());
    la.set_sessionid(req.session_key());
    std::string u_sendData = "";
    la.SerializeToString(&u_sendData);
    if (u_sendData.size() > 0) {
        res = curl_easy_setopt(curl, CURLOPT_URL, logAuthUrl.c_str());    
        res = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, u_sendData.c_str());
        res = curl_easy_setopt(curl,CURLOPT_POSTFIELDSIZE,u_sendData.size());
        res = curl_easy_setopt(curl, CURLOPT_POST, true); 
        string u_stream = "";
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);
        res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &u_stream);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            USER_FAST_LOG_FATAL("curl perform failure!!!!!");
            return;    
        }
        protoc::serverInternal::NineOneLoginAuthAck laAck;
        if (!laAck.ParseFromString(u_stream)) {
            USER_FAST_LOG_FATAL("NineOneLoginAuth ParseFromString faliure,account:%s,sessionId:%s,u_stream:%s",req.account(),req.session_key(),u_stream.c_str());
            return;         
        }
        USER_FAST_LOG_FATAL("errorCode:%d,errorDesc:%s,u_stream:%s",laAck.errorcode(),laAck.errordesc(),u_stream.c_str());
    } else {
        USER_FAST_LOG_FATAL("NineOneLoginAuth SerializeToString faliure,account:%s,sessionId:%s",req.account(),req.session_key());
        return;
    }
}
