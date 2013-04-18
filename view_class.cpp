#include "view_class.h"
#define DEBUG_WRITE_BUFFER_TO_FILE false

View_class::View_class(std::string theName,std::string theDescription)
{

    Name = theName;
    Description = theDescription;
    Flag_Advanced = false;
    istheLeftOne = false;
    istheRightOne = false;
    isDoubled = false;
    interpolation = CV_INTER_LINEAR;
    threshold = 0;
    gain = 0;
    type_of_process = BASE_7BIT;
    mat_processing = new cv::Mat;
    mat_processing->create(104,104,CV_8U);
    mat_temp = new cv::Mat;
    mat_temp->create(104,104,CV_8U);
    mat_processing_double = new cv::Mat;
    mat_processing_double->create(208,208,CV_8U);
}
/*
View_class::~View_class(){
    //cvReleaseMat(&mat_processing);
}
*/
//return a pointer to mat_processing
cv::Mat * View_class::pointer_to_mat_processing(){
    return mat_processing;
}

cv::Mat* View_class::process_selection(){

    switch (type_of_process){
    //pair and odd frames
    case BASE_7BIT:
        process_frame_enervis_8bit_BASE_7BIT();
    break;
    case NOTZERO_8BIT:
        process_frame_enervis_8bit_NOTZERO_8BIT();
    break;
    case OVERTHRESHOLD_8BIT:
        process_frame_enervis_8bit_OVERTHRESHOLD_8BIT();
    break;
    //pair frames:
    case BASE_7BIT_PF:
        process_frame_enervis_8bit_BASE_7BIT_PF();
    break;
    case NOTZERO_8BIT_PF:
        process_frame_enervis_8bit_NOTZERO_8BIT_PF();
    break;
    case OVERTHRESHOLD_8BIT_PF:
        process_frame_enervis_8bit_OVERTHRESHOLD_8BIT_PF();
    break;
    case THRESHOLD_TO_ZERO_PF:
        process_frame_enervis_8bit_THRESHOLD_TO_ZERO_PF();
    break;
    case THRESHOLD_TO_ZERO_EQ_PF:
        process_frame_enervis_8bit_THRESHOLD_TO_ZERO_EQ_PF();
    break;
    //odd frames:
    case BASE_7BIT_OF:
        process_frame_enervis_8bit_BASE_7BIT_OF();
    break;
    case NOTZERO_8BIT_OF:
        process_frame_enervis_8bit_NOTZERO_8BIT_OF();
    break;
    case OVERTHRESHOLD_8BIT_OF:
        process_frame_enervis_8bit_OVERTHRESHOLD_8BIT_OF();
    break;
    case THRESHOLD_TO_ZERO_OF:
        process_frame_enervis_8bit_THRESHOLD_TO_ZERO_OF();
    break;
    case THRESHOLD_TO_ZERO_EQ_OF:
        process_frame_enervis_8bit_THRESHOLD_TO_ZERO_EQ_OF();
    break;
    default:
        process_frame_enervis_8bit_BASE_7BIT();
    break;
    }
    if (isDoubled == false){
        return mat_processing;
    } else {
        cv::resize(*mat_processing,*mat_processing_double,cv::Size(208,208),interpolation);
        return mat_processing_double;
    }


}
//////////////////////////////////////////////////////////////////////////
//pair and odd frames:
void View_class::process_frame_enervis_8bit_NOTZERO_8BIT(){

    cv::threshold(*gCV_MAT_FRAME_VIEW,*mat_processing,0,255,CV_THRESH_BINARY);
}

void View_class::process_frame_enervis_8bit_BASE_7BIT(){
    mat_processing = gCV_MAT_FRAME_VIEW;

}
void View_class::process_frame_enervis_8bit_OVERTHRESHOLD_8BIT(){
    cv::threshold(*gCV_MAT_FRAME_VIEW,*mat_processing,threshold,255,CV_THRESH_BINARY);
}
///////////////////////////////////////////////////////////////////////////////////
//pair frames:
void View_class::process_frame_enervis_8bit_BASE_7BIT_PF(){
    if (gCV_ACQ_OF_ENERVIS->last_frame_type == PAIR_FRAME) {
        mat_processing = gCV_MAT_FRAME_VIEW;
        //make a copy of gCV_FRAME_VIEW for the next call
        *mat_temp = gCV_MAT_FRAME_VIEW->clone();
    } else {
        mat_processing = mat_temp;
    }
}
void View_class::process_frame_enervis_8bit_NOTZERO_8BIT_PF(){
    if (gCV_ACQ_OF_ENERVIS->last_frame_type == PAIR_FRAME) {
        cv::threshold(*gCV_MAT_FRAME_VIEW,*mat_processing,0,255,CV_THRESH_BINARY);
        //make a copy of mat_processing for the next call
        *mat_temp = mat_processing->clone();
    } else {
        mat_processing = mat_temp;
    }
}
void View_class::process_frame_enervis_8bit_OVERTHRESHOLD_8BIT_PF(){
    if (gCV_ACQ_OF_ENERVIS->last_frame_type == PAIR_FRAME) {
       cv::threshold(*gCV_MAT_FRAME_VIEW,*mat_processing,threshold,255,CV_THRESH_BINARY);
       //make a copy of mat_processing for the next call
       *mat_temp = mat_processing->clone();
    }else {
        mat_processing = mat_temp;
    }
}
void View_class::process_frame_enervis_8bit_THRESHOLD_TO_ZERO_PF(){
    if (gCV_ACQ_OF_ENERVIS->last_frame_type == PAIR_FRAME) {
       cv::threshold(*gCV_MAT_FRAME_VIEW,*mat_processing,threshold,255,CV_THRESH_TOZERO);
       //make a copy of mat_processing for the next call
       *mat_temp = mat_processing->clone();
    }else {
        mat_processing = mat_temp;
    }
}
void View_class::process_frame_enervis_8bit_THRESHOLD_TO_ZERO_EQ_PF(){
    if (gCV_ACQ_OF_ENERVIS->last_frame_type == PAIR_FRAME) {
       cv::threshold(*gCV_MAT_FRAME_VIEW,*mat_temp,threshold,255,CV_THRESH_TOZERO);
       cv::equalizeHist(*mat_temp,*mat_processing);
       //make a copy of mat_processing for the next call
       *mat_temp = mat_processing->clone();
    }else {
        mat_processing = mat_temp;
    }
}
///////////////////////////////////////////////////////////////////////////////////
//odd frames:
void View_class::process_frame_enervis_8bit_BASE_7BIT_OF(){
    if (gCV_ACQ_OF_ENERVIS->last_frame_type == ODD_FRAME) {
        mat_processing = gCV_MAT_FRAME_VIEW;
        //make a copy of gCV_FRAME_VIEW for the next call
        *mat_temp = gCV_MAT_FRAME_VIEW->clone();
    } else {
        mat_processing = mat_temp;
    }
}
void View_class::process_frame_enervis_8bit_NOTZERO_8BIT_OF(){
    if (gCV_ACQ_OF_ENERVIS->last_frame_type == ODD_FRAME) {
        cv::threshold(*gCV_MAT_FRAME_VIEW,*mat_processing,0,255,CV_THRESH_BINARY);
        //make a copy of mat_processing for the next call
        *mat_temp = mat_processing->clone();
    } else {
        mat_processing = mat_temp;
    }
}
void View_class::process_frame_enervis_8bit_OVERTHRESHOLD_8BIT_OF(){
    if (gCV_ACQ_OF_ENERVIS->last_frame_type == ODD_FRAME) {
       cv::threshold(*gCV_MAT_FRAME_VIEW,*mat_processing,threshold,255,CV_THRESH_BINARY);
       //make a copy of mat_processing for the next call
       *mat_temp = mat_processing->clone();
    }else {
        mat_processing = mat_temp;
    }
}
void View_class::process_frame_enervis_8bit_THRESHOLD_TO_ZERO_OF(){
    if (gCV_ACQ_OF_ENERVIS->last_frame_type == ODD_FRAME) {
       cv::threshold(*gCV_MAT_FRAME_VIEW,*mat_processing,threshold,255,CV_THRESH_TOZERO);
       //make a copy of mat_processing for the next call
       *mat_temp = mat_processing->clone();
    }else {
        mat_processing = mat_temp;
    }
}
void View_class::process_frame_enervis_8bit_THRESHOLD_TO_ZERO_EQ_OF(){
    if (gCV_ACQ_OF_ENERVIS->last_frame_type == ODD_FRAME) {
       cv::threshold(*gCV_MAT_FRAME_VIEW,*mat_temp,threshold,255,CV_THRESH_TOZERO);
       cv::equalizeHist(*mat_temp,*mat_processing);
       //make a copy of mat_processing for the next call
       *mat_temp = mat_processing->clone();
    }else {
        mat_processing = mat_temp;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
//// class View Initialization /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
View_initialization::View_initialization(){

    last_time_query = QTime::currentTime();
    isAcquisitionActive = false;
    last_frame_type = ODD_FRAME;

}

/** \brief process the data from enervis and save it in matrix CvMat that is globally defined
*
* To access the data in the opencv Mat structure gCV_
* It use the macro CV_MAT_ELEM_PTR macro discussed at page 36/40 of
* OpenCv Manual
*
*
*/
void View_initialization::process_frame_enervis(){

    last_time_query = QTime::currentTime();
    last_frame_type = gEnervis->GetFrameOn_XEMFPGA_NB();
    int i,row,col;


    for (i=0;i<1024;i++){
        //data from first ram block
        gEnervis->frame_processed_8bit[i*2]= (gEnervis->bufout_1[i*2] >> 1) & 0x7F;
        gEnervis->frame_processed_8bit[i*2 + 1]= (gEnervis->bufout_1[i*2 + 1] >> 1) & 0x7F;
        //data from second ram block
        gEnervis->frame_processed_8bit[i*2 + 2048]= (gEnervis->bufout_2[i*2] >> 1) & 0x7F;
        gEnervis->frame_processed_8bit[i*2 + 2049]= (gEnervis->bufout_2[i*2 + 1] >> 1) & 0x7F;
        //data from third ram block
        gEnervis->frame_processed_8bit[i*2 + 4096]= (gEnervis->bufout_3[i*2] >> 1) & 0x7F;
        gEnervis->frame_processed_8bit[i*2 + 4097]= (gEnervis->bufout_3[i*2 + 1] >> 1) & 0x7F;
        //data from fourth ram block
        gEnervis->frame_processed_8bit[i*2 + 6144]= (gEnervis->bufout_4[i*2] >> 1) & 0x7F;
        gEnervis->frame_processed_8bit[i*2 + 6145]= (gEnervis->bufout_4[i*2 + 1] >> 1) & 0x7F;
        //data from fifth ram block
        gEnervis->frame_processed_8bit[i*2 + 8192]= (gEnervis->bufout_5[i*2] >> 1) & 0x7F;
        gEnervis->frame_processed_8bit[i*2 + 8193]= (gEnervis->bufout_5[i*2 + 1] >> 1) & 0x7F;
        //data from sixth ram block
        if (i<288){
            gEnervis->frame_processed_8bit[i*2 + 10240]= (gEnervis->bufout_6[i*2] >> 1) & 0x7F;
            gEnervis->frame_processed_8bit[i*2 + 10241]= (gEnervis->bufout_6[i*2 + 1] >> 1) & 0x7F;
        }
    }
    for (row=0;row< gCV_MAT_FRAME_VIEW->rows;row++){
        for (col=0; col<gCV_MAT_FRAME_VIEW->cols; col++){
            //*((unsigned char*)CV_MAT_ELEM_PTR( *gCV_MAT_FRAME_VIEW,row,col))= gEnervis->frame_processed_8bit[row*104+col];
            gCV_MAT_FRAME_VIEW->at<unsigned char>(row,col)= gEnervis->frame_processed_8bit[row*104+col];
            //unsigned char c = frame[row*104+col];
        }
    }

    if (DEBUG_WRITE_BUFFER_TO_FILE) {
        //save buffer in a binary file
        const char *buffer_file_name;
        buffer_file_name = "frame.dat";
        std::ofstream bin_buffer(buffer_file_name,std::ios::out|std::ios::binary);
        bin_buffer.write(reinterpret_cast<const char*>(gEnervis->frame_processed_8bit),10816);
        bin_buffer.close();
    }
    /*
    unsigned char a;
    for (row=0;row< gCV_MAT_FRAME_VIEW->rows;row++){
        for (col=0; col<gCV_MAT_FRAME_VIEW->cols; col++){
            a = *((unsigned char*)CV_MAT_ELEM_PTR( *gCV_MAT_FRAME_VIEW,row,col));
        }
     }*/
}
