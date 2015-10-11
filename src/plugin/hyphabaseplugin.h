#ifndef HYPHABASEPLUGIN_H
#define HYPHABASEPLUGIN_H

#include <QtCore/QObject>
#include <QtCore/QtPlugin>
#include <QtWidgets/QWidget>

namespace hypha{
namespace plugin{

class HyphaBasePlugin: public QObject{
public:

    virtual ~HyphaBasePlugin(){}

    virtual QString getName(){ return "hyphabaseplugin"; }
    virtual QString getTitle() { return "Hypha Base Plugin"; }
    virtual QString getVersion() { return "1.0"; }
    virtual QString getDescription() { return "Hypha base plugin";}
    virtual HyphaBasePlugin * getInstance(QString id, QObject *parent) = 0;
    virtual void loadConfig(QString json) = 0;
    virtual QString getConfig() = 0;
    QString getId(){ return id; }
    void setId(QString id){ this->id = id; }
    QString getHost(){ return host; }
    void setHost(QString host){ this-> host = host; }

    virtual QWidget * widget() = 0;

protected:
    QString id;
    QString host;
};
}
}

#define HyphaBasePluginIID "Hypha.BasePlugin/1.0"
Q_DECLARE_INTERFACE(hypha::plugin::HyphaBasePlugin, HyphaBasePluginIID)

#endif // HYPHABASEPLUGIN_H
