/** \file main.cpp
 *
 * \brief application main file, declaration of global variables
 *
 * This file contains the entry point to the application, and the declaration
 * of global variables that have been extern declared int he .h files.
 */

#include <QtGui/QApplication>
#include "appwindow.h"
#include "okFrontPanelDLL_ben.h"
#include "enervis.h"
#include "global_variables.h"
#include "view_class_container.h"
#include "acquisition_class.h"
#include "view_combo_class_container.h"
#include <opencv2/core/core.hpp>
//////////////////////////////////////////////////////////////////////////////////////////////
//global variables declarations:
enervis_class *gEnervis;                    //extern declaration in enervis.h
okCFrontPanel *gDev;                        //extern declaration in okFrontPanelDLL_ben.h
View_initialization *gCV_ACQ_OF_ENERVIS;    //extern declaration in view_class.h
//CvMat *gCV_MAT_FRAME_VIEW;                  //extern declaration in view_class.h
cv::Mat * gCV_MAT_FRAME_VIEW;                  //extern declaration in view_class.h

View_class_container *gDefinedViews_left;   //extern declaration in view_class_container.h
View_class_container *gDefinedViews_right;  //extern declaration in view_class_container.h
//CvMat *gCV_MAT_FRAME_VIEW_left;             //extern declaration in view_class_container.h
cv::Mat * gCV_MAT_FRAME_VIEW_left;             //extern declaration in view_class_container.h
//CvMat *gCV_MAT_FRAME_VIEW_right;            //extern declaration in view_class_container.h
cv::Mat * gCV_MAT_FRAME_VIEW_right;            //extern declaration in view_class_container.h

Acquisition_class * gAcquisition;         //extern declaration in acquisition_class.h

View_combo_class_container *gDefinedComboViews; //extern declaration in view_combo_class_container.h
cv::Mat * gCV_MAT_FRAME_VIEW_COMBO;     //extern declaration in view_combo_class_container.h
/////////////////////////////////////////////////////////////////////////////////////////////
//global variables to control the instantations:
bool gFlag_dev_instantiated = false;                        //extern declaration in global_variables.h
bool gFlag_enervis_instantiated = false;                    //extern declaration in global_variables.h
bool gFlag_cv_acq_of_enervis_instantiated = false;          //extern declaration in global_variables.h
bool gFlag_cv_mat_frame_view_instantiated = false;          //extern declaration in global_variables.h

bool gFlag_definedview_left_instantiated = false;           //extern declaration in global_variables.h
bool gFlag_definedview_right_instantiated = false;          //extern declaration in global_variables.h
bool gFlag_cv_mat_frame_view_left_instantiated = false;     //extern declaration in global_variables.h
bool gFlag_cv_mat_frame_view_right_instantiated = false;    //extern declaration in global_variables.h

bool gFlag_definedcomboview_instantiated = false; //extern declaration in global_variables.h
//////////////////////////////////////////////////////////////////////////////////////////////
//global variables to control the program flux
bool gFlag_xem_configured = false;          //extern declaration in global_variables.h
bool gFlag_dev_connected = false;           //extern declaration in global_variables.h
bool gTool_webcam_active = false;           //extern declaration in global_variables.h
bool gWebcam_found = false;                 //extern declaration in global_variables.h
//////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    QApplication app_qt_ben(argc, argv);
    AppWindow main_window_qt_ben;
    main_window_qt_ben.show();
    
    return app_qt_ben.exec();
}
