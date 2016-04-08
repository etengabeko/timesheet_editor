#ifndef TIMESHEETEDITOR_TIMESHEET_H
#define TIMESHEETEDITOR_TIMESHEET_H

#include <QString>

class QDateTime;
class QStringList;

namespace timesheet {

class Timesheet
{
public:
  Timesheet() = default;
  static Timesheet fromString(const QString& timesheet);

  bool setMinute(const QString& minute);
  bool setHour(const QString& hour);
  bool setDay(const QString& day);
  bool setMonth(const QString& month);
  bool setDayOfWeek(const QString& dayOfWeek);

  const QString& minute() const;
  const QString& hour() const;
  const QString& day() const;
  const QString& month() const;
  const QString& dayOfWeek() const;

  bool isValid() const;

  bool match(const QDateTime& dateTime) const;

  QString toString() const;

private:
  enum class FieldFormat {
    kInvalid,
    kAny,
    kValue,
    kRage,
    kList,
    kDivisible
  };

  QString processField(const QString& value, int min, int max) const;
  FieldFormat parseFormat(const QString& value) const;

  bool checkValue(const QString& value, int min, int max) const;
  bool checkRange(const QString& valueFrom, const QString& valueTo, int min, int max) const;
  bool checkList(const QStringList& values, int min, int max) const;

  bool matchField(const QString& fieldValue, int value) const;

private:
  QString minute_;
  QString hour_;
  QString day_;
  QString month_;
  QString dayOfWeek_;

};

} // meteo

#endif // TIMESHEETEDITOR_TIMESHEET_H
