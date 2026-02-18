#include "json.h"
#include "renamedialog.h"
#include "util.h"
#include "ui_renamedialog.h"

#include <QDebug>

renamedialog::renamedialog(QVariantMap Map, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::renamedialog)
{
    ui->setupUi(this);
    _map = Map;

    QString description;
    QString name;
    QString alias;

    _lastWidgetFocus = NULL;
    virtualKeyBoard = new WidgetKeyboard(this);
    _nav.setContext("rename","any");
    pNav=NULL;

    if (_map.contains("name"))
    {
        QString fullname = _map.value("name").toString();
        name = getNameParts(fullname, eCORE);
        alias = getNameParts(fullname, eNICKNAME|eSPLIT);
    }
    if (_map.contains("description"))
        description = _map.value("description").toString();

    ui->nameEdit->setText(name);
    ui->aliasEdit->setText(alias);
    ui->descriptionEdit->setText(description);
}

renamedialog::~renamedialog()
{
    virtualKeyBoard->hide();
    delete virtualKeyBoard;
    delete ui;
}


void renamedialog::on_buttonBox_accepted()
{
    QString core = ui->nameEdit->text();
    QString alias = ui->aliasEdit->text();
    QString description = ui->descriptionEdit->text();

    //Set Nickname to alias
    QString name = _map.value("name").toString();
    QStringList parts = splitNameParts(name);
    setNameParts(parts, eNICKNAME, alias);
    setNameParts(parts, eDATE, "");
    name = joinNameParts(parts);

    //Update map with new name & Description
    _map["name"] = name;
    _map["description"] = description;

    //Retrieve existing list of installed_os
    QVariantList installed_os = Json::loadFromFile("/settings/installed_os.json").toList();

    //remove these keys from the map - they are not required.
    _map.remove("installed");
    _map.remove("source");
    _map.remove("partition_setup");

    int i=0;
    foreach (QVariant v, installed_os)
    {
        QVariantMap m = v.toMap();
        QString fullname = m.value("name").toString();
        QString basename = getNameParts(fullname, eCORE);

        if ( (basename == core) &&
             (getDevice(m.value("partitions").toList().at(0).toString())  == getDevice(_map["partitions"].toList().at(0).toString())) )
            installed_os.replace(i,_map);
        i++;
    }

    Json::saveToFile("/settings/installed_os.json", installed_os);
}

void renamedialog::on_cbvk_toggled(bool checked)
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

void renamedialog::my_focusChanged(QWidget * old, QWidget* nw)
{
    if (nw == ui->cbvk)
        _lastWidgetFocus = old;
}
