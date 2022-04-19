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
dem = {}


# -----------------  FONCTION QUI VERIFIE UN MOT VALIDE (les mots composés sont interdits)
invalid_chars = ["'", " ", "-"]

def is_valid(mot):
    return not any([c in mot for c in invalid_chars])

# -----------------  DEM : ouverture et stockage en mémoire du dico DEM, pour le moment uniquement la définition

demFile = open('DEM.jsonl', 'r')
demLines = demFile.readlines()

for line in demLines:
    j = json.loads(line)
    o = {}
    dem[j["M"]] = j["SENS"]


# -----------------  LEXIQUE : chargement en mémoire

with open('Lexique383.tsv', newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter='\t', quotechar='|')
    firstLine = True
    for row in spamreader:
        # On saute la première ligne du fichier TSV car elle contient le label des colonnes
        if ((len(row) >= 35) and not firstLine):
            # colonnes :
            # 7: occurence
            # 0: le mot
            # 5 : nombre (s = singulier)
            # 3 : cartégorie grammaticale (NOM, VER ADJ ...)
            # 14: nombre de lettres
            # 2 : lemme, forme canonique
            
        #    if (row[3] == "NOM") and (row[5] == "s") and (float(row[7]) > 1):
        
            if (is_valid(row[0])):
                
                lemme = row[2]
                
                if (lemme in dem):
                    obj = {} # On construit l'objet de notre dictionnaire
                    obj["lettres"] = row[14]
                    obj["frequence"] = row[7]
                    obj["lemme"] = row[2]
                    obj["categorie"] = row[3]
                    obj["sens"] = dem[lemme]
                    # On cherche si on trouve 
                    lexique[row[0]] = obj
                else:
                    print("Mot non trouvé dans DEM: " + row[0])
                    
            #else:
                #print("Invalid: " + row[0])
        else:
            firstLine = False

# -----------------  CREATION DES TABLES ET REMPLISSAGE DE LA DB
db = sqlite3.connect('lexique.db')
db.execute('''DROP TABLE IF EXISTS lexique''')
db.execute('''CREATE TABLE IF NOT EXISTS lexique (mot TEXT, frequence REAL, lettres INTEGER, sens TEXT, categorie TEXT)''')


for key in lexique:
    obj = lexique[key]
    db.execute("INSERT INTO lexique VALUES(?, ?, ?, ?, ?)", (key, obj["frequence"], obj["lettres"], obj["sens"], obj["categorie"]))
    
db.commit()


print("Nombre de mots: " + str(len(lexique)))

