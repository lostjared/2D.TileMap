#include"new_window.hpp"
#include"main_window.hpp"
#include<QLabel>

NewWindow::NewWindow(game::Level *lvl, QWidget *parent) : QDialog(parent), level{lvl} {
    setFixedSize(640, 320);
    setWindowTitle(tr("Create a New Map"));
    setWindowIcon(QIcon(":/images/col2.bmp"));
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

    QLabel *gfx_lbl = new QLabel(tr("Gfx File: "), this);
    gfx_lbl->setGeometry(25, 55, 75, 25);
    gfx_box = new QComboBox(this);
    gfx_box->setGeometry(75, 55, 200, 25);

    gfx_box->addItem("level.gfx");
    gfx_box->setCurrentIndex(0);

    page_new_gfx = new QPushButton(tr("New"), this);
    page_new_gfx->setGeometry(285, 55, 50, 25);
    connect(page_new_gfx, SIGNAL(clicked()), this, SLOT(createNewGfx()));

}

void NewWindow::createNewGfx() {
    main_window->showGfx();
}


void NewWindow::setMainWindow(MainWindow *w) {
    main_window = w;
}

void NewWindow::createMap() {
    int width = page_width1->text().toInt();
    int height = page_height1->text().toInt();
    level->create(1280/16 * width, 720/16 * height, game::Tile{});
    main_window->createdNewMap();
    hide();
}