#！/bin/bash
array1=(12 34 56 "dilipa")
array2=(78 910)
echo ${array1[*]}
echo ${array1[3]}
array1[4]=1112
echo ${#array1[@]}
array=(${array1[*]} ${array2[@]})
echo ${array[*]}
echo ${#array[3]}

str="http//:baidu.com"
echo ${str:4:5}
echo ${str:0-4}
echo ${str#*/} #从前第一个符号开始
echo ${str##*/} #第二个符号开始
echo ${str%/*}          #从后开始
echo ${str%%/*}
