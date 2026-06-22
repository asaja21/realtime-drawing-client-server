
// DrawClient.h : fichier d'en-tête principal pour l'application DrawClient
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"       // symboles principaux


// CDrawClientApp:
// Consultez DrawClient.cpp pour l'implémentation de cette classe
//

class CDrawClientApp : public CWinApp
{
public:
	CDrawClientApp();


// Substitutions
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implémentation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDrawClientApp theApp;
