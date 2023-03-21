#ifndef _OPEN_WINDOW_H__
#define _OPEN_WINDOW_H__

#include<QDialog>

class MainWindow;

class OpenWindow : public QDialog {
    Q_OBJECT
public:
    OpenWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
protected:
    MainWindow *main_window;
};


#endif