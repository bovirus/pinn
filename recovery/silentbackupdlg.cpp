
#include "config.h"
#include <stdio.h>
#include <QDebug>

#include "silentbackupdlg.h"
//#include "ui_silentbackupdlg.h"

#define TIMEOUT 10

SilentBackupDlg::SilentBackupDlg(QWidget *parent) :
    QProgressDialog("Backing up in 10 seconds", "Cancel", 0, TIMEOUT, parent)
{
//    ui->setupUi(this);

    connect(&_counter, SIGNAL(countdownTick(int)), this, SLOT(countdown(int)));
    connect(&_counter, SIGNAL(countdownExpired()), this, SLOT(countdownExpired()) );
    //ui->list->installEventFilter(&_counter);
    setValue(0);
    //setAutoReset(false);
    _counter.startCountdown(TIMEOUT);
}

SilentBackupDlg::~SilentBackupDlg()
{
}

void SilentBackupDlg::countdown(int count)
{
    setValue(TIMEOUT-count);
    if (count)
        setWindowTitle(QString(tr("SilentBackup in %1 seconds")).arg(TIMEOUT-count));
    else
        setWindowTitle(tr("SilentBackup Cancelled"));

}

void SilentBackupDlg::countdownExpired()
{
    QTimer::singleShot(1, this, SLOT(accept()));
}


