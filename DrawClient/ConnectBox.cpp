#include "stdafx.h"
#include "ConnectBox.h"
#include "DrawClient.h"


IMPLEMENT_DYNAMIC(ConnectBox, CDialog)

ConnectBox::ConnectBox(CWnd* pParent)
    : CDialog(ConnectBox::IDD, pParent) 
    , AddrServ(_T(""))
{
}

ConnectBox::~ConnectBox()
{
}


void ConnectBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ADDR, AddrServ);
}


BEGIN_MESSAGE_MAP(ConnectBox, CDialog)
END_MESSAGE_MAP()

