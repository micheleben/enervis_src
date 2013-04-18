#include "dialog_save_2.h"
#include "ui_dialog_save_2.h"
#include <QFileDialog>

Dialog_save_2::Dialog_save_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_save_2)
{
    ui->setupUi(this);
}

Dialog_save_2::~Dialog_save_2()
{
    delete ui;
}

void Dialog_save_2::on_btn_choose_dir_clicked()
{
    //set the directory where the data has to be saved
    QString path = QFileDialog::getExistingDirectory (this, tr("Directory"), gAcquisition->directory_where_save.path());
    if ( path.isNull() == false )
    {
        gAcquisition->directory_where_save.setPath(path);

    }

}

void Dialog_save_2::on_buttonBox_accepted()
{
    gAcquisition->save_left_view = ui->chk_LV->isChecked();
    gAcquisition->save_right_view = ui->chk_RV->isChecked();
    gAcquisition->save_combo_view = ui->chk_CV->isChecked();
    gAcquisition->number_of_frames = ui->lne_number_of_frames->text().toInt();
    gAcquisition->update_values();

}
