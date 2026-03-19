args=$@
nproc=`nproc`

cd ..

source scripts/benchlist/all.sh  # set benchlist

mkdir -p result
logfile=result/compile.log
> $logfile

echo -e "\nTest with 000.hello ...\n"
make -C bench/000.hello -j $nproc $args run
if [[ "$?" != "0" ]] ; then
  echo -e "\n\nFail to run hello"
  exit
fi

/bin/time parallel --bar -j $nproc echo 'Compiling {} ...' "&&" make -C bench/{} -j $nproc $args ">>" $logfile ::: $benchlist
if [[ "$?" != "0" ]] ; then
  echo -e "\n\nFail to compile"
  exit
fi

echo -e "\nRunning ...\n"
/bin/time parallel --bar -j $nproc \
  make -C bench/{} $args run "|" \
     tee result/{}.log "|" \
     grep -A1 -a \'^\\\[RESULT\\\]\' "|" \
     tac "|" \
     tr '\\n' \' \' "|" \
     sed -e \'s/\\\(.*\\\)/{}: \\1\\n/\' ::: $benchlist

echo -e "\n======== $@ =======\n"
for d in $benchlist; do
  res=`grep -A1 -a '^\[RESULT\]' result/$d.log | tac | tr '\n' ' '`
  score=`echo $res | grep -o '[0-9]* Marks' | awk '{print $1}' | xargs printf "%7d"`
  printf "%-15s: %s\n" $d "$res"
  array="$array$score, "
done

mean=`python -c "import numpy as np; print(int(np.mean([$array])))"`
geomean=`python -c "import numpy as np; print(int(np.exp(np.log([$array]).mean())))"`
echo "$geomean, $mean, $array" > result/excel.txt
printf "GEOMEAN: %7d Marks\n" $geomean
printf "   MEAN: %7d Marks\n" $mean
printf "   vs.   %7d Marks @ AMD Ryzen(TM) 9 7950X3D\n" 1000000

cd -
