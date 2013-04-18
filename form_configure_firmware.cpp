#include <QtGui>
#include "form_configure_firmware.h"
#include "ui_form_configure_firmware.h"
#include "enervis.h"
#include "view_class.h"
#include "okFrontPanelDLL_ben.h"
#include "global_variables.h"

Form_Configure_Firmware::Form_Configure_Firmware(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Configure_Firmware)
{
    ui->setupUi(this);
    ui->l_1->setText("RMP C du.");
    ui->l_2->setText("RMP C len.");
    ui->l_3->setText("RMP length");
    ui->l_4->setText("RMP end");
    ui->l_5->setText("RMP delta");
    ui->l_6->setText("Vt c du.");
    ui->l_7->setText("Vt length");
    ui->l_8->setText("Vt start");
    ui->l_9->setText("Vt delta");
    ui->l_10->setText("RSNBL start");
    ui->l_11->setText("RSNBL stop");
    ui->l_12->setText("prep. int.");
    ui->l_13->setText("fin. int.");
    ui->l_14->setText("prep. rout");
    ui->l_15->setText("fin. rout");
    ui->l_16->setText("update row");
    ui->l_17->setText("next row");
    ui->l_18->setText("time A");
    ui->l_19->setText("time B");
    ui->l_20->setText("time C");
    ui->l_21->setText("time Max");
    ui->l_22->setText("div. A");
    ui->l_23->setText("div. B");
    ui->l_24->setText("div C");

    ui->ckBox_1->setText("S8B");
    ui->ckBox_2->setText("Mask");
    ui->ckBox_3->setText("MaxMin");
    ui->ckBox_4->setText("autoMM");
    ui->ckBox_5->setText("CNT");
    ui->ckBox_6->setText("S0");
    ui->ckBox_7->setText("S1");
    ui->ckBox_8->setText("fUPD");
    UpdateForm();
}
bool Form_Configure_Firmware::GetFormValues(){
    if (gFlag_enervis_instantiated == true){
        int base = 10;
        int value_1,value_3;
        int value_5,value_6,value_8;
        //int value_9,value_2,value_4,value_7;
        int value_10,value_11,value_12;
        int value_13,value_14,value_15,value_16;
        int value_17,value_18,value_19,value_20;
        int value_21,value_22,value_23,value_24;
        bool conv_1,conv_3;
        bool conv_5,conv_6,conv_8;
        //bool conv_2,conv_4,conv_9,conv_7;
        bool conv_10,conv_11,conv_12;
        bool conv_13,conv_14,conv_15,conv_16;
        bool conv_17,conv_18,conv_19,conv_20;
        bool conv_21,conv_22,conv_23,conv_24;
        value_1 = ui->LE_1->text().toInt(&conv_1,base);
        //value_2 = ui->LE_2->text().toInt(&conv_2,base);
        value_3 = ui->LE_3->text().toInt(&conv_3,base);
        //value_4 = ui->LE_4->text().toInt(&conv_4,base);
        value_5 = ui->LE_5->text().toInt(&conv_5,base);
        value_6 = ui->LE_6->text().toInt(&conv_6,base);
        //value_7 = ui->LE_7->text().toInt(&conv_7,base);
        value_8 = ui->LE_8->text().toInt(&conv_8,base);
        //value_9 = ui->LE_9->text().toInt(&conv_9,base);
        value_10 = ui->LE_10->text().toInt(&conv_10,base);
        value_11 = ui->LE_11->text().toInt(&conv_11,base);
        value_12 = ui->LE_12->text().toInt(&conv_12,base);
        value_13 = ui->LE_13->text().toInt(&conv_13,base);
        value_14 = ui->LE_14->text().toInt(&conv_14,base);
        value_15 = ui->LE_15->text().toInt(&conv_15,base);
        value_16 = ui->LE_16->text().toInt(&conv_16,base);
        value_17 = ui->LE_17->text().toInt(&conv_17,base);
        value_18 = ui->LE_18->text().toInt(&conv_18,base);
        value_19 = ui->LE_19->text().toInt(&conv_19,base);
        value_20 = ui->LE_20->text().toInt(&conv_20,base);
        value_21 = ui->LE_21->text().toInt(&conv_21,base);
        value_22 = ui->LE_22->text().toInt(&conv_22,base);
        value_23 = ui->LE_23->text().toInt(&conv_23,base);
        value_24 = ui->LE_24->text().toInt(&conv_24,base);

        if (conv_1  && conv_3  && conv_5 && conv_6  && conv_8  && conv_10 && conv_11 && conv_12 && conv_13 && conv_14 && conv_15 && conv_16 && conv_17 && conv_18 && conv_19 && conv_20 && conv_21 && conv_22 & conv_23 && conv_24){
            gEnervis->proposed_PWM_DOWN_COST_duty = static_cast<unsigned int>(value_1);
            gEnervis->proposed_PWM_DOWN_length = static_cast<unsigned int>(value_3);
            gEnervis->proposed_PWM_DOWN_increment = static_cast<unsigned int>(value_5);
            gEnervis->proposed_PWM_UP_COST_duty = static_cast<unsigned int>(value_6);
            gEnervis->proposed_PWM_UP_length = static_cast<unsigned int>(value_8);
            gEnervis->proposed_PWM_UP_increment = static_cast<unsigned int>(value_10);
            gEnervis->proposed_rsnbl_start_value = static_cast<unsigned int>(value_11);
            gEnervis->proposed_rsnbl_stop_value = static_cast<unsigned int>(value_12);
            gEnervis->proposed_WAIT_prepare_integration = static_cast<unsigned int>(value_13);
            gEnervis->proposed_WAIT_finish_integration = static_cast<unsigned int>(value_14);
            gEnervis->proposed_WAIT_prepare_readout = static_cast<unsigned int>(value_15);
            gEnervis->proposed_WAIT_finish_readout = static_cast<unsigned int>(value_16);
            gEnervis->proposed_WAIT_update_row = static_cast<unsigned int>(value_17);
            gEnervis->proposed_WAIT_next_row_eof = static_cast<unsigned int>(value_18);
            gEnervis->proposed_time_point_A_11bit = static_cast<unsigned int>(value_19);
            gEnervis->proposed_conv_div_A_5bit = static_cast<unsigned int>(value_20);
            gEnervis->proposed_time_point_B_11bit = static_cast<unsigned int>(value_21);
            gEnervis->proposed_conv_div_B_5bit = static_cast<unsigned int>(value_22);
            gEnervis->proposed_time_conversion_max_11bit = static_cast<unsigned int>(value_23);
            gEnervis->proposed_conv_div_C_5bit = static_cast<unsigned int>(value_24);

            if (ui->ckBox_1->isChecked()){
                gEnervis->flag_S8B = 1;
            } else {
                gEnervis->flag_S8B = 0;
            }
            if (ui->ckBox_2->isChecked()){
                gEnervis->flag_Mask = 1;
            } else {
                gEnervis->flag_Mask = 0;
            }
            if (ui->ckBox_3->isChecked()){
                gEnervis->flag_MaxMin = 1;
            } else {
                gEnervis->flag_MaxMin = 0;
            }
            if (ui->ckBox_4->isChecked()){
                gEnervis->flag_Auto_MAXMIN = 1;
            } else {
                gEnervis->flag_Auto_MAXMIN = 0;
            }
            if (ui->ckBox_5->isChecked()){
               gEnervis->flag_CNT = 1;
            } else {
               gEnervis->flag_CNT = 0;
            }
            if (ui->ckBox_6->isChecked()){
               gEnervis->flag_S0 = 1;
            } else {
              gEnervis->flag_S0 = 0;
            }
            if (ui->ckBox_7->isChecked()){
               gEnervis->flag_S1 = 1;
            } else {
               gEnervis->flag_S1 = 0;
            }
            if (ui->ckBox_8->isChecked()){
               gEnervis->flag_fUPD = 1;
            } else {
               gEnervis->flag_fUPD = 0;
            }
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void Form_Configure_Firmware::UpdateForm(){
    if (gFlag_enervis_instantiated == true)  {
        DisableAllControls(false);
        ui->LE_1->setText(QString::number(gEnervis->PWM_DOWN_COST_duty));
        ui->LE_2->setText(QString::number(gEnervis->PWM_DOWN_COST_length));
        ui->LE_3->setText(QString::number(gEnervis->PWM_DOWN_length));
        ui->LE_4->setText(QString::number(gEnervis->PWM_DOWN_end));
        ui->LE_5->setText(QString::number(gEnervis->PWM_DOWN_increment));
        ui->LE_6->setText(QString::number(gEnervis->PWM_UP_COST_duty));
        ui->LE_7->setText(QString::number(gEnervis->PWM_UP_COST_length));
        ui->LE_8->setText(QString::number(gEnervis->PWM_UP_length));
        ui->LE_9->setText(QString::number(gEnervis->PWM_UP_start));
        ui->LE_10->setText(QString::number(gEnervis->PWM_UP_increment));
        ui->LE_11->setText(QString::number(gEnervis->rsnbl_start_value));
        ui->LE_12->setText(QString::number(gEnervis->rsnbl_stop_value));
        ui->LE_13->setText(QString::number(gEnervis->clk_wait_prepare_integration));
        ui->LE_14->setText(QString::number(gEnervis->clk_wait_finish_integration));
        ui->LE_15->setText(QString::number(gEnervis->clk_wait_prepare_readout));
        ui->LE_16->setText(QString::number(gEnervis->clk_wait_finish_readout));
        ui->LE_17->setText(QString::number(gEnervis->clk_wait_update_row));
        ui->LE_18->setText(QString::number(gEnervis->clk_wait_next_row_eof));
        ui->LE_19->setText(QString::number(gEnervis->time_point_A_11bit));
        ui->LE_20->setText(QString::number(gEnervis->conv_div_A_5bit));
        ui->LE_21->setText(QString::number(gEnervis->time_point_B_11bit));
        ui->LE_22->setText(QString::number(gEnervis->conv_div_B_5bit));
        ui->LE_23->setText(QString::number(gEnervis->time_conversion_max_11bit));
        ui->LE_24->setText(QString::number(gEnervis->conv_div_C_5bit));
        if (gEnervis->flag_S8B==1) {
            ui->ckBox_1->setChecked(true);
        } else {
            ui->ckBox_1->setChecked(false);
        }
        if (gEnervis->flag_Mask==1) {
            ui->ckBox_2->setChecked(true);
        } else {
            ui->ckBox_2->setChecked(false);
        }

        if (gEnervis->flag_MaxMin== 1) {
            ui->ckBox_3->setChecked(true);
        } else {
            ui->ckBox_3->setChecked(false);
        }

        if (gEnervis->flag_Auto_MAXMIN==1) {
            ui->ckBox_4->setChecked(true);
        } else {
            ui->ckBox_4->setChecked(false);
        }

        if (gEnervis->flag_CNT==1) {
            ui->ckBox_5->setChecked(true);
        } else {
            ui->ckBox_5->setChecked(false);
        }
        if (gEnervis->flag_S0==1) {
            ui->ckBox_6->setChecked(true);
        } else {
            ui->ckBox_6->setChecked(false);
        }
        if (gEnervis->flag_S1==1) {
            ui->ckBox_7->setChecked(true);
        } else {
            ui->ckBox_7->setChecked(false);
        }
        if (gEnervis->flag_fUPD==1) {
            ui->ckBox_8->setChecked(true);
        } else {
            ui->ckBox_8->setChecked(false);
        }
    } else {
        DisableAllControls(true);
    }
}
void Form_Configure_Firmware::DisableAllControls(bool flag){
    if (flag==true) {
        ui->LE_1->setEnabled(false);
        ui->LE_2->setEnabled(false);
        ui->LE_3->setEnabled(false);
        ui->LE_4->setEnabled(false);
        ui->LE_5->setEnabled(false);
        ui->LE_6->setEnabled(false);
        ui->LE_7->setEnabled(false);
        ui->LE_8->setEnabled(false);
        ui->LE_9->setEnabled(false);
        ui->LE_10->setEnabled(false);
        ui->LE_11->setEnabled(false);
        ui->LE_12->setEnabled(false);
        ui->LE_13->setEnabled(false);
        ui->LE_14->setEnabled(false);
        ui->LE_15->setEnabled(false);
        ui->LE_16->setEnabled(false);
        ui->LE_17->setEnabled(false);
        ui->LE_18->setEnabled(false);
        ui->LE_19->setEnabled(false);
        ui->LE_20->setEnabled(false);
        ui->LE_21->setEnabled(false);
        ui->LE_22->setEnabled(false);
        ui->LE_23->setEnabled(false);
        ui->LE_24->setEnabled(false);
        ui->ckBox_1->setEnabled(false);
        ui->ckBox_2->setEnabled(false);
        ui->ckBox_3->setEnabled(false);
        ui->ckBox_4->setEnabled(false);
        ui->ckBox_5->setEnabled(false);
        ui->ckBox_6->setEnabled(false);
        ui->ckBox_7->setEnabled(false);
        ui->ckBox_8->setEnabled(false);
    } else {
        ui->LE_1->setEnabled(true);
        //ui->LE_2->setEnabled(true);
        ui->LE_3->setEnabled(true);
        //ui->LE_4->setEnabled(true);
        ui->LE_5->setEnabled(true);
        ui->LE_6->setEnabled(true);
        //ui->LE_7->setEnabled(true);
        ui->LE_8->setEnabled(true);
        //ui->LE_9->setEnabled(true);
        ui->LE_10->setEnabled(true);
        ui->LE_11->setEnabled(true);
        ui->LE_12->setEnabled(true);
        ui->LE_13->setEnabled(true);
        ui->LE_14->setEnabled(true);
        ui->LE_15->setEnabled(true);
        ui->LE_16->setEnabled(true);
        ui->LE_17->setEnabled(true);
        ui->LE_18->setEnabled(true);
        ui->LE_19->setEnabled(true);
        ui->LE_20->setEnabled(true);
        ui->LE_21->setEnabled(true);
        ui->LE_22->setEnabled(true);
        ui->LE_23->setEnabled(true);
        ui->LE_24->setEnabled(true);
        ui->ckBox_1->setEnabled(true);
        ui->ckBox_2->setEnabled(true);
        ui->ckBox_3->setEnabled(true);
        ui->ckBox_4->setEnabled(true);
        ui->ckBox_5->setEnabled(true);
        ui->ckBox_6->setEnabled(true);
        ui->ckBox_7->setEnabled(true);
        ui->ckBox_8->setEnabled(true);
    }
}

void Form_Configure_Firmware::on_btnConfEnervis_clicked()
{
    bool show_error = true;
    if (GetFormValues()== true){
        if (gEnervis->CheckProposedValues() == true)  {
            gEnervis->SetProposedValues();
            if (gFlag_xem_configured) {
                if(gEnervis->SetValueOn_XEMFPGA()){
                  show_error = false;
                }
            }
        }
    }
    UpdateForm();
    if (show_error) {
        QMessageBox::about(this, tr("Error"),tr("Check values or communication.."));
    }
}

Form_Configure_Firmware::~Form_Configure_Firmware()
{
    delete ui;
}



void Form_Configure_Firmware::on_btnActiveAcq_clicked()
{
    if (gCV_ACQ_OF_ENERVIS->isAcquisitionActive == false) {
        gCV_ACQ_OF_ENERVIS->isAcquisitionActive = true;
        ui->btnActiveAcq->setText("Stop Acq.");
    } else {
        gCV_ACQ_OF_ENERVIS->isAcquisitionActive = false;
        ui->btnActiveAcq->setText("Start Acq.");
    }

}
