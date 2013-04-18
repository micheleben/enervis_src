#ifndef VIEW_CLASS_H
#define VIEW_CLASS_H

#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "enervis.h"
#include <QTime>

/*!
 \brief different type of image processing available

 BASE_7BIT : the frame buffer at 7 bit as is read from FPGA
 NOTZERO_8 BIT: if one of the bit is different from zero set the pixel to white
 OVERTHRESHOLD_8BIT: if the pixel value exceed the threshold set the pixel to white
*/
enum ProcessType {
    //pair and odd frames:
    BASE_7BIT, //the frame buffer at 7 bit as is read from FPGA
    NOTZERO_8BIT, //if one of the bit is different from zero set the pixel to white
    OVERTHRESHOLD_8BIT, //if the pixel value exceed the threshold set the pixel to white
    //pair frames:
    BASE_7BIT_PF, //the frame buffer at 7 bit as it is read from FPGA (only pair frames)
    NOTZERO_8BIT_PF, //if one of the bit is different from zero set the pixel to white (only pair frames)
    OVERTHRESHOLD_8BIT_PF, //if the pixel value exceed the threshold set the pixel to white (only pair frames)
    THRESHOLD_TO_ZERO_PF, //dst(x,y) = src(x,y) if src(x,y) > Th, otherwise dst(x,y) = 0 (only pair frames)
    THRESHOLD_TO_ZERO_EQ_PF, //dst(x,y) = src(x,y) if src(x,y) > Th, otherwise dst(x,y) = 0 with equalization (only pair frames)
    //odd frames:
    BASE_7BIT_OF, //the frame buffer at 7 bit as it is read from FPGA (only odd frames)
    NOTZERO_8BIT_OF, //if one of the bit is different from zero set the pixel to white (only odd frames)
    OVERTHRESHOLD_8BIT_OF, //if the pixel value exceed the threshold set the pixel to white (only odd frames),
    THRESHOLD_TO_ZERO_OF, //dst(x,y) = src(x,y) if src(x,y) > Th, otherwise dst(x,y) = 0 (only odd frames)
    THRESHOLD_TO_ZERO_EQ_OF //dst(x,y) = src(x,y) if src(x,y) > Th, otherwise dst(x,y) = 0 with equalization (only odd frames)
};


/*! \brief this class performs final openCV operation on the data to build the image
*
* data chain: fpga->enervis obj->View_initialization obj-> [View class obj]
*/

class View_class
{
private:
    int ID; /*! the position of the View_class in a View_class container */
    enum ProcessType type_of_process; /*! the type of process that will be done in this view */
    bool isDoubled; /*! true if the result image will be doubled before visualization*/

    bool istheLeftOne; /*!< TODO */
    bool istheRightOne; /*!< TODO */
private:
    //CvMat * mat_processing;
    cv::Mat * mat_processing;
    cv::Mat * mat_processing_double;
    cv::Mat * mat_temp;
    //different types of image processing
    /*!
     \brief this show the frame as it is built from the buffer, it's called when type_of_process is set to BASE_7BIT
    */
    void process_frame_enervis_8bit_BASE_7BIT();
    /*!
     \brief this show a frame where a pixel is settled to white if it has a value different from 0
    */
    void process_frame_enervis_8bit_NOTZERO_8BIT();
    /*!
     \brief this show a frame where a pixel is settled to white if it has a value that exceed the threshold
    */
    void process_frame_enervis_8bit_OVERTHRESHOLD_8BIT();
    //same functions as previous but performed only for pair frames
    void process_frame_enervis_8bit_BASE_7BIT_PF();
    void process_frame_enervis_8bit_NOTZERO_8BIT_PF();
    void process_frame_enervis_8bit_OVERTHRESHOLD_8BIT_PF();
    void process_frame_enervis_8bit_THRESHOLD_TO_ZERO_PF();
    void process_frame_enervis_8bit_THRESHOLD_TO_ZERO_EQ_PF();
    //same functions as previous but performed only for odd frames
    void process_frame_enervis_8bit_BASE_7BIT_OF();
    void process_frame_enervis_8bit_NOTZERO_8BIT_OF();
    void process_frame_enervis_8bit_OVERTHRESHOLD_8BIT_OF();
    void process_frame_enervis_8bit_THRESHOLD_TO_ZERO_OF();
    void process_frame_enervis_8bit_THRESHOLD_TO_ZERO_EQ_OF();
public:
    int threshold; /*!< TODO */
    int gain; /*!< TODO */
    int interpolation; /*! interpolation method to double the image; default linear interpolation */
    bool Flag_Advanced; /*!< TODO */
    std::string Name; /*!< TODO */
    std::string Description; /*!< TODO */

    void set_ID(int newID){ID = newID;}
    int get_ID() {return ID;}

    bool get_isDoubled() {return isDoubled;}
    void set_isDoubled (bool flag){isDoubled = flag;}

    bool get_istheLeftOne() {return istheLeftOne;}
    void set_istheLeftOne (bool flag){istheLeftOne = flag;}

    bool get_istheRightOne() {return istheRightOne;}
    void set_istheRightOne (bool flag){istheRightOne = flag;}

    void set_ProcessType (enum ProcessType process_type){type_of_process = process_type;}
    enum ProcessType get_ProcessType(){return type_of_process;}

    View_class(std::string theName,std::string theDescription);
    //~View_class();
    //cvMat* process_selection();
    cv::Mat * process_selection();
    cv::Mat * pointer_to_mat_processing();

};
//////////////////////////////////////////////////////////////////////////////

/*! \brief this class builds a openCV rapresentation of the data buffer
*
* data chain: fpga->enervis obj->[View_initialization obj]-> View class
*/


class View_initialization{

public:
    QTime last_time_query; /*!< TODO */
    bool isAcquisitionActive; /*!< TODO */
    FrameType last_frame_type; /*!< TODO */

    View_initialization();

    void process_frame_enervis();
};

extern View_initialization* gCV_ACQ_OF_ENERVIS; /*!< TODO */
//extern CvMat* gCV_MAT_FRAME_VIEW; /*! This is the opencv rapresentation of the frame as it has been build from the bufout of the data   */
extern cv::Mat * gCV_MAT_FRAME_VIEW; /*! This is the opencv rapresentation of the frame as it has been build from the bufout of the data   */


#endif // VIEW_CLASS_H
