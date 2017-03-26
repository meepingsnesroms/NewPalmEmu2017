#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

#include <QMainWindow>

namespace Ui {
class settingspanel;
}

class settingspanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit settingspanel(QWidget *parent = 0);
    ~settingspanel();

private slots:
    void on_returntopalm_clicked();

    void on_selectrootdir_clicked();

private:
    Ui::settingspanel *ui;
};

#endif // SETTINGSPANEL_H
