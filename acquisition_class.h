#ifndef ACQUISITION_CLASS_H
#define ACQUISITION_CLASS_H

#include <qstring.h>
#include <QTime>
#include "view_class_container.h"
#include "view_combo_class_container.h"
#include <QDir>
/*!
 \brief An acquisition is a sequence of images that is stored in the hd.
    The acquisition_class is used to manage the storage .


*/
class Acquisition_class
{
public:

    int number_of_frames; //total number of frames to be saved
    int current_frame; //the current frame
    double current_percent_frame; //current percentage of the total number of frames (for log purposes)

    bool save_left_view;
    View_class * p_left_view; //pointer to the view selected in the left view
    bool save_right_view;
    View_class * p_right_view; //pointer to the view selected in the right view
    bool save_combo_view;
    View_combo_class * p_combo_view; //pointer to the view selected in the combo view
    bool isActive;
    QString prefix_filename_left_view; // prefix of the filename left view;
    QString prefix_filename_right_view; // prefix of the filename right view;
    QString prefix_filename_combo_view; // prefix of the filename right view;

    QString label_left_view; // the label that is used at the beginning of left view file name
    QString label_right_view; //the label that is used at the beginning of right view file name
    QString label_combo_view; //the label that is used at the beginning of combo view file name
    QString file_extension; // ".bmp" default

    QString current_filepath_left_frame; //the filename and path where store the current left frame
    QString current_filepath_right_frame; //the filename and path where store the current right frame
    QString current_filepath_combo_frame; //the filename and path where store the current combo frame

    QDir directory_where_save; // the directory where save data
    QTime last_acquisition_setting_time; // the time when the acquisition settings has changed
    QString format_time_filename;
    QString format_time_label;

    Acquisition_class();
    /*! \brief update the two pointers used to copy the memory location of the image to the
      storage. It update also the label of the filename that identify the sequence
    */
    void update_values();
    /*! \brief compose the filename (comprehensive of th global path)
        of the two files where the current frame should be saved
      */
    void compose_filename();
    /*! \brief this function it's the entry point of the class during the acquisition. It's called
      each time the acquisition timer is elapsed in order to save new frames in the memory storage.
      */
    void new_frame_to_save();

};
extern Acquisition_class * gAcquisition;
#endif // ACQUISITION_CLASS_H
