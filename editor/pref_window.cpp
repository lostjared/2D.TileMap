#include"pref_window.hpp"
#include"main_window.hpp"

PrefWindow::PrefWindow(QWidget *parent) : QDialog(parent) {


}

void PrefWindow::setMainWindow(MainWindow *m) {
    main_window = m;
}