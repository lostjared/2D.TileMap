#include"run_window.hpp"
#include"main_window.hpp"
#include<QLabel>
#include<QDir>

RunWindow::RunWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(400, 400);
    setWindowTitle(tr("Run Settings"));
    setWindowIcon(QIcon(":/images/col3.bmp"));
    QLabel *lbl_exec = new QLabel(tr("Path: "), this);
    lbl_exec->setGeometry(10, 10, 50, 20);
    exec_path = new QLineEdit(this);
    exec_path->setGeometry(50, 10, 330, 20);
    
    exec_path->setText(QDir::currentPath()+"/..");
    QLabel *lbl_res = new QLabel(tr("Resolution: "), this);
    lbl_res->setGeometry(10, 40, 100, 25);
    exec_res = new QComboBox(this);
    exec_res->setGeometry(100, 40, 400-110, 25);
    exec_res->addItem("640x360");
    exec_res->addItem("1280x720");
    exec_res->addItem("1920x1080");
    exec_res->addItem("3840x2160");
    exec_res->setCurrentIndex(1);
}

void RunWindow::setMainWindow(MainWindow *main) {
    main_window = main;
}