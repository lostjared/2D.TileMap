#include"gfx_window.hpp"
#include"main_window.hpp"
#include"../gfx_file.hpp"
#include<QLabel>
#include<QListWidgetItem>
#include<QFileDialog>
#include<QMessageBox>

GfxWindow::GfxWindow(QWidget *parent) : QDialog(parent) {
    setFixedSize(400, 400);
    setWindowTitle("Graphics");
    setWindowIcon(QIcon(":/images/col3.bmp"));
    QLabel *lbl_type = new QLabel(tr("Image Type:"), this);
    lbl_type->setGeometry(10, 10, 75, 20);
    image_type = new QComboBox(this);
    image_type->setGeometry(80, 10, 300, 25);
    image_type->addItem(tr("Tile"));
    image_type->addItem(tr("Object"));
    image_type->setCurrentIndex(0);
    image_list = new QListWidget(this);
    image_list->setGeometry(10, 50, 380, 300);
    image_add = new QPushButton(tr("+"), this);
    image_add->setGeometry(10,360,50, 25);
    image_remove = new QPushButton(tr("-"), this);
    image_remove->setGeometry(65,360,50,25);
    image_solid = new QCheckBox(tr("Solid"), this);
    image_solid->setGeometry(65+50+5,360,50,25);
    image_build = new QPushButton(tr("Export"), this);
    image_build->setGeometry(400-10-60, 360, 60, 25);

    connect(image_add, SIGNAL(clicked()), this, SLOT(addFile()));
    connect(image_remove, SIGNAL(clicked()), this, SLOT(rmvFile()));
    connect(image_build, SIGNAL(clicked()), this, SLOT(exportFile()));
    connect(image_type, SIGNAL(currentIndexChanged(int)), this, SLOT(setIndex(int)));
    
}

void GfxWindow::setMainWindow(MainWindow *main) {
    main_window = main;
}

void GfxWindow::updateList() {

    image_list->clear();

    switch(image_type->currentIndex()) {
        case 0:
        for(int i = 0; i < tile_list.size(); ++i) {
            image_list->addItem(tile_list[i]);
        }
        break;
        case 1:
        for(int i = 0; i < object_list.size(); ++i) {
            image_list->addItem(object_list[i]);
        }
        break;
    }
}

void GfxWindow::setIndex(int) {
    updateList();    
}

void GfxWindow::addFile() {
    QStringList filename = QFileDialog::getOpenFileNames(this, "Add Image", "", "Bitmaps (*.bmp)");
    if(filename.size() > 0) {
        for(int i = 0; i < filename.size(); ++i) {
            QString text;
            QTextStream stream(&text);
            stream << filename[i] << ":";
            if(image_solid->isChecked() == true) {
                stream << "1";
            } else {
                stream << "0";
            }
            switch(image_type->currentIndex()) {
                case 0:
                    tile_list.append(text);
                     break;
                case 1:
                    object_list.append(text);
                    break;
            }
        }
        updateList();
    }
}

void GfxWindow::rmvFile() {

}

void GfxWindow::exportFile() {
    QString outfile = QFileDialog::getSaveFileName(this, "Export File", "", "Gfx Files (*.gfx)");

    static auto toTextSolid = [](const std::string &text, int &solid, std::string &file) {
            auto pos = text.rfind(":");
            solid = atoi(text.substr(pos+1, text.length()).c_str());
            file = text.substr(0, pos);
    };

    if(outfile != "") {

        game::GfxTable table;
        for(int i = 0; i < tile_list.size(); ++i) {
            int solid;
            std::string file;
            toTextSolid(tile_list[i].toStdString(), solid, file);
            table.addItem(i, solid, 0, file);
        }
        for(int i = 0; i < object_list.size(); ++i) {
            int solid;
            std::string file;
            toTextSolid(object_list[i].toStdString(), solid, file);
            table.addItem(i, solid, 1, file);
        }

        game::GfxCompress cmp;
        if(cmp.open(outfile.toStdString())) {
            if(cmp.compress(table)) {
                QMessageBox msgbox;
                msgbox.setText(tr("Successfully wrote file"));
                msgbox.setWindowTitle(tr("Sucess"));
                msgbox.setIcon(QMessageBox::Icon::Information);
                msgbox.exec();
                cmp.close();
                main_window->setNewGfx(outfile);
                //main_window->new_window->gfx_box->addItem(outfile);
                //main_window->new_window->gfx_box->setCurrentIndex()
            } else {
                QMessageBox msgbox;
                msgbox.setText(tr("Could not write file error"));
                msgbox.setWindowTitle(tr("Error"));
                msgbox.setIcon(QMessageBox::Icon::Warning);
                msgbox.exec();
            }
        }
    }
}
    