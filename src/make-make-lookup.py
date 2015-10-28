infile = open("lookup.hpp", "r")
outfile = open("make-lookup.py", "w")

old = infile.readline()
count = 0
outfile.write("f = open('lookup.hpp', 'w')\n")

for line in infile:
    count += 1
    if old != line:
        old = old.rstrip('\n')
        outfile.write("for i in range({}):\n".format(count))
        outfile.write("    f.write(\"" + old + "\\n\")\n")
        count = 0
    old = line
    
outfile.write("\nf.write(\"};\")\nf.close()")
outfile.close()
infile.close()
