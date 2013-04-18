#ifndef MAIN_WINDOW_WIDGET_H
#define MAIN_WINDOW_WIDGET_H
#include "ui_main_window_widget.h"

#include "view_class_container.h"
#include "acquisition_class.h"

/*!
 \brief this class controls the visualization of two frames, one in the left and one in the right

*/
class Main_window_widget : public QWidget, public Ui::Form
{
    Q_OBJECT

public:

    Main_window_widget(QWidget *parent = 0);
    /*!
     \brief Visualize new frame on the left label of the widget

    */
    void Visualize_new_Frame_on_The_Left_Of_UI();
    /*!
     \brief Visualize new frame on the right label of the widget

    */
    void Visualize_new_Frame_on_The_Right_Of_UI();
    /*!
     \brief update the labels that give informations about recording status when acq is active
     */
    void update_recording_labels_acq_active();
    /*!
     \brief update the labels that give informations about recording status when acq is disabled
     */
    void update_recording_labels_acq_disabled();
private slots:
    /*! \brief set status of gAcquisition in order to start acq */
    void on_btn_rec_control_clicked();
};


#endif // MAIN_WINDOW_WIDGET_H
