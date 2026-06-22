#ifndef DRAWSERVER_H
#define DRAWSERVER_H

#include <QtGui/QMainWindow>
#include "ui_drawserver.h"

class DrawServer : public QMainWindow
{
    Q_OBJECT

public:
    DrawServer(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~DrawServer();

private:
    Ui::DrawServerClass ui;
};

#endif // DRAWSERVER_H
