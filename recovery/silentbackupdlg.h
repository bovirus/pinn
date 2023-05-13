#ifndef SILENTBACKUPDLG_H
#define SILENTBACKUPDLG_H
#include "countdownfilter.h"

#include <QDialog>

namespace Ui {
class SilentBackupDlg;
}

class SilentBackupDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SilentBackupDlg(QWidget *parent = 0);
    ~SilentBackupDlg();
    virtual void accept();

protected slots:
    void countdown(int);
    void countdownExpired();

private:
    Ui::SilentBackupDlg *ui;
    CountdownFilter _counter;

};

#endif // SILENTBACKUPDLG_H
