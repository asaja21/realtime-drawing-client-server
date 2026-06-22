
// ChildView.cpp : implémentation de la classe CChildView
//

#include "stdafx.h"
#include "DrawClient.h"
#include "ChildView.h"
#include "ConnectBox.h"
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView(): m_gdi(true), m_connected(false)
{
    m_socket.SetParent(this);
}

CChildView::~CChildView() 
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
    ON_COMMAND(ID_CONNECT, &CChildView::OnConnectCmd)
    ON_UPDATE_COMMAND_UI(ID_CONNECT, &CChildView::OnUpdateConnectCmd)
    ON_COMMAND(ID_GDI, &CChildView::OnGdi)
    ON_UPDATE_COMMAND_UI(ID_GDI, &CChildView::OnUpdateGdi)
    ON_COMMAND(ID_GDI_PLUS, &CChildView::OnGdiPlus)
    ON_UPDATE_COMMAND_UI(ID_GDI_PLUS, &CChildView::OnUpdateGdiPlus)
    ON_COMMAND(ID_EFFACER, &CChildView::OnEffacer)
END_MESSAGE_MAP()



// gestionnaires de messages pour CChildView

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // contexte de périphérique pour la peinture
	
	// TODO : ajoutez ici le code de votre gestionnaire de messages
	
	// Ne pas appeler CWnd::OnPaint() pour la peinture des messages
}

void CChildView::OnConnectCmd()
{
    if(!m_connected)
    {
        ConnectBox dlg;
        dlg.AddrServ = "127.0.0.1"; //TODO : on doit pouvoir récupérer l'entrée de l'utilisateur 
	    if(dlg.DoModal()!=IDOK) return; 
        m_socket.Create();
        m_socket.Connect(dlg.AddrServ,SERVER_PORT);
    }else{
	    m_socket.Close();
        m_connected = false;

    }
}

void CChildView::OnUpdateConnectCmd(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_connected);
    // TODO : ajoutez ici le code du gestionnaire d'interface utilisateur de mise à jour des commandes
}

void CChildView::OnGdi()
{
    m_gdi = true;
    // TODO : ajoutez ici le code de votre gestionnaire de commande
}

void CChildView::OnUpdateGdi(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_gdi);
    // TODO : ajoutez ici le code du gestionnaire d'interface utilisateur de mise à jour des commandes
}


void CChildView::OnGdiPlus()
{
    m_gdi = false;
    // TODO : ajoutez ici le code de votre gestionnaire de commande
}

void CChildView::OnUpdateGdiPlus(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(!m_gdi);
    // TODO : ajoutez ici le code du gestionnaire d'interface utilisateur de mise à jour des commandes
}
void CChildView::OnEffacer()
{
    Invalidate();
    // TODO : ajoutez ici le code de votre gestionnaire de commande
}


void CChildView::OnDataReceived(int x0, int y0, int x1, int y1)
{
    CDC* dc = GetDC();
        if (m_gdi) {
            CPen pen(PS_SOLID, 3, RGB(255, 0, 0));
            CPen* old = dc->SelectObject(&pen);
            dc->MoveTo(x0, y0);
            dc->LineTo(x1, y1);
            dc->SelectObject(old);
        } else {

			Graphics g(dc->m_hDC);
			Point points[4];
			points[0].X = 0;points[0].Y = 0;
			points[1].X = 0;points[1].Y = 100;
			points[3].X = 100;points[3].Y = 0;
			points[2].X = 100;points[2].Y = 100;
			Color colors[] = {Color(255, 255, 0, 0),  // (0, 0) red
                  Color(255, 0, 255, 0),    // (160, 200) green
                  Color(255, 0, 0, 255),  // (80, 150) blue
                  Color(255, 255, 255, 0)};
			int count = 4;

			PathGradientBrush brush (points, 4, WrapModeTileFlipXY);
			brush.SetSurroundColors(colors, &count);
			brush.SetCenterColor(Color(255,0,0,0));
			Pen pen(&brush, 10);
			pen.SetStartCap(LineCapRound);
			pen.SetEndCap(LineCapRound);
			g.DrawLine(&pen,x0, y0, x1, y1);
        }
        ReleaseDC(dc);   
}