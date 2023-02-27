#include"new_window.hpp"
#include<QLabel>

NewWindow::NewWindow(game::Level *lvl, QWidget *parent) : QDialog(parent), level{lvl} {
    setFixedSize(640, 320);
    setWindowTitle(tr("New Map"));
    page_width1 = new QLineEdit("2", this);
    page_height1 = new QLineEdit("2", this);

    QLabel *lbl_width = new QLabel(tr("Width: "), this);
    QLabel *lbl_height = new QLabel(tr("Height: "), this);

    lbl_width->setGeometry(25, 25, 75, 20);
    page_width1->setGeometry(100, 25, 100, 20);
    lbl_height->setGeometry(225, 25, 75, 20);
    page_height1->setGeometry(300, 25, 100, 20);

    page_create = new QPushButton(tr("Create"), this);
    page_create->setGeometry(640-125, 320-35, 100, 25);
    connect(page_create, SIGNAL(clicked()), this, SLOT(createMap()));
}

void NewWindow::createMap() {
    int width = page_width1->text().toInt();
    int height = page_height1->text().toInt();
    level->create(1280/16 * width, 720/16 * height, game::Tile{});
}