#include <afxsock.h>
// Socket MyClientSocket qui s'occupe de la connexion en réseau, reception/transfert à la fenêtre des données, déconnexion


#pragma once

class CChildView;

class MyClientSocket : public CAsyncSocket
{

public:
    CChildView* m_pParent; //La fenêtre à laquelle sera liée notre socket

    
public:
    //Construction
    MyClientSocket() : m_pParent(0) {};
    virtual ~MyClientSocket(){};


    void SetParent(CChildView* pParent) {m_pParent = pParent; } //Cette méthode sera utlisée dans le constructeur de la fenêtre

    //Réseau
    virtual void OnReceive(int nErrorCode);
    virtual void OnConnect(int nErrorCode);
    virtual void OnClose(int nErrorCode);


};

