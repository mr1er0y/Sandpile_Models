#include "settings_dialog.h"
#include "ui_settings_dialog.h"
#include <QString>

Settings_dialog::Settings_dialog(MainWindow *m_window, QWidget *parent) :
    QDialog(parent),
    main_window(m_window),
    ui(new Ui::Settings_dialog)
{
    ui->setupUi(this);
    ui->listWidget->addItems(QStringList({
                                             "600x600",
                                             "720x480",
                                             "720x576",
                                             "800x800",
                                             "1000x1000",
                                             "1200x1200",
                                             "1280x720",
                                             "1920x1080"
                                         }));
    /*,
    "3840x2160 (4k UHD)",
    "7680x4320 (8k UHD)"
    */
    ui->list_grid->setCurrentRow(0);
    ui->listWidget->setCurrentRow(0);

}

Settings_dialog::~Settings_dialog()
{
    delete ui;
}

void Settings_dialog::on_Settings_dialog_finished(int result)
{
    if(!result ) {
        return;
    }
    QStringList lst = current_Text.split(" ").first().split("x");  // for example 10x15

    int resolution_x = lst.first().toInt(), resolution_y = lst.last().toInt();
    main_window->change_screen_resolution(resolution_y, resolution_x);
    main_window->change_state_list_mebius(ui->List_mebius_v->checkState(), ui->List_mebius_h->checkState());
    main_window->change_type_of_model(ui->list_grid->currentRow());


}

void Settings_dialog::on_listWidget_currentTextChanged(const QString &currentText)
{
    current_Text = currentText;
}
