#ifndef ALARM_H
#define ALARM_H

#include <QtCore/QObject>
#include "../../handler/hyphahandler.h"
#include "alarmwidget.h"

namespace hypha{
namespace handler{
namespace alarm{
class Alarm : public HyphaHandler
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "hypha.alarm" FILE "alarm.json")
    Q_INTERFACES(hypha::handler::HyphaHandler)
public:
    explicit Alarm();
    ~Alarm();
    static Alarm * instance();
    QString getName(){ return "alarm"; }
    QString getTitle() { return "Alarm"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Handler for Alarm Control.";}
    void parse(QString message);
    void loadConfig(QString config);
    QString getConfig();
    HyphaHandler *getInstance(QString id, QObject *parent);

    QWidget *widget();

protected:
    AlarmWidget *alarmWidget = 0;

};
}
}
}

#endif // ALARM_H
