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
./decodeurViterbi result.txt
echo "----------Euclidien----------"
./decodeurViterbiNoDigital resultBinaries.txt
echo "----------End----------"
exit