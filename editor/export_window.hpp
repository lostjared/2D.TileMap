#ifndef _EX_WINDOW_H__
#define _EX_WINDOW_H__

#include<QDialog>

class QComboBox;
class QPushButton;

class ExportWindow : public QDialog {
    Q_OBJECT
public:
    ExportWindow(QWidget *parent = 0);

    QComboBox *export_type;
    QPushButton *export_file;

public slots:
    void exportFile();

};


#endif