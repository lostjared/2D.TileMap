#ifndef _GFX_WINDOW_H__
#define _GFX_WINDOW_H__

#include<QDialog>
#include<QComboBox>
#include<QListView>

class MainWindow;

class GfxWindow : public QDialog {
    Q_OBJECT
public:
    GfxWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *main);
protected:
    MainWindow *main_window;
    QComboBox *image_type;
    QListView *image_list;

};


#endif