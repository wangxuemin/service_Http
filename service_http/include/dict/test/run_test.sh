#!/bin/bash
./rand_string 100 > tmp
for mode in 1 2 3 4 5 6 7
do  
  echo "====================running mode $mode===================="
  ./test_sign $mode 1 < tmp
done
rm -f tmprm -f tmp
echo "====================running mode 8,9===================="
./test_sign 8 1 < case.list
./test_sign 9 1 < case.list




