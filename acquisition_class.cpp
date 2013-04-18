#include "acquisition_class.h"

Acquisition_class::Acquisition_class()
{
    //at start the acquisition is stopped
    isActive = false;
    //set pointer p_left_view to the selected Left view
    p_left_view = & gDefinedViews_left->view_vector.at(gDefinedViews_left->selection);
    //set pointer p_right_view to the selected Right view
    p_right_view = & gDefinedViews_right->view_vector.at(gDefinedViews_right->selection);
    //set pointer p_combo_view to the selected Combo view
    p_combo_view = & gDefinedComboViews->view_combo_vector.at(gDefinedComboViews->selection);
    //by default save only the left view
    save_left_view = true;
    save_right_view = false;
    save_combo_view = false;
    current_frame = 0;
    directory_where_save= QDir::current();
    number_of_frames = 1000;
    label_left_view = "LV";
    label_right_view = "RV";
    label_combo_view = "CV";
    last_acquisition_setting_time = QTime::currentTime();
    file_extension = ".bmp";
    format_time_filename = "hhmmss";
    format_time_label = "hh:mm:ss";
}

void Acquisition_class::update_values(){
    //update gAcquisition values
    //set pointer p_left_view to the selected Left view
    p_left_view = & gDefinedViews_left->view_vector.at(gDefinedViews_left->selection);
    //set pointer p_right_view to the selected Right view
    p_right_view = & gDefinedViews_right->view_vector.at(gDefinedViews_right->selection);
    //set pointer p_combo_view to the selected Combo view
    p_combo_view = & gDefinedComboViews->view_combo_vector.at(gDefinedComboViews->selection);
    last_acquisition_setting_time = QTime::currentTime();
    //compose the new filename prefix
    prefix_filename_left_view =   last_acquisition_setting_time.toString(format_time_filename)+ QChar('s') + label_left_view+ QChar('_');
    prefix_filename_right_view =  last_acquisition_setting_time.toString(format_time_filename) + QChar('s') + label_right_view+ QChar('_');
    prefix_filename_combo_view =  last_acquisition_setting_time.toString(format_time_filename) + QChar('s') + label_combo_view+ QChar('_');
    //stop the acquisition when values are changed /reseted
    isActive = false;
    current_frame = 0;

}
void Acquisition_class::new_frame_to_save(){
    //check if current frame is less than the total number of frames, otherwise stop the acquisition
    if (current_frame < (number_of_frames + 1)){
        compose_filename();
        double current_percent_frame =  (current_frame / number_of_frames) * 100; //todo
        current_frame = current_frame + 1;

    }  else {
        //reset gAcquisition values
        update_values();
    }
}

void Acquisition_class::compose_filename(){
    QString strfilenum = QString::number( current_frame,10 );
    current_filepath_left_frame = directory_where_save.absolutePath() + QChar('\\') + prefix_filename_left_view + strfilenum + file_extension;
    current_filepath_right_frame = directory_where_save.absolutePath()+ QChar('\\') + prefix_filename_right_view + strfilenum + file_extension;
    current_filepath_combo_frame = directory_where_save.absolutePath()+ QChar('\\') + prefix_filename_combo_view + strfilenum + file_extension;
}
