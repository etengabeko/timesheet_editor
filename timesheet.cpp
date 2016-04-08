#include "timesheet.h"

#include <QRegExp>
#include <QDateTime>
#include <QStringList>

namespace timesheet {

Timesheet Timesheet::fromString(const QString& timesheet)
{
  QStringList fields = timesheet.split(QRegExp("[\\s]+"), QString::SkipEmptyParts);
  Timesheet ts;
  if ( fields.size() == 5 ) {
    ts.setMinute(fields[0]);
    ts.setHour(fields[1]);
    ts.setDay(fields[2]);
    ts.setMonth(fields[3]);
    ts.setDayOfWeek(fields[4]);
  }
  return ts;
}

bool Timesheet::setMinute(const QString& minute)
{
  minute_ = processField(minute.trimmed(), 0, 59);
  return !minute_.isEmpty();
}

bool Timesheet::setHour(const QString& hour)
{
  hour_ = processField(hour.trimmed(), 0, 23);
  return !hour_.isEmpty();
}

bool Timesheet::setDay(const QString& day)
{
  day_ = processField(day.trimmed(), 1, 31);
  return !day_.isEmpty();
}

bool Timesheet::setMonth(const QString& month)
{
  month_ = processField(month.trimmed(), 1, 12);
  return !month_.isEmpty();
}

bool Timesheet::setDayOfWeek(const QString& dayOfWeek)
{
  dayOfWeek_ = processField(dayOfWeek.trimmed(), 1, 7);
  return !dayOfWeek_.isEmpty();
}

const QString& Timesheet::minute() const
{
  return minute_;
}

const QString& Timesheet::hour() const
{
  return hour_;
}

const QString& Timesheet::day() const
{
  return day_;
}

const QString& Timesheet::month() const
{
  return month_;
}

const QString& Timesheet::dayOfWeek() const
{
  return dayOfWeek_;
}

bool Timesheet::isValid() const
{
  return !minute_.isEmpty() &&
         !hour_.isEmpty() &&
         !day_.isEmpty() &&
         !month_.isEmpty() &&
         !dayOfWeek_.isEmpty();
}

bool Timesheet::match(const QDateTime& dateTime) const
{
  if (isValid() == false ||
      dateTime.isValid() == false) {
    return false;
  }

  return (matchField(minute_, dateTime.time().minute()) &&
          matchField(hour_, dateTime.time().hour()) &&
          matchField(day_, dateTime.date().day()) &&
          matchField(month_,dateTime.date().month()) &&
          matchField(dayOfWeek_, dateTime.date().dayOfWeek()));
}

QString Timesheet::toString() const
{
  return isValid() ? QString("%1 %2 %3 %4 %5").arg(minute_)
                                              .arg(hour_)
                                              .arg(day_)
                                              .arg(month_)
                                              .arg(dayOfWeek_)
                   : QString::null;
}

QString Timesheet::processField(const QString& value, int min, int max) const
{
  switch (parseFormat(value)) {
    case FieldFormat::kAny:
        qt_noop();
      break;
    case FieldFormat::kValue:
        if (checkValue(value, min, max) == false) {
          return QString::null;
        }
      break;
    case FieldFormat::kRage:
        if (checkRange(value.section("-", 0, 0), value.section("-", 1, 1), min, max) == false) {
          return QString::null;
        }
      break;
    case FieldFormat::kList:
        if (checkList(value.split(","), min, max) == false) {
          return QString::null;
        }
      break;
    case FieldFormat::kDivisible:
        if (value.section("/", 1, 1).toInt() < 0) {
          return QString::null;
        }
      break;
    case FieldFormat::kInvalid:
    default:
      return QString::null;
  }
  return value;
}

Timesheet::FieldFormat Timesheet::parseFormat(const QString& value) const
{
  if (value == "*") {
    return FieldFormat::kAny;
  }
  else if (QRegExp("[\\d]+").exactMatch(value) == true) {
    return FieldFormat::kValue;
  }
  else if (QRegExp("[\\d]+\\-[\\d]+").exactMatch(value) == true) {
    return FieldFormat::kRage;
  }
  else if (QRegExp("([\\d]+[,]?)+").exactMatch(value) == true) {
    return FieldFormat::kList;
  }
  else if (QRegExp("\\*\\/[\\d]+").exactMatch(value) == true) {
    return FieldFormat::kDivisible;
  }
  else {
    return FieldFormat::kInvalid;
  }
}

bool Timesheet::checkValue(const QString& value, int min, int max) const
{
  bool ok = false;
  int v = value.toInt(&ok);

  return (ok == true &&
          (min <= v && v <= max));
}

bool Timesheet::checkRange(const QString& valueFrom, const QString& valueTo, int min, int max) const
{
  bool ok = false;
  int v1 = valueFrom.toInt(&ok);
  if (ok == false) {
    return false;
  }

  int v2 = valueTo.toInt(&ok);

  return (ok == true &&
          (min <= v1 && v1 <= max) &&
          (min <= v2 && v2 <= max) &&
          v1 < v2);
}

bool Timesheet::checkList(const QStringList& values, int min, int max) const
{
  for (auto it = values.constBegin(), end = values.constEnd(); it != end; ++it) {
    if (checkValue(*it, min, max) == false) {
      return false;
    }
  }
  return true;
}

bool Timesheet::matchField(const QString& fieldValue, int value) const
{
  bool result = false;
  switch (parseFormat(fieldValue)) {
    case FieldFormat::kAny:
        result = true;
      break;
    case FieldFormat::kValue:
        result = fieldValue.toInt() == value;
      break;
    case FieldFormat::kRage:
        result = (fieldValue.section("-", 0, 0).toInt() <= value &&
                  value <= fieldValue.section("-", 1, 1).toInt());
      break;
    case FieldFormat::kList:
        result = fieldValue.split(",").contains(QString::number(value));
      break;
    case FieldFormat::kDivisible:
        result = (value % fieldValue.section("/", 1, 1).toInt() == 0);
      break;
    case FieldFormat::kInvalid:
    default:
      break;
  }
  return result;
}

} // meteo
