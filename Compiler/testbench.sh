#!/bin/bash

# Input arguments
if [[ "$1" -eq "" ]]; then
    COMPILER="build/src/COMPILER"
    echo "Using default ${COMPILER}"
elif [[ -f "$1" ]]; then
    COMPILER = ${1}
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
    echo "########################################################################"
    echo "Testing ${FOLDER##*/}"

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
        echo && echo "Compiling & running reference C code."
        C_TARGET=$BIN_DIR/$NAME
        gcc $C_FILE $DRIVER -o $C_TARGET
        ./$C_TARGET
        REF_RETURN=$?
        
        # Compile C to MIPS using our compiler
        echo && echo "Compiling C to MIPS."
        $COMPILER -S $C_FILE -o $MIPS

        # Compile MIPS to BIN 
        echo && echo "Compiling MIPS to BIN."
        mips-linux-gnu-gcc -mfp32 -o $BIN -c $MIPS

        #Linking the file
        echo && echo "Linking the file."
        mips-linux-gnu-gcc -mfp32 -static -o $C_FILE $BIN $DRIVER

        # Running the file
        if [[ -f ${MIPS} ]] ; then
            echo "Running the file."
            qemu-mips $C_FILE
            MIPS_RETURN=$?
        else 
            MIPS_RETURN=-1
            echo "Could not run the MIPS!"
        fi

        if [[ ${REF_RETURN} -ne ${MIPS_RETURN} ]] ; then
            echo "	${NAME}, Expected ${REF_RETURN}, got ${MIPS_RETURN}"
            echo "								FAIL"
            FAILED+=($NAME)
            #cat ${i}
            #cat ${py_file}
        else
            echo "${REF_RETURN} == ${MIPS_RETURN}"
            echo "								pass"
            ((PASSED++))
        fi
        echo

    done
    echo
done

echo "#############################################################"
echo "Failed Tests:"
for i in ${FAILED[@]} ; do
    echo ${i};
done
echo
echo "Passed ${PASSED} out of ${TOTAL}"