#include "dialog_save.h"
#include "ui_dialog_save.h"
#include <QFileDialog>

Dialog_save::Dialog_save(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_save)
{
    ui->setupUi(this);
    this->Model_Item_View = new QStandardItemModel;
    this->Item_View_1 = new QStandardItem;
    this->Item_View_1->setText("Left view");
    this->Item_View_1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    if (gAcquisition->save_left_view == true){
       this->Item_View_1->setData(Qt::Checked, Qt::CheckStateRole);
    } else {
       this->Item_View_1->setData(Qt::Unchecked, Qt::CheckStateRole);
    }


    this->Item_View_2 = new QStandardItem;
    this->Item_View_2->setText("Right view");
    this->Item_View_2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    if (gAcquisition->save_right_view == true){
       this->Item_View_2->setData(Qt::Checked, Qt::CheckStateRole);
    } else {
       this->Item_View_2->setData(Qt::Unchecked, Qt::CheckStateRole);
    }

    this->Item_View_3 = new QStandardItem;
    this->Item_View_3->setText("Combo view");
    this->Item_View_3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    if (gAcquisition->save_combo_view == true){
       this->Item_View_3->setData(Qt::Checked, Qt::CheckStateRole);
    } else {
       this->Item_View_3->setData(Qt::Unchecked, Qt::CheckStateRole);
    }

    connect(this->Model_Item_View, SIGNAL(dataChanged ( const QModelIndex&, const QModelIndex&)), this, SLOT(slot_changed(const QModelIndex&, const QModelIndex&)));

    this->Model_Item_View->insertRow(0,this->Item_View_1);
    this->Model_Item_View->insertRow(1,this->Item_View_2);
    this->Model_Item_View->insertRow(2,this->Item_View_3);
    this->Items_Views.push_back(this->Item_View_1);
    this->Items_Views.push_back(this->Item_View_2);
    this->Items_Views.push_back(this->Item_View_3);
    ui->cmb_data_source->setModel(this->Model_Item_View);
    ui->lne_number_of_frames->setText(QString::number(gAcquisition->number_of_frames,10));
}

Dialog_save::~Dialog_save()
{
    delete ui;
}


void Dialog_save::slot_changed(const QModelIndex & topLeft, const QModelIndex & bottomRight){
    bool value;
    int index = topLeft.row();
    QStandardItem* item = this->Items_Views[index];
    if(item->checkState() == Qt::Unchecked){
        value = false;
    }
    else if(item->checkState() == Qt::Checked){
        value = true;
    }
    switch (index) {
        case 0:
            gAcquisition->save_left_view = value;
            break;
        case 1:
            gAcquisition->save_right_view = value;
            break;
        case 2:
            gAcquisition->save_combo_view = value;
            break;
    }

}

void Dialog_save::on_buttonBox_accepted()
{
    gAcquisition->number_of_frames = ui->lne_number_of_frames->text().toInt();
    gAcquisition->update_values();
}



void Dialog_save::on_btn_choose_dir_clicked()
{
    //set the directory where the data has to be saved
    QString path = QFileDialog::getExistingDirectory (this, tr("Directory"), gAcquisition->directory_where_save.path());
    if ( path.isNull() == false )
    {
        gAcquisition->directory_where_save.setPath(path);

    }

}
