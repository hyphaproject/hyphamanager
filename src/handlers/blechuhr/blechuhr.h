#ifndef BLECHUHR_H
#define BLECHUHR_H

#include <QtCore/QObject>
#include "../../handler/hyphahandler.h"
#include "blechuhrwidget.h"

namespace hypha{
namespace handler{
namespace blechuhr{
class BlechUhr : public HyphaHandler
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "hypha.blechuhr" FILE "blechuhr.json")
    Q_INTERFACES(hypha::handler::HyphaHandler)
public:
    explicit BlechUhr();
    ~BlechUhr();
    static BlechUhr * instance();
    QString getName(){ return "blechuhr"; }
    QString getTitle() { return "Blechuhr"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Handler like a time recorder.";}
    void parse(QString message);

    void loadConfig(QString config);
    QString getConfig();
    HyphaHandler *getInstance(QString id, QObject *parent);

    QWidget *widget();


private:
protected:
    BlechUhrWidget *buwidget;


};
}
}
}

#endif // BLECHUHR_H
