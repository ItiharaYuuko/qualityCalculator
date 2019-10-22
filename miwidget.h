#ifndef MIWIDGET_H
#define MIWIDGET_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QStringListModel>
#include <QMessageBox>
#include <QtMath>

namespace Ui {
class miwidget;
}

class miwidget : public QWidget
{
    Q_OBJECT

public:
    explicit miwidget(QWidget *parent = 0);
    ~miwidget();
private slots:
    void on_cccbtn_clicked();

    void on_clearbtn_clicked();

    void on_cccom_activated(int index);

    void on_aboutBtn_clicked();

    void on_radchek_stateChanged(int arg1);

    void on_cchistorylist_doubleClicked(const QModelIndex &index);

    void on_cchistorylist_clicked(const QModelIndex &index);

private:
    Ui::miwidget *ui;

    QStringList ccstrlist;

    QStringListModel *ccstrliModel;

    QStringList tempSelected;

    double cccountx;

    bool aboutflg;

    double radModeFlag;

    void answerSolution(double);

    double torusCalculate(double bigD,
                          double smalld,
                          double hight,
                          double density);

    double cylinderCalculate(double bigD,
                           double hight,
                           double density);

    double cuboidCalculate(double bigD,
                         double smalld,
                         double hight,
                         double density);

    void dataPurge();

    void initPrepare();

    void insertValuesAlert();
};

#endif // MIWIDGET_H
