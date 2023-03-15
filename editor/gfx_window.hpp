#ifndef _GFX_WINDOW_H__
#define _GFX_WINDOW_H__

#include<QDialog>
#include<QComboBox>
#include<QListView>
#include<QPushButton>

class MainWindow;

class GfxWindow : public QDialog {
    Q_OBJECT
public:
    GfxWindow(QWidget *parent = 0);
    void setMainWindow(MainWindow *main);

public slots:
    void addFile();
    void rmvFile();
    void exportFile();
    
protected:
    MainWindow *main_window;
    QComboBox *image_type;
    QListView *image_list;
    QPushButton *image_add, *image_remove, *image_build;

};


#endif