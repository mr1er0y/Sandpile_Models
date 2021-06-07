#ifndef CHOOSECOLOR_H
#define CHOOSECOLOR_H

#include <QDialog>
#include <QColorDialog>
#include "mainwindow.h"


namespace Ui {
class ChooseColor;
}

class ChooseColor : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseColor(MainWindow *m_window, QWidget *parent = nullptr);
    ~ChooseColor();

private:
    QImage *block;

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_clicked();

private:
    MainWindow *main_window;
    Ui::ChooseColor *ui;
};

#endif // CHOOSECOLOR_H
