#define BOOST_TEST_MODULE WorkingTimeTests
#include <boost/test/unit_test.hpp>
#include "blechuhr/model/workingtime.h"

BOOST_AUTO_TEST_CASE(FailTest)
{
    BOOST_CHECK_EQUAL(5, 4);
}

BOOST_AUTO_TEST_CASE(PassTest)
{
    QDateTime start(QDate(2015, 7, 5), QTime(8,0,0));
    QDateTime end(QDate(2015, 7, 5), QTime(9,0,0));
    WorkingTime wt(QString("testuser"), QString("2015,7,5"), start, end);
    BOOST_CHECK_EQUAL(wt.hours(), 1);
}
