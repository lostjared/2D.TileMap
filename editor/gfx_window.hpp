#ifndef _GFX_WINDOW_H__
#define _GFX_WINDOW_H__

#include<QDialog>

class GfxWindow : public QDialog {
    Q_OBJECT
public:
    GfxWindow(QWidget *parent = 0);

};


#endif