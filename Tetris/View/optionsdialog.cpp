#include "View/optionsdialog.h"

#include <QDebug>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

OptionsDialog::OptionsDialog(QWidget *parent):
    QDialog(parent)
{
    setGeometry(500,300,150,100);
    setWindowTitle("Vaikeustaso");

    QWidget * wdg = new QWidget(this);
    QVBoxLayout *vlay = new QVBoxLayout(wdg);

    difficulties_ = new QComboBox(this);
    difficulties_->addItem("Vaikea");
    difficulties_->addItem("Keskitaso");
    difficulties_->addItem("Helppo");
    vlay->addWidget(difficulties_);

    QPushButton *okButton = new QPushButton("OK", this);
    connect(okButton, &QPushButton::clicked, this, &OptionsDialog::okClicked);
    vlay->addWidget(okButton);
    wdg->setLayout(vlay);
}

void OptionsDialog::okClicked()
{
    int interval = DIFFICULTIES.at( difficulties_->currentText() );
    qDebug() << "lähetetään intervalli " << interval;
    emit setDifficulty(interval);
    close();
}
