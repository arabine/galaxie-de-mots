
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
import collections
import locale
import datetime
from os.path import basename
import sqlite3
import csv
from unidecode import unidecode

f = open("lexique_5_letters.inc", "w")
f.write("static const Lexique lexique_5_letters[] = {\n\n")

nb_mots = 0

with open('Lexique383.tsv', newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter='\t', quotechar='|')
    for row in spamreader:
        if (len(row) >= 35):
            # on filtre les entrées :
            #   - uniquement les nom
            #   - au singulier
            #   - si l'occurence est supérieur à 1
            if (row[3] == "NOM") and (row[5] == "s"): # and (float(row[7]) > 1):
                word = unidecode(row[0], "utf-8")
                # row[14] : nombre de lettres
                # row[7]: fréquence d'apparition
                # row[0] : le mot, avec accent
                if (row[14] == "5"):
                    f.write('{ "' + word.upper() + '", ' + row[7] + " },\n")
                    nb_mots = nb_mots + 1

f.write("};\n\n")
f.close()
print("Nombre de mots: " + str(nb_mots))


