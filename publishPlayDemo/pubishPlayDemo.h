
// pubishPlayDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CpubishPlayDemoApp: 
// �йش����ʵ�֣������ pubishPlayDemo.cpp
//

class CpubishPlayDemoApp : public CWinApp
{
public:
	CpubishPlayDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CpubishPlayDemoApp theApp;