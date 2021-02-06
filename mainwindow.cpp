#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "railwaystation.h"
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
QList<HomeLibrary> list;

void MainWindow::on_pushButton_clicked()
{
    RailWayStation train;
    QString title = ui->lineEdit->text();
    QString author = ui->lineEdit_2->text();
    QString publish_year = ui->lineEdit_3->text();
    QString genre = ui->lineEdit_4->text();
    if(title!="" && author!="" && publish_year!="" && genre!=""){
        if(!(publish_year.toInt()<2022 && publish_year.toInt()>=1457)){
            message("Помилка", "Некоректно введений рік\nПерша книга була видана у 1457 році!");
            ui->lineEdit_3->setText("");
            return;
        }
            train.set_id(list.length()+1);
            train.set_title(title);
            train.set_author(author);
            train.set_publish_year(publish_year);
            train.set_genre(genre);
            list.append(train);
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
            ui->lineEdit_3->setText("");
            ui->lineEdit_4->setText("");
            RailWayStation::fillByObject(ui->tableWidget, train);
            message("Важливо", "Нова книга була додана");
    }else{
        message("Помилка", "Заповніть всі поля");
    }
}

void RailWayStation::fillByList(QTableWidget *tw, QList<RailWayStation> list){
    tw->setRowCount(0);
    foreach(RailWayStation train, list){
        tw->setRowCount(tw->rowCount()+1);
        tw->setItem(tw->rowCount()-1, 0, new QTableWidgetItem(QString::number(train.get_id())));
        tw->setItem(tw->rowCount()-1, 1, new QTableWidgetItem(QString::number(train.get_number())));
        tw->setItem(tw->rowCount()-1, 2, new QTableWidgetItem(train.get_destination_station()));
        tw->setItem(tw->rowCount()-1, 3, new QTableWidgetItem(train.get_dispatch_station()));
        tw->setItem(tw->rowCount()-1, 4, new QTableWidgetItem(train.get_destination_time()));
        tw->setItem(tw->rowCount()-1, 5, new QTableWidgetItem(train.get_dispatch_time()));
    }
}

void RailWayStation::fillHeaders(QTableWidget *tw, QList<QString> list){
    if(list.length()>=1){
    tw->setColumnCount(list.length());
    for(int i = 0; i < list.length(); i++){
        tw->setHorizontalHeaderItem(i, new QTableWidgetItem(list.at(i)));
    }
    }
}

void RailWayStation::fillByObject(QTableWidget *tw,RailWayStation train){
    tw->setRowCount(tw->rowCount()+1);
    tw->setItem(tw->rowCount()-1, 0, new QTableWidgetItem(QString::number(train.get_id())));
    tw->setItem(tw->rowCount()-1, 0, new QTableWidgetItem(QString::number(train.get_number())));
    tw->setItem(tw->rowCount()-1, 1, new QTableWidgetItem(train.get_destination_station()));
    tw->setItem(tw->rowCount()-1, 2, new QTableWidgetItem(train.get_dispatch_station()));
    tw->setItem(tw->rowCount()-1, 3, new QTableWidgetItem(train.get_destination_time()));
    tw->setItem(tw->rowCount()-1, 4, new QTableWidgetItem(train.get_dispatch_time()));
}

void MainWindow::message(QString title, QString text){
    QMessageBox msgbox;
    msgbox.setWindowTitle(title);
    msgbox.setText(text);
    msgbox.exec();
}
