#include "vortex.h"
#include <QTimer>
#include <QMessageBox>
#include <QMainWindow>

vortex::vortex(QWidget* parent, QString sUrl, helpers* pHelpers, const QPixmap & pixmap, Qt::WindowFlags f):QSplashScreen(parent, pixmap, f)
{
    this->m_phelpers = pHelpers;
    setup(sUrl);
}

void vortex::setup(QString sUrl)
{
    m_pLucyBrowser = new vortexbrowser(this);
    m_pLucyBrowser->load(QUrl(sUrl));
}

void vortex::show()
{
    QSplashScreen::show();

    int w = m_phelpers->GetCFG_int("vortex.width" , m_phelpers->m_pApp, m_phelpers->m_pLogTarget, "", "CFG", "", 333);
    int h = m_phelpers->GetCFG_int("vortex.height", m_phelpers->m_pApp, m_phelpers->m_pLogTarget, "", "CFG", "", 333);
    this->setFixedSize(w,h);
    m_pLucyBrowser->setFixedSize(this->size());
    int iTimeOut = m_phelpers->GetCFG_int("vortex.timeout", m_phelpers->m_pApp, m_phelpers->m_pLogTarget, "", "CFG", "", 5000);
    QTimer::singleShot(iTimeOut, this, SLOT(close()));
}

void vortex::closeEvent(QCloseEvent* e)
{
    QWidget* p = this->parentWidget();
    if(p)p->close();
}
