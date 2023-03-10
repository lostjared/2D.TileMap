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
#include<QProcess>
#include<QThread>

MainWindow::MainWindow() {
    file_name = "Untitled.lvl";
    map_init = false;
    pos_x = pos_y = 0;
    setGeometry(230, 10, 1280, 720+offset_y);
    setFixedSize(1280, 720+offset_y);
    setWindowIcon(QIcon(":/images/col1.bmp"));
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

    run_window = new RunWindow(this);
    run_window->setMainWindow(this);
    run_window->hide();

    debug_window = new DebugWindow(this);
    debug_window->setGeometry(230, 830+offset_y, 640, 320);
    debug_window->show();

    gfx_window = new GfxWindow(this);
    gfx_window->setMainWindow(this);
    gfx_window->setGeometry(450, 175, 800, 600);
    gfx_window->hide();

    file_menu = menuBar()->addMenu(tr("&File"));
    file_new = new QAction(tr("New Map"), this);
    connect(file_new, SIGNAL(triggered()), this, SLOT(openNewMenu()));
    file_menu->addAction(file_new);
    file_menu->addSeparator();
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

    file_menu->addSeparator();

    file_exit = new QAction(tr("E&xit"), this);
    connect(file_exit, SIGNAL(triggered()), this, SLOT(shutdownProgram()));
    file_menu->addAction(file_exit);


    level_menu = menuBar()->addMenu(tr("&Level"));
    level_left = new QAction(tr("Scroll Left"));
    connect(level_left, SIGNAL(triggered()), this, SLOT(levelLeft()));
    level_menu->addAction(level_left);

    level_right = new QAction(tr("Scroll Right"));
    connect(level_right, SIGNAL(triggered()), this, SLOT(levelRight()));
    level_menu->addAction(level_right);

    level_up = new QAction(tr("Scroll Up"));
    connect(level_up, SIGNAL(triggered()), this, SLOT(levelUp()));
    level_menu->addAction(level_up);

    level_down = new QAction(tr("Scroll Down"));
    connect(level_down, SIGNAL(triggered()), this, SLOT(levelDown()));
    level_menu->addAction(level_down);
    connect(tool_window->hover_object, SIGNAL(stateChanged(int)), this, SLOT(updateMap(int)));

    level_menu->addSeparator();

    level_gfx = new QAction(tr("Level Graphics"));
    connect(level_gfx, SIGNAL(triggered()), this, SLOT(levelGraphicsOpen()));
    level_menu->addAction(level_gfx);

    run_menu = menuBar()->addMenu(tr("&Run"));
    run_settings = new QAction(tr("Run &Settings"));
    connect(run_settings, SIGNAL(triggered()), this, SLOT(runSettings()));
    run_menu->addAction(run_settings);
    run_menu->addSeparator();
    run_exec = new QAction(tr("&Run"));
    connect(run_exec, SIGNAL(triggered()), this, SLOT(runExec()));
    run_menu->addAction(run_exec);

    setMouseTracking(true);
    debug_window->clear();
    debug_window->Log("editor: successfully initalized..\n");
    cursor_visible = false;
}

void MainWindow::closeEvent(QCloseEvent *) {
    if(proc_run == true) {
        proc->terminate();
        proc->waitForFinished();
        proc_run = false;
        delete proc;
        proc = nullptr;
    }
}

void MainWindow::shutdownProgram() {
    if(proc_run == true) {
        proc->terminate();
        proc->waitForFinished();
        proc_run = false;
        delete proc;
        proc = nullptr;
    }
    QApplication::exit(0);
}

void MainWindow::readStdout() {
    if(proc_run) {
        QString data = proc->readAll();
        std::cout << data.toStdString() << "\n";
        debug_window->Log(data);
    }
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter paint(this);
    paint.fillRect(QRect(0, 0, 1280, 720), QColor(255,255,255));
    for(int i = 0; i < MAP_WIDTH; ++i) {
        for(int z = 0; z < MAP_HEIGHT; ++z) {
            int x = (i*16)+offset_x;
            int y = (z*16)+offset_y;
            game::Tile *tile = level.at(pos_x+i, pos_y+z);
            if(map_init == false) {
                paint.fillRect(QRect(x, y, 15, 15), QColor(0, 0, 0));
            } else {
                paint.drawImage((i*16)+offset_x, (z*16)+offset_y, images[tile->img]);
            }
        }
    }
    drawLayer1(paint);
    drawLayer2(paint);
    drawLayer3(paint);

    if(cursor_visible == true) {
        QImage &img = (tool_window->hover_object->isChecked()) ? col[tool_window->tile_objects->currentIndex()] : images[tool_window->tiles->currentIndex()];
        int cx = draw_pos.x(), cy = draw_pos.y();
        int zx = 0, zy = 0;
        if(game::atPoint(cx, cy-offset_y, 16, 16, zx, zy)) {
            cx = (zx*16)+offset_x, cy = (zy*16)+offset_y;
            paint.drawImage(cx, cy, img);
            paint.fillRect(QRect(cx, cy-1, img.width(), 1), QColor(qRgb(255, 255, 255)));
            paint.fillRect(QRect(cx, cy+img.height(), img.width(), 1), QColor(qRgb(255, 255, 255)));
            paint.fillRect(QRect(cx, cy-1, 1, img.height()), QColor(qRgb(255,255,255)));
            paint.fillRect(QRect(cx+img.width(), cy-1, 1, img.height()), QColor(qRgb(255,255,255)));
        }
    }
}

void MainWindow::updateMap(int) {        
    update();
}

void MainWindow::drawLayer1(QPainter & paint) {
    for(int i = 0; i < MAP_WIDTH; ++i) {
        for(int z = 0; z < MAP_HEIGHT; ++z) {
            int x = (i*16)+offset_x;
            int y = (z*16)+offset_y;
            game::Tile *tile = level.at(pos_x+i, pos_y+z);
            if(tile != nullptr) {
                if(tile->layers[0] > 0 && tile->layers[0] <= col.size()) {
                    paint.drawImage(x, y, col[tile->layers[0]-1]);
                }
            }
        }
    }
}
 
void MainWindow::drawLayer2(QPainter & /*paint*/) {

}
 
void MainWindow::drawLayer3(QPainter & /*paint*/) {

}

void MainWindow::mouseMoveEvent(QMouseEvent *e) {
    if(map_init == true) { 
            cursor_visible = true;
            draw_pos = e->pos();
    } 
    if(e->buttons() & Qt::MouseButton::LeftButton) {
        setTile(e->pos());
    } else if(e->buttons() & Qt::MouseButton::RightButton) {
        setObject(e->pos());
    } 
    update();
    
}

void MainWindow::mousePressEvent(QMouseEvent *e) {
    if(e->button() == Qt::MouseButton::LeftButton) {
        setTile(e->pos());
        update();
    } else if(e->button() == Qt::MouseButton::RightButton) {
        setObject(e->pos());
        update();
    }
}

void MainWindow::leaveEvent(QEvent *) {
   cursor_visible = false;
   update();
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
    tool_window->camera_x->setSliderPosition(pos_x);
    tool_window->camera_y->setSliderPosition(pos_y);
    updateLabelText();
    update();
}


void MainWindow::setTile(const QPoint &pos) {
    if(map_init == true) {
        int x,y;
        if(game::atPoint(pos.x(), pos.y()-offset_y,16,16,x, y)) {
            game::Tile *tile = level.at(pos_x+x, pos_y+y);
            if(tile != nullptr) {
                //tile->img = 2;
                switch(tool_window->tool->currentIndex()) {
                    case 0:
                        tile->setTile(tiles[tool_window->tiles->currentIndex()]);
                    break;
                    case 1:
                        tile->setTile(tiles[0]);
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

void MainWindow::setObject(const QPoint &pos) {
    if(map_init == true) {
        if(tool_window->tool->currentIndex() == 1) {
            int width = col[tool_window->tile_objects->currentIndex()].width();
            int height = col[tool_window->tile_objects->currentIndex()].height();
            int px = pos.x();
            int py = pos.y()-offset_y;
            for(int i = 0; i < MAP_WIDTH; ++i) {
                for(int z = 0; z < MAP_HEIGHT; ++z) {
                    game::Tile *tile = level.at(pos_x+i, pos_y+z);
                    if(tile != nullptr) {
                        int x = (i*16-16);
                        int y = (z*16-16);
                        if(tile->layers[0] > 0) {
                            if(px >= x && px <= x+width && py >= y && py <= y+height) {
                                tile->layers[0] = 0;
                                return;
                            }
                        }
                    }
                }
            }
            return;
        }
        int x,y;
        if(game::atPoint(pos.x(), pos.y()-offset_y, 16,16, x, y)) {
            game::Tile *tile = level.at(pos_x+x, pos_y+y);
            if(tile != nullptr) {
                switch(tool_window->tool->currentIndex()) {
                    case 0:
                        tile->layers[0] = tool_window->tile_objects->currentIndex()+1;
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
    tool_window->camera_x->setSliderPosition(0);
    tool_window->camera_y->setSliderPosition(0);
    map_init = true;
    update();
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
                msgbox.setIcon(QMessageBox::Icon::Warning);
                msgbox.setWindowIcon(QIcon(":/images/col1.bmp"));
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
                msgbox.setIcon(QMessageBox::Icon::Warning);
                msgbox.setWindowIcon(QIcon(":/images/col1.bmp"));
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
            msgbox.setIcon(QMessageBox::Icon::Warning);
            msgbox.setWindowIcon(QIcon(":/images/col1.bmp"));
            msgbox.exec();
        }
    }
}

void MainWindow::levelUp() {
   if(pos_y > 0) pos_y--;
    tool_window->camera_y->setSliderPosition(pos_y);
    updateLabelText();
    update();
}
 
void MainWindow::levelDown() {
    if(pos_y < level.height - (720/16))
        pos_y++;

    tool_window->camera_y->setSliderPosition(pos_y);
    updateLabelText();
    update();
}

void MainWindow::levelLeft() {
    if(pos_x > 0)
        pos_x--;

    tool_window->camera_x->setSliderPosition(pos_x);
    updateLabelText();
    update();
}

void MainWindow::levelRight() {
    if(pos_x < level.width - (1280/16))
        pos_x++;
    tool_window->camera_x->setSliderPosition(pos_x);
    updateLabelText();
    update();
}

void MainWindow::levelGraphicsOpen() {
    gfx_window->show();
}


void MainWindow::runSettings() {
    run_window->show();
}

void MainWindow::procStopped(int, QProcess::ExitStatus) {
    std::cout << proc->readAllStandardOutput().toStdString();
    run_exec->setText(tr("&Run"));
    debug_window->Log("editor: Map successfully exited. ");
    proc_run = false;
}

void MainWindow::runExec() {
    saveFile();
    if(file_name != "Untitled.lvl") {
        QString path = run_window->exec_path->text();
        if(proc_run == false) {
            proc = new QProcess(this);
            QStringList args;
            args << file_name;
            connect(proc, SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(procStopped(int, QProcess::ExitStatus)));
            connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(readStdout()));
            proc->setWorkingDirectory(path+"/");
            proc->start(path+"/test-game", args);
            if(proc->waitForStarted()) {
                run_exec->setText(tr("&Stop"));
                debug_window->clear();
                debug_window->Log("editor: Started Level: " + file_name + "\n");
                proc_run = true;
            }
            else {
                run_exec->setText(tr("&Run"));
                delete proc;
                proc = nullptr;
                QMessageBox msgbox;
                msgbox.setText("Error on execution of map executable");
                msgbox.setWindowTitle("Error loading map");
                msgbox.setIcon(QMessageBox::Icon::Warning);
                msgbox.setWindowIcon(QIcon(":/images/col1.bmp"));
                msgbox.exec();
                debug_window->Log("editor: Could not open map executable file: " + path+"/test-game");
            }
        } else {
            proc->terminate();
            proc->waitForFinished();
            proc_run = false;
            delete proc;
            proc = nullptr;
            run_exec->setText(tr("&Run"));
        }
    } else {
        QMessageBox msgbox;
        msgbox.setText("You must create a map");
        msgbox.setWindowTitle("Error loading map");
        msgbox.setIcon(QMessageBox::Icon::Warning);
        msgbox.setWindowIcon(QIcon(":/images/col1.bmp"));
        msgbox.exec();
    }
}


void MainWindow::loadImages() {
    const char *fileNames[] = {  "black.bmp", "bluebrick.bmp", "bluesky.bmp", "brick.bmp", "eblock.bmp", "red_brick.bmp", "sand1.bmp", "sand2.bmp", "snow.bmp", "stone.bmp", "stone2.bmp", "stone3.bmp", "stone4.bmp", "grass.bmp", 0 };
    for(uint8_t i = 0; fileNames[i] != 0; ++i) {
        QString fn;
        QTextStream stream(&fn);
        stream << ":/images/" << fileNames[i];
        images.append(QImage(fn));
        tiles.append(game::Tile{0, 1, i});
    }

    tiles[0].solid = 0;
    tiles[2].solid = 0;

    for(int i = 1; i <= 6; ++i) {
        QString text;
        QTextStream stream(&text);
        stream << ":/images/col" << i << ".bmp";
        QImage img(text);
        QImage img_t = img.convertToFormat(QImage::Format_ARGB32);
        for(int i = 0; i < img.width(); ++i) {
            for(int z = 0; z < img.height(); ++z) {
                if(img_t.pixel(i, z) == qRgb(255, 255, 255)) {
                    img_t.setPixel(i, z, qRgba(0, 0, 0, 0));
                }
            }
        }
        col.append(img_t);
    }
    col.append(QImage(":/images/tree.png"));
}