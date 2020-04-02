#!/bin/bash

if [[ "$1" -eq "" ]]; then
    C_FILE="tmpTEST.c"
    C_DRIVER="tmpTEST_driver.c"
else
    C_FILE="$1"
    C_DRIVER="${C_FILE%%.}_driver.c"
fi

COMPILER="build/src/compiler"

echo && echo "Compiling & running reference C code."
gcc ${C_FILE} $C_DRIVER -o c_out
./c_out
REF_RETURN=$?
rm c_out

# Compile C to MIPS using our compiler
echo && echo "Compiling C to MIPS. (out.s)"
$COMPILER -S $C_FILE -o out.s #> /dev/null 2>&

# Compile MIPS to BIN
echo && echo "Compiling MIPS to BIN."
mips-linux-gnu-gcc -mfp32 -o mips_out -c out.s

# Linking the file
echo && echo "Linking the file."
mips-linux-gnu-gcc -mfp32 -static -o res_out mips_out $C_DRIVER
# Running the file
if [[ -f ${MIPS} ]] ; then
    echo "Running the file."
    qemu-mips $BIN_DIR/${NAME}
    MIPS_RETURN=$?
else 
    MIPS_RETURN=-1
    echo "Could not run the MIPS!"
fi

if [[ ${REF_RETURN} -ne ${MIPS_RETURN} ]] ; then
    echo "	${NAME}, Expected ${REF_RETURN}, got ${MIPS_RETURN}"
    echo "								FAIL"
    echo && echo "Produced MIPS:"
    cat out.s
else
    echo "${REF_RETURN} == ${MIPS_RETURN}"
    echo "								pass"
fi

rm mips_out res_out