#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Face Detection GUI");
    setWindowIcon(QIcon("icon.png"));

    connect(&ui_Auth, SIGNAL(login_button_clicked()), this, SLOT(authorizeUser()));
    connect(&ui_Auth, SIGNAL(destroyed()), this, SLOT(show()));

    connect(&tevian_cl, &TevianDLL::loginSuccess, this, &MainWindow::loginSuccess);
    connect(&tevian_cl, &TevianDLL::requestError, this, &MainWindow::requestError);
    connect(&tevian_cl, &TevianDLL::detectSuccess, this, &MainWindow::detectSuccess);

    settings = new QSettings("settings.ini", QSettings::IniFormat);

    zoom_x = ui->widget->width();
    zoom_y = ui->widget->height();

    ui->processing->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
}

void MainWindow::authorizeUser()
{
    tevian_cl.login(urls[0], ui_Auth.getLogin(), ui_Auth.getPass());
    ui_Auth.close();

    show();
    showMaximized();
}

void MainWindow::display()
{
    ui_Auth.show();
}

void MainWindow::on_fileChoose_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Select files for processing"), "", tr("JPEG (*.jpg);"));
    QMessageBox::information(this, "Information", "Files uploaded: " + QString::number(fileNames.count()));

    images = fileNames;
    ui->files->clear();

    for(const auto& item : fileNames)
    {
        ui->files->addItem(item);
    }

    if(!fileNames.isEmpty())
    {
        ui->processing->setEnabled(true);
    }
}

void MainWindow::resizeEvent(QResizeEvent *resize)
{
    zoom_x = ui->widget->width();
    zoom_y = ui->widget->height();
}

void MainWindow::loginSuccess(const QByteArray& file)
{
    ui->groupBox->setEnabled(true);
    ui->groupBox_3->setEnabled(true);

    QString token = parser.getToken(file);

    this->token = token;

    QFile f("token.txt");
    f.open(QIODevice::WriteOnly);
    f.write(token.toUtf8());
    f.close();
}

void MainWindow::requestError(const QString& error)
{
    if(error.size() == 0)
    {
        QMessageBox::warning(this, "Error", "Connection Error : Cannot connect to server");
    }
    else
    {
        QMessageBox::warning(this, "Error", error);
    }
}

void MainWindow::detectSuccess(const QByteArray& file)
{
    ui->progressBar->setValue(ui->progressBar->value() + 1);
    info.insert(lastFile, parser.getFaceInfo(file));

    if(images.count() > 0)
    {
        images.removeFirst();
        processNextImage();
    }

    if(images.count() == 0)
    {
        ui->processing->setEnabled(true);
        ui->fileChoose->setEnabled(true);
    }
}

void MainWindow::processNextImage()
{
    if(images.count() > 0)
    {
        tevian_cl.detect(urls[1], images[0], token);
        lastFile = images[0];
    }
    else
    {
        ui->files->itemClicked(ui->files->item(0));
    }
}

void MainWindow::on_processing_clicked()
{
    ui->processing->setDisabled(true);
    ui->fileChoose->setDisabled(true);

    if(images.count() > 0)
    {
        ui->progressBar->setValue(0);
        ui->progressBar->setMaximum(images.count());

        processNextImage();
    }
    else
    {
        QMessageBox::warning(this, "Error", "List Error : No images selected");
    }
}

void MainWindow::on_files_itemClicked(QListWidgetItem *item)
{
    if(prev_item == item->text())
    {
        return;
    }
    if(!info.values(item->text()).count())
    {
        QMessageBox::warning(this, "Error", "Visualization Error : Picture information unavailable");
    }
    else
    {
        ui->widget->centerOn(0, 0);
        ui->widget->resetTransform();

        QString result = "";

        QPixmap pixmap(item->text());
        ui->widget->setImage(pixmap);

        QString infoText = "Age: " + QString::number(info[item->text()].age, 'f', 2);

        auto tmp = info[item->text()];
        ui->widget->setRectangle(tmp.x - pixmap.width() / 2, tmp.y - pixmap.height() / 2, tmp.width, tmp.height, infoText);

        result += info[item->text()].toString();

        ui->fieldX->setText(QString::number(info[item->text()].x));
        ui->fieldY->setText(QString::number(info[item->text()].y));

        ui->fieldWidth->setText(QString::number(info[item->text()].width));
        ui->fieldHeight->setText(QString::number(info[item->text()].height));

        ui->fieldAge->setText(QString::number(info[item->text()].age));
        ui->fieldVariance->setText(QString::number(info[item->text()].variance));
        ui->fieldEthnicity->setText(info[item->text()].ethnicity);
        ui->fieldGender->setText(info[item->text()].gender);
    }
    prev_item = item->text();
}
