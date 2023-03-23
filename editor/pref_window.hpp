#ifndef _PREF_WINDOW_H_
#define _PREF_WINDOW_H_


#include<QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>

class MainWindow;

class PrefWindow : public QDialog {
    Q_OBJECT
public:
    PrefWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *m);
public slots:
    void saveDetails();
    
protected:
    MainWindow *main_window;

    QLineEdit *pref_pen_w, *pref_pen_h;
    QPushButton *pref_save;
};




#endif