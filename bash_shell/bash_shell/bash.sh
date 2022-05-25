#! /bin/bash
function fun()
{
read key
   if($key >12)
      then
          {
                echo "process id:$$"
                echo name:$0
                echo 'test.sh word:'$(wc -w $(ls |grep te*))
                echo "first parameter:$1"
                echo "second parameter:$2"
                echo $*
                echo $#      //参数个数
                echo $@
                echo $(expr substr "ksudgfs;lhdsg" 2 9)
                return 1
          }  
        else
           return 0
   fi   
}
echo `date +%s`
fun dilipa  260301
echo "$?"
echo $(date +%s)
