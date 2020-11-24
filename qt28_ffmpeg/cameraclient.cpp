#include "cameraclient.h"

#include <QDebug>

CameraClient::CameraClient()
{
    m_videoID=0;
    m_recvDataToggle=false;
    m_recvCommandToggle=false;

    pthread_mutex_init(&mutex_cRecv, NULL);
    pthread_mutex_init(&mutex_cSend, NULL);
    pthread_mutex_init(&mutex_dRecv, NULL);
    pthread_mutex_init(&mutex_dSend, NULL);

}
CameraClient::~CameraClient()
{
}
bool CameraClient::startTCPSocketConnection(CC_NetConnectInfo*  connectionInfo)
{
    printf("IP: %s\n",connectionInfo->server_ip);
    printf("PORT: %d\n",connectionInfo->port);
    printf("USER: %s\n",connectionInfo->user_name);
    printf("PASS: %s\n",connectionInfo->pass_word);



    memcpy(m_IPAdress,connectionInfo->server_ip,sizeof(m_IPAdress));
    memcpy(m_userName,connectionInfo->user_name,sizeof(m_userName));
    memcpy(m_password, connectionInfo->pass_word, sizeof(m_password));
    m_port=connectionInfo->port;


    int ret= initTCPCSocketConnection(connectionInfo);

    if(ret==0)
    {
        detachThreadCreate(NULL,(void*)doLoginAuthenticationThread,(void *)this);
    }

    return true;

}

void* CameraClient::doLoginAuthenticationThread(void* arg)
{
    CameraClient* camClient=(CameraClient*)arg;
    if(camClient!=NULL){
        camClient->doLoginAuthentication();
    }

    return NULL;
}

void CameraClient::doLoginAuthentication()
{
    printf("登陆认证:...........\n");

    int error=0;
    fd_set r_set,w_set;

    FD_ZERO(&w_set);
    FD_ZERO(&r_set);

    FD_SET(m_cSockfd,&r_set);
    FD_SET(m_cSockfd,&w_set);

    struct timeval timeout={10,0};

    int retValue=select(m_cSockfd+1, &r_set, &w_set, NULL, &timeout);

    switch (retValue) {
        case -1:
        {
            printf("select 系统调用出错\n");
            return ;

        }break;
        case 0://select超时
        {
            printf("select超时...\n");
            return ;

        }break;

        default:
        {
            //套接字即可读又可写,需要进一步判断。
            if(FD_ISSET(m_cSockfd,&r_set) && FD_ISSET(m_cSockfd,&w_set))
            {
                //如果套接口及可写也可读，需要进一步判断
                socklen_t len = sizeof(error);
                if(getsockopt(m_cSockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0){
                    return ;//获取SO_ERROR属性选项，当然getsockopt也有可能错误返回
                }
                printf("error = %d\n", error);
                if(error != 0)
                {   //如果error不为0， 则表示链接到此没有建立完成
                    printf("connect failed\n");
                    return ;
                }
                //如果error为0，则说明链接建立完成

            }
            //如果套接字可写但是不可读，说明连接完成。
            if(!FD_ISSET(m_cSockfd,&r_set) && FD_ISSET(m_cSockfd,&w_set))
            {
                //如果套接口可写不可读,则链接完成
                printf("connect success\n");

                //登陆，认证......
                printf("登陆，认证......!\n");

                if(sendUserLoginRequest())
                {
                    int ret=recvUserLoginReply();
                    //登陆成功
                    if(ret==0)
                    {

                        m_recvDataToggle=true;
                        m_recvCommandToggle=true;
                        printf("开始接收音视频 命令......!\n");

                        //一直接收视频
                        detachThreadCreate(NULL,(void*)recvDataThread,(void *)this);
                        //一直接收命令
                         detachThreadCreate(NULL,(void*)recvControllCommandThread,(void *)this);
                    }


                }

            }

        }break;
    }


}


void* CameraClient::recvControllCommandThread(void* arg)
{
    CameraClient* camClient=(CameraClient*)arg;
    if(camClient!=NULL){
        camClient->recvControllCommand();
    }

    return NULL;
}

void CameraClient::recvControllCommand()
{

    while(m_recvCommandToggle)
    {
        CC_MsgHeader msgHeader;
        memset(&msgHeader, 0, sizeof(msgHeader));

        //读包头

        if(!recvCSocketData((char*)&msgHeader,sizeof(msgHeader))){
            break;
        }

        //strncpy strncmp
        if(strncmp((char*)msgHeader.messageHeader,"CCTC",4)==0)
        {
            if(msgHeader.controlMask==CONTROLLCODE_VIDEOTRANSLATION_REPLY)
            {
                CC_videoTranslationRequestReply  transtionReply;
                memset(&transtionReply, 0, sizeof(transtionReply));


                if(recvCSocketData((char*)&transtionReply,sizeof(transtionReply)))
                {
                    printf("请求视频成功: %d 0 同意传输\n",transtionReply.result);


                }

            }
            else if(msgHeader.controlMask==CONTROLLCODE_LISTENSTART_REPLY)
            {
                CC_audioRequestCommandReply  transtionReply;
                memset(&transtionReply, 0, sizeof(transtionReply));

                if(recvCSocketData((char*)&transtionReply,sizeof(transtionReply)))
                {
                    printf("请求音频成功: %d 0 同意传输\n",transtionReply.result);


                }

            }
            else if(msgHeader.controlMask==CODECONTROLL_SEND_KEEPALIVE_REQUEST)
            {
                printf("心跳包的返回.......\n");

            }


        }

    }

}

void* CameraClient::recvDataThread(void* arg)
{
    CameraClient* camClient=(CameraClient*)arg;
    if(camClient!=NULL){
        camClient->recvData();
    }
    return NULL;
}
void CameraClient::updateRGBData(RGBData_Define* rgbData)
{
    if((rgbData != NULL) && (rgbData->bufferSize >0) &&(rgbData->databuffer !=NULL)){

        m_updateVideoCallback(rgbData,m_userData);
    }

}

void CameraClient::recvData()
{

    H264Decoder* decoder= new H264Decoder();

    char* videoData=(char*)malloc(1920*1080*3);//接收到的视频Buffer.

    while(m_recvDataToggle)
    {

        CC_MsgHeader msgHeader;
        memset(&msgHeader, 0, sizeof(msgHeader));

        //读包头
        if(!recvDSocketData((char*)&msgHeader,sizeof(msgHeader))){
            break;
        }


        if(strncmp((char*)msgHeader.messageHeader,"CCTD",4)==0)
        {

            //视频数据
            if(msgHeader.controlMask==CODECONTROLL_VIDEOTRANS_WIDTHID_REPLY )
            {
                CC_videoDataContent dataContent;
                memset(&dataContent, 0, sizeof(dataContent));


                if(recvDSocketData((char*)&dataContent,sizeof(dataContent)))
                {

                    int dataLength=dataContent.videoLength;

                    if(recvDSocketData((char*)videoData,dataLength))
                    {
                        //接收到视频以后的处理....

                        if(videoData==NULL){
                            continue;
                        }
                        //printf("视频 xxxxxxxxxxxxxxxxxxxxxxxxx% d\n",dataLength);
                        qDebug()<<"视频 xxxxxxxxxxxxxxxxxxxxxxxxx%d"<<dataLength;
                        RGBData_Define rgbData;
                        decoder->DecodeH264Frames((unsigned char*)videoData,dataLength,(RGBData_Define*)&rgbData);
                        updateRGBData(&rgbData);


                    }
                }

            }
            //音频数据
            else if(msgHeader.controlMask==CONTROLLCODE_LISTENTRANSPORTREPLY)
            {
                CC_audioDataContent dataContent;
                memset(&dataContent, 0, sizeof(dataContent));

                if(recvDSocketData((char*)&dataContent,sizeof(dataContent)))
                {
                    char audioData[81920];//音频数据Buffer
                    memset(&audioData, 0, sizeof(audioData));

                    int audioLength=dataContent.dataLength;

                    if(recvDSocketData(audioData,audioLength))
                    {
                        //接收到音频以后的处理
                        //解码音频 pcm
                        //调用ios 音频播放接口播放pcm  OpenAL 播放音频。
                        //printf("音频 ==============================% d\n",audioLength);
                        qDebug()<<"音频 ==============================% d"<<audioLength;
                    }
                }
            }
        }

    }


    free(videoData);

    if(decoder != NULL){
        delete decoder;
    }
    printf("RECV VIODE AUDIO Exit................\n");

}


bool CameraClient::sendUserLoginRequest()
{
    CC_MsgHeader loginMsgHeader;
    memset(&loginMsgHeader,0,sizeof(loginMsgHeader));

    loginMsgHeader.messageHeader[0]='C';
    loginMsgHeader.messageHeader[1]='C';
    loginMsgHeader.messageHeader[2]='T';
    loginMsgHeader.messageHeader[3]='C';

    loginMsgHeader.controlMask=CONTROLCODE_LOGIN_REQUEST;

    int loginLength=sizeof(loginMsgHeader);

    if(sendCSocketData((char*)&loginMsgHeader,loginLength))
    {
        return true;
    }

    return false;
}

int CameraClient::recvUserLoginReply()
{
    CC_LoginRequestReply   loginReply;
    memset(&loginReply, 0, sizeof(loginReply));

    if(recvCSocketData((char*)&loginReply,sizeof(loginReply)) ==false){
        return -1;
    }


    if(strncmp((char*)loginReply.msgHeader.messageHeader,"CCTC",4)==0)
    {

        if((loginReply.msgHeader.controlMask==CONTROLCODE_LOGIN_REPLY)&&
           (loginReply.result==LOGIN_REQUEST_REPLY_VALUE_OK))
        {

            printf("LoginReply INFO Result:   %d\n",loginReply.result);       //登陆响应结果
            printf("LoginReply INFO DevID:    %s\n",loginReply.devID);        //设备ID
            printf("LoginReply INFO DevHDVer: %s\n",loginReply.devVersion);   //固件版本

            if(sendCVerifyRequest())
            {
                CC_VerifyReply verifyReply;
                memset(&verifyReply, 0, sizeof(verifyReply));


                if(recvCSocketData((char*)&verifyReply,sizeof(verifyReply)))
                {
                    if((verifyReply.msgHeader.controlMask==CONTROLCODE_VERIFY_REPLY)&&
                       (verifyReply.result==VERIFY_REPLY_VALUE_OK))
                    {
                        printf("较验结果:  较验正确\n");

                        //较验后自动返回的信息---------------------------------------------------------

                        //视频传输请求
                        if(sendVideoTransRequest())
                        {
                            printf("Client: send Video Translation Request OK.....\n");

                            CC_videoTranslationRequestReply   videoReply;
                            memset(&videoReply, 0, sizeof(videoReply));


                            if(recvCSocketData((char *)&videoReply,sizeof(videoReply)))
                            {
                                //视频传输响应结果.
                                printf("Receive Header: 视频请求命令响应 ------------------------------>%d\n",videoReply.msgHeader.controlMask);
                                printf("Receive Header: 视频请求命令响应长度 ------------------------------>%d\n",videoReply.msgHeader.commandLength);

                                if(videoReply.msgHeader.controlMask==CONTROLLCODE_VIDEOTRANSLATION_REPLY)
                                {
                                    printf("Client: 视频请求命令响应 成功!!!.....\n");
                                    printf("视频回应 视频ID信息 :   %X\n",videoReply.videoID);
                                    if(videoReply.result==VIDEOIREQUESTREPLY_OK) //同意连接
                                    {
                                        printf("视频回应 :   同意连接\n");
                                        m_videoID=videoReply.videoID;

                                        //初始化数据通道Socket2
                                        initDSocketConnection();

                                        //请求视频数据传输 数据通道
                                        sendVideoDataTransRequestWithID();

                                    }
                                    else if(videoReply.result==VIDEOIREQUESTREPLY_USERFULL) //用户已经满
                                    {
                                        printf("视频回应 :   用户已经满\n");

                                    }else if(videoReply.result==VIDEOIREQUESTREPLY_FORBIDEN) //禁止连接
                                    {
                                        printf("视频回应  :  禁止连接\n");
                                    }

                                }
                                else
                                {
                                    printf("视频回应控制码出错 -------------------\n");
                                }

                            }
                            else
                            {
                                printf("视频返回读头出错: \n");
                            }
                        }
                        else
                        {
                            printf("视频命令发送失败: \n");

                        }//视频传输请求 END

                    }
                    else if(verifyReply.result==VERIFY_REPLY_VALUE_USER_ERROR)
                    {

                        printf("较验结果:  用户名出错\n");

                    }
                    else if(verifyReply.result==VERIFY_REPLY_VALUE_PASS_ERROR)
                    {

                        printf("较验结果:  密码出错\n");

                    }



                }

            }

        }



    }


    return 0;
}


int CameraClient::initTCPCSocketConnection(CC_NetConnectInfo*  connectionInfo)
{
    printf("控制命令socket初始化:...........\n");

    memset(&m_cSockaddr_in, 0, sizeof(struct sockaddr_in));

    m_cSockfd=socket(AF_INET,SOCK_STREAM,0);

    printf("controll socket init %d\n",m_cSockfd);

    if(m_cSockfd<0){
        printf("socket error!\n");
        return -1;
    }

    m_cSockaddr_in.sin_family=AF_INET;
    m_cSockaddr_in.sin_port=htons(connectionInfo->port);
    m_cSockaddr_in.sin_addr.s_addr=htons(INADDR_ANY);


    if(inet_pton(AF_INET,m_IPAdress,&m_cSockaddr_in.sin_addr.s_addr)<=0)
    {
        printf("inet_pton error!!!\n");
        return -1;
    }
    //非阻塞的connect模式.
    int flags=fcntl(m_cSockfd, F_GETFL,0);
    fcntl(m_cSockfd, F_SETFL,flags|O_NONBLOCK);

    int connetRet=connect(m_cSockfd,(struct sockaddr*)&m_cSockaddr_in,sizeof(struct sockaddr));
    printf("socket connection result: %d\n",connetRet);

    //设置回阻塞模式.
    int flags1=fcntl(m_cSockfd, F_GETFL,0);
    fcntl(m_cSockfd, F_SETFL,flags1 &(~O_NONBLOCK));


    struct timeval timeout={2,0};

    int nRet1=setsockopt(m_cSockfd, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(struct timeval));

    if(nRet1<0){
        printf("setsockopt1 error!!!\n");
        return -1;
    }

    int nRet2=setsockopt(m_cSockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(struct timeval));

    if(nRet2<0){
        printf("setsockopt2 error!!!\n");
        return -1;
    }


    return 0;
}


int CameraClient::initDSocketConnection()
{

    printf("\n\n数据传输Socket: 初始化数据传输Socket.........\n");


    memset( &m_dSockaddr_in, 0, sizeof( struct sockaddr));

    m_dSockfd = socket(AF_INET,SOCK_STREAM,0);

    printf("数据传输Socket Socket ID:! %d \n",m_dSockfd);

    if( m_dSockfd < 0)
    {
        printf("socket error! \n");
        return -1;
    }

    memset(&m_dSockaddr_in, 0, sizeof(m_dSockaddr_in));
    m_dSockaddr_in.sin_family = AF_INET;
    m_dSockaddr_in.sin_port = htons(m_port);
    m_dSockaddr_in.sin_addr.s_addr = htons(INADDR_ANY);



    if(inet_pton(AF_INET,m_IPAdress,&m_dSockaddr_in.sin_addr.s_addr)<=0)
    {
        printf("inet_pton for error!\n");
        return -3;
    }


    //2.连接服务器
    int retConn=connect(m_dSockfd, ( struct sockaddr*)&m_dSockaddr_in, sizeof( struct sockaddr));
    printf("数据传输Socket: Socket Connect Result:%d\n",retConn);

    //2.设置阻塞模式
    int flags1 = fcntl(m_dSockfd, F_GETFL, 0);
    fcntl(m_dSockfd, F_SETFL, flags1 &( ~O_NONBLOCK));


    struct timeval timeout = {10,0};


    if(setsockopt(m_dSockfd, SOL_SOCKET, SO_SNDTIMEO, (const char *)&timeout, sizeof(struct timeval)))
    {
        return -1;
    }
    if(setsockopt(m_dSockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(struct timeval) ))
    {
        return -1;
    }


    printf("数据传输Socket: 初始化结束.........\n\n\n");

    return 0;

}

void CameraClient::stopTCPSocketClient()
{

    printf("Client:---------------------STOP----------------------------------\n");

    m_recvDataToggle=false;
    m_recvCommandToggle=false;


    if(m_dSockfd>0)
    {
        close(m_dSockfd);
        m_dSockfd=-1;
    }

    if(m_cSockfd>0)
    {
        close(m_cSockfd);
        m_cSockfd=-1;
    }

}

bool CameraClient::sendCVerifyRequest()
{

    CC_VerifyRequestContent requestContent;
    memset(&requestContent, 0, sizeof(requestContent));

    memcpy(requestContent.userName, m_userName, sizeof(m_userName));
    memcpy(requestContent.password, m_password, sizeof(m_password));

    int contentLength=sizeof(requestContent);


    CC_MsgHeader msgHeader;
    memset(&msgHeader, 0, sizeof(msgHeader));

    int msgHeaderLength=sizeof(msgHeader);

    msgHeader.messageHeader[0]='C';
    msgHeader.messageHeader[1]='C';
    msgHeader.messageHeader[2]='T';
    msgHeader.messageHeader[3]='C';

    msgHeader.controlMask=CONTROLCODE_VERIFY_REQUEST;

    msgHeader.commandLength=contentLength;

    int totalLength=contentLength+msgHeaderLength;

    char * sendBuffer=(char *)malloc((totalLength)*sizeof(char));
    memcpy(sendBuffer, &msgHeader, msgHeaderLength);
    memcpy(sendBuffer+msgHeaderLength, &requestContent, contentLength);



    if(sendCSocketData(sendBuffer,totalLength))
    {
        free(sendBuffer);
        return true;
    }

    free(sendBuffer);
    return false;
}

//操作命令------视频传输请求
bool CameraClient::sendVideoTransRequest()
{
    //printf("Client: send video translation Request:.........\n");



    //头部信息
    CC_MsgHeader msgHeader;
    memset(&msgHeader, 0, sizeof(msgHeader));



    msgHeader.messageHeader[0]='C';
    msgHeader.messageHeader[1]='C';
    msgHeader.messageHeader[2]='T';
    msgHeader.messageHeader[3]='C';

    msgHeader.controlMask=CONTROLLCODE_VIDEOTRANSLATION_REQUEST;
    msgHeader.commandLength=1;

    //命令正文信息......
    CC_videoTranslationRequest  videoTranslationRq;
    memset(&videoTranslationRq, 0, sizeof(videoTranslationRq));

    videoTranslationRq.msgHeader=msgHeader;
    videoTranslationRq.reserved=1;


    unsigned long sendLength= sizeof(videoTranslationRq);


    if(sendCSocketData(( char*)&videoTranslationRq,sendLength))
    {
        return true;
    }

    return false;
}

bool CameraClient::sendVideoDataTransRequestWithID()
{
    printf("视频请求传输 ID.......\n");

    char  videoRequestBuffer[27]={0};

    CC_VideoTransRequestWithID request;
    memset(&request, 0, sizeof(request));



    strncpy((char*)request.msgHeader.messageHeader, "CCTD",4);


    request.msgHeader.controlMask=CODECONTROLL_VIDEOTRANS_WIDTHID_REQUEST;
    request.msgHeader.commandLength=4;

    request.videoID=m_videoID;

    memcpy(videoRequestBuffer, &request, sizeof(videoRequestBuffer));
    int sendLength=sizeof(videoRequestBuffer);

    if(sendDSocketData((char*)&request,sendLength))
    {
        return true;
    }

    return false;
}

bool CameraClient::startListenCommand()
{
    printf("开始监听 .......\n");



    CC_audioRequestCommand request;
    memset(&request, 0, sizeof(request));

    request.msgHeader.messageHeader[0]='C';
    request.msgHeader.messageHeader[1]='C';
    request.msgHeader.messageHeader[2]='T';
    request.msgHeader.messageHeader[3]='C';

    request.msgHeader.controlMask=CONTROLLCODE_LISTENSTART_COMMAND;
    request.msgHeader.commandLength=1;


    int sendLength=sizeof(request);


    if(sendCSocketData((char*)&request,sendLength))
    {
        return true;
    }

    return false;
}

bool CameraClient::stopListenCommand()
{
    printf("停止监听 .......\n");

    CC_audioRequestCommand request;
    memset(&request, 0, sizeof(request));

    request.msgHeader.messageHeader[0]='C';
    request.msgHeader.messageHeader[1]='C';
    request.msgHeader.messageHeader[2]='T';
    request.msgHeader.messageHeader[3]='C';

    request.msgHeader.controlMask=CONTROLLCODE_LISTENSTOP_COMMAND;
    request.msgHeader.commandLength=1;


    int sendLength=sizeof(request);


    if(sendCSocketData((char*)&request,sendLength))
    {
        return true;
    }

    return false;
}

bool CameraClient::sendKeepAliveRequest()
{
    printf("发送心跳包 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");

    CC_MsgHeader msgHeader;
    memset(&msgHeader, 0, sizeof(msgHeader));

    msgHeader.messageHeader[0]='C';
    msgHeader.messageHeader[1]='C';
    msgHeader.messageHeader[2]='T';
    msgHeader.messageHeader[3]='C';

    msgHeader.controlMask=CODECONTROLL_SEND_KEEPALIVE_REQUEST;
    msgHeader.commandLength=0;


    int sendLength=sizeof(msgHeader);

    if(sendCSocketData((char*)&msgHeader,sendLength))
    {
        return true;
    }

    return false;
}
bool CameraClient::sendCSocketData(char* pBuf , int aLength)
{

    signal(SIGPIPE, SIG_IGN);

    pthread_mutex_lock(&mutex_cSend);

    int sendLen=0;
    int nRet=0;

    while(sendLen<aLength)
    {
        nRet=send(m_cSockfd,pBuf,aLength-sendLen,0);

        if(nRet<0)
        {
            if(errno==EAGAIN || errno == EINTR ||errno == EWOULDBLOCK){
                usleep(10*1000);
                continue;
            }
        }

        if(-1==nRet || 0==nRet)
        {
            pthread_mutex_unlock(&mutex_cSend);
            printf("cSocket send error\n");
            return false;
        }

        sendLen+=nRet;
        pBuf+=nRet;
        printf("cSocket send ok %d %d\n",m_cSockfd, nRet);
    }


    pthread_mutex_unlock(&mutex_cSend);

    return true;
}



bool CameraClient::recvCSocketData(char* pBuf ,int aLength)
{
    signal(SIGPIPE, SIG_IGN);

    pthread_mutex_lock(&mutex_cRecv);

    int recvLen=0;
    int nRet=0;

    while(recvLen<aLength)
    {
        nRet=recv(m_cSockfd,pBuf,aLength-recvLen,0);

        if(nRet<0)
        {
            if(errno==EAGAIN || errno == EINTR ||errno == EWOULDBLOCK){
                usleep(10*1000);
                continue;
            }
        }

        if(-1==nRet || 0==nRet)
        {
            pthread_mutex_unlock(&mutex_cRecv);
            printf("cSocket recv error\n");
            return false;
        }
        recvLen+=nRet;
        pBuf+=nRet;
    }

    pthread_mutex_unlock(&mutex_cRecv);

    return true;
}

bool CameraClient::sendDSocketData(char* pBuf, int aLength)
{

    signal(SIGPIPE, SIG_IGN);

    pthread_mutex_lock(&mutex_dSend);

    int sendLen=0;
    int nRet=0;

    while(sendLen<aLength)
    {
        if(m_dSockfd>0)
        {
            nRet=send(m_dSockfd,pBuf,aLength-sendLen,0);

            if(nRet<0)
            {
                if(errno==EAGAIN || errno == EINTR ||errno == EWOULDBLOCK){
                    usleep(10*1000);
                    continue;
                }
            }

            if(-1==nRet || 0==nRet)
            {
                pthread_mutex_unlock(&mutex_dSend);
                printf("cSocket send error\n");
                return false;
            }

            sendLen+=nRet;
            pBuf+=nRet;

            printf("SEND LEN: %d %d\n",aLength,sendLen);
        }
        else
        {
            printf("dSocket fd error %d\n",m_dSockfd);
            pthread_mutex_unlock(&mutex_dSend);
            return false;
        }

    }

    pthread_mutex_unlock(&mutex_dSend);

    return true;
}



bool CameraClient::recvDSocketData(char *pBuf, int aLength)
{
    if(aLength>81920)
        return false;

    signal(SIGPIPE, SIG_IGN);

    //pthread_mutex_lock(&mutex_dRecv);

    int recvLen=0;
    int nRet=0;

    while(recvLen<aLength)
    {
        nRet=recv(m_dSockfd,pBuf,aLength-recvLen,0);

        if(nRet<0)
        {
            if(errno==EAGAIN || errno == EINTR ||errno == EWOULDBLOCK){
                usleep(10*1000);
                continue;
            }
        }

        if(-1==nRet || 0==nRet)
        {
            //pthread_mutex_unlock(&mutex_dRecv);
            printf("DSocket recv error\n");
            return false;
        }
        recvLen+=nRet;
        pBuf+=nRet;
    }

    //pthread_mutex_unlock(&mutex_dRecv);

    return true;
}

void CameraClient::setupUpdateGUICallback(UpdateVideo2GUI_Callback callback,unsigned long userData)
{
    m_updateVideoCallback=callback;
    m_userData=userData;
}

int CameraClient::detachThreadCreate(pthread_t *thread, void * start_routine, void *arg)
{
    pthread_attr_t attr;
    pthread_t thread_t;
    int ret = 0;

    if(thread==NULL){
        thread = &thread_t;
    }
    //初始化线程的属性
    if(pthread_attr_init(&attr))
    {
        printf("pthread_attr_init fail!\n");
        return -1;
    }

    //设置线程detachstate属性。该表示新线程是否与进程中其他线程脱离同步
    if(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED))
    {//新线程不能用pthread_join()来同步，且在退出时自行释放所占用的资源。
        printf("pthread_attr_setdetachstate fail!\n");
        goto error;
    }

    ret = pthread_create(thread, &attr, (void *(*)(void *))start_routine, arg);
    if(ret < 0){
        printf("pthread_create fail!\n");
        goto error;
    }

    //将状态改为unjoinable状态，确保资源的释放。
   ret =  pthread_detach(thread_t);

error:
    pthread_attr_destroy(&attr);

    return ret;
}
