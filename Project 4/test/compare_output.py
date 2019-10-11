import math
import sys

NUM_CLASSES = 10

if len(sys.argv) < 3:
    print("Usage: python compare_output.py <file> <reference>")
    sys.exit(2)

with open(sys.argv[1], "r") as fin:
    indata = fin.readlines()

with open(sys.argv[2], "r") as fref:
    refdata = fref.readlines()

for i in range(len(indata)):
    invals = indata[i].split(",")
    if invals[0] != "PAR{}".format(i):
        print("ERROR: Invalid input data for output {}".format(i))
        sys.exit(2)

    refvals = refdata[i].split(",")
    if refvals[0] != "PAR{}".format(i):
        print("ERROR: Invalid reference data for output ".format(i))
        sys.exit(2)

    for j in range(1, len(invals)):
        if not(math.isclose(float(invals[j]), float(refvals[j]), abs_tol=1e-10)):
            print("ERROR: Value {} at output {} is wrong: {} (should be {})"
                .format(j, i, float(invals[j]), float(refvals[j])))
            sys.exit(1)

print("Passed")
