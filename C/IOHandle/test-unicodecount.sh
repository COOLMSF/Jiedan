#!/bin/bash

#
# A test script for the unicodecount command.
#
# Created by gback@cs.vt.edu for CS 3214, Fall 2021
# updated Spring 2022
#

# Create small sample files
cat > sample1.in << EOF
This is sample input file 1
EOF

BASEDIR=$(dirname "$(realpath "${BASH_SOURCE[0]}")")

function check_valid() {
    testname=$1
    filename=$2
    expect=$(env LANG=en_US.UTF-8 wc -m < ${filename} | cut -d\  -f1)
    OUTPUT=$(./${PRG} < ${filename})
    if [[ $OUTPUT = ${expect} ]]
    then
        echo "Passed ${testname}"
    elif [[ ${#OUTPUT} -gt 300 ]]
    then
        echo "Failed ${testname}, excessive output was truncated."\
             "Is this your concatenate program by mistake?"
    else
        echo "Failed ${testname}, expected ${expect} but got ${OUTPUT}"
    fi
}

function check_invalid() {
    testname=$1
    filename=$2
    iconv --from=utf8 ${filename} >/dev/null 2>&1
    if [[ $? = 0 ]];
    then
        echo Test bug
        echo ${filename} is a valid UTF-8 file
        exit
    fi
    OUTPUT=$(./${PRG} < ${filename} 2>&1)
    expect="Invalid or incomplete multibyte or wide character"
    if [[ $OUTPUT = ${expect} ]]
    then
        echo "Passed ${testname}"
    elif [[ ${#OUTPUT} -gt 300 ]]
    then
        echo "Failed ${testname}, excessive output was truncated."\
             "Is this your concatenate program by mistake?"
    else
        echo "Failed ${testname}, expected ${expect} but got ${OUTPUT}"
    fi
}

#
# Invoke your program in several combinations to test its function.
#
#

function test_program() {
    PRG=$1

    #OUTPUT1=$(./${PRG} sample1.in sample2.in | sha256sum | cut -d\  -f1)
    #check "Test 1" c4b579e3ea3922765db153a6ed49058025fc3c0a59ff130fc67cb03d578c8e33 "${OUTPUT1}"

    check_valid "Test 1 simple ASCII" sample1.in

    check_valid "Test 2 file with various unicode chars" ${BASEDIR}/utf8-demo.txt

    check_valid "Test 3 file with all zeros" ${BASEDIR}/zero.txt

    OFILE=/tmp/allf.$(whoami)
    head -c 1000 < /dev/zero | tr '\0' 'f' > ${OFILE}
    check_valid "Test 4 file with just one ASCII character" ${OFILE}
    /bin/rm ${OFILE}

    OFILE=/tmp/ucs2.$(whoami)
    python3 -c 'print(u"\U0001F602"*5)' > $OFILE
    check_valid "Test 5 small file with just one Unicode character" ${OFILE}
    /bin/rm ${OFILE}

    OFILE=/tmp/surrogate.$(whoami)
    javac -d . ${BASEDIR}/SurrogateTest.java
    java SurrogateTest 10000000 > ${OFILE}
    check_valid "Test 6 file santa clauses and smiling faces" ${OFILE}
    /bin/rm ${OFILE}

    OFILE=/tmp/large.$(whoami)
    head -c 200000000 < /dev/zero | tr '\0' 'f' > ${OFILE}

    if [[ ! "$SKIP_MEMORY_LIMIT" = "yes" ]]; then
        # The JVM, and possibly other language runtimes, don't react
        # well when run under a small virtual memory limit.
        # We will not use ulimit in those cases, instead,
        # for Java, we will use a wrapper script that limits memory on the
        # JVM side, as in java -Xmx120m ....
        ulimit -d 120000
    fi
    check_valid "Test 7 large file with just one ASCII character and 120MB limit" ${OFILE}
    /bin/rm ${OFILE}

    check_invalid "Test 8 random invalid" ${BASEDIR}/random.txt
}

if [[ $1 != "" && $1 != "unicodecount.c" ]]
then
    echo "Testing your program, which is called $1"
    if test -x $1
    then
        test_program $1
    else
        echo $1 is not an executable file, did you forget to run
        echo chmod +x $1
    fi
else
    echo "Testing unicodecount.c"

    # Compile your program
    PRG=unicodecount
    gcc -O2 -Wall -Werror -o ${PRG} unicodecount.c && test_program ${PRG}
fi

# clean up
/bin/rm sample1.in
