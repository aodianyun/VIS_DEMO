#pragma once

typedef enum RTMPMODEL{
	RTMP_NULL = 0,
	RTMP_PLAY,		// 播放参数
	RTMP_PUBLISH	// 上麦参数
}RtmpModel;

// VIS 通知类
class IPublicPlayNotify
{
public:

	/**
	 * 接    口：OnRtmpPublishManagerMsg
	 * 接口功能：上麦消息回调
	 * 参    数：MsgLev	消息级别 MSG_DEBUG=0, MSG_WARNING=1, MSG_ERR=2
	 *           pMsg	消息主体
	 * 调    用：pszCmd { "cmd":"OnRtmpPublishManagerMsg", "params":{"MsgLev":1,"pMsg":"OnNotifyFail",} }
	 **/

	/**
	 * 接    口：OnRtmpPlayManagerMsg
	 * 接口功能：播放消息回调
	 * 参    数：MsgLev	消息级别 MSG_DEBUG=0, MSG_WARNING=1, MSG_ERR=2
	 *           pMsg	消息主体
	 *           pDetail消息详细说明
	 * 调    用：pszCmd { "cmd":"OnRtmpPlayManagerMsg", "params":{"MsgLev":1,"pMsg":"OnRtmpDead","pDetail":"NetConnection.Connect.Closed"} }
	 **/

	/**
	 * 接    口：OnRtmpPublishPlayState
	 * 接口功能：VIS启动状态回调
	 * 参    数：MsgLev	消息级别 MSG_DEBUG=0, MSG_WARNING=1, MSG_ERR=2
	 *           pMsg	消息主体
	 *           pDetail消息详细说明
	 * 调    用：pszCmd { "cmd":"OnRtmpPlayManagerMsg", "params":{"MsgLev":1,"pMsg":{"code":"-1",message:"varify faild",...},"pDetail":"NetConnection.Connect.Closed"} }
	 **/

	/**
	 * 接口功能：JSON回调统一接口
	 * 参    数：pszJson	JSON格式字符串
	 * 返 回 值：成功/失败
	 * 示    例：{ "cmd":"xxx", "params":{"x":true, "xx":12, "xxx":"abc"} }
	 **/
	virtual bool OnRtmpPublishOrPlayNotifyInJson(const char* pszJson){ return true; };
};

class IPublicPlay{
public: 
	//----------------------RTMP_PLAY模式开始-------------------------------------
	/**
	* 接    口：JSON调用统一接口 SetAdPara
	* 接口功能：设置播放音量  （可以在播放过程中调用）
	* 参	数：int uOutVolum,	音量
	*			bool bMute		是否静音
	* 调    用：pszCmd { "cmd":"SetAdPara", "params":{"uOutVolum":80,bMute:false} }
	* 返回：无
	**/	

	/**
	* 接    口：JSON调用统一接口 GetAudioPlayDevList
	* 接口功能：获取播放设备列表 （必须在 SetPublishPlayAndStart 之前调用）
	* 调    用：pszCmd { "cmd":"GetAudioPlayDevList", "params":{} }
	* 成功返回：ppszRes { "code":0, "data":{"player":["dirsound", "guagua"]} }
	* 失败返回：ppszRes { "code":1, "data":{} }
	**/

	/**
	* 接    口：JSON调用统一接口 SetAudioPlayDev
	* 接口功能：设置播放设备ID （必须在 SetPublishPlayAndStart 之前调用）
	* 参	数：int uDevID      (播放设备ID(count from 0))
	* 调    用：pszCmd { "cmd":"SetAudioPlayDev", "params":{"uDevID":1} }
	* 成功返回：ppszRes { "code":0, "data":{} }
	* 失败返回：ppszRes { "code":1, "data":{} }
	**/

	//----------------------RTMP_PLAY模式结束-------------------------------------

	//----------------------RTMP_PUBLISH模式开始-------------------------------------



	/**
	 * 接    口：JSON调用统一接口 GetCamList
	 * 接口功能：获取摄像头列表（必须在 StartPublish 之前调用）
	 * 调    用：pszCmd { "cmd":"GetCamList", "params":{} }
	 * 成功返回：ppszRes { "code":0, "data":{"cameras":["cam1", "cam2"]} }
	 * 失败返回：ppszRes { "code":1, "data":{} }
	 **/

	/**
	 * 接    口：JSON调用统一接口 GetMicList
	 * 接口功能：获取摄像头列表（必须在 StartPublish 之前调用）
	 * 调    用：pszCmd { "cmd":"GetMicList", "params":{} }
	 * 成功返回：ppszRes { "code":0, "data":{"mics":["mic1", "mic2"]} }
	 * 失败返回：ppszRes { "code":1, "data":{} }
	 **/

	/**
	 * 接    口：JSON调用统一接口 SetCam
	 * 接口功能：设置摄像头ID. （必须在 StartPublish 之前调用）
	 * 参	 数：int uCamID 摄像头ID
	 * 调    用：pszCmd { "cmd":"SetCam", "params":{"uCamID":0} }
	 * 成功返回：ppszRes { "code":0, "data":{} }
	 * 失败返回：ppszRes { "code":1, "data":{} }
	 **/

	/**
	 * 接    口：JSON调用统一接口 SetMic
	 * 接口功能：设置摄像头ID. （必须在 StartPublish 之前调用）
	 * 参	 数：int uMicID 麦克风ID
	 * 调    用：pszCmd { "cmd":"SetMic", "params":{"uMicID":0} }
	 * 成功返回：ppszRes { "code":0, "data":{} }
	 * 失败返回：ppszRes { "code":1, "data":{} }
	 **/
	
	/**
	 * 接    口：JSON调用统一接口 SetPublishVolum
	 * 接口功能：设置设备捕获音量.（可以在发布过程中调用）
	 * 参	 数：int uVolum,	音量.
	 *			 bool bMute		是否静音
	 * 调    用：pszCmd { "cmd":"SetPublishVolum", "params":{"uVolum":80,"bMute":false} }
	 * 成功返回：ppszRes { "code":0, "data":{} }
	 * 失败返回：ppszRes { "code":1, "data":{} }
	 **/

	//----------------------RTMP_PUBLISH模式结束-------------------------------------
	/**
	 * 接口功能：JSON调用统一接口
	 * 参    数：mode 设置参数模式 
	 *			 pszCmd	JSON格式命令
	 *			 ppszRes JSON格式结果
	 * 返 回 值：成功/失败
	 * 示    例：mode   RTMP_PLAY 设置播放参数
	 * 示    例：pszCmd { "cmd":"xxx", "params":{"x":true, "xx":12, "xxx":"abc"} }
	 * 示    例：ppszRes { "code":0, "data":{"reason":"abc"} }
	 * 说    明：code含义 0：success，1：fail
	 **/
	virtual bool CallInJson(RtmpModel model, const char* pszCmd, char** ppszRes) = 0;

	/*
	接口功能：	设置VIS参数（必须在 SetPublishPlayAndStart 之前调用）
	参    数：	httpUrl VIS 请求地址
				strPubApp VIS 使用的app
				strPubStream VIS 使用的stream
				strPassword  VIS 密码
	返 回 值：	true -- 成功 	false -- 失败
	*/

	virtual bool SetPubPlayUrlPara(const char* httpUrl,const char* strPubApp,const char* strPubStream, const char* strPassword)=0;

	/*
	接口功能：	启动VIS
	参    数：	hPlayVideo 播放句柄
				hPublishVideo 上麦句柄
	返 回 值：	true -- 成功 	false -- 失败
	*/

	virtual bool SetPublishPlayAndStart(HWND hPlayVideo, HWND hPublishVideo)=0;

	/*
	接口功能：	停止VIS
	参    数：	无
	返 回 值：	true -- 成功 	false -- 失败
	*/

	virtual bool StopPublishPlay()=0;

	/*
	接口功能：	释放VIS对象
	参    数：	无
	返 回 值：	无
	*/

	virtual void Release()=0;
};

extern "C" __declspec(dllexport) IPublicPlay* CreatePublicPlay(IPublicPlayNotify* pNotify); 

