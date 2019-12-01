#!/usr/bin/env python
# -*- coding: utf-8 -*-

import codecs
import csv
import os
import re
import glob

readme_path = './README.md'

def get_actual_file_name(name):
    name = "%s[%s]" % (name[:-1], name[-1])
    return glob.glob(name)[0]

def get_full_path(file_path_candidate):
    if not isinstance(file_path_candidate, list):
        file_path_candidate = [file_path_candidate]

    for suffix in ['.cpp', '.py', '.txt']:
        for file_path in file_path_candidate:
            if os.path.exists(file_path + suffix):
                file_path_with_suffix = file_path + suffix
                actual_file_name = get_actual_file_name(file_path_with_suffix)
                actual_file_name = os.path.basename(actual_file_name)
                return file_path_with_suffix[:-len(actual_file_name)] + actual_file_name
    return ''

def write_to_readme(oj_name, oj_config, output):
    # oj_name = oj_config['name']
    # problem_prefix = oj_config['url']

    file_path_rule = oj_config['file_path_rule']
    url_rule = oj_config['url_rule']
    
    records = dict()
    category_map = dict()
    with open('./%s/category.csv' % oj_name, 'r') as input:
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
    for category in category_map:
        output.write("#### %s\n" % category)
        # counter = 0
        for id in category_map[category]:
            # if counter > 0 and counter % 10 == 0:
            #     # 10 problems per line
            #     output.write('<br>\n')
            # counter += 1

            rec = records[id]
            file_path_candidate = file_path_rule(rec)
            file_path = get_full_path(file_path_candidate)

            if file_path:
                output.write('[%s](%s)' % ('\U0001F388', file_path))
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

    # oj end
    output.write('<br><br>\n')

def PE_file_path_rule(rec):
    id = int(rec['id'])
    folder_id = (id-1) // 100 * 100
    return './%s/%d_%d/%04d' % ('ProjectEuler', folder_id+1, folder_id+100, id)

def HR_url_rule(rec):
    contest = rec.get('contest')
    if contest:
        return 'https://www.hackerrank.com/contests/%s/challenges/%s' % (contest, rec['id'])    
    return 'https://www.hackerrank.com/challenges/%s/problem' % rec['id']

pattern = re.compile("['{}*&.?!,…:;]+")
def HR_file_path_rule(rec):
    title = rec.get('title')
    if title:
        file_name = '_'.join(pattern.sub('', title).split(' '))
    else:
        # generate file name from id
        id = rec.get('id')
        file_name = '_'.join([token.capitalize() for token in id.split('-')])

    prefix = './HackerRank'
    contest = rec.get('contest')
    if contest:
        prefix += '/' + contest
    
    return ['%s/HR_%s' % (prefix, file_name), '%s/%s' % (prefix, file_name)]

def get_oj_config(oj_name):
    ojs = {
        'ProjectEuler' : {
            'url_rule': lambda rec: 'https://projecteuler.net/problem=%d' % int(rec['id']),
            'file_path_rule': PE_file_path_rule
        },
        'HackerRank' : {
            'url_rule': HR_url_rule,
            'file_path_rule': HR_file_path_rule
        }
    }

    # icon_url = 'https://projecteuler.net/favicon.ico'
    return ojs.get(oj_name)

def main():
    oj_names = ['ProjectEuler', 'HackerRank']
    with codecs.open(readme_path, 'w', 'utf-8') as output:
        for name in oj_names:
            # write header
            headers = []
            for other_name in oj_names:
                if other_name == name:
                    headers.append('**%s**' % name)
                else:
                    headers.append('[%s](#%s)' % (other_name, other_name.lower()))
            output.write('### <a id="%s"></a> | %s |\n' % (name.lower() ,' | '.join(headers)))
            write_to_readme(name, get_oj_config(name), output)

if __name__ == '__main__':
    main()