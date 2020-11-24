#ifndef CAMERACLIENT_H
#define CAMERACLIENT_H

#include "cctcpdatadefine.h"
#include "h264decoder.h"

typedef void (*UpdateVideo2GUI_Callback)(RGBData_Define* rgbData,unsigned long userData);

class CameraClient
{
public:
    CameraClient();
    ~CameraClient();

public:

    bool startTCPSocketConnection(CC_NetConnectInfo*  connectionInfo);
    void stopTCPSocketClient();

    void setupUpdateGUICallback(UpdateVideo2GUI_Callback callback,unsigned long userData);
private:
    int initTCPCSocketConnection(CC_NetConnectInfo*  connectionInfo);
    int initDSocketConnection();

    static void* doLoginAuthenticationThread(void* arg);
    static void* recvControllCommandThread(void* arg);
    static void* recvDataThread(void* arg);

    void doLoginAuthentication();
    void recvControllCommand();
    void recvData();

    int detachThreadCreate(pthread_t *thread, void * start_routine, void *arg);

    int  recvUserLoginReply();
    bool sendUserLoginRequest();

    bool recvDSocketData(char *pBuf, int aLength);
    bool sendDSocketData(char* pBuf, int aLength);
    bool recvCSocketData(char* pBuf ,int aLength);
    bool sendCSocketData(char* pBuf , int aLength);

    bool sendKeepAliveRequest();
    bool stopListenCommand();
    bool startListenCommand();
    bool sendVideoDataTransRequestWithID();
    bool sendVideoTransRequest();
    bool sendCVerifyRequest();

    void updateRGBData(RGBData_Define* rgbData);

private:

    char                        m_IPAdress[64];                 //camIP
    int                         m_port;                       //端口
    char                        m_userName[13];                  //用户名
    char                        m_password[13];                  //密码

    int                         m_cSockfd;                      //命令套接字.
    int                         m_dSockfd;                      //数据通道套接字.

    int                         m_videoID;      //视频ID

    struct   sockaddr_in        m_cSockaddr_in;
    struct   sockaddr_in        m_dSockaddr_in;

    bool                        m_recvDataToggle;
    bool                        m_recvCommandToggle;

    pthread_mutex_t             mutex_cRecv;
    pthread_mutex_t             mutex_cSend;
    pthread_mutex_t             mutex_dRecv;
    pthread_mutex_t             mutex_dSend;



    UpdateVideo2GUI_Callback    m_updateVideoCallback;
    unsigned long               m_userData;
};

#endif // CAMERACLIENT_H
