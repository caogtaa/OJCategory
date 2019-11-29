#!/usr/bin/env python
# -*- coding: utf-8 -*-

import codecs
import csv

icon_url = 'https://projecteuler.net/favicon.ico'
problem_prefix = 'https://projecteuler.net/problem'

category_map = dict()
with open('category.csv', 'r') as input:
    reader = csv.reader(input, delimiter=',')
    for row in reader:
        for category in row[2:]:
            if not category:
                continue

            if category not in category_map:
                category_map[category] = [row[0]]
            else:
                category_map[category].append(row[0])

# sort category
# assign category with specific order
with codecs.open('category.md', 'w', 'utf-8') as output:
    for category in category_map:
        output.write("### %s" % category)
        counter = 0
        for id in category_map[category]:
            if counter % 10 == 0:
                output.write('\n')
            counter += 1
            output.write('[%04d](%s=%s)&nbsp;&nbsp;&nbsp;&nbsp;' % (int(id), problem_prefix, id))
        output.write('\n')
