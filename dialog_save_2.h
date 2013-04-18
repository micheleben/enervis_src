#ifndef DIALOG_SAVE_2_H
#define DIALOG_SAVE_2_H

#include <QDialog>
#include "acquisition_class.h"
namespace Ui {
class Dialog_save_2;
}
/*!
 \brief this dialog is used in order to configure acquisition_class object

*/
class Dialog_save_2 : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog_save_2(QWidget *parent = 0);
    ~Dialog_save_2();
    
private slots:
    void on_btn_choose_dir_clicked();

    void on_buttonBox_accepted();

private:
    Ui::Dialog_save_2 *ui;
};

#endif // DIALOG_SAVE_2_H
