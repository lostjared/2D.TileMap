#ifndef _PREF_WINDOW_H_
#define _PREF_WINDOW_H_


#include<QDialog>

class MainWindow;

class PrefWindow : public QDialog {
    Q_OBJECT
public:
    PrefWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
protected:
    MainWindow *main_window;

};




#endif