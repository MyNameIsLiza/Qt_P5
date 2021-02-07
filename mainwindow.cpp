#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "railwaystation.h"
#include<QMessageBox>
#include<QDateTime>
#include<iostream>
#include<QFile>
#include<QXmlStreamWriter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(770,410);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->dateTimeEdit->setDate(QDate::currentDate());
    ui->dateTimeEdit_2->setDate(QDate::currentDate());
    ui->dateTimeEdit_3->setDate(QDate::currentDate());
    QList<QString> headers;
    headers << "id" << "№" << "Станція відправлення" << "Станція прибуття" << "Час відправлення" << "Час прибуття" ;
    RailWayStation::fillHeaders(ui->tableWidget, headers);
    RailWayStation::fillHeaders(ui->tableWidget_2, headers);
    ui->tableWidget->setColumnWidth(0, 25);
    ui->tableWidget->setColumnWidth(1, 25);
    ui->tableWidget->setColumnWidth(2, 130);
    ui->tableWidget->setColumnWidth(3, 110);
    ui->tableWidget->setColumnWidth(4, 110);
    ui->tableWidget->setColumnWidth(5, 100);
    ui->tableWidget_2->setColumnWidth(0, 25);
    ui->tableWidget_2->setColumnWidth(1, 25);
    ui->tableWidget_2->setColumnWidth(2, 130);
    ui->tableWidget_2->setColumnWidth(3, 110);
    ui->tableWidget_2->setColumnWidth(4, 110);
    ui->tableWidget_2->setColumnWidth(5, 100);
    ui->dateTimeEdit_3->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
QList<RailWayStation> list;

void MainWindow::on_pushButton_clicked()
{
    RailWayStation train;
    QString number = ui->lineEdit->text();
    QString dispatch_station = ui->lineEdit_2->text();
    QString destination_station = ui->lineEdit_3->text();
    QString destination_time = ui->dateTimeEdit_2->dateTime().toString("yyyy.MM.dd hh:mm");
    QString dispatch_time = ui->dateTimeEdit->dateTime().toString("yyyy.MM.dd hh:mm");// && destination_time!="" && dispatch_time!=""
    if(destination_station!="" && dispatch_station!=""){
        if(destination_time > dispatch_time){
            if(destination_station != dispatch_station){
            train.set_id(list.length()+1);
            train.set_number(number.toInt());
            train.set_destination_station(destination_station);
            train.set_dispatch_station(dispatch_station);
            train.set_destination_time(destination_time);
            train.set_dispatch_time(dispatch_time);
            list.append(train);
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
            ui->lineEdit_3->setText("");
            ui->dateTimeEdit->setDate(QDate::currentDate());
            ui->dateTimeEdit_2->setDate(QDate::currentDate());
            ui->dateTimeEdit->setTime(QTime(0, 0));
            ui->dateTimeEdit_2->setTime(QTime(0, 0));
            //ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
            RailWayStation::fillByObject(ui->tableWidget, train);
            message("Важливо", "Новий запис був доданий");
            }else{
            message("Помилка", "Станція прибуття не може бути однаковою зі станцією відправлення");
        }
        }else{
        message("Помилка", "Час прибуття не може бути раніше за час відправлення");
    }
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
        tw->setItem(tw->rowCount()-1, 2, new QTableWidgetItem(train.get_dispatch_station()));
        tw->setItem(tw->rowCount()-1, 3, new QTableWidgetItem(train.get_destination_station()));
        tw->setItem(tw->rowCount()-1, 4, new QTableWidgetItem(train.get_dispatch_time()));
        tw->setItem(tw->rowCount()-1, 5, new QTableWidgetItem(train.get_destination_time()));
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

void RailWayStation::fillByObject(QTableWidget *tw, RailWayStation train){
    tw->setRowCount(tw->rowCount()+1);
    tw->setItem(tw->rowCount()-1, 0, new QTableWidgetItem(QString::number(train.get_id())));
    tw->setItem(tw->rowCount()-1, 1, new QTableWidgetItem(QString::number(train.get_number())));
    tw->setItem(tw->rowCount()-1, 2, new QTableWidgetItem(train.get_dispatch_station()));
    tw->setItem(tw->rowCount()-1, 3, new QTableWidgetItem(train.get_destination_station()));
    tw->setItem(tw->rowCount()-1, 4, new QTableWidgetItem(train.get_dispatch_time()));
    tw->setItem(tw->rowCount()-1, 5, new QTableWidgetItem(train.get_destination_time()));
}

void MainWindow::message(QString title, QString text){
    QMessageBox msgbox;
    msgbox.setWindowTitle(title);
    msgbox.setText(text);
    msgbox.exec();
}

void MainWindow::on_lineEdit_5_textChanged(const QString &arg1)
{
    QString text = arg1;
    if(ui->comboBox->currentIndex() == 0)
    {
        foreach(QChar c, arg1)
            {
                if(!c.isNumber())
                {
                    message("Помилка", "Ви повинні ввести число");
                    text.chop(1);
                    ui->lineEdit_5->setText(text);
                    return;
                }
        }
    }
    if(ui->comboBox->currentIndex() == 1)
    {
        foreach(QChar c, arg1)
            {
                if(!c.isNumber())
                {
                    message("Помилка", "Ви повинні ввести число від 1 до 999");
                    text.chop(1);
                    ui->lineEdit_5->setText(text);
                    return;
                }
        }
        if(arg1.length()>3)
        {
            message("Помилка", "Ви повинні ввести число від 1 до 999");
            text.chop(1);
            ui->lineEdit_5->setText(text);
            return;
        }
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QString text = arg1;
    foreach(QChar c, arg1)
        {
            if(!c.isNumber())
            {
                message("Помилка", "Ви повинні ввести число від 1 до 999");
                text.chop(1);
                ui->lineEdit->setText(text);
                return;
            }
    }
    if(arg1.length()>3)
    {
        message("Помилка", "Ви повинні ввести число від 1 до 999");
        text.chop(1);
        ui->lineEdit->setText(text);
        return;
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(ui->comboBox->currentIndex()== 4 || ui->comboBox->currentIndex()== 5)
    {
        ui->dateTimeEdit_3->setVisible(true);
        ui->lineEdit_5->setVisible(false);
    }
    else
    {
        ui->dateTimeEdit_3->setVisible(false);
        ui->lineEdit_5->setVisible(true);
    }
    ui->lineEdit_5->setText("");
    ui->dateTimeEdit_3->setDate(QDate::currentDate());
    ui->dateTimeEdit_3->setTime(QTime(0, 0));
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    //ui->comboBox_2->setVisible(false);
    switch (index) {
        case 0: std::sort(list.begin(), list.end(), RailWayStation::compare_by_id);
        break;
        case 1: std::sort(list.begin(), list.end(), RailWayStation::compare_by_number);
        break;
        case 2: std::sort(list.begin(), list.end(), RailWayStation::compare_by_destination_station);
        break;
        case 3: std::sort(list.begin(), list.end(), RailWayStation::compare_by_dispatch_station);
        break;
        case 4: std::sort(list.begin(), list.end(), RailWayStation::compare_by_destination_time);
        break;
        case 5: std::sort(list.begin(), list.end(), RailWayStation::compare_by_dispatch_time);
        break;
    }
    RailWayStation::fillByList(ui->tableWidget, list);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString id = ui->lineEdit_6->text();
    for(int i = 0; i <list.length(); i++){
    if(ui->tableWidget->item(i, 0)->text() == id){
        ui->tableWidget->removeRow(i);
        list.remove(i);
        ui->lineEdit_6->setText("");
        return;
    }
    }
    message("Важливо", "Запис з id = " + id + " відсутній у списку");
    ui->lineEdit_6->setText("");
}

void MainWindow::on_lineEdit_6_textChanged(const QString &arg1)
{
    QString text = arg1;
    foreach(QChar c, arg1)
        {
            if(!c.isNumber())
            {
                message("Помилка", "Ви повинні ввести число");
                text.chop(1);
                ui->lineEdit_6->setText(text);
                return;
            }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString s = ui->lineEdit_5->text();
    int index = ui->comboBox->currentIndex();
    QList<RailWayStation> search;
    ui->tableWidget_2->setRowCount(0);
    switch (index) {
    case 0: search = RailWayStation::search_by_id(list, s.toInt());
        break;
    case 1: search = RailWayStation::search_by_number(list, s.toInt());
        break;
    case 2: search = RailWayStation::search_by_destination_station(list, s);
         break;
    case 3: search = RailWayStation::search_by_dispatch_station(list, s);
         break;
    case 4: s = ui->dateTimeEdit_3->dateTime().toString("yyyy.MM.dd hh:mm");
        search = RailWayStation::search_by_destination_time(list, s);
         break;
    case 5: s = ui->dateTimeEdit_3->dateTime().toString("yyyy.MM.dd hh:mm");
        search = RailWayStation::search_by_dispatch_time(list, s);
         break;
    }

    if(search.length()!=0) RailWayStation::fillByList(ui->tableWidget_2, search);
    else{
        message("Помилка", "Потрібних записів не знайдено");
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    for(int i = 0; i <list.length(); i++){
    if(ui->tableWidget->item(i, 5)->text() < QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm"))
    {
        for(int j = 0; j < ui->tableWidget->columnCount(); j++){
        ui->tableWidget->item(i, j)->setBackground(QColor::fromRgb(255, 180, 153));
    }
    }else if(ui->tableWidget->item(i, 4)->text() < QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm"))
    {
        for(int j = 0; j <ui->tableWidget->columnCount(); j++){
        ui->tableWidget->item(i, j)->setBackground(QColor::fromRgb(254, 243, 123));
        }
    }else
    {
        for(int j = 0; j <ui->tableWidget->columnCount(); j++){
        ui->tableWidget->item(i, j)->setBackground(QColor::fromRgb(187, 249, 129));
        }
    }
}
}
QString filename ="trains.xml";
void MainWindow::on_pushButton_5_clicked()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Важливо", "Ви впевнені, що хочете переписати файл?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::No) {
        return;
      }
    QFile file(filename);
    if( !file.open(QIODevice::WriteOnly) ) {
        message( "Помилка","Не вдалось відкрити/створити файл на запис");
        return;
    } else {
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartElement("Trains");
        int i = 0;
        while (i < list.length()) {
            xmlWriter.writeStartElement("Train");
            xmlWriter.writeStartElement("id");
            xmlWriter.writeAttribute("QString", RailWayStation::get_id(list.at(i)));
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("number");
            xmlWriter.writeAttribute("QString", RailWayStation::get_number(list.at(i)));
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("dispatch_station");
            xmlWriter.writeAttribute("QString", RailWayStation::get_dispatch_station(list.at(i)));
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("destination_station");
            xmlWriter.writeAttribute("QString", RailWayStation::get_destination_station(list.at(i)));
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("dispatch_time");
            xmlWriter.writeAttribute("QString", RailWayStation::get_dispatch_time(list.at(i)));
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("destination_time");
            xmlWriter.writeAttribute("QString", RailWayStation::get_destination_time(list.at(i)));
            xmlWriter.writeEndElement();
            i++;
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
        file.close();
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    QList<RailWayStation> new_list;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(this,"Помилка",
            "Не вдалося відкрити файл",
            QMessageBox::Ok);
            return;
    }
    QXmlStreamReader xmlReader(&file);
    RailWayStation t;
    while(!xmlReader.atEnd() && !xmlReader.hasError()) {

        QXmlStreamReader::TokenType token = xmlReader.readNext();
        if(token == QXmlStreamReader::StartDocument) {
                        continue;
                }
                if(token == QXmlStreamReader::StartElement) {

        if(xmlReader.name().toString() == "id") {
            QXmlStreamAttribute a = xmlReader.attributes().at(0);
            t.set_id(a.value().toInt());
        }
        if(xmlReader.name().toString() == "number") {
            QXmlStreamAttribute a = xmlReader.attributes().at(0);
            t.set_number(a.value().toInt());
        }
        if(xmlReader.name().toString() == "dispatch_station") {
            QXmlStreamAttribute a = xmlReader.attributes().at(0);
            t.set_dispatch_station(a.value().toString());
        }
        if(xmlReader.name().toString() == "destination_station") {
            QXmlStreamAttribute a = xmlReader.attributes().at(0);
            t.set_destination_station(a.value().toString());
        }
        if(xmlReader.name().toString() == "dispatch_time") {
            QXmlStreamAttribute a = xmlReader.attributes().at(0);
            t.set_dispatch_time(a.value().toString());
        }
        if(xmlReader.name().toString() == "destination_time") {
            QXmlStreamAttribute a = xmlReader.attributes().at(0);
            t.set_destination_time(a.value().toString());
        }
        if (t.get_id()!=0 && t.get_destination_time()!="") {
            new_list.append(t);
            RailWayStation tn;
            t = tn;
        }
    }

    }
    if(xmlReader.hasError()) {
            QMessageBox::critical(this,
            "xmlFile.xml Parse Error",xmlReader.errorString(),
            QMessageBox::Ok);
            return;
    }
    xmlReader.clear();
    file.close();
    list = new_list;
    RailWayStation::fillByList(ui->tableWidget, list);
}
