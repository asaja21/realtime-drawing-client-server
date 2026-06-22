#include "StdAfx.h"
#include "MyClientSocket.h"
#include "ChildView.h"


void MyClientSocket::OnReceive(int nErrorCode)
{
    int val[4];

    if(Receive((char*)val, sizeof(val)) == sizeof(val))
    {
        if (m_pParent)
        {
            m_pParent->OnDataReceived(val[0],val[1],val[2],val[3]);
            //TODO : on passe les données à la fenêtre ChildView
        }
    }
    __super::OnReceive(nErrorCode);
}

void MyClientSocket::OnConnect(int nErrorCode)//Signal (CALLBACK) reçu si notre demande de connexion "Connect(m_addr,SERV_PORT)" a été validée
{

	if(nErrorCode==0){ //nErrorCode = 0 donc connexion acceptée
        if (m_pParent){
            m_pParent->m_connected = true;
            m_pParent->Invalidate(); // La fenêtre se redéssine
        }
        linger l={1,0}; //Si la connexion est fermée, le socket n'attend pas que les derniers paquets
		SetSockOpt(SO_LINGER, &l, sizeof(l));
	}
	else{
        if (m_pParent) m_pParent->m_connected = false;
		Close();
		m_pParent->MessageBox(_T("Connexion MBANG"), _T("Erreur"),MB_OK|MB_ICONHAND);
	}
	__super::OnConnect(nErrorCode);
}

void MyClientSocket::OnClose(int nErrorCode)
{
	Close();
    m_pParent->MessageBox(_T("Connexion fermée"), _T("Erreur"),MB_OK|MB_ICONHAND);
    if (m_pParent) {
        m_pParent->m_connected = false;
        //m_pParent->Invalidate(); // Optionnel : pour mettre à jour l'UI
    }
	__super::OnClose(nErrorCode);
}