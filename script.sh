#!/bin/bash
if [ $# -ne 2 ]
then
    echo "Syntaxe : $0 [lenword1] [lenword2]"
    exit
fi
make
echo "----------Generator----------"
./generator $1 $2
echo "----------Hamming----------"
./decodeurViterbi resultBinaries.txt
echo "----------Euclidien----------"
./decodeurViterbiNoDigital result.txt
echo "----------End----------"
exit