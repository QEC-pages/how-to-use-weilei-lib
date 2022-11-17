#Use this script to try the command multiple times

for i in {1..10}
do
    echo hello $i
    make srun
done

echo finish
