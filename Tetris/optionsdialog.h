#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QObject>
#include <QDialog>
#include <QString>
#include <map>
#include <QComboBox>

const std::map<QString, int> DIFFICULTIES =
{
    {"heleppo", 100},
    {"heleepompi", 500},
    {"heleeeeepoin", 1000}
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
