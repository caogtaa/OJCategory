from datetime import datetime
from datetime import date
from datetime import timedelta

day = datetime(1900, 1, 7)  # Sunday

sday = datetime(1901, 1, 1)
eday = datetime(2000, 12, 31)

count = 0
delta = timedelta(days=7)
while day <= eday:
    if day >= sday and day.day == 1:
        count += 1

    day += delta

print(count)

# Brute Force