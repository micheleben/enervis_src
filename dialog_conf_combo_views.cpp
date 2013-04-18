#include "dialog_conf_combo_views.h"
#include "ui_dialog_conf_combo_views.h"

Dialog_conf_combo_views::Dialog_conf_combo_views(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_conf_combo_views)
{
    ui->setupUi(this);
    //combo view selector
    for (int i = 0; i <gDefinedComboViews->Number_of_defined_combo_views; i++){
        ui->cmb_combo_sel->addItem((QString::fromUtf8(gDefinedComboViews->view_combo_vector.at(i).Name.c_str())));
    }
    connect(ui->cmb_combo_sel,SIGNAL(activated(const QString &)),this,SLOT(on_cmb_combo_sel_activated(const QString &)));
    //doubled combo view check box
    connect(ui->chk_combo_double,SIGNAL(clicked()),this,SLOT(on_chk_combo_double_clicked()));
    //view activation check box
    connect(ui->chk_isActive,SIGNAL(clicked()),this,SLOT(on_chk_isActive_clicked()));
    ui->chk_isActive->setChecked(gDefinedComboViews->isActive );
    /////////////////////////////////////////////////////////////////////
    //select the first view
    ui->cmb_combo_sel->setCurrentIndex(0);
    on_cmb_combo_sel_activated(ui->cmb_combo_sel->currentText());
}

Dialog_conf_combo_views::~Dialog_conf_combo_views()
{
    delete ui;
}

void Dialog_conf_combo_views::on_chk_isActive_clicked()
{
   gDefinedComboViews->isActive = ui->chk_isActive->isChecked();
   //update values for acquisition. This will stop the acquisition if it's running
   gAcquisition->update_values();
}

void Dialog_conf_combo_views::on_cmb_combo_sel_activated(const QString &arg1)
{
    int item = ui->cmb_combo_sel->currentIndex();
    //set the current item in class view container
    gDefinedComboViews->selection = item;
    //update the UI
    ui->textEdit->setText(QString::fromUtf8(gDefinedComboViews->view_combo_vector.at(item).Description.c_str()));
    ui->chk_combo_double->setChecked(gDefinedComboViews->view_combo_vector.at(item).get_isDoubled());
    //update values for acquisition. This will stop the acquisition if it's running
    gAcquisition->update_values();
}

void Dialog_conf_combo_views::on_chk_combo_double_clicked()
{
    gDefinedComboViews->view_combo_vector.at(gDefinedComboViews->selection).set_isDoubled(ui->chk_combo_double->isChecked());
    //update values for acquisition. This will stop the acquisition if it's running
    gAcquisition->update_values();
}

void Dialog_conf_combo_views::Visualize_new_Combo_Frame(){
    //visualize the image in the label
    QImage leftimage((uchar*)gCV_MAT_FRAME_VIEW_COMBO->data,gCV_MAT_FRAME_VIEW_COMBO->cols,gCV_MAT_FRAME_VIEW_COMBO->rows,gCV_MAT_FRAME_VIEW_COMBO->step,QImage::Format_RGB888);
    ui->lbl_combo->setPixmap(QPixmap::fromImage(leftimage));
}
