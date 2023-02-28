#include"main_window.hpp"
#include<QPainter>
#include<QMenuBar>
#include<QAction>
#include<QDir>
#include<QApplication>
#include<QMouseEvent>
#include<QKeyEvent>
#include<QFileDialog>
#include<QMessageBox>

MainWindow::MainWindow() {
    file_name = "Untitled.lvl";
    map_init = false;
    pos_x = pos_y = 0;
    setGeometry(200, 10, 1280, 720);
    setFixedSize(1280, 720);
    setWindowTitle(tr("Editor [Please Create/Open a Map]"));
    loadImages();

    tool_window = new ToolWindow(this);
    tool_window->setGeometry(10, 10, 150, 480);
    tool_window->show(); 

    connect(tool_window->camera_x, SIGNAL(valueChanged(int)), this, SLOT(cameraChanged(int)));
    connect(tool_window->camera_y, SIGNAL(valueChanged(int)), this, SLOT(cameraChanged(int)));    

    new_window = new NewWindow(&level, this);
    new_window->setMainWindow(this);
    new_window->hide();

    file_menu = menuBar()->addMenu(tr("&File"));
    file_new = new QAction(tr("New Map"), this);
    connect(file_new, SIGNAL(triggered()), this, SLOT(openNewMenu()));
    file_menu->addAction(file_new);
    //setMouseTracking(true);
    file_load = new QAction(tr("Open Map"), this);
    connect(file_load, SIGNAL(triggered()), this, SLOT(loadFile()));
    file_menu->addAction(file_load);
    file_save = new QAction(tr("Save Map"), this);
    connect(file_save, SIGNAL(triggered()), this, SLOT(saveFile()));
    file_menu->addAction(file_save);
    file_save_as = new QAction(tr("Save Map As"), this);
    connect(file_save_as, SIGNAL(triggered()), this, SLOT(saveFileAs()));
    file_menu->addAction(file_save_as);
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter paint(this);
    paint.fillRect(QRect(0, 0, 1280, 720), QColor(255,255,255));
    for(int i = 0; i < MAP_WIDTH; ++i) {
        for(int z = 0; z < MAP_HEIGHT; ++z) {
            int x = i*16;
            int y = z*16;
            game::Tile *tile = level.at(pos_x+i, pos_y+z);
            if(map_init == false) {
                paint.fillRect(QRect(x, y, 15, 15), QColor(0, 0, 0));
            } else {
                paint.drawImage(i*16, z*16, images[tile->img]);
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e) {
    setTile(e->pos());
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *e) {
    if(e->button() == Qt::MouseButton::LeftButton) {
        setTile(e->pos());
        update();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    switch(e->key()) {
        case Qt::Key::Key_Left:
        if(pos_x > 0) pos_x--;
        break;
        case Qt::Key::Key_Right:
        if(pos_x < level.width - (1280/16))
        pos_x++;
        break;
        case Qt::Key::Key_Up:
        if(pos_y > 0) pos_y--;
        break;
        case Qt::Key::Key_Down:
        if(pos_y < level.height - (720/16))
        pos_y++;
        break;
    }
    updateLabelText();
    update();
}


void MainWindow::setTile(const QPoint &pos) {
    if(map_init == true) {
        int x,y;
        if(game::atPoint(pos.x(), pos.y(), x, y)) {
            game::Tile *tile = level.at(pos_x+x, pos_y+y);
            if(tile != nullptr) {
                //tile->img = 2;
                switch(tool_window->tool->currentIndex()) {
                    case 0:
                        *tile = tiles[tool_window->tiles->currentIndex()];
                    break;
                    case 1:
                        *tile = tiles[0];
                    break;
                    case 2:
                       for(int i = pos_x; i < pos_x+(1280/16) && i < level.width; ++i) {
                            for(int z = pos_y; z < pos_y+(720/16) && z < level.height; ++z) {
                                game::Tile *tile = level.at(i, z);
                                if(tile != nullptr) {
                                    *tile = tiles[tool_window->tiles->currentIndex()];
                                }
                            }
                        }
                    break;
                }
            } 
        }
    }
}


void MainWindow::createdNewMap() {
    updateTitle();
    tool_window->camera_x->setMinimum(0);
    tool_window->camera_x->setMaximum(level.width-(1280/16));
    tool_window->camera_y->setMinimum(0);
    tool_window->camera_y->setMaximum(level.height-(720/16));
    map_init = true;
}

void MainWindow::updateTitle() {
    QString title;
    QTextStream stream(&title);
    stream << file_name << " - Map [" << level.width << "x" << level.height << "]";
    setWindowTitle(title);
}


void MainWindow::cameraChanged(int) {
    pos_x = tool_window->camera_x->sliderPosition();
    pos_y = tool_window->camera_y->sliderPosition();
    updateLabelText();
    update();
}

void MainWindow::updateLabelText() {
    QString lbl;
    QTextStream stream(&lbl);
    stream << "Camera X: " << pos_x;
    tool_window->lbl_x->setText(lbl);
    lbl = "";
    stream << "Camera Y: " << pos_y;
    tool_window->lbl_y->setText(lbl);
}


void MainWindow::openNewMenu() {
    new_window->show();
}

void MainWindow::saveFile() {

    if(file_name == "Untitled.lvl")
        saveFileAs();
    else {
        if(!level.saveLevel(file_name.toStdString())) {
                QMessageBox msgbox;
                msgbox.setText("Error on load of map");
                msgbox.setWindowTitle("Error loading map");
                msgbox.exec();
            } else {
                updateTitle();
            }
    }
}


void MainWindow::saveFileAs() {
    if(map_init == true) {
        QString filename = QFileDialog::getSaveFileName(nullptr, tr("Save File"), "", tr("LVL (*.lvl)"));
        if(filename != "") {
            if(!level.saveLevel(filename.toStdString())) {
                QMessageBox msgbox;
                msgbox.setText("Error on load of map");
                msgbox.setWindowTitle("Error loading map");
                msgbox.exec();
            } else {
                file_name = filename;
                updateTitle();
            }
        }
    }
}

void MainWindow::loadFile() {
    QString filename = QFileDialog::getOpenFileName(nullptr, tr("Save File"), "", tr("LVL (*.lvl)"));
    if(filename != "") {
        if(level.loadLevel(filename.toStdString())) {
            createdNewMap();
            file_name = filename;
            updateTitle();
            update();
        } else {
            QMessageBox msgbox;
            msgbox.setText("Could not load map");
            msgbox.setWindowTitle("Error on load");
            msgbox.exec();
        }
    }
}


void MainWindow::loadImages() {
    const char *fileNames[] = {  "black.bmp", "bluebrick.bmp", "bluesky.bmp", "brick.bmp", "eblock.bmp", "red_brick.bmp", "sand1.bmp", "sand2.bmp", "snow.bmp", "stone.bmp", "stone2.bmp", "stone3.bmp", "stone4.bmp", 0 };
    for(uint8_t i = 0; fileNames[i] != 0; ++i) {
        QString fn;
        QTextStream stream(&fn);
        stream << ":/images/" << fileNames[i];
        images.append(QImage(fn));
        tiles.append(game::Tile{0, 1, i});
    }

    tiles[0].solid = 0;
    tiles[2].solid = 0;
}