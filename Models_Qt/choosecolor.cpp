#include "choosecolor.h"
#include "ui_choosecolor.h"
#include <QColorDialog>
#include <QImage>

ChooseColor::ChooseColor(MainWindow *m_window, QWidget *parent) :
    QDialog(parent),
    main_window(m_window),
    ui(new Ui::ChooseColor)
{
    ui->setupUi(this);
    block = new QImage(ui->d_block->width(), ui->d_block->height(), QImage::Format_RGB32);
    block->fill(main_window->colormaps[0]);
    ui->d_block->setPixmap(QPixmap::fromImage(*block));
    ui->spinBox->setMaximum(main_window->colormaps.size()-1);

}

ChooseColor::~ChooseColor()
{

    delete block;
    delete ui;
}

void ChooseColor::on_spinBox_valueChanged(int arg1)
{
    block->fill(main_window->colormaps[arg1]);
    ui->d_block->setPixmap(QPixmap::fromImage(*block));
    update();
}

void ChooseColor::on_pushButton_clicked()
{
    QColor col = QColorDialog::getColor();
    main_window->colormaps[ui->spinBox->value()] = col.rgb();
    block->fill(main_window->colormaps[ui->spinBox->value()]);
    ui->d_block->setPixmap(QPixmap::fromImage(*block));
    update();
}
