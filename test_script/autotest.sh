#!/bin/bash
#Remember that last line of txt file needs to end with NEWLINE also
#TODO path to testfolder variable, also create
sh="../21sh"
testdir="tests"
test_main="test_main.txt"
outdir="out"
diffdir="diff"
mkdir $outdir; mkdir $diffdir
rm -f $outdir/* $diffdir/*
while read -r file
do
	while read -r line
	do
	  echo "$line" > autotest_file.txt
 	  $sh -c $(cat autotest_file.txt) > $outdir/sh.out 2> $outdir/sh_stderror.out
	  bash -c "$(cat autotest_file.txt)" > $outdir/bash.out 2> $outdir/bash_stderror.out
	  wait $!
	  diff -q $outdir/sh.out $outdir/bash.out > $diffdir/sh_bash_diff.out
	  diff -q $outdir/sh_stderror.out $outdir/bash_stderror.out > $diffdir/stderror_diff.out
	  if [ ! -s $diffdir/sh_bash_diff.out ]  || [ ! -s $diffdir/stderror_diff.out ];
	  then
			printf "%-70s\e[32;40;1m%s\e[0m\\n" "$line" [OK]
		else
			printf "%-70s\e[31;40;1m%s\e[0m\\n" "$line" [FAIL]
			if [ -s $diffdir/sh_bash_diff.out ]
			then
				printf "\e[31;40;1m%s\e[0m\\n" "STDOUT DIFF"
				diff -y -W 200 $outdir/sh.out $outdir/bash.out
			fi
			if [ -s $diffdir/stderror_diff.out ]
			then
				printf "\e[31;40;1m%s\e[0m\\n" "STDERR DIFF"
				diff -y -W 200 $outdir/sh_stderror.out $outdir/bash_stderror.out
			fi
		fi
	done < $testdir/$file
done < $testdir/$test_main
