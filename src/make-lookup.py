#generates the lookup table for rcurse map generation

f = open('lookup.h', 'w')
f.write('static const char tiles[] = {\n')
for i in range(0, 3400):
    f.write('CHAR_WATER,\n')
    
for i in range(3400, 3700):
    f.write('CHAR_EMPTY,\n')
    
for i in range(3700, 4500):
    f.write('CHAR_GRASS,\n')
    
for i in range(4500, 5000):
    f.write('CHAR_TALLGRASS,\n')
    
f.write('CHAR_TREASURE,\n')

for i in range(5001, 5500):
    f.write('CHAR_TALLGRASS,\n')
    
for i in range(5500, 6000):
    f.write('CHAR_EMPTY,\n')
    
for i in range(6000, 8000):
    f.write('CHAR_WALL,\n')
    
for i in range(8000, 10000):
    f.write('CHAR_ICE,\n')
    
f.write('};')
