#include "MyClientSocket.h"
#define SERVER_PORT 4040

// ChildView.h : interface de la classe CChildView

#pragma once

// fenêtre CChildView

class CChildView : public CWnd
{
// Construction
public:
    CChildView();

// Attributs
public:
    MyClientSocket m_socket;
    bool m_connected;

protected :
    bool m_gdi;

// Opérations
public:
    void OnDataReceived(int x0, int y0, int x1, int y1);

// Substitutions
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implémentation
public:
	virtual ~CChildView();

// Fonctions générées de la table des messages
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnConnectCmd();
    afx_msg void OnUpdateConnectCmd(CCmdUI *pCmdUI);
    afx_msg void OnGdi();
    afx_msg void OnUpdateGdi(CCmdUI *pCmdUI);
    afx_msg void OnEffacer();
    afx_msg void OnGdiPlus();
    afx_msg void OnUpdateGdiPlus(CCmdUI *pCmdUI);
};

