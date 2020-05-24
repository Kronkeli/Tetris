#include "optionsdialog.h"

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
    difficulties_->addItem("heleppo");
    difficulties_->addItem("heleepompi");
    difficulties_->addItem("heleeeeepoin");
    vlay->addWidget(difficulties_);

    QPushButton *okButton = new QPushButton("OK");
    connect( okButton, &QPushButton::clicked, this, &OptionsDialog::okClicked );
    vlay->addWidget(okButton);
    wdg->setLayout(vlay);
}

void OptionsDialog::okClicked()
{
    int interval = DIFFICULTIES.at( difficulties_->currentText() );
    emit setDifficulty(interval);
    close();
}
