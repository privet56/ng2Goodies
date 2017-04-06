#ifndef VORTEXBROWSER_H
#define VORTEXBROWSER_H

#include "../qt/helpers.h"
#include "lucybrowser.h"

class vortexbrowser : public lucybrowser
{
Q_OBJECT
public:
    explicit vortexbrowser(QWidget *parent = 0);
    virtual void mousePressEvent(QMouseEvent* event);

signals:

public slots:

};

#endif // VORTEXBROWSER_H
