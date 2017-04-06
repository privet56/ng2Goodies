#include "vortexbrowser.h"

vortexbrowser::vortexbrowser(QWidget *parent) : lucybrowser(parent)
{
}
void vortexbrowser::mousePressEvent(QMouseEvent* event)
{
    QWidget* p = this->parentWidget();
    if(p)p->close();
}
