#
#  Taken from Zed Shaw's awesome 'Learn to Code C the Hard Way': http://c.learncodethehardway.org/book
#  and modified a smidge
#

echo "\n\nRunning C Specs:"

for i in $(find ./spec/c-unit -name "*_spec" -type f -maxdepth 4) $specs/*_spec
do
  if test -f $i
  then
    if $VALGRIND ./$i 2>> spec/c-unit/spec.log
    then
      echo $i PASS
    else
      echo "ERROR in test $i: here's spec/c-unit/spec.log"
      echo "------"
      tail spec/c-unit/spec.log
      exit 1
    fi
  fi
done

echo ""
