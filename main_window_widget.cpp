#include <QtGui>
#include "main_window_widget.h"

//! [0]
Main_window_widget::Main_window_widget(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    update_recording_labels_acq_disabled();
}
//! [0]
void Main_window_widget::Visualize_new_Frame_on_The_Left_Of_UI(){
    /* DEBUG snippet
    cv::Mat IM1(104,104,CV_8U);
    for (int row=0; row<IM1.rows; row++){
        for (int col=0; col <IM1.cols; col++){
            IM1.at< unsigned char >(col,row)= 0;
        }
    }
    QImage leftimage((uchar*)IM1.data,IM1.cols,IM1.rows,IM1.step,QImage::Format_Indexed8);
    */
    QImage leftimage((uchar*)gCV_MAT_FRAME_VIEW_left->data,gCV_MAT_FRAME_VIEW_left->cols,gCV_MAT_FRAME_VIEW_left->rows,gCV_MAT_FRAME_VIEW_left->step,QImage::Format_Indexed8);
    label->setPixmap(QPixmap::fromImage(leftimage));
}
void Main_window_widget::Visualize_new_Frame_on_The_Right_Of_UI(){
    /* DEBUG snippet
    cv::Mat IM2(104,104,CV_8U);
    for (int row=0; row<IM1.rows; row++){
        for (int col=0; col <IM1.cols; col++){
            IM2.at< unsigned char >(col,row)= 255;
    }
    QImage rightimage((uchar*)IM2.data,IM2.cols,IM2.rows,IM2.step,QImage::Format_Indexed8);
    */
    QImage rightimage((uchar*)gCV_MAT_FRAME_VIEW_right->data,gCV_MAT_FRAME_VIEW_right->cols,gCV_MAT_FRAME_VIEW_right->rows,gCV_MAT_FRAME_VIEW_right->step,QImage::Format_Indexed8);
    label_2->setPixmap(QPixmap::fromImage(rightimage));
}

//set the property of global object gAcquisition in order to start or stop the
//recording
void Main_window_widget::on_btn_rec_control_clicked()
{
    if (gAcquisition->isActive == false){
       gAcquisition->isActive = true;
       update_recording_labels_acq_active();
    } else {
       gAcquisition->isActive = false;
       update_recording_labels_acq_disabled();
     }
}
//update labels when acquisition is active
void Main_window_widget::update_recording_labels_acq_active()
{
    this->lbl_current_frame_10->setText( QString::number(gAcquisition->current_frame,10));
    this->btn_rec_control->setText("stop");
    this->lbl_status->setText("..recording");
}
//update labels when acquisition is disabled
void Main_window_widget::update_recording_labels_acq_disabled(){
    this->lbl_frame_num->setText( QString::number(gAcquisition->number_of_frames,10) );
    this->lbl_current_frame_10->setText( QString::number(gAcquisition->current_frame,10));
    this->btn_rec_control->setText("rec");
    this->lbl_status->setText("..idle");
    this->ledt_dir->setText(gAcquisition->directory_where_save.absolutePath());
    this->lbl_setting_date->setText(gAcquisition->last_acquisition_setting_time.toString(gAcquisition->format_time_label));
}
