#ifndef backupdialog_H
#define backupdialog_H

#include "WidgetKeyboard.h"
#include "input.h"

#include <QDialog>
#include <QVariantMap>

namespace Ui {
class backupdialog;
}

class backupdialog : public QDialog
{
    Q_OBJECT

public:
    explicit backupdialog(QVariantMap &map, QWidget *parent = 0);
    ~backupdialog();

private slots:
    void on_buttonBox_accepted();
    void on_cbvk_toggled(bool checked);
    void my_focusChanged(QWidget * old, QWidget* nw);

private:
    Ui::backupdialog *ui;
    QVariantMap &_map;
    WidgetKeyboard *virtualKeyBoard;
    QWidget * _lastWidgetFocus;
    navigate _nav;
    navigate * pNav;

};

#endif // backupdialog_H
