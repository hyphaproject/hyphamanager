#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QtCore/QObject>
#include <QtCore/QMultiMap>
#include <QtCore/QStringList>

class Translation : public QObject {
  Q_OBJECT
 public:
  static Translation *instance();
  void loadLanguage();
  void loadTranslations(QString dir);
  void setLanguage(QString lang);
  QString locale();
  QStringList getLanguages();
  QString language();
  void loadLanguageFile();
  static QString languageName(const QString &qmFile);
 signals:

 public slots:

 protected:
  explicit Translation(QObject *parent = 0);

  static Translation *singleton;

  QMultiMap<QString, QString> languages;
  QString currentLanguage;

};

#endif // TRANSLATION_H
