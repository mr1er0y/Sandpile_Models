#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QDialog>
#include <QString>
#include "mainwindow.h"

namespace Ui {
class Settings_dialog;
}

class Settings_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Settings_dialog(MainWindow *m_window,QWidget *parent = nullptr);
    ~Settings_dialog();

private slots:
    void on_Settings_dialog_finished(int result);

    void on_listWidget_currentTextChanged(const QString &currentText);

private:
    MainWindow *main_window;
    QString current_Text;
    Ui::Settings_dialog *ui;
};

#endif // SETTINGS_DIALOG_H
