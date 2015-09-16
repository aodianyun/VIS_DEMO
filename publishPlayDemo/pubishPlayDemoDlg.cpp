
// pubishPlayDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pubishPlayDemo.h"
#include "pubishPlayDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


bool OnRtmpPublishOrPlayNotifyInJson(const char* message)
{
	return true;
}


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CpubishPlayDemoDlg 对话框



CpubishPlayDemoDlg::CpubishPlayDemoDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CpubishPlayDemoDlg::IDD, pParent), m_pPublicPlay(NULL), m_pPlayManager(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CpubishPlayDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_VIDEO, m_ComboBoxVideo);
	DDX_Control(pDX, IDC_COMBO_AUDIO, m_ComboBoxMic);
	DDX_Control(pDX, IDC_COMBO_PLAYAUDIO, m_ComboBoxAudioPlay);
	DDX_Control(pDX, IDC_LIST1, m_MsgList);
}

BEGIN_MESSAGE_MAP(CpubishPlayDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SWITCH, &CpubishPlayDemoDlg::OnBnClickedButtonSwitch)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CpubishPlayDemoDlg::OnBnClickedButtonStop)
	ON_MESSAGE(WM_JSONMESSAGE,OnJsonNotify)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_START, &CpubishPlayDemoDlg::OnBnClickedButtonPlayStart)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_STOP, &CpubishPlayDemoDlg::OnBnClickedButtonPlayStop)
END_MESSAGE_MAP()


// CpubishPlayDemoDlg 消息处理程序

BOOL CpubishPlayDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_pPublicPlay = CreatePublicPlay(this);
	m_pPlayManager = CreateRtmpPlayManager(this);
	if (!m_pPublicPlay || !m_pPlayManager)
	{
		return FALSE;
	}
	// TODO:  在此添加额外的初始化代码
	GetAndShowList();
	SetDefaultPara();
	m_bChange = true;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CpubishPlayDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CpubishPlayDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CpubishPlayDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


bool CpubishPlayDemoDlg::OnRtmpPublishOrPlayNotifyInJson(const char* pszJson)
{

	string* pString = new string;
	*pString = pszJson;
	PostMessage(WM_JSONMESSAGE, 0, (WPARAM)pString);
	return true;
}

LRESULT CpubishPlayDemoDlg::OnJsonNotify(WPARAM wParam, LPARAM lParam)
{
	string *pString = (string*)lParam;
	int iLineNum = m_MsgList.GetCount();
	if (iLineNum <= 200)
	{
		//m_MsgList.AddString(ConvertString::s2ws(strMsg).c_str());
		m_MsgList.InsertString(0, ConvertString::s2ws(*pString).c_str());
	}
	else
	{
		//m_MsgList.DeleteString(0); 
		m_MsgList.DeleteString(iLineNum - 1);
	}
	delete pString;
	return 0;
}

bool CpubishPlayDemoDlg::GetAndShowList()
{
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

BOOL CpubishPlayDemoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case  VK_ESCAPE:
			return TRUE;
		case  VK_RETURN:
			return TRUE;
		default:
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CpubishPlayDemoDlg::SetDefaultPara()
{
	m_strHttpPublishAddr = "http://vis.aodianyun.com:5000/RequestPublish";
	m_strPublishApp = "demo";
	m_strPublishStream = "visdemo";
	m_strPublishPwd = "123456";
	GetDlgItem(IDC_EDIT_PUBLISHADDR)->SetWindowTextW((ConvertString::s2ws(m_strHttpPublishAddr)).c_str());
	GetDlgItem(IDC_EDIT_PUBLISHAPP)->SetWindowTextW(ConvertString::s2ws(m_strPublishApp).c_str());
	GetDlgItem(IDC_EDIT_PUBLISHSTREAM)->SetWindowTextW(ConvertString::s2ws(m_strPublishStream).c_str());
	GetDlgItem(IDC_EDIT_PUBLISHPWD)->SetWindowTextW(ConvertString::s2ws(m_strPublishPwd).c_str());

	//play param
	m_strPlayAddr = "rtmp://lssplay.aodianyun.com:1935";
	m_strPlayApp = "demo";
	m_strPlayStream = "visdemo";
	GetDlgItem(IDC_EDIT_PLAYADDR)->SetWindowTextW((ConvertString::s2ws(m_strPlayAddr)).c_str());
	GetDlgItem(IDC_EDIT_PLAYAPP)->SetWindowTextW(ConvertString::s2ws(m_strPlayApp).c_str());
	GetDlgItem(IDC_EDIT_PLAYSTREAM)->SetWindowTextW(ConvertString::s2ws(m_strPlayStream).c_str());
}

void CpubishPlayDemoDlg::OnBnClickedButtonSwitch()
{
	// TODO:  在此添加控件通知处理程序代码
	(CStatic*)GetDlgItem(IDC_STATIC_PUBLISH)->ShowWindow(SW_NORMAL);
	(CStatic*)GetDlgItem(IDC_STATIC_PLAY)->ShowWindow(SW_NORMAL);
	(CStatic*)GetDlgItem(IDC_STATIC_PUBLISH2)->ShowWindow(SW_HIDE);
	(CStatic*)GetDlgItem(IDC_STATIC_PLAY2)->ShowWindow(SW_HIDE);

	if (!m_pPublicPlay)
	{
		m_pPublicPlay = CreatePublicPlay(this);
	}

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
		// SetAudioPara
		//m_jsonRoot.clear();
		//m_jsonParams.clear();
		//m_jsonRoot["cmd"] = Json::Value("SetPublishAudioPara");
		//m_jsonParams["iSampleRate"] = Json::Value(44100);
		//m_jsonParams["iChannels"] = Json::Value(2);
		//m_jsonParams["iBitPerSample"] = Json::Value(16);
		//m_jsonParams["iBitRate"] = Json::Value(32000);
		//m_jsonParams["iVolum"] = Json::Value(80);
		//m_jsonParams["bMute"] = Json::Value(false);
		//m_jsonRoot["params"] = m_jsonParams;
		//strCmd = m_jsonRoot.toStyledString();
		//memset(pszRes, 0, sizeof(pszRes));
		//if (!m_pPublicPlay->CallInJson(RTMP_PUBLISH, strCmd.c_str(), &pszRes))
		//{
		//	return;
		//}


		wchar_t buf[100] = { L'0' };
		GetDlgItem(IDC_EDIT_PUBLISHADDR)->GetWindowText(buf, sizeof(buf));
		m_strHttpPublishAddr = ConvertString::ws2s(wstring(buf));
		GetDlgItem(IDC_EDIT_PUBLISHAPP)->GetWindowText(buf, sizeof(buf));
		m_strPublishApp = ConvertString::ws2s(wstring(buf));
		GetDlgItem(IDC_EDIT_PUBLISHSTREAM)->GetWindowText(buf, sizeof(buf));
		m_strPublishStream = ConvertString::ws2s(wstring(buf));
		GetDlgItem(IDC_EDIT_PUBLISHPWD)->GetWindowText(buf, sizeof(buf));
		m_strPublishPwd = ConvertString::ws2s(wstring(buf));

		m_pPublicPlay->SetPubPlayUrlPara(m_strHttpPublishAddr.c_str(), m_strPublishApp.c_str(), m_strPublishStream.c_str(), m_strPublishPwd.c_str());

		//SetPublishVideoPara(320,240,10,160000,GetDlgItem(IDC_STATIC_PLAY)->m_hWnd,30);
		m_pPublicPlay->SetPublishPlayAndStart(GetDlgItem(IDC_STATIC_PLAY)->m_hWnd, GetDlgItem(IDC_STATIC_PUBLISH)->m_hWnd);
	delete[] pszRes;
}


void CpubishPlayDemoDlg::OnBnClickedButtonStop()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_pPublicPlay)
	{
		m_pPublicPlay->StopPublishPlay();
		m_pPublicPlay->Release();
		m_pPublicPlay = NULL;
	}
	CRect rectPublish, rectPlay;
	((CStatic*)GetDlgItem(IDC_STATIC_PUBLISH))->GetWindowRect(&rectPublish);
	((CStatic*)GetDlgItem(IDC_STATIC_PLAY))->GetWindowRect(&rectPlay);
	(CStatic*)GetDlgItem(IDC_STATIC_PUBLISH)->ShowWindow(SW_HIDE);
	(CStatic*)GetDlgItem(IDC_STATIC_PLAY)->ShowWindow(SW_HIDE);
	ScreenToClient(&rectPublish);
	((CStatic*)GetDlgItem(IDC_STATIC_PUBLISH2))->MoveWindow(rectPublish);
	ScreenToClient(&rectPlay);
	((CStatic*)GetDlgItem(IDC_STATIC_PLAY2))->MoveWindow(rectPlay);
	(CStatic*)GetDlgItem(IDC_STATIC_PUBLISH2)->ShowWindow(SW_NORMAL);
	(CStatic*)GetDlgItem(IDC_STATIC_PLAY2)->ShowWindow(SW_NORMAL);
}


// 播放回调接口实现
bool CpubishPlayDemoDlg::OnRtmpPlayManagerMsg(eMsgLevel MsgLev, const char *pMsg, const char *pDetail)
{
	return true;
}
bool CpubishPlayDemoDlg::OnRtmpPlayManagerNetInfo(RtmpPublishNetInfo &RtmpNetInfo)
{
	return true;
}
bool CpubishPlayDemoDlg::OnRtmpPlayManagerComputerStatusInfo(RtmpPublishComputerStatusInfo &RtmpStatusInfo)
{
	return true;
}
bool CpubishPlayDemoDlg::OnRtmpPlayManagerAVInfo(RtmpPlayAVInfo &RtmpPlayAVInfo)
{
	return true;
}
bool CpubishPlayDemoDlg::OnRtmpPlayManagerPlayQuality(RtmpPlayQuality &RtmpPlayQuality)
{
	return true;
}
bool CpubishPlayDemoDlg::OnRtmpPlayNotifyInJson(const char* pszJson)
{
	return true;
}

void CpubishPlayDemoDlg::OnBnClickedButtonPlayStart()
{
	if (!m_pPlayManager)
	{
		m_pPlayManager = CreateRtmpPlayManager(this);
	}

	wchar_t buf[100] = { L'0' };
	GetDlgItem(IDC_EDIT_PLAYADDR)->GetWindowText(buf, sizeof(buf));
	string m_strScheduleSvr = ConvertString::ws2s(wstring(buf));
	GetDlgItem(IDC_EDIT_PLAYAPP)->GetWindowText(buf, sizeof(buf));
	string strApp = ConvertString::ws2s(wstring(buf));
	GetDlgItem(IDC_EDIT_PLAYSTREAM)->GetWindowText(buf, sizeof(buf));
	string m_strPublishStageInfo = ConvertString::ws2s(wstring(buf));

	m_pPlayManager->SetAudioPlayDev(m_ComboBoxAudioPlay.GetCurSel());
	m_pPlayManager->SetStreamInfo(m_strScheduleSvr.c_str(), /*m_strPublishSiteInfo*/strApp.c_str(), m_strPublishStageInfo.c_str());
	m_pPlayManager->SetVdDisplayWnd(GetDlgItem(IDC_STATIC_MERGE)->m_hWnd);
	m_pPlayManager->SetAdPara(80, false);
	m_pPlayManager->StartPlay();
}


void CpubishPlayDemoDlg::OnBnClickedButtonPlayStop()
{
	if (m_pPlayManager){
		m_pPlayManager->StopPlay();
		m_pPlayManager->Release();
		m_pPlayManager = NULL;
	}
}
