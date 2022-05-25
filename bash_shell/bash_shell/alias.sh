#! /bin/bash
alias timenow="date +%s"
if
    read -t 20 -sp "password one(20s)>" pass1 && printf "\n" && #第一次
    read -t 20 -sp "password two(20s)>" pass2 && printf "\n" && #第二次
    [ "$pass1"a = "$pass2"b ]
  then
    echo "sucess$(timenow)"
  else
    echo "defate$(timenow)"
fi
echo `timenow`
