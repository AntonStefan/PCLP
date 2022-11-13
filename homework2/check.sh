#!/bin/bash
EXEC=task
TESTS_NO_PROBLEMS=(1 5 10 10)
PROBLEMS_NO=4
TOTAL=0
WORKING_DIR=`pwd`
array_points=(0 0 0 0 0)
array_points_per_test=(0 40 6 3 3)
max_array_points=(0 40 30 30 30)
leak_check=0

make build

function check_test() {
    in_path=$1
	out_path=$2
	ref_path=$3
	test_no=$4
	problem_no=$5
	exec="$EXEC$problem_no"

	if [ $test_no -lt 10 ]; then
		echo -n "Test: 0$test_no ...................... "
	else
		echo -n "Test: $test_no ...................... "
	fi

	 if [ $problem_no -eq 1 ]; then
	 	timeout 30 ./$exec > $out_path
		timeout 30 valgrind --leak-check=full --error-exitcode=10 ./$exec > $out_path 2>/dev/null
	 else
		 if [ $test_no -eq 4 ]; then
		 	timeout 30 valgrind --leak-check=full --error-exitcode=10 ./$exec < $in_path > $out_path 2>/dev/null
		 else
			timeout 30 ./$exec < $in_path > $out_path
		 fi
	 fi
	
	if [ $? -eq 10 ]; then
		leak_check=1
	fi

	if [ $? -eq 124 ]; then
		echo "TIMEOUT"
		return
	fi
	
	# Check the result
	diff $ref_path $out_path 2>&1 1> my_diff
	if test $? -eq 0; then
	    echo "PASS"
        array_points[$problem_no]=$(bc <<< "${array_points[$problem_no]} + ${array_points_per_test[$problem_no]}")
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

	leak_check=0
    echo "============== Problema $PROBLEM_NO ==============="
    for ((i=1;i<=$NO_TESTS;i++)); do
		if [ $i -lt 10 ]; then
			test_input="$input/test0$i.in"
			test_output="$output/test0$i.out"
			test_ref="$ref/test0$i.ref"
		else
			test_input="$input/test$i.in"
			test_output="$output/test$i.out"
	    	test_ref="$ref/test$i.ref"
		fi
        check_test $test_input $test_output $test_ref $i $PROBLEM_NO
    done

	echo -n "Memcheck ...................... "
	if [ $leak_check -eq 1 ]; then
		echo "FAIL"
	else
		echo "PASS"
	fi

	# array_points[$PROBLEM_NO]=$(echo ${array_points[$PROBLEM_NO]} | awk '{print int($1+0.5)}')
    echo "========= Punctaj P$PROBLEM_NO:  ${array_points[$PROBLEM_NO]} / ${max_array_points[$PROBLEM_NO]} =========="

	echo "" && echo
}

function run_tests() {
	for ((j=1;j<=$PROBLEMS_NO;j++)); do
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

for ((k=1;k<=$PROBLEMS_NO;k++)); do
    TOTAL=$(expr ${array_points[$k]} + $TOTAL)
done

echo "=================="
echo "| TOTAL: $TOTAL/130 |"
echo "=================="

if [ $TOTAL -eq 130 ]; then
	echo "  Punctaj maxim! Felicitari! :D"
fi
echo
