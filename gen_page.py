#!/usr/bin/env python
# -*- coding: utf-8 -*-

import codecs
import csv
import os

# icon_url = 'https://projecteuler.net/favicon.ico'
problem_prefix = 'https://projecteuler.net/problem'
oj_name = 'ProjectEuler'

def get_suffix(file_path):
    for suffix in ['.cpp', '.py', '.txt']:
        if os.path.exists(file_path + suffix):
            return suffix
    return ''

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
            folder_name = '%s_%s' % (folder_id+1, folder_id+100)
            file_path = './%s/%s/%04d' % (oj_name, folder_name, id)
            suffix = get_suffix(file_path)

            if suffix:
                output.write('[%s](%s%s)' % ('\U0001F388', file_path, suffix))
            else:
                # file not found, print question emoji
                output.write('\U00002754')

            output.write('[%04d](%s=%s)' % (id, problem_prefix, id))
            output.write('&nbsp;&nbsp;&nbsp;&nbsp;')
            
            # output.write('[%04d](./%s/%d_%d/%04d.py)&nbsp;&nbsp;&nbsp;&nbsp;' % (id, oj_name, from_id, to_id, id))
        output.write('<br>\n')
