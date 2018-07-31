#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->convertor_status->setValue(0);
    ui->s_status->setText("");
    ui->d_status->setText("");
    this->setWindowTitle("Subtitle editor");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_databaza_clicked()
{
    std::cout << "Open databaze file" << std::endl;

    d_file = QFileDialog::getOpenFileName(this,tr("Open Document"),QDir::currentPath(),tr("Document files (*.txt *.srt);;All files (*.*)") );

    std::cout << d_file.toStdString() << std::endl;

    inFile.open(d_file.toStdString().c_str());

    if (!(inFile.is_open()))
    {
        std::cout << "Error open file" << std::endl;
        ui->d_status->setText("Error open file");
        inFile.close();
    }
    else
    {
        char config[3];
        std::cout << "\nNacitanie databazy znakov: " << std::endl;

        for(d_array_size=0;inFile.good();d_array_size++)
        {
            inFile.getline(config,5);

            std::cout << config << std::endl;
            znaky[d_array_size][0] = config[0]; znaky[d_array_size][1] = config[2];
            std::cout << d_array_size << ": " << znaky[d_array_size][0] << " - " << znaky[d_array_size][1] << std::endl;
        }

        std::cout << std::endl << std::endl;
        inFile.close();

        ui->d_status->setText("Open file OK");
    }
}

void MainWindow::on_titulky_clicked()
{
    std::cout << "Open subtitle file" << std::endl;

    s_file = QFileDialog::getOpenFileName(this,tr("Open Document"),QDir::currentPath(),tr("Document files (*.txt *.srt);;All files (*.*)") );
    if( !s_file.isNull() )
    {
        //qDebug( s_file.toAscii() );
    }

    std::cout << s_file.toStdString() << std::endl;

    inFile.open(s_file.toStdString().c_str());
    if (!(inFile.is_open()))
    {
        std::cout << "Error open file" << std::endl;
        ui->s_status->setText("Error open file");
        inFile.close();
    }
    else
    {
        // zistim nazov povodneho suboru, pridam zan retazec "_uprava", pridam nakoniec priponu suboru

        QString s_e_name;

        std::cout << s_file.toStdString().find(".srt") << std::endl;
        o_file = QString::fromStdString(s_file.toStdString().erase(s_file.toStdString().find(".srt"),s_file.toStdString().length()));
        o_file += QString("_edit.srt");

        std::cout << s_file.toStdString() << std::endl;
        std::cout << o_file.toStdString() << std::endl;

        inFile.close();
        ui->s_status->setText("Open OK");
    }
}

void MainWindow::on_start_clicked()
{
    std::cout << "Databaze: " << d_file.toStdString() << std::endl;
    std::cout << "Source file: " << s_file.toStdString() << std::endl;
    std::cout << "Out file: " << o_file.toStdString() << std::endl;

    ouFile.open(o_file.toStdString().c_str());
    if (!(ouFile.is_open()))
    {
        std::cout << "Not create" << std::endl;
        ui->process_status->setText("Error create out file");
        ouFile.close();
    }
    else
    {
        char c_temp_o;
        bool b_temp;

        inFile.open(s_file.toStdString().c_str());
        if (!(inFile.is_open()))
        {
            std::cout << "Error open source file" << std::endl;
            ui->process_status->setText("Error open source file");
            inFile.close();
        }
        else
        {
            while (inFile.good())
            {
                c_temp_o = int (inFile.get());

                for (int i=0;i<d_array_size;i++)
                {
                    if ( c_temp_o == znaky[i][0])
                    {
                        b_temp = true;
                        ouFile << char (znaky[i][1]);
                        break;
                    }
                    else
                        b_temp = false;
                }

                if (!(b_temp))
                    ouFile << c_temp_o;

                ui->convertor_status->setValue(ui->convertor_status->value()+1);
            }

            inFile.close();
            ouFile.close();

            ui->process_status->setText("Complete!");
        }
        ouFile.close();
    }
}

void MainWindow::on_exit_clicked()
{
    QApplication::quit();
}

void MainWindow::on_pushButton_clicked()
{
    help mhelp;
    mhelp.setModal(true);
    mhelp.exec();
}
