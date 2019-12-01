#!/usr/bin/env python
# -*- coding: utf-8 -*-

import codecs
import csv
import os

def get_suffix(file_path):
    for suffix in ['.cpp', '.py', '.txt']:
        if os.path.exists(file_path + suffix):
            return suffix
    return ''

def gen_page(oj_config):
    # oj_name = oj_config['name']
    # problem_prefix = oj_config['url']

    file_path_rule = oj_config['file_path_rule']
    url_rule = oj_config['url_rule']
    
    records = dict()
    category_map = dict()
    with open('category.csv', 'r') as input:
        reader = csv.DictReader(input, delimiter=',')
        for row in reader:
            records[row['id']] = row
            for key in row:
                if key.startswith('category'):
                    category = row[key]
                    if not category:
                        continue

                    if category not in category_map:
                        category_map[category] = [row['id']]
                    else:
                        category_map[category].append(row['id'])

    # todo: sort category
    # assign category with specific order
    with codecs.open('README.md', 'w', 'utf-8') as output:
        for category in category_map:
            output.write("### %s\n" % category)
            counter = 0
            for id in category_map[category]:
                if counter > 0 and counter % 10 == 0:
                    # 10 problems per line
                    output.write('<br>\n')
                counter += 1

                rec = records[id]
                file_path = file_path_rule(rec)
                suffix = get_suffix(file_path)

                if suffix:
                    output.write('[%s](%s%s)' % ('\U0001F388', file_path, suffix))
                else:
                    # file not found, print question emoji
                    output.write('\U00002754')
                
                try:
                    readable_id = '%04d' % int(id)
                except:
                    readable_id = id

                output.write('[%s](%s)' % (readable_id, url_rule(rec)))
                output.write('&nbsp;&nbsp;&nbsp;&nbsp;')

                # output.write('[%04d](./%s/%d_%d/%04d.py)&nbsp;&nbsp;&nbsp;&nbsp;' % (id, oj_name, from_id, to_id, id))
            output.write('<br>\n')

def PE_file_path_rule(rec):
    id = int(rec['id'])
    folder_id = (id-1) // 100 * 100
    return './%s/%d_%d/%04d' % ('ProjectEuler', folder_id+1, folder_id+100, id)

def get_oj_config(oj_name):
    ojs = {
        'ProjectEuler' : {
            'url_rule': lambda rec: 'https://projecteuler.net/problem=%d' % int(rec['id']),
            'file_path_rule': PE_file_path_rule
        }
    }

    # icon_url = 'https://projecteuler.net/favicon.ico'
    return ojs.get(oj_name)

def main():
    oj_names = ['ProjectEuler']
    for name in oj_names:
        gen_page(get_oj_config(name))

if __name__ == '__main__':
    main()