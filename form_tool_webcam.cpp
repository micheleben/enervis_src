#include "form_tool_webcam.h"
#include "ui_form_tool_webcam.h"
#include "global_variables.h"

form_tool_webcam::form_tool_webcam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::form_tool_webcam)
{
    ui->setupUi(this);
    capWebcam.open(0);
    if (capWebcam.isOpened()==false){
        ui->lblOriginal->setText("error opening webcam");
        gWebcam_found = false;
        ui->btnPauseAndResume->setEnabled(false);
    } else {
        gWebcam_found = true;
        ui->btnPauseAndResume->setEnabled(true);
        ui->btnPauseAndResume->setText("start");
    }

}

form_tool_webcam::~form_tool_webcam()
{
    delete ui;
}

void form_tool_webcam::processFrameAndUpdateGUI(){
    capWebcam.read(MatOriginal);
    if (MatOriginal.empty()== true) return;
    QImage qimgOriginal((uchar*)MatOriginal.data,MatOriginal.cols,MatOriginal.rows,MatOriginal.step,QImage::Format_RGB888);
    ui->lblOriginal->setPixmap(QPixmap::fromImage(qimgOriginal));
}

void form_tool_webcam::on_btnPauseAndResume_clicked()
{
    if (gTool_webcam_active == true){
        gTool_webcam_active = false;
        ui->btnPauseAndResume->setText("resume");
    } else {
        gTool_webcam_active = true;
        ui->btnPauseAndResume->setText("pause");
    }
}
