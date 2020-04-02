#!/bin/bash

if [[ "$1" != "" ]] ; then
    compiler="$1"
else
    compiler="build/src/compiler"
fi

have_compiler=0
if [[ ! -f $compiler ]] ; then
    >&2 echo "Warning : cannot find compiler at path ${compiler}. Only checking C reference against python reference."
    have_compiler=1
fi

cd build/src
make
cd ../../

input_dir="target/given"

working="tmp/default"
mkdir -p ${working}
TOTAL=0
PASSED=0
FailedTests=()
for i in $(find $input_dir -type f -name "*_driver.c") ; do
    base=$(echo $i | sed -E -e "s|${input_dir}/([^.]+)[.]c|\1|g");
    echo
    echo -e " \e[33mTesting $base  **************************************************************************\e[0m"
    echo
    NON_DRIVER=${i:0:${#i}-9}
    ASSEMBLY="$NON_DRIVER.s"
    OBJECT="$NON_DRIVER.o"

    #reference c program
    gcc "$NON_DRIVER.c" $i -o $NON_DRIVER
    ./$NON_DRIVER
    REF_CODE=$?
    rm $NON_DRIVER

    # Compile our compuler
    $compiler -S "$NON_DRIVER.c" -o $ASSEMBLY
    echo
    echo -e "[*] Compiling the file  "
    echo "*********************************************"

    mips-linux-gnu-gcc -mfp32 -o $OBJECT -c $ASSEMBLY
    echo "[*] Object creation"
    echo "*********************************************"

    mips-linux-gnu-gcc -mfp32 -static -o $NON_DRIVER $OBJECT $i
    echo "[*] Linking the file"
    echo "*********************************************"

    qemu-mips $NON_DRIVER
    OUR_MIPS=$?
    echo "[*] Simulating"
    echo "*********************************************"

    let "TOTAL++"
    if [[ ${have_compiler} -ne 0 ]] ; then
        echo "$base, Fail, No C compiler/translator"
    elif [[ $REF_CODE -ne $OUR_MIPS ]] ; then
        echo -e "$base, \e[91mFail\e[0m, Expected ${REF_CODE}, got ${OUR_MIPS}"
        FailedTests+=($base)
    else
        echo -e "$base, \e[92mPass\e[0m"
        let "PASSED++"
    fi
    rm $NON_DRIVER
    rm $OBJECT

    echo
done
echo -e "\e[37mPassed $PASSED out of $TOTAL\e[0m"
echo
echo "The folowing tests have failed: "
for item in "${FailedTests[@]}"; do
    echo "$item"
done
echo
