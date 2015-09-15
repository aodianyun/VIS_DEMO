# VIS_DEMO
VIS sdk使用说明
接口文件：include下IRtmpPublishPlayParent_c

1,在自己的工程中包含include下的头文件，链接库lib的文件

2,是自己的类继承IPublicPlayNotify并实现其方法
    class MyClass: publick IPublicPlayNotify
    {
        bool OnRtmpPublishOrPlayNotifyInJson(const char* pszJson){ 
        // 处理vis回调的消息
        return true; 
        }
    };

3,使用CreatePublicPlay创建vis对象，
    m_pPublicPlay = CreatePublicPlay(this);

4,利用vsi对象设置参数，启动和停止vis
    利用vis通用接口获取上麦的mi，cam 和播放设备并设置进去
    
     {// 
        string strCmd;
        m_jsonRoot.clear();
        m_jsonParams.clear();
        m_jsonRoot["cmd"] = Json::Value("GetCamList");
        m_jsonRoot["params"] = m_jsonParams;
        strCmd = m_jsonRoot.toStyledString();
        char* pszRes = new char[1024];
        if (!m_pPublicPlay->CallInJson(RTMP_PUBLISH, strCmd.c_str(), &pszRes))
        {
            return false;
        }
        // 解析PlayerList
        Json::Reader reader;
        Json::Value root;
        Json::Value resRoot;
        Json::Value data;
    
        if (reader.parse(pszRes, root))
        {
            data = root["data"];
            int size = data["cameras"].size();
            for (unsigned int i = 0; i < size; i++)
            {
                m_ComboBoxVideo.InsertString(m_ComboBoxVideo.GetCount(),
                    ConvertString::s2ws(data["cameras"][i].asString()).c_str());
            }
            m_ComboBoxVideo.SetCurSel(0);
        }
    
        // mic 
        m_jsonRoot.clear();
        m_jsonParams.clear();
        m_jsonRoot["cmd"] = Json::Value("GetMicList");
        m_jsonRoot["params"] = m_jsonParams;
        strCmd = m_jsonRoot.toStyledString();
        memset(pszRes, 0, sizeof(pszRes));
        if (!m_pPublicPlay->CallInJson(RTMP_PUBLISH, strCmd.c_str(), &pszRes))
        {
            return false;
        }
        if (reader.parse(pszRes, root))
        {
            data = root["data"];
            int size = data["mics"].size();
            for (unsigned int i = 0; i < size; i++)
            {
                m_ComboBoxMic.InsertString(m_ComboBoxMic.GetCount(),
                    ConvertString::s2ws(data["mics"][i].asString()).c_str());
            }
            m_ComboBoxMic.SetCurSel(0);
        }
    
    
        // AudioPlayer
        m_jsonRoot.clear();
        m_jsonParams.clear();
        m_jsonRoot["cmd"] = Json::Value("GetAudioPlayDevList");
        m_jsonRoot["params"] = m_jsonParams;
        strCmd = m_jsonRoot.toStyledString();
        memset(pszRes, 0, sizeof(pszRes));
        if (!m_pPublicPlay->CallInJson(RTMP_PLAY, strCmd.c_str(), &pszRes))
        {
            return false;
        }
        // 解析PlayerList
        if (reader.parse(pszRes, root))
        {
            data = root["data"];
            int size = data["player"].size();
            for (unsigned int i = 0; i < size; i++)
            {
                m_ComboBoxAudioPlay.InsertString(m_ComboBoxAudioPlay.GetCount(),
                    ConvertString::s2ws(data["player"][i].asString()).c_str());
            }
            m_ComboBoxAudioPlay.SetCurSel(0);
        }
    
        delete[] pszRes;
        return true;
    }
 //设置
    string strCmd;
    Json::Reader reader;
    Json::Value root;
    Json::Value resRoot;
    Json::Value data;
    char* pszRes = new char[1024];
        int iDevId = m_ComboBoxAudioPlay.GetCurSel();
        m_jsonRoot.clear();
        m_jsonParams.clear();
        m_jsonRoot["cmd"] = Json::Value("SetAudioPlayDev");
        m_jsonParams["uDevID"] = Json::Value(iDevId);
        m_jsonRoot["params"] = m_jsonParams;
        strCmd = m_jsonRoot.toStyledString();
        memset(pszRes, 0, sizeof(pszRes));
        if (!m_pPublicPlay->CallInJson(RTMP_PLAY, strCmd.c_str(), &pszRes))
        {
            return;
        }
        // 解析PlayerList
        if (reader.parse(pszRes, root))
        {
            data = root["code"];
        }

        //m_pPublicPlay->SetVdDisplayWnd(GetDlgItem(IDC_STATIC_PLAY)->m_hWnd);

        int iCamId = m_ComboBoxVideo.GetCurSel();
        int iMicId = m_ComboBoxMic.GetCurSel();
        m_jsonRoot.clear();
        m_jsonParams.clear();
        m_jsonRoot["cmd"] = Json::Value("SetCam");
        m_jsonParams["uCamID"] = Json::Value(iCamId);
        m_jsonRoot["params"] = m_jsonParams;
        strCmd = m_jsonRoot.toStyledString();
        memset(pszRes, 0, sizeof(pszRes));
        if (!m_pPublicPlay->CallInJson(RTMP_PUBLISH, strCmd.c_str(), &pszRes))
        {
            return;
        }
        // 解析PlayerList
        if (reader.parse(pszRes, root))
        {
            data = root["code"];
        }
        //
        m_jsonRoot.clear();
        m_jsonParams.clear();
        m_jsonRoot["cmd"] = Json::Value("SetMic");
        m_jsonParams["uMicID"] = Json::Value(iMicId);
        m_jsonRoot["params"] = m_jsonParams;
        strCmd = m_jsonRoot.toStyledString();
        memset(pszRes, 0, sizeof(pszRes));
        if (!m_pPublicPlay->CallInJson(RTMP_PUBLISH, strCmd.c_str(), &pszRes))
        {
            return;
        }
        
5,设置VIS地址，app和stream以及自己的密码
     //
     m_pPublicPlay->SetPubPlayUrlPara(m_strHttpPublishAddr.c_str(), m_strPublishApp.c_str(), m_strPublishStream.c_str(), m_strPublishPwd.c_str())
//
6,启动上麦  需要两个窗口句柄，一个publish，一个play 
    m_pPublicPlay->SetPublishPlayAndStart(GetDlgItem(IDC_STATIC_PLAY)->m_hWnd, GetDlgItem(IDC_STATIC_PUBLISH)->m_hWnd);
    //
7,停止和销毁vis
    if (m_pPublicPlay)
    {
        m_pPublicPlay->StopPublishPlay();
        m_pPublicPlay->Release();
        m_pPublicPlay = NULL;
    }
