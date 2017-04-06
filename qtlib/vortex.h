#ifndef VORTEX_H
#define VORTEX_H

#include <QSplashScreen>
#include "../qt/helpers.h"
#include "vortexbrowser.h"

class vortex : public QSplashScreen
{
Q_OBJECT
public:
    vortexbrowser* m_pLucyBrowser;
    helpers* m_phelpers;
    explicit vortex(QWidget * parent, QString sUrl, helpers* pHelpers, const QPixmap & pixmap = QPixmap(), Qt::WindowFlags f = 0);
    void show();

protected:
    void closeEvent(QCloseEvent *e);
    void setup(QString sUrl);

signals:

public slots:

};

#endif // VORTEX_H
