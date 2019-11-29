#!/usr/bin/env python
# -*- coding: utf-8 -*-

import codecs
import csv

icon_url = 'https://projecteuler.net/favicon.ico'
problem_prefix = 'https://projecteuler.net/problem'
oj_name = 'ProjectEuler'

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

# todo: sort category
# assign category with specific order
with codecs.open('README.md', 'w', 'utf-8') as output:
    for category in category_map:
        output.write("### %s\n" % category)
        counter = 0
        for v in category_map[category]:
            id = int(v)

            if counter > 0 and counter % 10 == 0:
                # 10 problems per line
                output.write('<br>\n')
            counter += 1

            folder_id = (id-1) // 100 * 100
            from_id = folder_id + 1
            to_id = folder_id + 100

            output.write('[%s](./%s/%d_%d/%04d.py)' % ('\U0001F388', oj_name, from_id, to_id, id))
            output.write('[%04d](%s=%s)' % (id, problem_prefix, id))
            output.write('&nbsp;&nbsp;&nbsp;&nbsp;')
            
            # output.write('[%04d](./%s/%d_%d/%04d.py)&nbsp;&nbsp;&nbsp;&nbsp;' % (id, oj_name, from_id, to_id, id))
        output.write('<br>\n')
