# copy all json files to another folder. not in use any more
date

trial=run1
folder=../data/CSS-Codes/${trial}

#ls ${folder} |wc -l
echo start generating json file list for folder ${folder}
echo this may take ~1 minute

#find ${folder} -name "*json" | cut -c 24- > filelist-${trial}.txt 
#reduce file amount to 1/10
find ${folder} -name "*-0.json" | cut -c 24- > filelist-${trial}.txt 

echo "number of files: `wc -l filelist-${trial}.txt`" 

date
echo finish


# Sample run
# run1 contains 214948 files with 71647 json files 
# takes 30 secs to generate the list
