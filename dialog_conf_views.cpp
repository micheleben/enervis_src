#include "dialog_conf_views.h"
#include "ui_dialog_conf_views.h"

Dialog_conf_views::Dialog_conf_views(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_conf_views)
{
    ui->setupUi(this);
    ////////////////////////////////////////////////////////////////////////////////////////////
    //threshold slide
    ui->hslid_th_left->setRange(0,127);
    connect(ui->hslid_th_left,SIGNAL(sliderReleased()),this,SLOT(on_hslid_th_left_sliderReleased()));
    ui->hslid_th_right->setRange(0,127);
    connect(ui->hslid_th_right,SIGNAL(sliderReleased()),this,SLOT(on_hslid_th_right_sliderReleased()));
    //gain slide
    ui->hslid_gain_left->setRange(0,6);
    connect(ui->hslid_gain_left,SIGNAL(sliderReleased()),this,SLOT(on_hslid_gain_left_sliderReleased()));
    ui->hslid_gain_right->setRange(0,6);
    connect(ui->hslid_gain_right,SIGNAL(sliderReleased()),this,SLOT(on_hslid_gain_right_sliderReleased()));
    //combo view selector
    for (int i = 0; i <gDefinedViews_left->Number_of_defined_views; i++){
        ui->comboBox->addItem((QString::fromUtf8(gDefinedViews_left->view_vector.at(i).Name.c_str())));
    }
    connect(ui->comboBox,SIGNAL(activated(const QString &)),this,SLOT(on_comboBox_activated(const QString &)));
    for (int i = 0; i <gDefinedViews_right->Number_of_defined_views; i++){
        ui->comboBox_2->addItem((QString::fromUtf8(gDefinedViews_right->view_vector.at(i).Name.c_str())));
    }
    connect(ui->comboBox_2,SIGNAL(activated(const QString &)),this,SLOT(on_comboBox_2_activated(const QString &)));
    //doubled view check box
    connect(ui->chk_double_left,SIGNAL(clicked()),this,SLOT(on_chk_double_left_clicked()));
    connect(ui->chk_double_right,SIGNAL(clicked()),this,SLOT(on_chk_double_right_clicked()));
    //combo interpolation methods
    ui->cmb_double_left->addItem(QString::fromUtf8("Nearest Neighbour"));
    ui->cmb_double_left->addItem(QString::fromUtf8("Bilinear"));
    ui->cmb_double_left->addItem(QString::fromUtf8("Pixel area re-samp."));
    ui->cmb_double_left->addItem(QString::fromUtf8("Bicubic interpol."));
    connect(ui->cmb_double_left,SIGNAL(activated(const QString &)),this,SLOT(on_cmb_double_left_activated(const QString &)));

    ui->cmb_double_right->addItem(QString::fromUtf8("Nearest Neighbour"));
    ui->cmb_double_right->addItem(QString::fromUtf8("Bilinear"));
    ui->cmb_double_right->addItem(QString::fromUtf8("Pixel area re-samp."));
    ui->cmb_double_right->addItem(QString::fromUtf8("Bicubic interpol."));
    connect(ui->cmb_double_right,SIGNAL(activated(const QString &)),this,SLOT(on_cmb_double_right_activated(const QString &)));
    //view activation check box
    connect(ui->chk_View_left,SIGNAL(clicked()),this,SLOT(on_chk_View_left_clicked()));
    connect(ui->chk_View_right,SIGNAL(clicked()),this,SLOT(on_chk_View_right_clicked()));
    ui->chk_View_left->setChecked(gDefinedViews_left->isActive );
    ui->chk_View_right->setChecked(gDefinedViews_right->isActive );
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    //select the first view in both the interface and update the UI
    ui->comboBox->setCurrentIndex(0);
    on_comboBox_activated(ui->comboBox->currentText());
    ui->comboBox->setCurrentIndex(0);
    on_comboBox_2_activated(ui->comboBox_2->currentText());
}

Dialog_conf_views::~Dialog_conf_views()
{
    delete ui;
}



void Dialog_conf_views::on_comboBox_activated(const QString &arg1)
{
    int item = ui->comboBox->currentIndex();
    //set the current item in class view container
    gDefinedViews_left->selection = item;
    //update the UI
    ui->textEdit->setText((QString::fromUtf8(gDefinedViews_left->view_vector.at(item).Description.c_str())));
    ui->hslid_th_left->setValue(gDefinedViews_left->view_vector.at(item).threshold);
    ui->lbl_th_left->setText(QString::number(gDefinedViews_left->view_vector.at(item).threshold));
    ui->hslid_gain_left->setValue(gDefinedViews_left->view_vector.at(item).gain);
    ui->lbl_gain_left->setText(QString ("x%1").arg(gDefinedViews_left->view_vector.at(item).gain));
    ui->chk_double_left->setChecked(gDefinedViews_left->view_vector.at(item).get_isDoubled());
    int item_combo_interpol = get_combo_value_from_enum_type_interp(gDefinedViews_left->view_vector.at(item).interpolation);
    ui->cmb_double_left->setCurrentIndex(item_combo_interpol);
    //update values for acquisition. This will stop the acquisition if it's running
    gAcquisition->update_values();
}

void Dialog_conf_views::on_comboBox_2_activated(const QString &arg1)
{
    int item = ui->comboBox_2->currentIndex();
    //set the current item in class view container
    gDefinedViews_right->selection = item;
    //update the UI
    ui->textEdit_2->setText((QString::fromUtf8(gDefinedViews_right->view_vector.at(item).Description.c_str())));
    ui->hslid_th_right->setValue(gDefinedViews_right->view_vector.at(item).threshold);
    ui->lbl_th_right->setText(QString::number(gDefinedViews_right->view_vector.at(item).threshold));
    ui->hslid_gain_right->setValue(gDefinedViews_right->view_vector.at(item).gain);
    ui->lbl_gain_right->setText(QString ("x%1").arg(gDefinedViews_right->view_vector.at(item).gain));
    ui->chk_double_right->setChecked(gDefinedViews_right->view_vector.at(item).get_isDoubled());
    int item_combo_interpol = get_combo_value_from_enum_type_interp(gDefinedViews_right->view_vector.at(item).interpolation);
    ui->cmb_double_right->setCurrentIndex(item_combo_interpol);
    //update values for acquisition. This will stop the acquisition if it's running
    gAcquisition->update_values();
}

void Dialog_conf_views::on_cmb_double_left_activated(const QString &arg1)
{
    int type_interpolation = get_enum_type_interp_from_combo_value(ui->cmb_double_left->currentIndex());
    gDefinedViews_left->view_vector.at(gDefinedViews_left->selection).interpolation = type_interpolation;
    //update values for acquisition. This will stop the acquisition if it's running
    gAcquisition->update_values();
}

void Dialog_conf_views::on_cmb_double_right_activated(const QString &arg1)
{
    int type_interpolation = get_enum_type_interp_from_combo_value(ui->cmb_double_right->currentIndex());
    gDefinedViews_right->view_vector.at(gDefinedViews_right->selection).interpolation = type_interpolation;
    //update values for acquisition. This will stop the acquisition if it's running
    gAcquisition->update_values();
}

void Dialog_conf_views::on_hslid_th_left_sliderReleased()
{
    int value = ui->hslid_th_left->value();
    gDefinedViews_left->view_vector.at(gDefinedViews_left->selection).threshold = value;
    ui->lbl_th_left->setText(QString::number(gDefinedViews_left->view_vector.at(gDefinedViews_left->selection).threshold));

}

void Dialog_conf_views::on_hslid_th_right_sliderReleased()
{
    int value = ui->hslid_th_right->value();
    gDefinedViews_right->view_vector.at(gDefinedViews_right->selection).threshold = value;
    ui->lbl_th_right->setText(QString::number(gDefinedViews_right->view_vector.at(gDefinedViews_right->selection).threshold));

}

void Dialog_conf_views::on_hslid_gain_left_sliderReleased()
{
    int value = ui->hslid_gain_left->value();
    gDefinedViews_left->view_vector.at(gDefinedViews_left->selection).gain = value;
    ui->lbl_gain_left->setText(QString ("x%1").arg(gDefinedViews_left->view_vector.at(gDefinedViews_left->selection).gain));
}

void Dialog_conf_views::on_hslid_gain_right_sliderReleased()
{
    int value = ui->hslid_gain_right->value();
    gDefinedViews_right->view_vector.at(gDefinedViews_right->selection).gain = value;
    ui->lbl_gain_right->setText(QString ("x%1").arg(gDefinedViews_right->view_vector.at(gDefinedViews_right->selection).gain));
}

void Dialog_conf_views::on_chk_View_left_clicked()
{
    gDefinedViews_left->isActive = ui->chk_View_left->isChecked();
    //update values for acquisition. This will stop the acquisition if it's running
    gAcquisition->update_values();
}

void Dialog_conf_views::on_chk_View_right_clicked()
{
    gDefinedViews_right->isActive = ui->chk_View_right->isChecked();
    //update values for acquisition. This will stop the acquisition if it's running
    gAcquisition->update_values();
}

void Dialog_conf_views::on_chk_double_left_clicked()
{
    gDefinedViews_left->view_vector.at(gDefinedViews_left->selection).set_isDoubled(ui->chk_double_left->isChecked());
    //update values for acquisition. This will stop the acquisition if it's running
    gAcquisition->update_values();
}

void Dialog_conf_views::on_chk_double_right_clicked()
{
    gDefinedViews_right->view_vector.at(gDefinedViews_right->selection).set_isDoubled(ui->chk_double_right->isChecked());
    //update values for acquisition. This will stop the acquisition if it's running
    gAcquisition->update_values();
}

int Dialog_conf_views::get_enum_type_interp_from_combo_value(int combo_selection){
    switch (combo_selection){
    case 0:
        return CV_INTER_NN;
        break;
    case 1:
        return CV_INTER_LINEAR;
        break;
    case 2:
        return CV_INTER_AREA;
        break;
    case 3:
        return CV_INTER_CUBIC;
        break;
    default:
        return CV_INTER_LINEAR;
        break;
    }
}
int Dialog_conf_views::get_combo_value_from_enum_type_interp(int type_interpolation){
    switch (type_interpolation){
    case CV_INTER_NN:
        return 0;
        break;
    case CV_INTER_LINEAR:
        return 1;
        break;
    case CV_INTER_AREA:
        return 2;
        break;
    case CV_INTER_CUBIC:
        return 3;
        break;
    default:
        return 1;
        break;
    }
}


