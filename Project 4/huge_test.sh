echo
echo '          *** CS 61C, Spring 2019: Project 4 ***'
echo
echo 'If your tests fail, you can find the output from each test run in a file'
echo 'test/out/<N>.txt, and the expected output in test/ref/<N>.txt. Each of'
echo 'these files contains the values produced by every layer. If something'
echo 'goes wrong, check your implementation of the layer right before the bug'
echo 'manifested itself.'
echo

FINAL_OUTPUT="ALL TESTS PASSED"

if [ ! -f "benchmark" ]; then
    echo "Need to run 'make' first!"
    exit 2
fi

for i in {1..20}; do
    echo -n "RUNNING TEST $i... "
    if [ ! -d "test/out" ]; then
        mkdir test/out
    fi
    ./benchmark test $i 2>/dev/null | grep LAYER > test/out/$i.txt
    python3 test/compare_layers.py test/out/$i.txt test/ref/$i.txt

    if [ "$?" -ne 0 ]; then
        FINAL_OUTPUT='SOME TESTS FAILED -- SEE ERROR MESSAGES FOR DETAILS!'
    fi
done

for i in 100 400 600 1200 6000 24000; do
    echo -n "PARALLEL TEST $i... "
    ./benchmark partest $i 2>/dev/null | grep PAR > test/out/par$i.txt
    python3 test/compare_output.py test/out/par$i.txt test/ref/par$i.txt

    if [ "$?" -ne 0 ]; then
        FINAL_OUTPUT='SOME TESTS FAILED -- SEE ERROR MESSAGES FOR DETAILS!'
    fi
done

echo
echo "$FINAL_OUTPUT"
echo
