#!/bin/bash
#Remember that last line of txt file needs to end with NEWLINE also
#TODO path to testfolder variable, also create
diff_width=200
sh_dir=".."
sh_exe="21sh"
sh=$sh_dir"/"$sh_exe
testdir="tests"
test_main="test_main.txt"
#Absolute paths:
outdir="/Users/jniemine/Workspace/21sh/21sh/21mike/test_script/out"
diffdir="/Users/jniemine/Workspace/21sh/21sh/21mike/test_script/diff"
autotest_file="/Users/jniemine/Workspace/21sh/21sh/21mike/test_script/autotest_file.txt"
(mkdir $outdir; mkdir $diffdir) 2>/dev/null
rm -f $outdir/* $diffdir/*
while read -r filename
do
	if ! [[ $filename =~ ^\# ]];
	then
		while read -r line #file
		do
		#	while read -r line
		#	do
				echo "$line" > $autotest_file
				(cd $sh_dir && ./$sh_exe -c "$(cat $autotest_file)" > $outdir/sh.out 2> $outdir/sh_stderror.out.temp)
				wait $!
				(cd $sh_dir && bash -c "$(cat $autotest_file)" > $outdir/bash.out 2> $outdir/bash_stderror.out.temp)
				wait $!
				diff -q $outdir/sh.out $outdir/bash.out > $diffdir/sh_bash_diff.out
#				awk -F':' '{ $1$2="" print $0 }' $outdir/sh_stderror.out.temp #> $outdir/sh_stderror.out
#				awk 'BEGIN{FS=":"} {print $0}' $outdir/sh_stderror.out.temp > $outdir/sh_stderror.out
				awk '{FS=":" ; for (i=2; i<NF; i++) printf $i " "; print $NF}' $outdir/sh_stderror.out.temp > $outdir/sh_stderror.out
				awk '{FS=":" ; for (i=2; i<NF; i++) printf $i " "; print $NF}' $outdir/bash_stderror.out.temp > $outdir/bash_stderror.out
#				awk '{for (i=2; i<NF; i++) printf $i " "; print $NF}' filename
#				awk FS = ":" $1$2="" { print $0 }  $outdir/bash_stderror.out.temp
				diff -q $outdir/sh_stderror.out $outdir/bash_stderror.out > $diffdir/stderror_diff.out
				if [ -s $diffdir/sh_bash_diff.out ]  || [ -s $diffdir/stderror_diff.out ];
				then
					printf "%-70s\e[31;40;1m%s\e[0m\\n" "$line" [FAIL]
					if [ -s $diffdir/sh_bash_diff.out ]
					then
						printf "\e[31;40;1m%s\e[0m\\n" "STDOUT DIFF"
						diff -y -W $diff_width $outdir/sh.out $outdir/bash.out
					fi
					if [ -s $diffdir/stderror_diff.out ]
					then
						printf "\e[31;40;1m%s\e[0m\\n" "STDERR DIFF"
						diff -y -W $diff_width $outdir/sh_stderror.out $outdir/bash_stderror.out
					fi
				else
					printf "%-70s\e[32;40;1m%s\e[0m\\n" "$line" [OK]
				fi
					printf "********************************\n"
		#	done < $testdir/$file
		done < $testdir/$filename
	fi
done < $testdir/$test_main
