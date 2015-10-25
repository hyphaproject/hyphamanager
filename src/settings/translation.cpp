#include <QtCore/QDir>
#include <QtCore/QTranslator>
#include <QtCore/QCoreApplication>
#include <QtCore/QSettings>
#include <QtCore/QMutex>

#include "translation.h"


Translation *Translation::singleton = 0;

Translation::Translation(QObject *parent) :
  QObject(parent) {
}

Translation *Translation::instance() {
  static QMutex mutex;
  if (!singleton) {
    mutex.lock();
    if (!singleton)
      singleton = new Translation(0);
    singleton->loadTranslations(QCoreApplication::applicationDirPath());
    singleton->loadLanguage();
    singleton->loadLanguageFile();
    mutex.unlock();
  }
  return singleton;
}


void Translation::loadLanguage() {
  QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
  this->currentLanguage = settings.value(QString::fromUtf8("language"), "english").toString();
}

void Translation::setLanguage(QString lang) {
  QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
  settings.setValue("language", lang);
}

QStringList Translation::getLanguages() {
  return QStringList(languages.keys());
}
QString Translation::language() {
  return this->currentLanguage;
}

QString Translation::locale() {
  return tr("en");
}

void Translation::loadLanguageFile() {
  QTranslator *translator = new QTranslator();
  translator->load(languages.value(this->currentLanguage));
  QCoreApplication::installTranslator(translator);
}

void Translation::loadTranslations(QString dir) {
  QDir translationsDir(dir);
  if (translationsDir.exists(dir)) {
#ifdef Q_OS_WIN32
    if (!translationsDir.cd("i18n"))
      return;
#else
    if (!translationsDir.cd("../i18n"))
      return;
#endif
  }
  foreach (QString qmFile, translationsDir.entryList(QStringList() << "*.qm")) {
    if (!languageName(translationsDir.absoluteFilePath(qmFile)).isEmpty()) {
      languages.insert(languageName(translationsDir.absoluteFilePath(qmFile)), translationsDir.absoluteFilePath(qmFile));
    }
  }
}


QString Translation::languageName(const QString &qmFile) {
  QTranslator translator;
  translator.load(qmFile);
  QString lang = translator.translate("Language", "english");
  return lang;
}
