
// pubishPlayDemoDlg.h : ͷ�ļ�
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

// CpubishPlayDemoDlg �Ի���
class CpubishPlayDemoDlg : public CDialogEx, public IPublicPlayNotify, public IRtmpPlayManagerNotify
{
// ����
public:
	CpubishPlayDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PUBISHPLAYDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:
	// ��ȡ����ʾ�豸�б�
	bool GetAndShowList();
	virtual bool OnRtmpPublishOrPlayNotifyInJson(const char* pszJson);
	
	// ���ŵĻص��ӿ�
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
	// �������
	string					m_strHttpPublishAddr;
	string					m_strPublishApp;
	string					m_strPublishStream;
	string					m_strPublishPwd;
	// ���Ų���
	string					m_strPlayAddr;
	string					m_strPlayApp;
	string					m_strPlayStream;
protected:
	// ����Ĭ�ϲ���
	void SetDefaultPara();
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
