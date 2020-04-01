#!/bin/bash

# Input arguments
if [[ "$1" -eq "" ]]; then
    compiler="build/src/translator"
    echo "Using default ${compiler}"
elif [[ -f "$1" ]]; then
    compiler = ${1}
else
    echo "Error: Could not find the given file $1."
    exit 1
fi

# Used directories
INPUT_DIR="target/given"
MIPS_DIR="target/got"
BIN_DIR="target/bin"
mkdir -p ${MIPS_DIR} ${BIN_DIR}
chmod 755 ${INPUT_DIR} ${MIPS_DIR} ${BIN_DIR}

# Assessment helpers
TOTAL=0
PASSED=0
FAILED=()

# Testing
for FOLDER in ${INPUT_DIR}/* ; do #Each folder
    echo "Testing ${FOLDER##*/} #####################################################"

    for DRIVER in ${FOLDER}/*_driver.c ; do
        NAME=${DRIVER%%_driver.c}
        C_FILE=${NAME}.c
        MIPS=${NAME}.s
        BIN=${NAME}.o
        NAME=${NAME##*/}
        ((TOTAL++))
        echo "-----------------------------------------------------------------------"
        echo  "#${TOTAL}: ${NAME}"

        # Compile and run reference C code
        C_TARGET=$BIN_DIR/$NAME
        gcc $C_FILE $DRIVER -o $C_TARGET
        ./$C_TARGET
        REF_RETURN=$?
        echo ${REF_RETURN}
    done
    echo
done
    
    # ./$C_FILE
    # REF_RETURN=$?
    # rm $C_FILE

    # # Compile our compuler
    # $compiler -S "$C_FILE.c" -o $MIPS
    # echo
    # echo -e "[*] Compiling the file  "
    # echo "*********************************************"

    # mips-linux-gnu-gcc -mfp32 -o $BIN -c $MIPS
    # echo "[*] BIN creation"
    # echo "*********************************************"

    # mips-linux-gnu-gcc -mfp32 -static -o $C_FILE $BIN $i
    # echo "[*] Linking the file"
    # echo "*********************************************"

    # qemu-mips $C_FILE
    # OUR_MIPS=$?
    # echo "[*] Simulating"
    # echo "*********************************************"

    # let "TOTAL++"
    # if [[ ${have_compiler} -ne 0 ]] ; then
    #     echo "$NAME, Fail, No C compiler/translator"
    # elif [[ $REF_RETURN -ne $OUR_MIPS ]] ; then
    #     echo -e "$NAME, \e[91mFail\e[0m, Expected ${REF_RETURN}, got ${OUR_MIPS}"
    #     FAILED+=($NAME)
    # else
    #     echo -e "$NAME, \e[92mPass\e[0m"
    #     let "PASSED++"
    # fi
    # rm $C_FILE
    # rm $BIN

    # echo
#done
# echo -e "\e[37mPASSED $PASSED out of $TOTAL\e[0m"
# echo
# echo "The folowing tests have FAILED: "
# for item in "${FAILED[@]}"; do
#     echo "$item"
# done
# echo
