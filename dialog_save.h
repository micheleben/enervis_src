#ifndef DIALOG_SAVE_H
#define DIALOG_SAVE_H

#include <QDialog>
#include <QStandardItemModel>

#include "acquisition_class.h"

namespace Ui {
class Dialog_save;
}
/*!
 \brief this dialog is used in order to configure acquisition_class object

*/
class Dialog_save : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog_save(QWidget *parent = 0);
    ~Dialog_save();

public slots:

  //void slot_changed();
  void slot_changed(const QModelIndex&, const QModelIndex&);
private:
    Ui::Dialog_save *ui;

protected:
  QStandardItemModel* Model_Item_View;
  QStandardItem* Item_View_1;
  QStandardItem* Item_View_2;
  QStandardItem* Item_View_3;
  std::vector<QStandardItem*> Items_Views;
private slots:
  void on_buttonBox_accepted();
  void on_btn_choose_dir_clicked();
};

#endif // DIALOG_SAVE_H
