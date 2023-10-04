#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "src/Controller/Controller.h"
#include "src/FileReader/ObjectFileReader.h"
#include "src/MediaSaver/MediaSaver.h"
#include "src/ObjectViewer/ObjectViewer.h"
#include "src/Transformer/Transformer.h"
#include "src/View/glwidget.h"
#include "src/View/mainwindow.h"

#define GL_SILENCE_DEPRECATION
int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString& locale : uiLanguages) {
    const QString baseName = "opengl-test_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }

  object_viewer::Transformer transformer{};
  object_viewer::ObjectFileReader reader{};
  object_viewer::MediaSaver media_saver{};
  object_viewer::ObjectViewer object_viewer(&reader, &transformer,
                                            &media_saver);
  object_viewer::Controller object_viewer_controller(&object_viewer);
  object_viewer::MainWindow w(&object_viewer_controller);
  w.show();
  return a.exec();
}
