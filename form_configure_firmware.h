#ifndef FORM_CONFIGURE_FIRMWARE_H
#define FORM_CONFIGURE_FIRMWARE_H

#include <QWidget>

namespace Ui {
class Form_Configure_Firmware;
}

/*!
 \brief this form is used to configure the object of the enervis class

*/
class Form_Configure_Firmware : public QWidget
{
    Q_OBJECT
    
public:

    explicit Form_Configure_Firmware(QWidget *parent = 0);

    ~Form_Configure_Firmware();

    void UpdateForm();

private slots:

    void on_btnConfEnervis_clicked();


    void on_btnActiveAcq_clicked();

private:
    Ui::Form_Configure_Firmware *ui; /*!< TODO */

    bool GetFormValues();

    void DisableAllControls(bool flag);
};

#endif // FORM_CONFIGURE_FIRMWARE_H
