#!/bin/bash

if [[ "$1" -eq "" ]]; then
    compiler="build/src/translator"
    echo "Using default ${compiler}"
elif [[ -f "$1" ]]; then
    compiler = ${1}
else
    echo "Error: Could not find the given file $1."
    exit 1
fi

input_dir="target/c_files"
py_dir="target/py_files"
bin_dir="target/c_bin"
mkdir -p ${py_dir} ${bin_dir}

total=0
passed=0
for i in ${input_dir}/*.c ; do
	test=$(echo $i | sed -E -e "s|${input_dir}/([^.]+)[.]c|\1|g");

	((total++))
	echo "----------------------------------------------------------------------"
	echo "Test ${total}"

    # Compile reference C code
    gcc $i -o $bin_dir/$test > /dev/null 2>&1

    # Run reference C code
    $bin_dir/$test > /dev/null 2>&1
    ref_out=$?

    # Translate C to python
    cat $i | $compiler

	#Rename and move output.py
    py_file="./${py_dir}/${test}.py"
	if [[ $? -eq 0 ]]; then
	mv ./output.py ${py_file}
	fi

        # Run translated python code
	if [[ -f ${py_file} ]] ; then
	    python3 ${py_file}
        py_out=$?

        if [[ ${ref_out} -ne ${py_out} ]] ; then
        echo "	${test}, Expected ${ref_out}, got ${py_out}"
        echo "								FAIL"
        cat ${i}
        cat ${py_file}
        else
        echo "	${test}, Got ${ref_out} (${py_out})"
        echo "								pass"
        ((passed++))
        fi
	else
		py_out=-1
        echo "	${test}, Could not translate!"
        echo "								FAIL"
	fi

done


echo
echo "Passed ${passed} out of ${total} tests."
echo
