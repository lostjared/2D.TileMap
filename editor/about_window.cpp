#include"about_window.hpp"
#include<QLabel>
#include<QIcon>
// About Window constructor - (init)
AboutWindow::AboutWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(350, 120);
    setWindowTitle(tr("About"));
    setWindowIcon(QIcon(":/images/bluebrick.bmp"));
    QLabel *lbl_img = new QLabel(this);
    lbl_img->setGeometry(25, 25, 64, 64);
    lbl_img->setPixmap(QPixmap(":/images/brick.bmp").scaled(QSize(64, 64)));
    QLabel *lbl_txt = new QLabel(this);
    lbl_txt->setText(tr("(C) 2023 LostSideDead Software - GPL v3"));
    lbl_txt->setGeometry(25+64+10, 25+16, 250, 45);

}