#ifndef VIDEO_H
#define VIDEO_H
#include <QtCore/QObject>
#include "plugin/hyphaplugin.h"
#include "videowidget.h"
namespace hypha{
namespace plugin{
namespace video{
class Video : public HyphaPlugin
{
Q_OBJECT
Q_PLUGIN_METADATA(IID "hypha.video" FILE "video.json")
Q_INTERFACES(hypha::plugin::HyphaPlugin)
public:
    QString getName(){ return "video"; }
    QString getTitle() { return "Video"; }
    QString getVersion() { return "0.1"; }
    QString getDescription() { return "Plugin to capture videos from webcam.";}
    void loadConfig(QString json);
    QString getConfig();
    HyphaPlugin *getInstance(QString id, QObject *parent);
    VideoWidget * videoWidget = 0;
    QWidget *widget();

private:
    QString language;
};
}
}
}
#endif // VIDEO_H
