
#include "config.h"
#include <stdio.h>

#include "silentbackupdlg.h"
#include "ui_silentbackupdlg.h"

#define TIMEOUT 5

SilentBackupDlg::SilentBackupDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SilentBackupDlg)
{
    ui->setupUi(this);

    connect(&_counter, SIGNAL(countdownTick(int)), this, SLOT(countdown(int)));
    connect(&_counter, SIGNAL(countdownExpired()), this, SLOT(countdownExpired()) );
    //ui->list->installEventFilter(&_counter);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(TIMEOUT);
    ui->progressBar->setValue(0);
    _counter.startCountdown(TIMEOUT);
}

SilentBackupDlg::~SilentBackupDlg()
{
    delete ui;
}

void SilentBackupDlg::accept()
{
}

void SilentBackupDlg::countdown(int count)
{
    ui->progressBar->setValue(count);
    if (count)
        setWindowTitle(QString(tr("SilentBackup in %1 seconds")).arg(count));
    else
        setWindowTitle(tr("SilentBackup Cancelled"));

    //if (cec->hasKeyPressed())
    //    _counter.stopCountdown();
}

void SilentBackupDlg::countdownExpired()
{
    QTimer::singleShot(1, this, SLOT(accept()));
}


