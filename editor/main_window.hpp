#ifndef _EDITOR_H__
#define _EDITOR_H__

#include<QMainWindow>

const int MAP_WIDTH=1280/16;
const int MAP_HEIGHT=720/16;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    void paintEvent(QPaintEvent *p);
    
};



#endif