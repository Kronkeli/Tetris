#ifndef ENDDIALOG_H
#define ENDDIALOG_H


#include <QObject>
#include <QWidget>
#include <QDialog>

class EndDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EndDialog( QWidget *parent = 0 );

private slots:
    void restartPressed();
    void quitPressed();

signals:
    void clearData();
    void quitOrRestart(bool playAgain);
};

#endif // ENDDIALOG_H
