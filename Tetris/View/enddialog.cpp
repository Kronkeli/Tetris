#include "View/enddialog.h"

#include <QHBoxLayout>
#include <QPushButton>

EndDialog::EndDialog(QWidget *parent):
    QDialog(parent)
{
    setGeometry(500,300,220,50);
    setWindowTitle("Peli loppui!");

    QWidget* wdg = new QWidget(this);
    QHBoxLayout* hlay = new QHBoxLayout(this);

    QPushButton* restartButton = new QPushButton("Uusi peli", this);
    connect(restartButton, &QPushButton::clicked, this, &EndDialog::restartPressed);
    hlay->addWidget( restartButton );

    QPushButton* quitButton = new QPushButton("Lopeta peli", this);
    connect(quitButton, &QPushButton::clicked, this, &EndDialog::quitPressed);
    hlay->addWidget( quitButton );
    wdg->setLayout( hlay );
}

void EndDialog::restartPressed()
{
    // Tähän vielä restarttitoimintoja:
    emit clearData();
    emit quitOrRestart(true);
    close();
}

void EndDialog::quitPressed()
{
    emit quitOrRestart(false);
    close();
}
