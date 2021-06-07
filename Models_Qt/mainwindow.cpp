#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sandpile.h"
#include <QColor>
#include <QBuffer>
#include <settings_dialog.h>
#include <choosecolor.h>
#include <limits>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), timer{this}, ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->coord_x->setMaximum(ui->display->width() - 1);
    ui->coord_y->setMaximum(ui->display->height() - 1 );
    model = new Sandpile(ui->display->height(), ui->display->width());
    ui->spinbox_reset->setMaximum(model->stability);
    image = new QImage(ui->display->width(), ui->display->height(), QImage::Format_RGB32);
    ui->display->setPixmap(QPixmap::fromImage(*image));
    connect(&timer, &QTimer::timeout, this, &MainWindow::work);
    timer.start(10);
    ui->num_grains->setMaximum(INT_MAX);

    colormaps = {qRgb(255, 255, 0), qRgb(0, 125, 52), qRgb(0, 125, 255), qRgb(139, 0, 255), qRgb(255, 10, 10), qRgb(10, 255, 141)};

}

void MainWindow::render() {
    ui->display->setPixmap(QPixmap::fromImage(*image));
    update();
}

void MainWindow::change_screen_resolution(int height_arg, int width_arg)
{
    int height = height_arg;
    int width = width_arg;
    delete image;
    this->resize(width + ui->menu_right->width(), height + ui->statusbar->height());
    ui->display->resize(width, height);
    model->change_settings(width, height);
    ui->display->move(0,0);
    ui->menu_right->resize(ui->menu_right->width(), height);
    ui->menu_right->move(width, 0);
    ui->coord_x->setMaximum(width - 1);
    ui->coord_y->setMaximum(height - 1);

    image = new QImage(ui->display->width(), ui->display->height(), QImage::Format_RGB32);
    statusBar()->showMessage(tr("New resolution"), 2000);

}


void MainWindow::work() {
    bool flag = true;
    for (int y = 0; y < model->height; ++y) {
        for (int x = 0; x < model->width; ++x) {
            if (model->matrix[y][x] > model->stability) {
                Point a(x, y);
                model->landslide(a, 0);
                flag = false;
            }
            QRgb value = colormaps[model->matrix[y][x] % (model->stability + 1)];
            image->setPixel(y, x, value);

//            switch (model->matrix[y][x]) {
//                case 0:
//                    value = qRgb(255, 255, 0); //yellow
//                    image->setPixel(y, x, value);
//                    break;
//                case 1:
//                    value = qRgb(0, 125, 52); // green
//                    image->setPixel(y, x, value);
//                    break;
//                case 2:
//                    value = qRgb(0, 125, 255); // blue light
//                    image->setPixel(y, x, value);
//                    break;
//                case 3:
//                    value = qRgb(139, 0, 255); // purple
//                    image->setPixel(y, x, value);
//                    break;
//                case 4:
//                    value = qRgb(255, 10, 10); // red
//                    image->setPixel(y, x, value);
//                    break;
//                case 5:
//                    value = qRgb(10, 255, 141); // green light
//                    image->setPixel(y, x, value);
//                    break;
//                default:
//                    value = qRgb(0, 0, 0); // black
//                    image->setPixel(y, x, value);
//                    break;
//            }
        }
    }
    if(flag) {
        // Stop approximation
        statusBar()->showMessage(tr("Approximation finished"), 500);
        //timer.stop();
    }
    render();
}

void MainWindow::change_state_list_mebius(bool v, bool h)
{
    model->v_teleport = v;
    model->h_teleport = h;
}

void MainWindow::change_type_of_model(int type)
{
    model->change_type(type);
    ui->spinbox_reset->setMaximum(model->stability);
    QString str = QString::number(type);
    statusBar()->showMessage(str, 2000);
}

MainWindow::~MainWindow() {
    delete model;
    delete ui;
    delete image;
}


void MainWindow::on_Button_Save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Open Image"), "/home/Sandplie", tr("Image Files (*.png *.jpg *.bmp)"));
    if( image->save(fileName, "PNG") ){
        statusBar()->showMessage(tr("Sucsesseful save file"), 2000);
    }
    else{
        statusBar()->showMessage(tr("Failed save file"), 2000);
    }
}

void MainWindow::on_Button_add_clicked()
{
//    ui->coord_x
     model->add_pieces(ui->num_grains->value(), ui->coord_y->value(), ui->coord_x->value());

}



void MainWindow::on_Button_pause_clicked()
{
    timer.stop();
}

void MainWindow::on_Button_play_clicked()
{
    timer.start(100);
}

void MainWindow::on_Settings_triggered()
{
    Settings_dialog extra_window(this);
    extra_window.setWindowTitle("Settings");
    extra_window.setModal(true);
    extra_window.exec();
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();
    if(e->button() == Qt::LeftButton && x < ui->display->width() && y < ui->display->height() ){
        QString str = QString::number(x) + " " + QString::number(y);
        statusBar()->showMessage(str, 2000);
        ui->coord_x->setValue(x);
        ui->coord_y->setValue(y);
    }


}

void MainWindow::on_Button_reset_clicked()
{
    model->change_settings(ui->display->width(),ui->display->height(), ui->spinbox_reset->value());
}

void MainWindow::on_action_triggered()
{
    ChooseColor extra_window(this);
    extra_window.setWindowTitle("Colors");
    extra_window.setModal(true);
    extra_window.exec();
}
