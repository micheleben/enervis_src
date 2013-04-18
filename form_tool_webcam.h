#ifndef FORM_TOOL_WEBCAM_H
#define FORM_TOOL_WEBCAM_H

#include <QWidget>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>



namespace Ui {
class form_tool_webcam;
}

/*!
 \brief simple form to visualize the output of a webcam.. debug purposes

*/
class form_tool_webcam : public QWidget
{
    Q_OBJECT
    
public:
    /*!
     \brief

     \param parent
    */
    explicit form_tool_webcam(QWidget *parent = 0);
    /*!
     \brief

    */
    ~form_tool_webcam();
public slots:
    /*!
     \brief

    */
    void processFrameAndUpdateGUI();
private slots:
    /*!
     \brief

    */
    void on_btnPauseAndResume_clicked();

private:
    Ui::form_tool_webcam *ui; /*!< TODO */
    cv::VideoCapture capWebcam; /*!< TODO */
    cv::Mat    MatOriginal; /*!< TODO */
};

#endif // FORM_TOOL_WEBCAM_H
