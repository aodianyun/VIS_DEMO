#pragma once

typedef enum RTMPMODEL{
	RTMP_NULL = 0,
	RTMP_PLAY,		// ���Ų���
	RTMP_PUBLISH	// �������
}RtmpModel;

// VIS ֪ͨ��
class IPublicPlayNotify
{
public:

	/**
	 * ��    �ڣ�OnRtmpPublishManagerMsg
	 * �ӿڹ��ܣ�������Ϣ�ص�
	 * ��    ����MsgLev	��Ϣ���� MSG_DEBUG=0, MSG_WARNING=1, MSG_ERR=2
	 *           pMsg	��Ϣ����
	 * ��    �ã�pszCmd { "cmd":"OnRtmpPublishManagerMsg", "params":{"MsgLev":1,"pMsg":"OnNotifyFail",} }
	 **/

	/**
	 * ��    �ڣ�OnRtmpPlayManagerMsg
	 * �ӿڹ��ܣ�������Ϣ�ص�
	 * ��    ����MsgLev	��Ϣ���� MSG_DEBUG=0, MSG_WARNING=1, MSG_ERR=2
	 *           pMsg	��Ϣ����
	 *           pDetail��Ϣ��ϸ˵��
	 * ��    �ã�pszCmd { "cmd":"OnRtmpPlayManagerMsg", "params":{"MsgLev":1,"pMsg":"OnRtmpDead","pDetail":"NetConnection.Connect.Closed"} }
	 **/

	/**
	 * ��    �ڣ�OnRtmpPublishPlayState
	 * �ӿڹ��ܣ�VIS����״̬�ص�
	 * ��    ����MsgLev	��Ϣ���� MSG_DEBUG=0, MSG_WARNING=1, MSG_ERR=2
	 *           pMsg	��Ϣ����
	 *           pDetail��Ϣ��ϸ˵��
	 * ��    �ã�pszCmd { "cmd":"OnRtmpPlayManagerMsg", "params":{"MsgLev":1,"pMsg":{"code":"-1",message:"varify faild",...},"pDetail":"NetConnection.Connect.Closed"} }
	 **/

	/**
	 * �ӿڹ��ܣ�JSON�ص�ͳһ�ӿ�
	 * ��    ����pszJson	JSON��ʽ�ַ���
	 * �� �� ֵ���ɹ�/ʧ��
	 * ʾ    ����{ "cmd":"xxx", "params":{"x":true, "xx":12, "xxx":"abc"} }
	 **/
	virtual bool OnRtmpPublishOrPlayNotifyInJson(const char* pszJson){ return true; };
};

class IPublicPlay{
public: 
	//----------------------RTMP_PLAYģʽ��ʼ-------------------------------------
	/**
	* ��    �ڣ�JSON����ͳһ�ӿ� SetAdPara
	* �ӿڹ��ܣ����ò�������  �������ڲ��Ź����е��ã�
	* ��	����int uOutVolum,	����
	*			bool bMute		�Ƿ���
	* ��    �ã�pszCmd { "cmd":"SetAdPara", "params":{"uOutVolum":80,bMute:false} }
	* ���أ���
	**/	

	/**
	* ��    �ڣ�JSON����ͳһ�ӿ� GetAudioPlayDevList
	* �ӿڹ��ܣ���ȡ�����豸�б� �������� SetPublishPlayAndStart ֮ǰ���ã�
	* ��    �ã�pszCmd { "cmd":"GetAudioPlayDevList", "params":{} }
	* �ɹ����أ�ppszRes { "code":0, "data":{"player":["dirsound", "guagua"]} }
	* ʧ�ܷ��أ�ppszRes { "code":1, "data":{} }
	**/

	/**
	* ��    �ڣ�JSON����ͳһ�ӿ� SetAudioPlayDev
	* �ӿڹ��ܣ����ò����豸ID �������� SetPublishPlayAndStart ֮ǰ���ã�
	* ��	����int uDevID      (�����豸ID(count from 0))
	* ��    �ã�pszCmd { "cmd":"SetAudioPlayDev", "params":{"uDevID":1} }
	* �ɹ����أ�ppszRes { "code":0, "data":{} }
	* ʧ�ܷ��أ�ppszRes { "code":1, "data":{} }
	**/

	//----------------------RTMP_PLAYģʽ����-------------------------------------

	//----------------------RTMP_PUBLISHģʽ��ʼ-------------------------------------



	/**
	 * ��    �ڣ�JSON����ͳһ�ӿ� GetCamList
	 * �ӿڹ��ܣ���ȡ����ͷ�б������� StartPublish ֮ǰ���ã�
	 * ��    �ã�pszCmd { "cmd":"GetCamList", "params":{} }
	 * �ɹ����أ�ppszRes { "code":0, "data":{"cameras":["cam1", "cam2"]} }
	 * ʧ�ܷ��أ�ppszRes { "code":1, "data":{} }
	 **/

	/**
	 * ��    �ڣ�JSON����ͳһ�ӿ� GetMicList
	 * �ӿڹ��ܣ���ȡ����ͷ�б������� StartPublish ֮ǰ���ã�
	 * ��    �ã�pszCmd { "cmd":"GetMicList", "params":{} }
	 * �ɹ����أ�ppszRes { "code":0, "data":{"mics":["mic1", "mic2"]} }
	 * ʧ�ܷ��أ�ppszRes { "code":1, "data":{} }
	 **/

	/**
	 * ��    �ڣ�JSON����ͳһ�ӿ� SetCam
	 * �ӿڹ��ܣ���������ͷID. �������� StartPublish ֮ǰ���ã�
	 * ��	 ����int uCamID ����ͷID
	 * ��    �ã�pszCmd { "cmd":"SetCam", "params":{"uCamID":0} }
	 * �ɹ����أ�ppszRes { "code":0, "data":{} }
	 * ʧ�ܷ��أ�ppszRes { "code":1, "data":{} }
	 **/

	/**
	 * ��    �ڣ�JSON����ͳһ�ӿ� SetMic
	 * �ӿڹ��ܣ���������ͷID. �������� StartPublish ֮ǰ���ã�
	 * ��	 ����int uMicID ��˷�ID
	 * ��    �ã�pszCmd { "cmd":"SetMic", "params":{"uMicID":0} }
	 * �ɹ����أ�ppszRes { "code":0, "data":{} }
	 * ʧ�ܷ��أ�ppszRes { "code":1, "data":{} }
	 **/
	
	/**
	 * ��    �ڣ�JSON����ͳһ�ӿ� SetPublishVolum
	 * �ӿڹ��ܣ������豸��������.�������ڷ��������е��ã�
	 * ��	 ����int uVolum,	����.
	 *			 bool bMute		�Ƿ���
	 * ��    �ã�pszCmd { "cmd":"SetPublishVolum", "params":{"uVolum":80,"bMute":false} }
	 * �ɹ����أ�ppszRes { "code":0, "data":{} }
	 * ʧ�ܷ��أ�ppszRes { "code":1, "data":{} }
	 **/

	//----------------------RTMP_PUBLISHģʽ����-------------------------------------
	/**
	 * �ӿڹ��ܣ�JSON����ͳһ�ӿ�
	 * ��    ����mode ���ò���ģʽ 
	 *			 pszCmd	JSON��ʽ����
	 *			 ppszRes JSON��ʽ���
	 * �� �� ֵ���ɹ�/ʧ��
	 * ʾ    ����mode   RTMP_PLAY ���ò��Ų���
	 * ʾ    ����pszCmd { "cmd":"xxx", "params":{"x":true, "xx":12, "xxx":"abc"} }
	 * ʾ    ����ppszRes { "code":0, "data":{"reason":"abc"} }
	 * ˵    ����code���� 0��success��1��fail
	 **/
	virtual bool CallInJson(RtmpModel model, const char* pszCmd, char** ppszRes) = 0;

	/*
	�ӿڹ��ܣ�	����VIS������������ SetPublishPlayAndStart ֮ǰ���ã�
	��    ����	httpUrl VIS �����ַ
				strPubApp VIS ʹ�õ�app
				strPubStream VIS ʹ�õ�stream
				strPassword  VIS ����
	�� �� ֵ��	true -- �ɹ� 	false -- ʧ��
	*/

	virtual bool SetPubPlayUrlPara(const char* httpUrl,const char* strPubApp,const char* strPubStream, const char* strPassword)=0;

	/*
	�ӿڹ��ܣ�	����VIS
	��    ����	hPlayVideo ���ž��
				hPublishVideo ������
	�� �� ֵ��	true -- �ɹ� 	false -- ʧ��
	*/

	virtual bool SetPublishPlayAndStart(HWND hPlayVideo, HWND hPublishVideo)=0;

	/*
	�ӿڹ��ܣ�	ֹͣVIS
	��    ����	��
	�� �� ֵ��	true -- �ɹ� 	false -- ʧ��
	*/

	virtual bool StopPublishPlay()=0;

	/*
	�ӿڹ��ܣ�	�ͷ�VIS����
	��    ����	��
	�� �� ֵ��	��
	*/

	virtual void Release()=0;
};

extern "C" __declspec(dllexport) IPublicPlay* CreatePublicPlay(IPublicPlayNotify* pNotify); 

