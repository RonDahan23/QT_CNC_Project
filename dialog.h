#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>


QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:

    void on_pushButtonON_clicked();
    void on_pushButtonOFF_clicked();
    void updateLed(QString command);

private:
    QString Number;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendorID = 9025;
    static const quint16 arduino_uno_productID = 67;
    QString arduino_port_name;
    bool arduino_is_available;

    Ui::Dialog *ui;
};
#endif // DIALOG_H
