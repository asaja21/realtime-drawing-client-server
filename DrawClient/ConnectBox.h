#pragma once
#include "resource.h"

class ConnectBox : public CDialog
{
    
	DECLARE_DYNAMIC(ConnectBox)

public:
    ConnectBox (CWnd* pParent = NULL);
    virtual ~ConnectBox();

//Attributs
public : 
    CString AddrServ; 

// Données de boîte de dialogue
	enum { IDD = IDD_DIALOG1 };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
};

