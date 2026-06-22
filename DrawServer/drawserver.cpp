#include "drawserver.h"

DrawServer::DrawServer(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
  ui.setupUi(this);
  QChildView* pView = qobject_cast<QChildView*>(centralWidget());
  connect(ui.m_quit,SIGNAL(triggered()),this,SLOT(close()));
  connect(ui.m_disconnectAll,SIGNAL(triggered()),pView,SLOT(on_Disconnect_All()));
  pView->Msg("DrawServer : qchildview créé");
}

DrawServer::~DrawServer()
{

}
