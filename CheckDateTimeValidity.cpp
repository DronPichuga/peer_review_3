enum class TimeValidityError {
    YEAR_TOO_SMALL,
    YEAR_TOO_BIG,
    MONTH_TOO_SMALL,
    MONTH_TOO_BIG,
    DAY_TOO_SMALL,
    DAY_TOO_BIG,
    HOUR_TOO_SMALL,
    HOUR_TOO_BIG,
    MINUTES_TOO_BIG,
    MINUTES_TOO_SMALL,
    SECONDS_TOO_BIG,
    SECONDS_TOO_SMALL,
};

string& Message(const TimeValidityError message)
{
    string ERROR_MESSAGES[] = 
    {
       "year is too small"s,
       "year is too big"s,
       "month is too small"s,
       "month is too big"s,
       "day is too small"s,
       "day is too big"s,
       "hour is too small"s,
       "hour is too big"s,
       "minute is too small"s,
       "minute is too big"s,
       "second is too small"s,
       "second is too big"s,
    };
    return ERROR_MESSAGES[(int)message];
}

void CheckYear(int year)
{
    if (year < 1) {
        throw domain_error(Message(TimeValidityError::YEAR_TOO_SMALL));
    }
    if (year > 9999) {
        throw domain_error(Message(TimeValidityError::YEAR_TOO_BIG));
    }
}

void CheckMonth(int month)
{
        if (month < 1) {
            throw domain_error(Message(TimeValidityError::MONTH_TOO_SMALL));
        }
        if (month > 12) {
            throw domain_error(Message(TimeValidityError::MONTH_TOO_BIG));
        }
}

void CheckDay(int day, const array<int, 12>& month_lengths, int month)
{
        if (day < 1) {
        throw domain_error(Message(TimeValidityError::DAY_TOO_SMALL));
    }
    if (day > month_lengths[month - 1]) {
        throw domain_error(Message(TimeValidityError::DAY_TOO_BIG));
    }
}

void CheckHour(int hour)
{
    if (hour < 0) {
    throw domain_error(Message(TimeValidityError::HOUR_TOO_SMALL));
    }
    if (hour > 23) {
        throw domain_error(Message(TimeValidityError::HOUR_TOO_BIG));
    }
}

void CheckMinute(int minute)
{
    if (minute < 0) {
    throw domain_error(Message(TimeValidityError::MINUTES_TOO_SMALL));
    }
    if (minute > 59) {
        throw domain_error(Message(TimeValidityError::MINUTES_TOO_BIG));
    }
}

void CheckSecond(int second)
{
    if (second < 0) {
    throw domain_error(Message(TimeValidityError::SECONDS_TOO_SMALL));
    }
    if (second > 59) {
        throw domain_error(Message(TimeValidityError::SECONDS_TOO_BIG));
    }
}

void CheckDateTimeValidity(const DateTime& dt) {


  const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const array month_lengths = { 31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    CheckYear(dt.year);
    CheckMonth(dt.month);
    CheckDay(dt.day, month_lengths, dt.month);
    CheckHour(dt.hour);
    CheckMinute(dt.minute);
    CheckSecond(dt.second);
}

