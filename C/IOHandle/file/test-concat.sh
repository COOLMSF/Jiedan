#!/bin/bash

#
# A test script for the concatenate command.
#
# Created by gback@cs.vt.edu for CS 3214, Summer 2020.
# updated Fall 2021 + Spring 2022
#

# Create 3 small sample files
cat > sample1.in << EOF
This is sample input file 1
EOF

cat > sample2.in << EOF
This is sample input file 2
EOF

cat > "sample 3.in" << EOF
This is sample input file 3
EOF

function check() {
    testname=$1
    expect=$2
    OUTPUT=$3
    STDERR=$(cat $4 | xargs echo)
    expectedSTDERR=$5
    if [[ $OUTPUT = ${expect} ]]
    then
        if [[ $STDERR = ${expectedSTDERR} ]]
        then
            echo "Passed ${testname}"
        else
            echo "Failed ${testname}"
            echo Received output ${STDERR}
            echo Expected output ${expectedSTDERR}
        fi
    else
        echo "Failed ${testname}, ${OUTPUT}"
    fi
}

#
# Invoke your program in several combinations to test its function.
# These tests try to anticipate various mistakes and shortcuts I've seen
# students take in the past.
# A SHA 256 hash of the expected output is used for each test.
#

function test_program() {
    PRG=$1
    ETEMP=$(mktemp)
    trap '/bin/rm -f "$ETEMP"' EXIT

    OUTPUT1=$(./${PRG} sample1.in sample2.in 2>${ETEMP} | sha256sum | cut -d\  -f1)
    check "Test 1" c4b579e3ea3922765db153a6ed49058025fc3c0a59ff130fc67cb03d578c8e33 "${OUTPUT1}" \
        ${ETEMP} "$(echo {sample1.in,sample2.in}' is a regular file')"

    OUTPUT2=$(./${PRG} sample2.in sample1.in 2>${ETEMP} | sha256sum | cut -d\  -f1)
    check "Test 2" 47271334789e3ada63fc48325ad428cfd449a7f948a63eb965cdc45d6d4d775a "${OUTPUT2}" \
        ${ETEMP} "$(echo {sample2.in,sample1.in}' is a regular file')"

    OUTPUT3=$(./${PRG} sample1.in sample2.in sample2.in sample1.in 2>${ETEMP} | sha256sum | cut -d\  -f1)
    check "Test 3" d9b86e31f2a51b191bb625c2f0deb35fbe2a921fae27ec4da4989761c72918c2 "${OUTPUT3}" \
        ${ETEMP} "$(echo {sample1.in,sample2.in,sample2.in,sample1.in}' is a regular file')"

    OUTPUT4=$(echo 'ABC' | ./${PRG} 2>${ETEMP} | sha256sum | cut -d\  -f1)
    check "Test 4" 8470d56547eea6236d7c81a644ce74670ca0bbda998e13c629ef6bb3f0d60b69 "${OUTPUT4}" \
        ${ETEMP} "$(echo standard input is a pipe)"

    OUTPUT5=$(echo -n 'ABC' | ./${PRG} 2>${ETEMP} | sha256sum | cut -d\  -f1)
    check "Test 5" b5d4045c3f466fa91fe2cc6abe79232a1a57cdf104f7a26e716e0a1e2789df78 "${OUTPUT5}" \
        ${ETEMP} "$(echo standard input is a pipe)"

    OUTPUT6=$(echo -n 'ABC' | ./${PRG} - 2>${ETEMP} | sha256sum | cut -d\  -f1)
    check "Test 6" b5d4045c3f466fa91fe2cc6abe79232a1a57cdf104f7a26e716e0a1e2789df78 "${OUTPUT6}" \
        ${ETEMP} "$(echo standard input is a pipe)"

    OUTPUT7=$(echo -n 'ABC' | ./${PRG} sample1.in - sample2.in 2>${ETEMP} | sha256sum | cut -d\  -f1)
    check "Test 7" fe86444009a4114a7278f4fbcfff9a7ed17844f6050c2db9e691316b902a6f39 "${OUTPUT7}" \
        ${ETEMP} "$(echo sample1.in is a regular file \
                         standard input is a pipe \
                         sample2.in is a regular file)"

    OUTPUT8=$(dd if=/dev/zero of=/dev/stdout bs=1024 count=10000 2>/dev/null | ./${PRG} sample1.in - sample2.in 2>${ETEMP} | sha256sum | cut -d\  -f1)
    check "Test 8" 292ed644f2902d0367fbc0a18a0659b12e6f177dc0a4d176069db012a943d222 "${OUTPUT8}" \
        ${ETEMP} "$(echo sample1.in is a regular file \
                         standard input is a pipe \
                         sample2.in is a regular file)"

    OFILE=/tmp/abc.$(whoami).$$
    # total size of file is about 150MB, but we limit the programs virtual memory to about 120MB
    # if the program doesn't buffer correctly, this will fail.
    # the large limit is to accommodate memory hogs like the JVM
    dd if=/dev/urandom of=${OFILE} bs=1024 count=150000 2>/dev/null
    if [[ ! "$SKIP_MEMORY_LIMIT" = "yes" ]]; then
        # The JVM, and possibly other language runtimes, don't react
        # well when run under a small virtual memory limit.
        # We will not use ulimit in those cases, instead, 
        # for Java, we will use a wrapper script that limits memory on the
        # JVM side, as in java -Xmx120m ....
        ulimit -d 120000
    fi
    EXPECT=$(sha256sum ${OFILE} | cut -d\  -f1)
    OUTPUT9=$(<${OFILE} ./${PRG} 2>${ETEMP} | sha256sum | cut -d\  -f1)
    check "Test 9" ${EXPECT} "${OUTPUT9}" \
        ${ETEMP} "$(echo standard input is a regular file)"

    OUTPUT10=$(./${PRG} ${OFILE} 2>${ETEMP} | sha256sum | cut -d\  -f1)
    check "Test 10" ${EXPECT} "${OUTPUT10}" \
        ${ETEMP} "$(echo ${OFILE} is a regular file)"

    /bin/rm ${OFILE}

    OUTPUT11=$(./${PRG} < sample1.in sample2.in sample2.in - sample1.in 2>${ETEMP} | sha256sum | cut -d\  -f1)
    check "Test 11" d8df9ea31448fc1d4304775269a456f0b2aca7e953fa54d4c14acb9c6243a4df "${OUTPUT11}" \
        ${ETEMP} "$(echo sample2.in is a regular file \
                         sample2.in is a regular file \
                         standard input is a regular file \
                         sample1.in is a regular file)"

    OUTPUT12=$(./${PRG} < sample2.in sample2.in sample2.in - sample1.in 2>${ETEMP} | sha256sum | cut -d\  -f1)
    check "Test 12" aae993f4d8517799820c7a2edd80291e24c35d42541296f47dbcb518f5078535 "${OUTPUT12}" \
        ${ETEMP} "$(echo sample2.in is a regular file \
                         sample2.in is a regular file \
                         standard input is a regular file \
                         sample1.in is a regular file)"

    OUTPUT13=$(./${PRG} < sample\ 3.in sample2.in "sample 3.in" - sample1.in 2>${ETEMP} | sha256sum | cut -d\  -f1)
    check "Test 13" 3ef507147ba354707fe3a877920e4efa23a92baa578fa81384f3d47db2171325 "${OUTPUT13}" \
        ${ETEMP} "$(echo sample2.in is a regular file \
                         sample 3.in is a regular file \
                         standard input is a regular file \
                         sample1.in is a regular file)"

    ARGS=$(for i in $(seq 1 100); do echo sample1.in; done)
    OUTPUT14=$(./${PRG} ${ARGS} 2>${ETEMP} | sha256sum | cut -d\  -f1)
    EXPECTED=$(echo "sample1.in is a regular file"$dummy{1..100})
    check "Test 14" 2d6074cd78e89aed039ab6a110c15114e6d8d2fa2404f9808e7a13ca138df864 "${OUTPUT14}" \
        ${ETEMP} "${EXPECTED}"
}

if [[ $1 != "" && $1 != "concatenate.c" ]]
then
    echo "Testing your program, which is $1"
    test_program $1
else
    echo "Testing concatenate.c"

    # Compile your program
    PRG=concatenate
    gcc -O2 -Wall -Werror -o ${PRG} concatenate.c && test_program ${PRG}
fi

# clean up
/bin/rm sample1.in sample2.in "sample 3.in"
