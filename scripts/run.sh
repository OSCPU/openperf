# Example usage: [nproc=2] bash run.sh ARCH=native mainargs=train

args=$@
mytime="python3 $BENCH_HOME/scripts/monotonic_time.py"

: "${nproc:=`nproc`}" # if nproc is not set, set it to `nproc`
echo "Running using $nproc threads..."

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
  "$mytime make -C bench/{} $args run 2>&1" "|" \
     tee result/{}.log "|" \
     grep -A1 -a \'^\\\[RESULT\\\]\' "|" \
     tac "|" \
     tr '\\n' \' \' "|" \
     sed -e \'s/\\\(.*\\\)/{}: \\1\\n/\' ::: $benchlist

echo -e "\n======== $@ =======\n"
for d in $benchlist; do
  res=`grep -A1 -a '^\[RESULT\]' result/$d.log | tac | tr '\n' ' '`
  wall=`grep -a '^\[WALL\]' result/$d.log`
  score=`echo $res | grep -o '[0-9]* Marks' | awk '{print $1}' | xargs printf "%7d"`
  printf "%-15s: %-100s %s\n" $d "$res" "$wall"
  array="$array$score, "
done

mean=`python -c "import numpy as np; print(int(np.mean([$array])))"`
if [[ $mean == "0" ]] ; then
  geomean="0"
else
  geomean=`python -c "import numpy as np; print(int(np.exp(np.log([$array]).mean())))"`
fi
echo "$geomean, $mean, $array" | sed -e 's/ //g' | sed -e 's/,$//' | tee result/excel.txt
printf "GEOMEAN: %7d Marks\n" $geomean
printf "   MEAN: %7d Marks\n" $mean
printf "   vs.   %7d Marks @ AMD Ryzen(TM) 9 7950X3D\n" 1000000

cd - > /dev/null
