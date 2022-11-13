#!/bin/bash
EXEC=problema
TESTS_NO_PROBLEMS=(20 20 25 25)
PROBLEMS_NO=4
TOTAL=0
WORKING_DIR=`pwd`
array_points=(0 0 0 0 0)
max_array_points=(0 40 40 50 50)
make

function check_test() {
    in_path=$1
	out_path=$2
	ref_path=$3
	test_no=$4
	problem_no=$5
	exec="$EXEC$problem_no"

	echo -n "Test: $test_no ...................... "

	./$exec < $in_path > $out_path
	
	# Check the result
	diff $ref_path $out_path 2>&1 1> my_diff

	if test $? -eq 0; then
	    echo "PASS"
        array_points[$problem_no]=$(expr ${array_points[$problem_no]} + 2)
	else
	    echo "FAILED"
	fi
}

function run_tests_for_problem() {
    PROBLEM_NO=$1
    NO_TESTS=${TESTS_NO_PROBLEMS[$((PROBLEM_NO-1))]}
		
    if test ! -x "$EXEC$PROBLEM_NO"; then
		echo "Executable for problem $1 is missing"
		return 1
	fi

	input="$WORKING_DIR/tests/problema$PROBLEM_NO/in"
	ref="$WORKING_DIR/tests/problema$PROBLEM_NO/ref"
	output="$WORKING_DIR/tests/problema$PROBLEM_NO/out"

    if [ ! -d "$output" ]; then
        mkdir $output
    fi

    echo "======Running tests for problem $PROBLEM_NO ======="
    for ((i=1;i<=$NO_TESTS;i++)); do
		test_input="$input/test$i.in"
		test_output="$output/test$i.out"
	    test_ref="$ref/test$i.ref"
        check_test $test_input $test_output $test_ref $i $PROBLEM_NO
    done
    echo "======You got ${array_points[$PROBLEM_NO]} out of ${max_array_points[$PROBLEM_NO]} for $PROBLEM_NO ======="

	echo ""
}

function run_tests() {
	for ((j=1;j<=4;j++)); do
		run_tests_for_problem $j
	done
}

if [ $# -eq 0 ]; then
    run_tests
else 
	if [ "$1" -gt "4" ] || [ "$1" -lt "1" ]; then
		echo "Invalid problem number"
  		exit 1
	fi

	run_tests_for_problem $1
fi

# And the result is ...

for ((k=1;k<=4;k++)); do
    TOTAL=$(expr ${array_points[$k]} + $TOTAL)
done

echo "TOTAL: $TOTAL/180"
echo ""
