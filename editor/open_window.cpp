#include "open_window.hpp"
#include"main_window.hpp"

OpenWindow::OpenWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(320, 240);
}

void OpenWindow::setMainWindow(MainWindow *main) {
    main_window = main;
}