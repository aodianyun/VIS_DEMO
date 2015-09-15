
// pubishPlayDemoDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "IRtmpPlayManager.h"
#include "IRtmpPublishPlayParent_c.h"
#include "ConvertString.h"
#include "json/json.h"
#include <iostream>
using namespace std;


#define WM_JSONMESSAGE	WM_USER+1

// CpubishPlayDemoDlg 对话框
class CpubishPlayDemoDlg : public CDialogEx, public IPublicPlayNotify, public IRtmpPlayManagerNotify
{
// 构造
public:
	CpubishPlayDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PUBISHPLAYDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public:
	// 获取和显示设备列表
	bool GetAndShowList();
	virtual bool OnRtmpPublishOrPlayNotifyInJson(const char* pszJson);
	
	// 播放的回调接口
public:
	virtual bool OnRtmpPlayManagerMsg(eMsgLevel MsgLev, const char *pMsg, const char *pDetail = NULL);
	virtual bool OnRtmpPlayManagerNetInfo(RtmpPublishNetInfo &RtmpNetInfo);
	virtual bool OnRtmpPlayManagerComputerStatusInfo(RtmpPublishComputerStatusInfo &RtmpStatusInfo);
	virtual bool OnRtmpPlayManagerAVInfo(RtmpPlayAVInfo &RtmpPlayAVInfo);
	virtual bool OnRtmpPlayManagerPlayQuality(RtmpPlayQuality &RtmpPlayQuality);
	virtual bool OnRtmpPlayNotifyInJson(const char* pszJson);
private:
	IRtmpPlayManager*		m_pPlayManager;
private:
	Json::Value				m_jsonRoot;
	Json::Value				m_jsonParams;
	bool					m_bChange;
	IPublicPlay				*m_pPublicPlay;
	
private:
	// 上麦参数
	string					m_strHttpPublishAddr;
	string					m_strPublishApp;
	string					m_strPublishStream;
	string					m_strPublishPwd;
	// 播放参数
	string					m_strPlayAddr;
	string					m_strPlayApp;
	string					m_strPlayStream;
protected:
	// 设置默认参数
	void SetDefaultPara();
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnJsonNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ComboBoxVideo;
	CComboBox m_ComboBoxMic;
	CComboBox m_ComboBoxAudioPlay;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonSwitch();
	CListBox m_MsgList;
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonPlayStart();
	afx_msg void OnBnClickedButtonPlayStop();
};
