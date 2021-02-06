#ifndef RAILWAYSTATION_H
#define RAILWAYSTATION_H

#include <QApplication>
#include <QList>
#include <QTableWidget>

class RailWayStation
{
private:
    int id;
    int number;
    QString destination_station;
    QString dispatch_station;
    QString destination_time;
    QString dispatch_time;
public:
    void static fillByList(QTableWidget *tw, QList<RailWayStation> list);
    void static fillByObject(QTableWidget *tw, RailWayStation book);
    void static fillHeaders(QTableWidget *tw, QList<QString> list);
    int get_id(){
        return id;
    }
    void set_id(int Id){
        id = Id;
    }
    int get_number(){
        return number;
    }
    void set_number(int Number){
        number = Number;
    }
    QString get_destination_station(){
        return destination_station;
    }
    void set_destination_station(QString Destination_station){
        destination_station = Destination_station;
    }
    QString get_dispatch_station(){
        return dispatch_station;
    }
    void set_dispatch_station(QString Dispatch_station){
        dispatch_station = Dispatch_station;
    }
    QString get_destination_time(){
        return destination_time;
    }
    void set_destination_time(QString Destination_time){
        destination_time = Destination_time;
    }
    QString get_dispatch_time(){
        return dispatch_time;
    }
    void set_dispatch_time(QString Dispatch_time){
        dispatch_time = Dispatch_time;
    }
    RailWayStation(){
    };
    RailWayStation(int Id, int Number, QString Destination_station, QString Dispatch_station, QString Destination_time, QString Dispatch_time){
        id = Id;
        number = Number;
        destination_station = Destination_station;
        dispatch_station = Dispatch_station;
        destination_time = Destination_time;
        dispatch_time = Dispatch_time;
    };

    static QList<RailWayStation> search_by_id(QList<RailWayStation> books, int id){
        QList<RailWayStation> search;
        foreach(RailWayStation book, books){
            if(book.id == id){
                search.append(book);
            }
        }
        return search;
    };

    static QList<RailWayStation> search_by_number(QList<RailWayStation> books, int number){

        QList<RailWayStation> search;
        foreach(RailWayStation book, books){
            if(book.number == number){
                search.append(book);
            }
        }
        return search;
    };

    static QList<RailWayStation> search_by_destination_station(QList<RailWayStation> books, QString s){

        QList<RailWayStation> search;
        foreach(RailWayStation book, books){
            if(book.destination_station == s){
                search.append(book);
            }
        }
        return search;
    };

    static QList<RailWayStation> search_by_dispatch_station(QList<RailWayStation> books, QString s){

        QList<RailWayStation> search;
        foreach(RailWayStation book, books){
            if(book.dispatch_station == s){
                search.append(book);
            }
        }
        return search;
    };

    static QList<RailWayStation> search_by_destination_time(QList<RailWayStation> books, QString s){

        QList<RailWayStation> search;
        foreach(RailWayStation book, books){
            if(book.destination_time == s){
                search.append(book);
            }
        }
        return search;
    };

    static QList<RailWayStation> search_by_dispatch_time(QList<RailWayStation> books, QString s){

        QList<RailWayStation> search;
        foreach(RailWayStation book, books){
            if(book.dispatch_time == s){
                search.append(book);
            }
        }
        return search;
    };
    static bool compare_by_id (RailWayStation i,RailWayStation j) { return (i.get_id() < j.get_id()); }
    static bool compare_by_number (RailWayStation i,RailWayStation j) { return (i.get_number() < j.get_number()); }
    static bool compare_by_destination_station (RailWayStation i,RailWayStation j) { return (i.get_destination_station()<j.get_destination_station()); }
    static bool compare_by_dispatch_station (RailWayStation i,RailWayStation j) { return (i.get_dispatch_station()<j.get_dispatch_station()); }
    static bool compare_by_destination_time (RailWayStation i,RailWayStation j) { return (i.get_destination_time()<j.get_destination_time()); }
    static bool compare_by_dispatch_time (RailWayStation i,RailWayStation j) { return (i.get_dispatch_time()<j.get_dispatch_time()); }
};



#endif // RAILWAYSTATION_H
