#ifndef RENAMEDIALOG_H
#define RENAMEDIALOG_H

#include "WidgetKeyboard.h"
#include "input.h"

#include <QDialog>
#include <QVariantMap>

namespace Ui {
class renamedialog;
}

class renamedialog : public QDialog
{
    Q_OBJECT

public:
    explicit renamedialog(QVariantMap map, QWidget *parent = 0);
    ~renamedialog();

private slots:
    void on_buttonBox_accepted();
    void on_cbvk_toggled(bool checked);
    void my_focusChanged(QWidget * old, QWidget* nw);

private:
    Ui::renamedialog *ui;
    QVariantMap _map;
    WidgetKeyboard *virtualKeyBoard;
    QWidget * _lastWidgetFocus;
    navigate _nav;
    navigate * pNav;
};

#endif // RENAMEDIALOG_H
