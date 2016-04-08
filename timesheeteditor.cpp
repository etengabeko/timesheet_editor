#include "timesheeteditor.h"
#include "timesheet.h"
#include "ui_timesheeteditor.h"

#include <QRegExp>

namespace {

timesheet::Timesheet defaultTimesheet() { return timesheet::Timesheet::fromString("* * * * *"); }

}

namespace timesheet {

TimesheetEditor::TimesheetEditor(QWidget* parent) :
  QDialog(parent),
  ui_(new Ui::TimesheetSetupWidget()),
  timesheet_(new Timesheet(::defaultTimesheet()))
{
  ui_->setupUi(this);
  connectSignalsToSlots();
}

TimesheetEditor::~TimesheetEditor()
{
  delete ui_;
  ui_ = nullptr;
}

void TimesheetEditor::init(const Timesheet& ts)
{
  setTimesheet(ts);
  updateViews(ts);
}

void TimesheetEditor::slotClearTimesheet()
{
  setTimesheet(::defaultTimesheet());

  ui_->dayofweekTabWidget->setCurrentIndex(static_cast<int>(Tab::EVERY));
  ui_->monthTabWidget->setCurrentIndex(static_cast<int>(Tab::EVERY));
  ui_->dayTabWidget->setCurrentIndex(static_cast<int>(Tab::EVERY));
  ui_->hourTabWidget->setCurrentIndex(static_cast<int>(Tab::EVERY));
  ui_->minuteTabWidget->setCurrentIndex(static_cast<int>(Tab::EVERY));
}

void TimesheetEditor::setTimesheet(const Timesheet& ts)
{
  *timesheet_ = ts;
  ui_->timesheetLineEdit->setText(timesheet_->toString());
}

Timesheet TimesheetEditor::timesheet() const
{
  return *timesheet_;
}

void TimesheetEditor::slotTabChange(int index)
{
  QTabWidget* tw = qobject_cast<QTabWidget*>(sender());
  if (tw == nullptr) {
    return;
  }

  switch (static_cast<Tab>(index)) {
    case Tab::EVERY:
        if (tw == ui_->minuteTabWidget) {
          slotSetMinute();
        }
        else if (tw == ui_->hourTabWidget) {
          slotSetHour();
        }
        else if (tw == ui_->dayTabWidget) {
          slotSetDay();
        }
        else if (tw == ui_->monthTabWidget) {
          slotSetMonth();
        }
        else if (tw == ui_->dayofweekTabWidget) {
          slotSetDayOfWeek();
        }
      break;
    case Tab::EVERY_N:
        if (tw == ui_->minuteTabWidget) {
          slotSetMinute(ui_->minuteSpinBox->value());
        }
        else if (tw == ui_->hourTabWidget) {
          slotSetHour(ui_->hourSpinBox->value());
        }
        else if (tw == ui_->dayTabWidget) {
          foreach (QToolButton* btn, tw->findChildren<QToolButton*>()) {
            btn->setChecked(false);
          }
          slotSetDay(false);
        }
        else if (tw == ui_->monthTabWidget) {
          foreach (QToolButton* btn, tw->findChildren<QToolButton*>()) {
            btn->setChecked(false);
          }
          slotSetMonth(false);
        }
        else if (tw == ui_->dayofweekTabWidget) {
          foreach (QToolButton* btn, tw->findChildren<QToolButton*>()) {
            btn->setChecked(false);
          }
          slotSetDayOfWeek(false);
        }
      break;
    case Tab::SELECTED:
        if (tw == ui_->minuteTabWidget) {
          foreach (QToolButton* btn, tw->findChildren<QToolButton*>()) {
            btn->setChecked(false);
          }
          slotSetMinute(false);
        }
        else if (tw == ui_->hourTabWidget) {
          foreach (QToolButton* btn, tw->findChildren<QToolButton*>()) {
            btn->setChecked(false);
          }
          slotSetHour(false);
        }
        else if (tw == ui_->dayTabWidget) {
          qt_noop();
        }
        else if (tw == ui_->monthTabWidget) {
          qt_noop();
        }
        else if (tw == ui_->dayofweekTabWidget) {
          qt_noop();
        }
      break;
    default:
      return;
  }
}

void TimesheetEditor::slotSetMinute(int minute)
{
  Timesheet ts = *timesheet_;
  ts.setMinute(QString("*/%1").arg(minute));
  setTimesheet(ts);
}

void TimesheetEditor::slotSetMinute()
{
  Timesheet ts = *timesheet_;
  ts.setMinute("*");
  setTimesheet(ts);
}

void TimesheetEditor::slotSetMinute(bool)
{
  QStringList minutes;
  if (ui_->minuteButton_00->isChecked() == true) {
    minutes.append("0");
  }
  if (ui_->minuteButton_01->isChecked() == true) {
    minutes.append("1");
  }
  if (ui_->minuteButton_02->isChecked() == true) {
    minutes.append("2");
  }
  if (ui_->minuteButton_03->isChecked() == true) {
    minutes.append("3");
  }
  if (ui_->minuteButton_04->isChecked() == true) {
    minutes.append("4");
  }
  if (ui_->minuteButton_05->isChecked() == true) {
    minutes.append("5");
  }
  if (ui_->minuteButton_06->isChecked() == true) {
    minutes.append("6");
  }
  if (ui_->minuteButton_07->isChecked() == true) {
    minutes.append("7");
  }
  if (ui_->minuteButton_08->isChecked() == true) {
    minutes.append("8");
  }
  if (ui_->minuteButton_09->isChecked() == true) {
    minutes.append("9");
  }
  if (ui_->minuteButton_10->isChecked() == true) {
    minutes.append("10");
  }
  if (ui_->minuteButton_11->isChecked() == true) {
    minutes.append("11");
  }
  if (ui_->minuteButton_12->isChecked() == true) {
    minutes.append("12");
  }
  if (ui_->minuteButton_13->isChecked() == true) {
    minutes.append("13");
  }
  if (ui_->minuteButton_14->isChecked() == true) {
    minutes.append("14");
  }
  if (ui_->minuteButton_15->isChecked() == true) {
    minutes.append("15");
  }
  if (ui_->minuteButton_16->isChecked() == true) {
    minutes.append("16");
  }
  if (ui_->minuteButton_17->isChecked() == true) {
    minutes.append("17");
  }
  if (ui_->minuteButton_18->isChecked() == true) {
    minutes.append("18");
  }
  if (ui_->minuteButton_19->isChecked() == true) {
    minutes.append("19");
  }
  if (ui_->minuteButton_20->isChecked() == true) {
    minutes.append("20");
  }
  if (ui_->minuteButton_21->isChecked() == true) {
    minutes.append("21");
  }
  if (ui_->minuteButton_22->isChecked() == true) {
    minutes.append("22");
  }
  if (ui_->minuteButton_23->isChecked() == true) {
    minutes.append("23");
  }
  if (ui_->minuteButton_24->isChecked() == true) {
    minutes.append("24");
  }
  if (ui_->minuteButton_25->isChecked() == true) {
    minutes.append("25");
  }
  if (ui_->minuteButton_26->isChecked() == true) {
    minutes.append("26");
  }
  if (ui_->minuteButton_27->isChecked() == true) {
    minutes.append("27");
  }
  if (ui_->minuteButton_28->isChecked() == true) {
    minutes.append("28");
  }
  if (ui_->minuteButton_29->isChecked() == true) {
    minutes.append("29");
  }
  if (ui_->minuteButton_30->isChecked() == true) {
    minutes.append("30");
  }
  if (ui_->minuteButton_31->isChecked() == true) {
    minutes.append("31");
  }
  if (ui_->minuteButton_32->isChecked() == true) {
    minutes.append("32");
  }
  if (ui_->minuteButton_33->isChecked() == true) {
    minutes.append("33");
  }
  if (ui_->minuteButton_34->isChecked() == true) {
    minutes.append("34");
  }
  if (ui_->minuteButton_35->isChecked() == true) {
    minutes.append("35");
  }
  if (ui_->minuteButton_36->isChecked() == true) {
    minutes.append("36");
  }
  if (ui_->minuteButton_37->isChecked() == true) {
    minutes.append("37");
  }
  if (ui_->minuteButton_38->isChecked() == true) {
    minutes.append("38");
  }
  if (ui_->minuteButton_39->isChecked() == true) {
    minutes.append("39");
  }
  if (ui_->minuteButton_40->isChecked() == true) {
    minutes.append("40");
  }
  if (ui_->minuteButton_41->isChecked() == true) {
    minutes.append("41");
  }
  if (ui_->minuteButton_42->isChecked() == true) {
    minutes.append("42");
  }
  if (ui_->minuteButton_43->isChecked() == true) {
    minutes.append("43");
  }
  if (ui_->minuteButton_44->isChecked() == true) {
    minutes.append("44");
  }
  if (ui_->minuteButton_45->isChecked() == true) {
    minutes.append("45");
  }
  if (ui_->minuteButton_46->isChecked() == true) {
    minutes.append("46");
  }
  if (ui_->minuteButton_47->isChecked() == true) {
    minutes.append("47");
  }
  if (ui_->minuteButton_48->isChecked() == true) {
    minutes.append("48");
  }
  if (ui_->minuteButton_49->isChecked() == true) {
    minutes.append("49");
  }
  if (ui_->minuteButton_50->isChecked() == true) {
    minutes.append("50");
  }
  if (ui_->minuteButton_51->isChecked() == true) {
    minutes.append("51");
  }
  if (ui_->minuteButton_52->isChecked() == true) {
    minutes.append("52");
  }
  if (ui_->minuteButton_53->isChecked() == true) {
    minutes.append("53");
  }
  if (ui_->minuteButton_54->isChecked() == true) {
    minutes.append("54");
  }
  if (ui_->minuteButton_55->isChecked() == true) {
    minutes.append("55");
  }
  if (ui_->minuteButton_56->isChecked() == true) {
    minutes.append("56");
  }
  if (ui_->minuteButton_57->isChecked() == true) {
    minutes.append("57");
  }
  if (ui_->minuteButton_58->isChecked() == true) {
    minutes.append("58");
  }
  if (ui_->minuteButton_59->isChecked() == true) {
    minutes.append("59");
  }

  Timesheet ts = *timesheet_;
  if (minutes.isEmpty() == false) {
    ts.setMinute(minutes.join(","));
  }
  else {
    ts.setMinute("*");
  }
  setTimesheet(ts);
}

void TimesheetEditor::slotSetHour()
{
  Timesheet ts = *timesheet_;
  ts.setHour("*");
  setTimesheet(ts);
}

void TimesheetEditor::slotSetHour(int hour)
{
  Timesheet ts = *timesheet_;
  ts.setHour(QString("*/%1").arg(hour));
  setTimesheet(ts);
}

void TimesheetEditor::slotSetHour(bool)
{
  QStringList hours;
  if (ui_->hourButton_00->isChecked() == true) {
    hours.append("0");
  }
  if (ui_->hourButton_01->isChecked() == true) {
    hours.append("1");
  }
  if (ui_->hourButton_02->isChecked() == true) {
    hours.append("2");
  }
  if (ui_->hourButton_03->isChecked() == true) {
    hours.append("3");
  }
  if (ui_->hourButton_04->isChecked() == true) {
    hours.append("4");
  }
  if (ui_->hourButton_05->isChecked() == true) {
    hours.append("5");
  }
  if (ui_->hourButton_06->isChecked() == true) {
    hours.append("6");
  }
  if (ui_->hourButton_07->isChecked() == true) {
    hours.append("7");
  }
  if (ui_->hourButton_08->isChecked() == true) {
    hours.append("8");
  }
  if (ui_->hourButton_09->isChecked() == true) {
    hours.append("9");
  }
  if (ui_->hourButton_10->isChecked() == true) {
    hours.append("10");
  }
  if (ui_->hourButton_11->isChecked() == true) {
    hours.append("11");
  }
  if (ui_->hourButton_12->isChecked() == true) {
    hours.append("12");
  }
  if (ui_->hourButton_13->isChecked() == true) {
    hours.append("13");
  }
  if (ui_->hourButton_14->isChecked() == true) {
    hours.append("14");
  }
  if (ui_->hourButton_15->isChecked() == true) {
    hours.append("15");
  }
  if (ui_->hourButton_16->isChecked() == true) {
    hours.append("16");
  }
  if (ui_->hourButton_17->isChecked() == true) {
    hours.append("17");
  }
  if (ui_->hourButton_18->isChecked() == true) {
    hours.append("18");
  }
  if (ui_->hourButton_19->isChecked() == true) {
    hours.append("19");
  }
  if (ui_->hourButton_20->isChecked() == true) {
    hours.append("20");
  }
  if (ui_->hourButton_21->isChecked() == true) {
    hours.append("21");
  }
  if (ui_->hourButton_22->isChecked() == true) {
    hours.append("22");
  }
  if (ui_->hourButton_23->isChecked() == true) {
    hours.append("23");
  }

  Timesheet ts = *timesheet_;
  if (hours.isEmpty() == false) {
    ts.setHour(hours.join(","));
  }
  else {
    ts.setHour("*");
  }
  setTimesheet(ts);
}

void TimesheetEditor::slotSetDay()
{
  Timesheet ts = *timesheet_;
  ts.setDay("*");
  setTimesheet(ts);
}

void TimesheetEditor::slotSetDay(bool)
{
  QStringList days;
  if (ui_->dayButton_01->isChecked() == true) {
    days.append("1");
  }
  if (ui_->dayButton_02->isChecked() == true) {
    days.append("2");
  }
  if (ui_->dayButton_03->isChecked() == true) {
    days.append("3");
  }
  if (ui_->dayButton_04->isChecked() == true) {
    days.append("4");
  }
  if (ui_->dayButton_05->isChecked() == true) {
    days.append("5");
  }
  if (ui_->dayButton_06->isChecked() == true) {
    days.append("6");
  }
  if (ui_->dayButton_07->isChecked() == true) {
    days.append("7");
  }
  if (ui_->dayButton_08->isChecked() == true) {
    days.append("8");
  }
  if (ui_->dayButton_09->isChecked() == true) {
    days.append("9");
  }
  if (ui_->dayButton_10->isChecked() == true) {
    days.append("10");
  }
  if (ui_->dayButton_11->isChecked() == true) {
    days.append("11");
  }
  if (ui_->dayButton_12->isChecked() == true) {
    days.append("12");
  }
  if (ui_->dayButton_13->isChecked() == true) {
    days.append("13");
  }
  if (ui_->dayButton_14->isChecked() == true) {
    days.append("14");
  }
  if (ui_->dayButton_15->isChecked() == true) {
    days.append("15");
  }
  if (ui_->dayButton_16->isChecked() == true) {
    days.append("16");
  }
  if (ui_->dayButton_17->isChecked() == true) {
    days.append("17");
  }
  if (ui_->dayButton_18->isChecked() == true) {
    days.append("18");
  }
  if (ui_->dayButton_19->isChecked() == true) {
    days.append("19");
  }
  if (ui_->dayButton_20->isChecked() == true) {
    days.append("20");
  }
  if (ui_->dayButton_21->isChecked() == true) {
    days.append("21");
  }
  if (ui_->dayButton_22->isChecked() == true) {
    days.append("22");
  }
  if (ui_->dayButton_23->isChecked() == true) {
    days.append("23");
  }
  if (ui_->dayButton_24->isChecked() == true) {
    days.append("24");
  }
  if (ui_->dayButton_25->isChecked() == true) {
    days.append("25");
  }
  if (ui_->dayButton_26->isChecked() == true) {
    days.append("26");
  }
  if (ui_->dayButton_27->isChecked() == true) {
    days.append("27");
  }
  if (ui_->dayButton_28->isChecked() == true) {
    days.append("28");
  }
  if (ui_->dayButton_29->isChecked() == true) {
    days.append("29");
  }
  if (ui_->dayButton_30->isChecked() == true) {
    days.append("30");
  }
  if (ui_->dayButton_31->isChecked() == true) {
    days.append("31");
  }

  Timesheet ts = *timesheet_;
  if (days.isEmpty() == false) {
    ts.setDay(days.join(","));
  }
  else {
    ts.setDay("*");
  }
  setTimesheet(ts);
}

void TimesheetEditor::slotSetMonth()
{
  Timesheet ts = *timesheet_;
  ts.setMonth("*");
  setTimesheet(ts);
}

void TimesheetEditor::slotSetMonth(bool)
{
  QStringList months;
  if (ui_->monthButton_01->isChecked() == true) {
    months.append("1");
  }
  if (ui_->monthButton_02->isChecked() == true) {
    months.append("2");
  }
  if (ui_->monthButton_03->isChecked() == true) {
    months.append("3");
  }
  if (ui_->monthButton_04->isChecked() == true) {
    months.append("4");
  }
  if (ui_->monthButton_05->isChecked() == true) {
    months.append("5");
  }
  if (ui_->monthButton_06->isChecked() == true) {
    months.append("6");
  }
  if (ui_->monthButton_07->isChecked() == true) {
    months.append("7");
  }
  if (ui_->monthButton_08->isChecked() == true) {
    months.append("8");
  }
  if (ui_->monthButton_09->isChecked() == true) {
    months.append("9");
  }
  if (ui_->monthButton_10->isChecked() == true) {
    months.append("10");
  }
  if (ui_->monthButton_11->isChecked() == true) {
    months.append("11");
  }
  if (ui_->monthButton_12->isChecked() == true) {
    months.append("12");
  }

  Timesheet ts = *timesheet_;
  if (months.isEmpty() == false) {
    ts.setMonth(months.join(","));
  }
  else {
    ts.setMonth("*");
  }
  setTimesheet(ts);
}

void TimesheetEditor::slotSetDayOfWeek()
{
  Timesheet ts = *timesheet_;
  ts.setDayOfWeek("*");
  setTimesheet(ts);
}

void TimesheetEditor::slotSetDayOfWeek(bool)
{
  QStringList dayOfWeeks;
  if (ui_->dayofweekButton_01->isChecked() == true) {
    dayOfWeeks.append("1");
  }
  if (ui_->dayofweekButton_02->isChecked() == true) {
    dayOfWeeks.append("2");
  }
  if (ui_->dayofweekButton_03->isChecked() == true) {
    dayOfWeeks.append("3");
  }
  if (ui_->dayofweekButton_04->isChecked() == true) {
    dayOfWeeks.append("4");
  }
  if (ui_->dayofweekButton_05->isChecked() == true) {
    dayOfWeeks.append("5");
  }
  if (ui_->dayofweekButton_06->isChecked() == true) {
    dayOfWeeks.append("6");
  }
  if (ui_->dayofweekButton_07->isChecked() == true) {
    dayOfWeeks.append("7");
  }

  Timesheet ts = *timesheet_;
  if (dayOfWeeks.isEmpty() == false) {
    ts.setDayOfWeek(dayOfWeeks.join(","));
  }
  else {
    ts.setDayOfWeek("*");
  }
  setTimesheet(ts);
}

void TimesheetEditor::updateViews(const Timesheet& ts)
{
  updateTabView3(ui_->minuteTabWidget, ts.minute(), "minuteButton");
  updateTabView3(ui_->hourTabWidget, ts.hour(), "hourButton");
  updateTabView2(ui_->dayTabWidget, ts.day(), "dayButton");
  updateTabView2(ui_->monthTabWidget, ts.month(), "monthButton");
  updateTabView2(ui_->dayofweekTabWidget, ts.dayOfWeek(), "dayofweekButton");
}

void TimesheetEditor::updateTabView2(QTabWidget* target, const QString& fromString, const QString& buttonName)
{
  Q_CHECK_PTR(target);

  QRegExp reCustom("[\\d]{1,2}(,[\\d]{1,2})*");

  if (fromString == "*") {
    target->setCurrentIndex(static_cast<int>(Tab::EVERY));
  }
  else if (reCustom.indexIn(fromString) > -1) {
    target->setCurrentIndex(static_cast<int>(Tab::EVERY_N));
    foreach (QString each, reCustom.cap().split(',')) {
      if (each.length() == 1) {
        each = "0" + each;
      }
      QToolButton* btn = target->findChild<QToolButton*>(QString("%1_%2").arg(buttonName).arg(each));
      if (btn != 0) {
        btn->setChecked(true);
      }
    }
  }
}

void TimesheetEditor::updateTabView3(QTabWidget* target, const QString& fromString, const QString& buttonName)
{
  Q_CHECK_PTR(target);

  QRegExp reEveryN("\\*\\/([\\d]{1,2})");
  QRegExp reCustom("[\\d]{1,2}(,[\\d]{1,2})*");

  if (fromString == "*") {
    target->setCurrentIndex(static_cast<int>(Tab::EVERY));
  }
  else if (reEveryN.indexIn(fromString) > -1) {
    target->setCurrentIndex(static_cast<int>(Tab::EVERY_N));
    int m = reEveryN.cap(1).toInt();
    if (m > 0) {
      QSpinBox* sp = target->findChild<QSpinBox*>();
      if (sp != nullptr) {
        sp->setValue(m);
      }
    }
  }
  else if (reCustom.indexIn(fromString) > -1) {
    target->setCurrentIndex(static_cast<int>(Tab::SELECTED));
    foreach (QString each, reCustom.cap().split(',')) {
      if (each.length() == 1) {
        each = "0" + each;
      }
      QToolButton* btn = target->findChild<QToolButton*>(QString("%1_%2").arg(buttonName).arg(each));
      if (btn != nullptr) {
        btn->setChecked(true);
      }
    }
  }
}

void TimesheetEditor::connectSignalsToSlots()
{
  connect(ui_->applyButton, SIGNAL(clicked()), SLOT(accept()));
  connect(ui_->cancelButton, SIGNAL(clicked()), SLOT(reject()));

  connect(ui_->clearButton, SIGNAL(clicked()), SLOT(slotClearTimesheet()));

  connect(ui_->minuteSlider, SIGNAL(valueChanged(int)), ui_->minuteSpinBox, SLOT(setValue(int)));
  connect(ui_->hourSlider, SIGNAL(valueChanged(int)), ui_->hourSpinBox, SLOT(setValue(int)));
  connect(ui_->minuteSpinBox, SIGNAL(valueChanged(int)), ui_->minuteSlider, SLOT(setValue(int)));
  connect(ui_->hourSpinBox, SIGNAL(valueChanged(int)), ui_->hourSlider, SLOT(setValue(int)));
  connect(ui_->minuteSpinBox, SIGNAL(valueChanged(int)), SLOT(slotSetMinute(int)));
  connect(ui_->hourSpinBox, SIGNAL(valueChanged(int)), SLOT(slotSetHour(int)));

  connect(ui_->minuteTabWidget, SIGNAL(currentChanged(int)), SLOT(slotTabChange(int)));
  connect(ui_->hourTabWidget, SIGNAL(currentChanged(int)), SLOT(slotTabChange(int)));
  connect(ui_->dayTabWidget, SIGNAL(currentChanged(int)), SLOT(slotTabChange(int)));
  connect(ui_->monthTabWidget, SIGNAL(currentChanged(int)), SLOT(slotTabChange(int)));
  connect(ui_->dayofweekTabWidget, SIGNAL(currentChanged(int)), SLOT(slotTabChange(int)));

  foreach (QToolButton* each, ui_->minuteTabWidget->findChildren<QToolButton*>()) {
    connect(each, SIGNAL(toggled(bool)), SLOT(slotSetMinute(bool)));
  }

  foreach (QToolButton* each, ui_->hourTabWidget->findChildren<QToolButton*>()) {
    connect(each, SIGNAL(toggled(bool)), SLOT(slotSetHour(bool)));
  }

  foreach (QToolButton* each, ui_->dayTabWidget->findChildren<QToolButton*>()) {
    connect(each, SIGNAL(toggled(bool)), SLOT(slotSetDay(bool)));
  }

  foreach (QToolButton* each, ui_->monthTabWidget->findChildren<QToolButton*>()) {
    connect(each, SIGNAL(toggled(bool)), SLOT(slotSetMonth(bool)));
  }

  foreach (QToolButton* each, ui_->dayofweekTabWidget->findChildren<QToolButton*>()) {
    connect(each, SIGNAL(toggled(bool)), SLOT(slotSetDayOfWeek(bool)));
  }
}

} // meteo
