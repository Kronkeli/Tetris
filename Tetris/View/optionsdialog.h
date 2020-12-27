#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QObject>
#include <QDialog>
#include <QString>
#include <map>
#include <QComboBox>

const std::map<QString, int> DIFFICULTIES =
{
    {"Vaikea", 100},
    {"Keskitaso", 500},
    {"Helppo", 1500}
};

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog( QWidget *parent = 0 );
//    ~OptionsDialog();

public slots:
    void okClicked();

signals:
    void setDifficulty(int interval);

private:
    QComboBox* difficulties_;
};

#endif // OPTIONSDIALOG_H
