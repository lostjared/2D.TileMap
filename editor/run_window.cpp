#include"run_window.hpp"
#include"main_window.hpp"
#include<QLabel>

RunWindow::RunWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(400, 400);

    QLabel *lbl_exec = new QLabel(tr("Path: "), this);
    lbl_exec->setGeometry(10, 10, 50, 20);
    exec_path = new QLineEdit(this);
    exec_path->setGeometry(50, 10, 330, 20);
    exec_path->setText("../test-game");
}

void RunWindow::setMainWindow(MainWindow *main) {
    main_window = main;
}