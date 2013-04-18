#ifndef DIALOG_CONF_COMBO_VIEWS_H
#define DIALOG_CONF_COMBO_VIEWS_H

#include "view_combo_class_container.h"
#include "acquisition_class.h"
#include <QDialog>

namespace Ui {
class Dialog_conf_combo_views;
}
/*! \brief This dialog is used to visualize the combo view*/
class Dialog_conf_combo_views : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog_conf_combo_views(QWidget *parent = 0);
    ~Dialog_conf_combo_views();
    /*!
     \brief Visualize new combo frame on the left label of the widget

    */
    void Visualize_new_Combo_Frame();

private slots:
    void on_chk_isActive_clicked();

    void on_cmb_combo_sel_activated(const QString &arg1);

    void on_chk_combo_double_clicked();

private:
    Ui::Dialog_conf_combo_views *ui;
};

#endif // DIALOG_CONF_COMBO_VIEWS_H
