#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);


    arduino = new QSerialPort;
    arduino_is_available = false;
    arduino_port_name = "";

    //view port on your system
    qDebug() << "Number of Ports: " << QSerialPortInfo::availablePorts().length();
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier())
        {
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
            qDebug() << "Product ID " << serialPortInfo.productIdentifier();

        }


    }

    //check which port the arduino is on
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier())
        {
            if(serialPortInfo.vendorIdentifier() == arduino_uno_vendorID)
            {
                if(serialPortInfo.productIdentifier() == arduino_uno_productID)
                {
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                    qDebug() << "Port Availble!";
                }
            }

        }
    }

    if(arduino_is_available)
    {
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::WriteOnly);
        arduino->setBaudRate(QSerialPort:: Baud9600);
        arduino->setDataBits(QSerialPort:: Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    }
    else
    {
        QMessageBox::warning(this, "Port error", "Couldn't find arduino");

    }

}

Dialog::~Dialog()
{
    if(arduino->isOpen())
    {
        qDebug() << "closing port";
        arduino->close();
    }
    delete ui;
}



void Dialog::on_pushButtonON_clicked()
{
    Number = "1";
    updateLed(Number);

}


void Dialog::on_pushButtonOFF_clicked()
{
    Number = "0";
    updateLed(Number);

}

void Dialog::updateLed(QString command)
{
    if(arduino->isWritable())
    {
        qDebug() << command.toStdString().c_str();
        arduino->write(command.toStdString().c_str());
    }
    else
    {
        qDebug() << "could not write to serial!";
    }

}
