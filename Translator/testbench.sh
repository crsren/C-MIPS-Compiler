#!/bin/bash

if [[ "$1" != "" ]] ; then
    compiler="$1"
else
    compiler="build/src/translator"
fi

if [[ ! -f ${compiler} ]] ; then
    >&2 echo "Error: could not find ${compiler}."
fi

input_dir="given/tests"

target_dir="results"
mkdir -p ${target_dir}

total=0
passed=0
for i in ${input_dir}/*.c ; do
	test=$(echo $i | sed -E -e "s|${input_dir}/([^.]+)[.]c|\1|g");

	((total++))
	echo "----------------------------------------------------------------------"
	echo "Test ${total}"

    # Compile reference C code
    gcc $i -o $target_dir/$test > /dev/null 2>&1

    # Run reference C code
    $target_dir/$test > /dev/null 2>&1
    ref_out=$?

    # Translate C to python
        cat $i | $compiler > /dev/null 2>&1

	#Rename output.py
	py_file="./${target_dir}/${test}.py"
	if [[ $? -eq 0 ]]; then
	mv ./output.py ${py_file}
	fi

        # Run translated python code
        python3 ${py_file}
        py_out=$?


    if [[ ${ref_out} -ne ${py_out} ]] ; then
        echo "	${test}, Expected ${ref_out}, got ${py_out}			FAIL"
	cat ${i}
	cat ${py_file}
    else
        echo "	${test}, Got ${ref_out} (${py_out})				PASS"
	((passed++))
    fi
done

echo
echo
echo "Passed ${passed} out of ${total} tests."
