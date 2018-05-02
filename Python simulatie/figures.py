import matplotlib.pyplot as plt
from matplotlib.path import Path
import matplotlib.patches as patches

D1 = [(0.5, 0.5),(0.5, 0.),(0., 0.)]
D2 = [(0., 0.),(0., 0.5),(0., 1.)]
D3 = [(0., 1.),(0.5, 1.),(0.5, 0.5)]

letter_D = [D1, D2, D3]

d1 = [(0,0.25),(0,0.5),(0.2,0.5)]
d2 = [(0.2,0.5),(0.4,0.5),(0.4,0.25)]
d3 = [(0.4,0.25),(0.4,0),(0.2,0)]
d4 = [(0.2,0),(0,0),(0,0.25)]
d5 = [(0,0.25),(0,0),(0.2,0)]
d6 = [(0.2,0),(0.4,0),(0.4,0.25)]
d7 = [(0.4,0.25),(0.4,0.5),(0.4,1)]
d8 = [(0.4,1),(0.4,0.5),(0.4,0.25)]
d9 = [(0.4,0.25),(0.4,0),(0.5,0.25)]

letter_d = [d1, d2, d3, d4, d5, d6, d7, d8, d9]

w1 = [(0,0.25),(0.05,0.75),(0.2,0)]
w2 = [(0.2,0),(0.25,0),(0.25,0.2)]
w3 = [(0.25,0.2),(0.25,0),(0.3,0)]
w4 = [(0.3,0),(0.45,0.75),(0.5,0.25)]

letter_w = [w1, w2, w3, w4]

e1 = [(0,0.25),(0.1,0),(0.125,0)]
e2 = [(0.125,0),(0.15,0),(0.25,0.1)]
e3 = [(0.25,0.1),(0.05,0.375),(0.25,0.5)]
e4 = [(0.25,0.5),(0.45,0.375),(0.25,0.1)]
e5 = [(0.25,0.1),(0.35,0),(0.375,0)]
e6 = [(0.375,0),(0.4,0),(0.5,0.25)]

letter_e = [e1, e2, e3, e4, e5, e6]

letter = letter_w

fig = plt.figure()
codes = [Path.MOVETO, Path.CURVE3, Path.CURVE3]
ax = fig.add_subplot(1, 1, 1)

for bezier in letter:
    ax.add_patch(patches.PathPatch(Path(bezier, codes), facecolor='none', lw=2))
    xs, ys = zip(*bezier)
    ax.plot(xs, ys, 'x--', lw=1, color='grey', ms=10)


ax.set_xlim(-0.1, 1.1)
ax.set_ylim(-0.1, 1.1)
plt.show()