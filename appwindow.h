#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "main_window_widget.h"
#include "form_configure_firmware.h"
#include "form_tool_webcam.h"
#include "dialog_conf_views.h"
//#include "dialog_save.h"
#include "dialog_save_2.h"
#include "dialog_conf_combo_views.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

/*!
 \brief

*/
class AppWindow : public QMainWindow
{
    Q_OBJECT
    
public:
/*!
 \brief

*/
     AppWindow();
protected:
    /*!
     \brief

     \param event
    */
    void closeEvent(QCloseEvent *event);

private slots:
    /*!
     \brief

    */
    void Load_bitstream();
    /*!
     \brief

    */
    void show_form_to_configure_firmware();
    /*!
     \brief

    */
    void show_form_of_the_tool_webcam();
    /*!
     \brief show the form to configure the two views of the main window (the left view and the right view)

    */
    void show_dialog_to_configure_view();

    /*!
     \brief show the form to configure the combo view of the combo view tool

    */
    void show_dialog_to_configure_combo_view();

    /*!
     \brief show the dialog to configure saving data. It's possible to configure data source and data destination

    */
    void show_dialog_to_save_data();
    /*!
     \brief

    */
    void about();

public slots:
    /*!
     \brief

    */
    void MainTimerElapsed();

private:
    Main_window_widget *centralWidget; /*!< TODO */
    Form_Configure_Firmware *form_to_configure_firmware; /*!< TODO */
    form_tool_webcam *form_of_the_tool_webcam; /*!< TODO */
    Dialog_conf_views *dialog_to_configure_views; /*!< TODO */
    Dialog_conf_combo_views *dialog_to_configure_combo_views;
    //Dialog_save *dialog_to_save_data;
    Dialog_save_2 *dialog_to_save_data;

    QMenu *File_Menu; /*!< TODO */
    QMenu *Conf_Menu; /*!< TODO */
    QMenu *Tools_Menu; /*!< TODO */
    QMenu *Help_Menu; /*!< TODO */

    QAction *Tool_Webcam_Act; /*!< TODO */
    QAction *Load_bitstream_Act; /*!< TODO */
    QAction *Configure_firmware_Act; /*!< TODO */
    QAction *Configure_Views_Act; /*!< TODO */
    QAction *Configure_Combo_Views_Act;
    QAction *Configure_Save_data_Act;

    QAction *aboutAct; /*!< TODO */
    QAction *exitAct; /*!< TODO */

    QTimer* MainTimer; /*!< TODO */

    /*!
     \brief

     \return bool
    */
    bool errorlib();
    /*!
     \brief

    */
    void createActions();
    /*!
     \brief

    */
    void createMenus();
};

#endif // APPWINDOW_H
