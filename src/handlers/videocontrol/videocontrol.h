#ifndef VIDEOCONTROL_H
#define VIDEOCONTROL_H

#include <QtCore/QObject>
#include "../../handler/hyphahandler.h"
#include "videocontrolwidget.h"

namespace hypha{
namespace handler{
namespace videocontrol{
class VideoControl : public HyphaHandler
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "hypha.videocontrol" FILE "videocontrol.json")
    Q_INTERFACES(hypha::handler::HyphaHandler)
public:
    explicit VideoControl();
    ~VideoControl();
    static VideoControl * instance();
    QString getName(){ return "videocontrol"; }
    QString getTitle() { return "VideoControl"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Handler for Video Control.";}
    void parse(QString message);
    void loadConfig(QString config);
    QString getConfig();
    HyphaHandler *getInstance(QString id, QObject *parent);

    QWidget *widget();

protected:
    QString mastercard;
    VideoControlWidget *vcwidget = 0;

};
}
}
}

#endif // VIDEOCONTROL_H
