
from subprocess import run, PIPE

from string import ascii_lowercase

template = """<svg width="100" height="100">
    <rect x="0" y="0" width="100" height="100" ry="5" rx="5" stroke-width="0px" fill="{{BACKGROUND}}"/>
    
    <g fill="{{LETTER_COLOR}}">
        <text x="50%" y ="50%"  font-size="70" dominant-baseline="central" text-anchor="middle">{{LETTER}}</text>
    </g>
    
    <g fill="{{POINTS_COLOR}}">
        <text x="60%" y ="90%"  font-size="25" >10</text>
    </g>
</svg>"""

# Avec inkscape, utiliser le nom spécial de fichier '-' pour sortir dans STDOUT
# exemple: cat template.svg | inkscape -p -l -T -o -

for c in ascii_lowercase:
    letter = template.replace("{{LETTER}}", c.upper())
    run(["inkscape", "-l", "-p", "-T", "-o",  "letter_" + c + ".svg"], stdout=PIPE, input=letter, encoding='ascii')


# POUR LA TOUCHE ENTRÉE : inkscape enter_template.svg -l -T -o enter.svg

