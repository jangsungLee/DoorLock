#include "doorlocksystem.h"
#include "ui_doorlocksystem.h"

#include <QMovie>
#include <QtCore/QDebug>
#include <QFile>

DoorLockSystem::DoorLockSystem(QWidget *_windows[]) :
  windows(_windows),
  ui(new Ui::DoorLockSystem)
{
    ui->setupUi(this);

    setWindowState(Qt::WindowFullScreen);
    setCursor(Qt::BlankCursor);

    m_pTimer = new QTimer();
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(OnTimerCallbackFunc()));

    this->raise();
    ui->LCD_Display->setAlignment(Qt::AlignCenter);
    ui->LCD_Display->setText("");

    if(!QFile::exists("password.bin"))
    {
        QFile file("password.bin");
        qDebug() << "not exist file";
        memcpy(password,initialPassword,strlen(initialPassword));
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "opened file";
            QTextStream out(&file);
            for(int i = 0;i<strlen(initialPassword);i++)
                out << password[i];
            file.close();
        }
    }
    else
    {
        QFile file("password.bin");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "not open file";
        }
        else
        {
            qDebug() << "read file";
            QTextStream stream(&file);
            strcpy(password, stream.readLine().toStdString().c_str());
            file.close();
        }
    }



    QMovie *movie = new QMovie(":/new/prefix1/a.gif");
    movie->setScaledSize(ui->label_2->size());
    ui->label_2->setMovie(movie);
    movie->start();
}

DoorLockSystem::~DoorLockSystem()
{
    delete ui;
}

void DoorLockSystem::OnTimerCallbackFunc()
{

    this->Clear();
    m_pTimer->stop();
}

void DoorLockSystem::on_pushButton_1_clicked() // button '1'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '1';
        input_value[number_index++] = '1';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_2_clicked() // button '2'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '2';
        input_value[number_index++] = '2';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_3_clicked() // button '3'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '3';
        input_value[number_index++] = '3';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_4_clicked() // button '4'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '4';
        input_value[number_index++] = '4';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_5_clicked() // button '5'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '5';
        input_value[number_index++] = '5';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_6_clicked() // button '6'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '6';
        input_value[number_index++] = '6';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_7_clicked() // button '7'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '7';
        input_value[number_index++] = '7';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_8_clicked() // button '8'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '8';
        input_value[number_index++] = '8';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_9_clicked() // button '9'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '9';
        input_value[number_index++] = '9';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_20_clicked() // button '0'
{
    if(number_index < display_count)
     {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '0';
        input_value[number_index++] = '0';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_19_clicked() // button '*'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
        {
            if(input_value[0] != '*')
                display_letters[i] = encrypted_character;
            else
                display_letters[i] = input_value[i];
        }
        display_letters[number_index] = '*';
        input_value[number_index++] = '*';

        ui->LCD_Display->setText(display_letters);

        if(input_value[0] != '*')
        {
            input_value[number_index - 1] = NULL;
            QMovie *movie;
            if(strcmp(input_value, password) == 0)
            {
                movie = new QMovie(":/new/prefix1/c.gif");

                connect(movie, &QMovie::frameChanged, [=](int frameNumber){ // just play at once.
                    if(frameNumber == movie->frameCount()-1){
                        movie->stop();
                        movie->deleteLater();

                        /*QMovie *movie = new QMovie(":/new/prefix1/a.gif");
                        movie->setScaledSize(ui->label_2->size());
                        ui->label_2->setMovie(movie);
                        movie->start();*/
                        this->changeInitImage();
                    }
                });

                qDebug() << "Matched";
            }
            else
            {
                movie = new QMovie(":/new/prefix1/d.gif");

                connect(movie, &QMovie::frameChanged, [=](int frameNumber){ // just play at once.
                    if(frameNumber == movie->frameCount() - 1){
                        movie->stop();
                        movie->deleteLater();

                        QMovie *movie = new QMovie(":/new/prefix1/a.gif");
                        movie->setScaledSize(ui->label_2->size());
                        ui->label_2->setMovie(movie);
                        movie->start();
                    }
                });

                qDebug() << "UnMatched";
            }


            movie->setScaledSize(ui->label_2->size());
            ui->label_2->setMovie(movie);
            movie->start();
            this->Clear();
            return;
        }
        else if(strcmp(input_value, changePassword) == 0)
        {
            this->Clear();
            ui->label_2->setText("Input The Password You Want To Change!!");
            ui->label_2->setAlignment(Qt::Alignment::enum_type::AlignCenter);
            m_pTimer->start(10);
        }
        else if(strcmp(input_value, systemSetting) == 0)
        {
            this->Clear();

            windows[1]->raise(); // window 1
            qDebug() << "A";
        }
        else
            m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_21_clicked() // button '#'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '#';
        input_value[number_index++] = '#';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }

}

void DoorLockSystem::Clear()
{
    number_index = 0;
    memset(display_letters, 0, sizeof(display_letters));
    memset(input_value, 0, sizeof(input_value));
    ui->LCD_Display->setText("");
}
void DoorLockSystem::changeInitImage()
{
    QMovie *movie = new QMovie(":/new/prefix1/a.gif");
    movie->setScaledSize(ui->label_2->size());
    ui->label_2->setMovie(movie);
    movie->start();
}

