#ifndef DIALOG_CONF_VIEWS_H
#define DIALOG_CONF_VIEWS_H
#include "view_class_container.h"
#include "acquisition_class.h"
#include <QDialog>

namespace Ui {
class Dialog_conf_views;
}

/*!
 \brief this dialog is used to configure the two main views

*/
class Dialog_conf_views : public QDialog
{
    Q_OBJECT
    
public:

    explicit Dialog_conf_views(QWidget *parent = 0);

    ~Dialog_conf_views();
    


private slots:

    void on_comboBox_activated(const QString &arg1);
    void on_comboBox_2_activated(const QString &arg1);
    void on_hslid_th_left_sliderReleased();

    void on_hslid_th_right_sliderReleased();

    void on_hslid_gain_left_sliderReleased();

    void on_hslid_gain_right_sliderReleased();

    void on_chk_View_left_clicked();

    void on_chk_View_right_clicked();

    void on_chk_double_left_clicked();

    void on_chk_double_right_clicked();

    void on_cmb_double_left_activated(const QString &arg1);

    void on_cmb_double_right_activated(const QString &arg1);

private:
    Ui::Dialog_conf_views *ui;
    void new_right_selection();
    void new_left_selection();
    int get_enum_type_interp_from_combo_value(int combo_selection);
    int get_combo_value_from_enum_type_interp(int type_interpolation);
};

#endif // DIALOG_CONF_VIEWS_H
