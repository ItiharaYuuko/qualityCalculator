#include "miwidget.h"
#include "ui_miwidget.h"

miwidget::miwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::miwidget)
{
    ui->setupUi(this);
    this->initPrepare();
}

miwidget::~miwidget()
{
    delete ui;
}

void miwidget::initPrepare()
{
    this->setWindowTitle(QString("Quality Calculator"));
    ui->densitye->setText(QString::number(7.85));
    this->ccstrliModel = new QStringListModel(this->ccstrlist);
    ui->cchistorylist->setModel(this->ccstrliModel);
    ui->hisansl->setText(QString::number(0));
    ui->cchistorylist->setEditTriggers(0);
    this->radModeFlag = 2.0;
    this->cccountx = 0.0;
    this->aboutflg = true;
    ui->pene->setText(QString::number(0));
    ui->pene->setHidden(true);
    ui->penl->setHidden(true);
}

void miwidget::on_cccbtn_clicked()
{
    double ccDdata = ui->ccDe->text().toDouble();
    double ccddata = ui->ccde->text().toDouble();
    double cchdata = ui->he->text().toDouble();
    double densitycc = ui->densitye->text().toDouble();
    double resultx = 0;
    switch (ui -> cccom -> currentIndex()) {
    case 0:
        resultx = this->torusCalculate(ccDdata,ccddata,cchdata,densitycc);
        this->answerSolution(resultx);
        break;
    case 1:
        resultx = this->cylinderCalculate(ccDdata, cchdata, densitycc);
        this->answerSolution(resultx);
        break;
    default:
        resultx = this->cuboidCalculate(ccDdata,ccddata,cchdata, densitycc);
        this->answerSolution(resultx);
        break;
    }
}

void miwidget::on_clearbtn_clicked()
{
    this->dataPurge();
}

void miwidget::on_cccom_activated(int index)
{
    ui->pene->setHidden(true);
    ui->penl->setHidden(true);
    switch (index) {
    case 0:
        ui->ccDl->setText("大D");
        ui->ccdl->setText("小d");
        ui->hl->setText("高h");
        break;
    case 1:
        ui->ccDl->setText("大D");
        ui->ccdl->setText("N/A");
        ui->hl->setText("高h");
        break;
    case 2:
        ui->ccDl->setText("长L");
        ui->ccdl->setText("宽W");
        ui->hl->setText("厚δ");
        ui->pene->setHidden(false);
        ui->penl->setHidden(false);
        break;
    default:
        break;
    }
}

double miwidget::torusCalculate(double bigD,
                                double smalld,
                                double hight,
                                double density)
{
    return (qPow((bigD / this->radModeFlag), 2)\
            - qPow((smalld / this->radModeFlag), 2))\
            * M_PI * hight * density / 1000000;
}

double miwidget::cylinderCalculate(double bigD,
                                 double hight,
                                 double density)
{
    return (qPow((bigD / this->radModeFlag), 2) * M_PI * hight * density) / 1000000;
}

double miwidget::cuboidCalculate(double bigD,
                               double smalld,
                               double hight,
                               double density)
{
    double qualityOfCuboid = bigD * smalld * hight * density / 1000000;
    double qualityOfCylinder = this->cylinderCalculate(ui->pene->text().toDouble(), hight,density);
    return qualityOfCuboid - qualityOfCylinder;
}

void miwidget::on_aboutBtn_clicked()
{
    double tempsul = 0.0;
    for(int i =0; i < this->tempSelected.count(); ++i)
    {
        tempsul += this->tempSelected.at(i).toDouble();
    }
    QMessageBox *boxxin = new QMessageBox();
    boxxin->setWindowTitle("About author");
    if(this->aboutflg)
    {
        boxxin->setText(QString("True solution is: ") + QString::number(tempsul, 'f', 2));
    }
    else
    {
        boxxin->setText(QString("False solution is: ") + QString::number(tempsul, 'f', 2));
    }
    boxxin->show();
    this->aboutflg = !(this->aboutflg);
    this->tempSelected.clear();
}

void miwidget::answerSolution(double answer)
{
    if(answer <= 0)
    {
        this->insertValuesAlert();
    }
    else
    {
        QString ansstr = QString::number(answer, 'f', 2);
        ui->ansl->setText(ansstr);
        this->cccountx+=answer;
        this->ccstrlist.append(ansstr);
        this->ccstrliModel->setStringList(this->ccstrlist);
        ui->hisansl->setText(QString::number(this->cccountx, 'f', 2));
    }
}

void miwidget::on_radchek_stateChanged(int arg1)
{
    switch (arg1) {
    case 0:
        this->radModeFlag = 2;
        ui->ccDl->setText("大D");
        if(ui->cccom->currentIndex() != 1)
            ui->ccdl->setText("小d");
        ui->penl->setText("PeneratedD");
        break;
    default:
        this->radModeFlag = 1;
        ui->ccDl->setText("大R");
        if(ui->cccom->currentIndex() != 1)
            ui->ccdl->setText("小r");
        ui->penl->setText("PeneratedR");
        break;
    }
}

void miwidget::dataPurge()
{
    this->cccountx = 0.0;
    this->ccstrlist.clear();
    this->ccstrliModel->setStringList(this->ccstrlist);
    ui->hisansl->setText(QString::number(cccountx, 'f', 2));
}

void miwidget::insertValuesAlert()
{
    QMessageBox *answerAlertBox = new QMessageBox();
    answerAlertBox->setWindowTitle("输入值警告！");
    answerAlertBox->setText("Please insert avaliable value.");
    answerAlertBox->show();
    ui->ccDe->setText("0");
    ui->ccde->setText("0");
    ui->he->setText("0");
    ui->pene->setText("0");
    ui->ansl->setText("0");
}

void miwidget::on_cchistorylist_doubleClicked(const QModelIndex &index)
{
    this->ccstrlist.removeAt(index.row());
    this->ccstrliModel->removeRow(index.row(),index);
    this->ccstrliModel->setStringList(this->ccstrlist);
}


void miwidget::on_cchistorylist_clicked(const QModelIndex &index)
{
    this->tempSelected.append(this->ccstrlist.at(index.row()));
    qDebug() << this->ccstrlist.at(index.row());
}
