
from subprocess import run, PIPE

from string import ascii_lowercase

template = """<svg width="100" height="100">
    <rect x="0" y="0" width="100" height="100" ry="5" rx="5" stroke-width="{{BORDER_WIDTH}}px" stroke="{{BORDER_COLOR}}" fill-opacity="{{BACKGROUND_OPACITY}}" fill="{{BACKGROUND_COLOR}}"/>
    
    <g fill="{{FOREGROUND_COLOR}}">
        <text x="50%" y ="50%"  font-size="70" dominant-baseline="central" text-anchor="middle">{{LETTER}}</text>
    </g>
    
    <g x="60%" y ="90%" fill="{{FOREGROUND_COLOR}}" fill-opacity="{{POINTS_OPACITY}}">
        <text font-size="25">{{POINTS}}</text>
    </g>
</svg>"""

# Avec inkscape, utiliser le nom spécial de fichier '-' pour sortir dans STDOUT
# exemple: cat template.svg | inkscape -p -l -T -o -

#A,E,I,L,N,O,R,S,T,U : 1 point.
#D,G,M : 2 points.
#B,C,P : 3 points.
#F,H,V : 4 points.
#J,Q : 8 points.
#K,W,X,Y,Z : 10 points.
points = {}
points['a'] = 1
points['b'] = 3
points['c'] = 3
points['d'] = 2
points['e'] = 1
points['f'] = 4
points['g'] = 2
points['h'] = 4
points['i'] = 1
points['j'] = 8
points['k'] = 10
points['l'] = 1
points['m'] = 2
points['n'] = 1
points['o'] = 1
points['p'] = 3
points['q'] = 8
points['r'] = 1
points['s'] = 1
points['t'] = 1
points['u'] = 1
points['v'] = 4
points['w'] = 10
points['x'] = 10
points['y'] = 10
points['z'] = 10

for c in ascii_lowercase:
    letter = template.replace("{{LETTER}}", c.upper())
    letter = letter.replace("{{POINTS}}", str(points[c]))
    run(["inkscape", "-l", "-p", "-T", "-o",  "letter_" + c + ".svg"], stdout=PIPE, input=letter, encoding='ascii')


# POUR LA TOUCHE ENTRÉE : inkscape enter_template.svg -l -T -o enter.svg
