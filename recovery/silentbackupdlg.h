#ifndef SILENTBACKUPDLG_H
#define SILENTBACKUPDLG_H
#include "countdownfilter.h"

#include <QProgressDialog>

class SilentBackupDlg : public QProgressDialog
{
    Q_OBJECT

public:
    explicit SilentBackupDlg(QWidget *parent = 0);
    ~SilentBackupDlg();

protected slots:
    void countdown(int);
    void countdownExpired();

private:
    //Ui::SilentBackupDlg *ui;
    CountdownFilter _counter;

};

#endif // SILENTBACKUPDLG_H
