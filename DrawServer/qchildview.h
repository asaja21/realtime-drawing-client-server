#ifndef QCHILDVIEW_H
#define QCHILDVIEW_H

#include <QWidget>
#include <QMainWindow>
#include <QStatusBar>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QByteArray>
#include <QIODevice>
#include <QTimer>
#include <Windows.h>
#include <winsock.h>
#pragma comment(lib, "wsock32.lib")

#define SERVER_PORT 4040
#define MAX_CLIENTS 50

class QChildView : public QWidget
{
    Q_OBJECT
	QTcpServer m_server;
	QTcpSocket* m_clients[MAX_CLIENTS];

public:
    QChildView(QWidget *parent = 0);
    ~QChildView();

protected:

    //Gestion des events souris dans la fenêtre
    void mouseReleaseEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );

    //Dessin 
    void paintEvent ( QPaintEvent * event );

    //Transmission réseau
    void sendSegments();

private:
    QPoint m_ptPrev; //Dernière position connue de la souris
    QPoint m_ptStart; //Point de départ du segment courant à tracer
    QPoint m_ptEnd; //Point d'arrivée du segment courant à tracer
    bool m_bSegment; //flag activé lorsqu'un nouveau segment courant est prêt à être tracer (soit m_ptStart et m_ptEnd mis à jour)
    bool m_bDrawing; //flag activé lorsqu'il y a clic gauche 

public : 

    void Msg(const QString& s)
    {
        QMainWindow* pMainWindow = qobject_cast<QMainWindow*>(parentWidget());
        pMainWindow->statusBar()->showMessage(s);
    }

public slots: 

	void on_connection(){ //Fonction qui s'execute dans notre app serveur lorsqu'un signal de demande de connexion est identifié par le système
		size_t i=0;
		while(m_clients[i] && i < MAX_CLIENTS) ++i; //On parcourt la table des clients pour rechercher l'espace libre
		
		QTcpSocket* s = m_server.nextPendingConnection(); //Permet de stocker le socket du nouveau client dans une var temporaire
		if(i>=MAX_CLIENTS) {
			Msg((QString("Connexion refusée pour %1:%2")).arg(s->peerAddress().toString()).arg(s->peerPort()));
			s->close(); delete s;
		}
		m_clients[i] = s;
		Msg((QString("Connexion acceptée pour %1:%2")).arg(s->peerAddress().toString()).arg(s->peerPort()));
		connect(s, SIGNAL(disconnected()), this, SLOT(on_disconnected()));
		SOCKET s_=(SOCKET)s->socketDescriptor();
        linger opt={1,0};
        setsockopt(s_,SOL_SOCKET,SO_LINGER,(const char*)&opt,sizeof(opt));//dit au kernel :"à la fermeture, ne pas attendre, couper immédiatement"
        
	}

	void on_disconnected(){//Fonction qui s'execute dans notre app serveur lorsqu'un signal de demande de déconnexion est identifié par le système
		QTcpSocket* s = (QTcpSocket*)sender(); //sender permet de remonter vers le client qui a émit le signal de demande de deconnexion
		if(!s) return;
		for(size_t i=0; i<MAX_CLIENTS; ++i){
			if(m_clients[i]!=s) continue;
			m_clients[i] = 0; //Lorsque le client émetteur est identifié, son socket est fermé et la var temporaire "s" est deleted
			s->close();
			s->deleteLater(); //Qt supprime l'objet après que la QEventLoop a fini de traiter l'événement courant
			break;
		}
        Msg("Client déconnecté");
	}

    void on_Disconnect_All()
    {
        QTcpSocket* s;
		for(size_t i=0; i<MAX_CLIENTS; ++i){
			if(m_clients[i])
            {
                s = m_clients[i];
               // s->disconnectFromHost(); //effectue le close() et le deleteLater()
                s->close();
			    s->deleteLater();
			    m_clients[i] = 0;
            } 
		}
        Msg("All clients disconnected");
    }

};

#endif // QCHILDVIEW_H