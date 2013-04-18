#ifndef VIEW_COMBO_CLASS_H
#define VIEW_COMBO_CLASS_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "view_class_container.h"

/*!
 \brief different type of combo image processing available

 BASE_COLOR : visualize using green for data coming from the first view and red from teh data coming from
              the secon view
 BASE_MONOCHROME: visualize the two views with the same color

*/
enum ProcessTypeCombo {
    BASE_COLOR,
    BASE_MONOCHROME
};

class View_combo_class
{
private:
     /*! the position of the View_class in a View_class container */
    int ID;
    /*! the type of process that will be done in this view */
    enum ProcessTypeCombo type_of_process_combo;
    /*! true if the result image will be doubled before visualization*/
    bool isDoubled;
    cv::Mat * mat_processing;
    cv::Mat * mat_processing_double;
    cv::Mat * mat_temp;
    void process_frame_combo_8bit_BASE_COLOR();
    void process_frame_combo_8bit_BASE_MONOCHROME();

public:
    /*! interpolation method to double the image; default linear interpolation */
    int interpolation;
    /*! Name of the combo view*/
    std::string Name;
    /*! short description*/
    std::string Description;

    void set_ID(int newID){ID = newID;}
    int get_ID() {return ID;}

    bool get_isDoubled() {return isDoubled;}
    void set_isDoubled (bool flag){isDoubled = flag;}
    void set_ProcessTypeCombo (enum ProcessTypeCombo process_type){type_of_process_combo = process_type;}
    enum ProcessTypeCombo get_ProcessTypeCombo(){return type_of_process_combo;}

    View_combo_class(std::string theName,std::string theDescription);
    cv::Mat * process_selection();
};

#endif // VIEW_COMBO_CLASS_H
