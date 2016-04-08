#include <QApplication>
#include <QDebug>

#include <../timesheet.h>
#include <../timesheeteditor.h>

using namespace timesheet;

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  TimesheetEditor ts;
  QObject::connect(&ts, SIGNAL(finished(int)), &app, SLOT(quit()), Qt::QueuedConnection);

  ts.init(Timesheet::fromString("* */5 * 3,4 5"));
  if (ts.exec() == QDialog::Accepted) {
    qDebug() << ts.timesheet().toString();
  }

  return app.exec();
}
