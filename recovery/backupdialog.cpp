#include "json.h"
#include "backupdialog.h"
#include "util.h"
#include "ui_backupdialog.h"

//#include <QDebug>
#define LOCAL_DBG_ON   1
#define LOCAL_DBG_FUNC 1
#define LOCAL_DBG_OUT  1
#define LOCAL_DBG_MSG  1

#include "mydebug.h"

backupdialog::backupdialog(QVariantMap &Map, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::backupdialog), _map(Map)
{
    TRACE
    ui->setupUi(this);

    QString description;
    QString name;
    QString datetime;

    _lastWidgetFocus = NULL;
    virtualKeyBoard = new WidgetKeyboard(this);
    _nav.setContext("backup","any");
    pNav=NULL;


    QString fullname;
    if (_map.contains("backupName"))
        fullname = _map.value("backupName").toString();
    else if (_map.contains("name"))
        fullname = _map.value("name").toString();

    name = getNameParts(fullname, eCORE);
    datetime = getNameParts(fullname, eDATE|eSPLIT);

    if (_map.contains("description"))
        description = _map.value("description").toString();

    ui->nameEdit->setText(name);
    ui->datetimeEdit->setText(datetime);
    ui->descriptionEdit->setText(description);
}

backupdialog::~backupdialog()
{
    virtualKeyBoard->hide();
    delete virtualKeyBoard;
    delete ui;
}


void backupdialog::on_buttonBox_accepted()
{
    QString core = ui->nameEdit->text();
    QString datetime = ui->datetimeEdit->text();
    QString description = ui->descriptionEdit->text();

    datetime.remove(QChar('#'));
    datetime.remove(QChar('='));
    datetime.remove(QChar('@'));

    //Set backupName to datetime
    QString name = _map.value("backupName").toString();
    QStringList parts = splitNameParts(name);
    setNameParts(parts, eDATE, datetime);
    name = joinNameParts(parts);

    //Update map with new name & Description
    _map["backupName"] = name; //@@ was .replace(" ","_")
    _map["description"] = description;
}

void backupdialog::on_cbvk_toggled(bool checked)
{

    if (checked)
    {

        if (_lastWidgetFocus)
            _lastWidgetFocus->setFocus();

        virtualKeyBoard->show();
        if (pNav)
            delete pNav;
        pNav = new navigate("VKeyboard", "any", virtualKeyBoard);
    }
    else
    {
        virtualKeyBoard->hide();
        if (pNav)
        {
            delete pNav;
            pNav=NULL;
        }
    }
}

void backupdialog::my_focusChanged(QWidget * old, QWidget* nw)
{
    if (nw == ui->cbvk)
        _lastWidgetFocus = old;
}
