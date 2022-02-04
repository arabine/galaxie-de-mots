
#fmt = '%z'
#winter = datetime(2002, 1, 1, 6, 0, 0)
#print('Timezones')

#for tz in pytz.common_timezones:
#    if '/' in tz:
#        tzObj = timezone(tz)
        #loc_dt = tzObj.localize()
#        print(str(int(tzObj.utcoffset(winter).total_seconds())) + ";" + tz)
        #print(loc_dt.strftime(fmt) + " => " + tz)
import os
import sys
import json
import sys
import os
import collections
import locale
import datetime
from os.path import basename
import sqlite3
import csv

lexique = {}

db = sqlite3.connect('lexique.db')
db.execute('''DROP TABLE IF EXISTS lexique''')
db.execute('''CREATE TABLE IF NOT EXISTS lexique (mot TEXT, frequence REAL, lettres INTEGER)''')


with open('Lexique383.tsv', newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter='\t', quotechar='|')
    for row in spamreader:
        if (len(row) >= 35):
            # on filtre les entrées :
            #   - uniquement les nom
            #   - au singulier
            #   - si l'occurence est supérieur à 1
            if (row[3] == "NOM") and (row[5] == "s") and (float(row[7]) > 1):
                obj = {} # On construit l'objet de notre dictionnaire
                obj["lettres"] = row[14]
                obj["frequence"] = row[7]
                lexique[row[0]] = obj
                db.execute("INSERT INTO lexique VALUES(?, ?, ?)", (row[0], row[7], row[14]))
    db.commit()


print("Nombre de mots: " + str(len(lexique)))


