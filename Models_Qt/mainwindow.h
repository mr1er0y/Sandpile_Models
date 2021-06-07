#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QFileDialog>
#include <QMouseEvent>
#include <QVector>
#include <QColor>
#include "sandpile.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    void render();

    void change_screen_resolution(int height_arg, int width_arg);
    void change_state_list_mebius(bool v, bool h);
    void change_type_of_model(int type);
    ~MainWindow();
    QVector<QRgb> colormaps;

private:
    QImage *image;
    QTimer timer;
    Sandpile *model;
    QMouseEvent *mouse;
    Ui::MainWindow *ui;

protected:
    void mousePressEvent(QMouseEvent *e);
private slots:
    void work();

    void on_Button_Save_clicked();
    void on_Button_add_clicked();

    void on_Button_pause_clicked();
    void on_Button_play_clicked();
    void on_Settings_triggered();
    void on_Button_reset_clicked();
    void on_action_triggered();
};
#endif // MAINWINDOW_H
