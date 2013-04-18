#include <QtGui>
#include "appwindow.h"
#include "okFrontPanelDLL_ben.h"
#include "enervis.h"
#include "global_variables.h"
#include "view_class_container.h"
#include "acquisition_class.h"
#include "view_combo_class_container.h"

AppWindow::AppWindow()
{
    bool try_to_load_oklib = errorlib();
    if (try_to_load_oklib == true) {
        //////////////////////////////////////////////////
        //instantiate device class pointers
        gDev = new okCFrontPanel;
        gFlag_dev_instantiated = true;

        //interface class enervis pointer
        gEnervis = new enervis_class;
        gFlag_enervis_instantiated = true;

        //buffer processing opencv interface
        gCV_ACQ_OF_ENERVIS = new View_initialization;
        gFlag_cv_acq_of_enervis_instantiated = true;
        //gCV_MAT_FRAME_VIEW =  cvCreateMat(104,104,CV_8U );
        gCV_MAT_FRAME_VIEW = new cv::Mat;
        gCV_MAT_FRAME_VIEW->create(104,104,CV_8U) ;
        gFlag_cv_mat_frame_view_instantiated = true;

        //interface "views" containers
        gDefinedViews_right = new View_class_container();
        gDefinedViews_right->Define_Some_Basic_Views();
        gDefinedViews_right->Define_Some_Basic_Views_PAIR();
        gFlag_definedview_right_instantiated = true;
        gDefinedViews_left = new View_class_container();
        gDefinedViews_left->Define_Some_Basic_Views();
        gDefinedViews_left->Define_Some_Basic_Views_ODD();
        gFlag_definedview_left_instantiated = true;

        //interface combo views container
        gDefinedComboViews = new View_combo_class_container();
        gDefinedComboViews->Define_Some_Basic_Combo_Views();
        gFlag_definedcomboview_instantiated = true;
        //gCV_MAT_FRAME_VIEW_left = cvCreateMat(104,104,CV_8U );
        //gFlag_cv_mat_frame_view_left_instantiated = true;
        //gCV_MAT_FRAME_VIEW_right = cvCreateMat(104,104,CV_8U );
        //gFlag_cv_mat_frame_view_right_instantiated = true;
        //Acquisition interface
        gAcquisition = new Acquisition_class();
        ///////////////////////////////////////////////////


        // Qt interface:
        createActions();
        createMenus();
        // create the central widget and the auxiliary forms
        centralWidget = new Main_window_widget(this);
        setCentralWidget(centralWidget);

        form_to_configure_firmware = new Form_Configure_Firmware();
        form_to_configure_firmware->hide();
        form_of_the_tool_webcam = new form_tool_webcam();
        form_of_the_tool_webcam->hide();
        dialog_to_configure_views = new Dialog_conf_views();
        dialog_to_configure_views->hide();
        dialog_to_save_data = new Dialog_save_2();
        dialog_to_save_data->hide();
        dialog_to_configure_combo_views = new Dialog_conf_combo_views();
        dialog_to_configure_combo_views->hide();

        MainTimer = new QTimer(this);
        connect(MainTimer,SIGNAL(timeout()),this, SLOT(MainTimerElapsed()));
        MainTimer->start(20);
    } else{
        close();
    }

}
void AppWindow::createActions()
{
	Load_bitstream_Act = new QAction(tr("&Load bitstream.."), this);
    Load_bitstream_Act->setStatusTip(tr("Load a bitfile"));
    connect(Load_bitstream_Act, SIGNAL(triggered()), this, SLOT(Load_bitstream()));

    Configure_Save_data_Act = new QAction(tr("&Save data.."), this);
    Configure_Save_data_Act->setStatusTip(tr("configure data save"));
    connect(Configure_Save_data_Act,SIGNAL(triggered()), this, SLOT(show_dialog_to_save_data()));

    Tool_Webcam_Act = new QAction(tr("&Webcam"), this);
    Tool_Webcam_Act->setStatusTip(tr("Show the Webcam Tool"));
    connect(Tool_Webcam_Act, SIGNAL(triggered()), this, SLOT(show_form_of_the_tool_webcam()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    Configure_Views_Act = new QAction(tr("Conf &Views.."), this);
    Configure_Views_Act->setStatusTip(tr("configure Views"));
    connect(Configure_Views_Act,SIGNAL(triggered()), this, SLOT(show_dialog_to_configure_view()));

    Configure_Combo_Views_Act = new QAction(tr("Co&Mbo View.."), this);
    Configure_Combo_Views_Act->setStatusTip(tr("configure combo view"));
    connect(Configure_Combo_Views_Act,SIGNAL(triggered()), this, SLOT(show_dialog_to_configure_combo_view()));

    Configure_firmware_Act = new QAction(tr("Conf &Firmware.."), this);
    Configure_firmware_Act->setStatusTip(tr("configure firmware"));
    connect(Configure_firmware_Act,SIGNAL(triggered()), this, SLOT(show_form_to_configure_firmware()));

}

void AppWindow::createMenus()
{
    File_Menu = menuBar()->addMenu(tr("&File"));
    File_Menu->addAction(Load_bitstream_Act);
    File_Menu->addSeparator();
    File_Menu->addAction(Configure_Save_data_Act);
    File_Menu->addSeparator();
    File_Menu->addAction(exitAct);

    Conf_Menu = menuBar()->addMenu(tr("&Configure"));
    Conf_Menu->addAction(Configure_firmware_Act);
    Conf_Menu->addAction(Configure_Views_Act);

    Tools_Menu = menuBar()->addMenu(tr("&Tools"));
    Tools_Menu->addAction(Tool_Webcam_Act);
    Tools_Menu->addAction(Configure_Combo_Views_Act);

    Help_Menu = menuBar()->addMenu(tr("&Help"));
    Help_Menu->addAction(aboutAct);
}

bool AppWindow::errorlib()
{
   if (FALSE == okFrontPanelDLL_LoadLib(NULL)) {
       QMessageBox::about(this, tr("About Application"),
            tr("The <b>opalkelly</b> libs cannot be loaded "
               "check that the file <b>okFrontPanel.dll</b> is in current"
               "execution directory"));
       return false;
  }
   return true;

}
void AppWindow::show_form_to_configure_firmware(){
    form_to_configure_firmware->show();
}

void AppWindow::show_dialog_to_configure_view(){
    dialog_to_configure_views->show();
}

void AppWindow::show_dialog_to_configure_combo_view(){
    dialog_to_configure_combo_views->show();
}
void AppWindow::show_form_of_the_tool_webcam(){
    form_of_the_tool_webcam->show();
}
void AppWindow::show_dialog_to_save_data(){
    dialog_to_save_data->show();
}

void AppWindow::Load_bitstream(){
    if (gFlag_xem_configured == false) {
        QString fileName = QFileDialog::getOpenFileName(this,tr("Load bitstream"),"",tr("Files(*.bit)"));
        //conversion from UTF-16 to UTF-8 on Windows:
        std::string fileName_stdstr = fileName.toLocal8Bit().constData();
        if (gEnervis->Configure_XEM(fileName_stdstr )== true){
            gFlag_xem_configured = true;
            gEnervis->SetDefaultValues();
            form_to_configure_firmware->UpdateForm();
        } else {
            QMessageBox::about(this, tr("Check connection"),
                     tr("Opalkelly device could not be opened. Is one connected?"));
        }
    } else {
        QMessageBox::about(this, tr("bitstream is loaded"),
                 tr("The bitstream has been loaded. To load a new bitstream please close the application"));
    }

}

void AppWindow::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("The <b>Enervis</b> application is a tool "
               "dialog with smart low power image sensors developed by SOI Group, FBK trento"
               "It include tools to configure and characterize the sensors."));
}

void AppWindow::MainTimerElapsed(){

    if ((gFlag_xem_configured) && (gCV_ACQ_OF_ENERVIS->isAcquisitionActive) ){
        //see code in View_Initialization class (file view_class.h):
        //the following function accomplish the following tasks:
        //download data from XEM and memorize in buffer(s) and char frame.
        //From the char frame it builds the global opencv mat gCV_MAT_FRAME.
        gCV_ACQ_OF_ENERVIS->process_frame_enervis();
    }
    if (gDefinedViews_left->isActive){
        //see code in View_container_class:
        //the following function accomplish the following tasks:
        //process the opencv global mat gCV_MAT_FRAME to build gCV_MAT_FRAME_VIEW_left
        gCV_MAT_FRAME_VIEW_left = gDefinedViews_left->view_vector.at(gDefinedViews_left->selection).process_selection();
        //visualization of the results on the left of the interface
        centralWidget->Visualize_new_Frame_on_The_Left_Of_UI();
    }
    if (gDefinedViews_right->isActive){
        //see code in view_container_class:
        //the following function accomplish the following tasks:
        //process the opencv global mat gCV_MAT_FRAME to build gCV_MAT_FRAME_VIEW_right
        gCV_MAT_FRAME_VIEW_right = gDefinedViews_right->view_vector.at(gDefinedViews_right->selection).process_selection();
        //visualization of the results on the right of the interface
        centralWidget->Visualize_new_Frame_on_The_Right_Of_UI();
    }
    if (gDefinedComboViews->isActive){
        //see code in view_container_combo_class:
        gCV_MAT_FRAME_VIEW_COMBO = gDefinedComboViews->view_combo_vector.at(gDefinedComboViews->selection).process_selection();
        //visualization of the result on the label at the left of the combo interface
        dialog_to_configure_combo_views->Visualize_new_Combo_Frame();
    }
    if (gAcquisition->isActive){
        //save files: see the code in acquisition_class
        //first update label in main_window every tot frame
        int tot = 10;
        if ((gAcquisition->current_frame % tot)==0 ) centralWidget->update_recording_labels_acq_active();
        //see code in acquisition class:
        //if the acquisition is active prepare file names and other info in order to store data in the files
        gAcquisition->new_frame_to_save();

        if (gAcquisition->save_left_view == true){
            cv::imwrite(gAcquisition->current_filepath_left_frame.toStdString().c_str(),*gCV_MAT_FRAME_VIEW_left);
        }
        if (gAcquisition->save_right_view == true){
            cv::imwrite(gAcquisition->current_filepath_right_frame.toStdString().c_str(),*gCV_MAT_FRAME_VIEW_right);
        }
        if (gAcquisition->save_combo_view == true){
            cv::imwrite(gAcquisition->current_filepath_combo_frame.toStdString().c_str(),*gCV_MAT_FRAME_VIEW_COMBO);
        }
    } else {
        //update label to keep track of the status..
        centralWidget->update_recording_labels_acq_disabled();
    }
    ////////////////////////////////////////////////////////////
    //other stuff related to tools:
    if ((gTool_webcam_active) && (gWebcam_found) ){
        //webcam tool. Use with caution, it can increase the time of acquisition. The webcam can
        //hold the system call until the end of its integration time.
        form_of_the_tool_webcam->processFrameAndUpdateGUI();
    }
}

void AppWindow::closeEvent(QCloseEvent *event)
//override to take care of the close event
{

    if (gFlag_enervis_instantiated) delete gEnervis;
    if (gFlag_dev_instantiated) delete gDev;

    if (gFlag_cv_acq_of_enervis_instantiated) delete gCV_ACQ_OF_ENERVIS;
    //if (gFlag_cv_mat_frame_view_instantiated) cvReleaseMat(&gCV_MAT_FRAME_VIEW);
    if (gFlag_cv_mat_frame_view_instantiated) gCV_MAT_FRAME_VIEW->release();
    if (gFlag_definedview_left_instantiated) delete gDefinedViews_left;
    if (gFlag_definedview_right_instantiated) delete gDefinedViews_right;
    //if (gFlag_cv_mat_frame_view_left_instantiated) cvReleaseMat(&gCV_MAT_FRAME_VIEW_left);
    //if (gFlag_cv_mat_frame_view_right_instantiated) cvReleaseMat(&gCV_MAT_FRAME_VIEW_left);
    if (gFlag_definedcomboview_instantiated) delete gDefinedComboViews;

    delete centralWidget;
    delete form_to_configure_firmware;
    delete form_of_the_tool_webcam;
    delete dialog_to_configure_views;
    delete dialog_to_save_data;
    event->accept();

    //event->ignore();

}


