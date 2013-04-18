#include "view_combo_class.h"

View_combo_class::View_combo_class(std::string theName,std::string theDescription)
{
    Name = theName;
    Description = theDescription;
    type_of_process_combo = BASE_COLOR;
    interpolation = CV_INTER_LINEAR;
    mat_processing = new cv::Mat;
    mat_processing->create(104,104,CV_8UC3 );
    mat_temp = new cv::Mat;
    mat_temp->create(104,104,CV_8UC3);
    mat_processing_double = new cv::Mat;
    mat_processing_double->create(208,208,CV_8UC3);

}

cv::Mat* View_combo_class::process_selection(){

    switch (type_of_process_combo){
    //pair and odd frames
    case BASE_COLOR:
        process_frame_combo_8bit_BASE_COLOR();
    break;
    case NOTZERO_8BIT:
        process_frame_combo_8bit_BASE_MONOCHROME();
    break;
    default:
        process_frame_combo_8bit_BASE_COLOR();
    break;
    }
    if (isDoubled == false){
        return mat_processing;
    } else {
        cv::resize(*mat_processing,*mat_processing_double,cv::Size(208,208),interpolation);
        return mat_processing_double;
    }
}

void View_combo_class::process_frame_combo_8bit_BASE_COLOR(){
    cv::Mat * mat_g = gDefinedViews_left->view_vector.at(gDefinedViews_left->selection).pointer_to_mat_processing();
    cv::Mat * mat_b = gDefinedViews_right->view_vector.at(gDefinedViews_right->selection).pointer_to_mat_processing();

    for (int row = 0; row < mat_processing->rows; ++row) {
            for (int col = 0; col < mat_processing->rows; ++col) {
                cv::Vec3b& gbr = mat_processing->at<cv::Vec3b>(row, col);
                gbr[0] = mat_g->at<unsigned char>(row,col);
                gbr[1] = mat_b->at<unsigned char>(row,col);
                gbr[2] = 0;
            }
   }
}

void View_combo_class::process_frame_combo_8bit_BASE_MONOCHROME(){
    cv::Mat * mat_g = gDefinedViews_left->view_vector.at(gDefinedViews_left->selection).pointer_to_mat_processing();
    cv::Mat * mat_b = gDefinedViews_right->view_vector.at(gDefinedViews_right->selection).pointer_to_mat_processing();

    for (int row = 0; row < mat_processing->rows; ++row) {
            for (int col = 0; col < mat_processing->rows; ++col) {
                cv::Vec3b& gbr = mat_processing->at<cv::Vec3b>(row, col);
                gbr[0] = mat_g->at<unsigned char>(row,col) + mat_b->at<unsigned char>(row,col);
                gbr[1] = mat_g->at<unsigned char>(row,col) + mat_b->at<unsigned char>(row,col);
                gbr[2] = mat_g->at<unsigned char>(row,col) + mat_b->at<unsigned char>(row,col);
            }
   }
}

