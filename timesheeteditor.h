#ifndef TIMESHEETEDITOR_TIMESHEET_EDITOR_H
#define TIMESHEETEDITOR_TIMESHEET_EDITOR_H

#include <QDialog>
#include <QScopedPointer>

class QTabWidget;

namespace Ui {
  class TimesheetSetupWidget;
}

namespace timesheet {

class Timesheet;

class TimesheetEditor : public QDialog
{
  Q_OBJECT

  enum class Tab {
    EVERY = 0,
    EVERY_N,
    SELECTED
  };

public:
  explicit TimesheetEditor(QWidget* parent = 0);

  TimesheetEditor(TimesheetEditor&& rhs) = default;
  TimesheetEditor& operator= (TimesheetEditor&& rhs) = default;

  ~TimesheetEditor();

  void init(const Timesheet& ts);
  Timesheet timesheet() const;

private slots:
  void slotClearTimesheet();
  void slotTabChange(int index);

  void slotSetMinute();
  void slotSetMinute(bool);
  void slotSetMinute(int minute);
  void slotSetHour();
  void slotSetHour(int hour);
  void slotSetHour(bool);
  void slotSetDay();
  void slotSetDay(bool);
  void slotSetMonth();
  void slotSetMonth(bool);
  void slotSetDayOfWeek();
  void slotSetDayOfWeek(bool);

private:
  void setTimesheet(const Timesheet& ts);
  void updateViews(const Timesheet& ts);
  void updateTabView3(QTabWidget* target, const QString& fromString, const QString& buttonName);
  void updateTabView2(QTabWidget* target, const QString& fromString, const QString& buttonName);
  void connectSignalsToSlots();

private:
  Ui::TimesheetSetupWidget* ui_;
  QScopedPointer<Timesheet> timesheet_;

};

} // timesheet

#endif // TIMESHEETEDITOR_TIMESHEET_EDITOR_H
