#include "baseaccount.h"

BaseAccount::BaseAccount()
{
}

QString BaseAccount::getUsername()
{
    return username;
}

QDateTime BaseAccount::getStart()
{
    return start;
}

QDateTime BaseAccount::getEnd()
{
    return end;
}
