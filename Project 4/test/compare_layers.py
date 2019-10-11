import math
import sys

NUM_LAYERS = 12

if len(sys.argv) < 3:
    print("Usage: python compare_layers.py <file> <reference>")
    sys.exit(2)

with open(sys.argv[1], "r") as fin:
    layer_data = fin.readlines()

with open(sys.argv[2], "r") as fref:
    ref_layer_data = fref.readlines()

for i in range(NUM_LAYERS):
    invals = layer_data[i].split(",")
    if invals[0] != "LAYER{}".format(i):
        print("ERROR: Invalid input data for layer {}".format(i))
        sys.exit(2)

    refvals = ref_layer_data[i].split(",")
    if refvals[0] != "LAYER{}".format(i):
        print("ERROR: Invalid reference data for layer {}".format(i))
        sys.exit(2)

    if len(refvals) != len(invals):
        print("ERROR: Dimensionality error in layer {} (expected: {}, was: {})"
            .format(i, len(refvals), len(invals)))
        sys.exit(2)

    for j in range(1, len(invals)):
        if not(math.isclose(float(invals[j]), float(refvals[j]), abs_tol=1e-10)):
            print("ERROR: Value {} at layer {} is wrong: {} (should be {})"
                .format(j, i, float(invals[j]), float(refvals[j])))
            sys.exit(1)

print("Passed")
