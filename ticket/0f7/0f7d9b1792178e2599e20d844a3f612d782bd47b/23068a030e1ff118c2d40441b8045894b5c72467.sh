#!/bin/bash


root=`pwd`
processed=0

function SubstituteOk1
{
    for d in $(/bin/ls $1)
    do
        file=$1/$d

        if [[ -d $file ]]; then
            echo "Recursing in $file..."
            SubstituteOk1 $file
        elif [[ -f $file ]]; then

            grep "bool Ok" $file >/dev/null
            if [[ $? = '0' ]]; then

                echo Processing $file...
                cat $file | sed 's/^\(.*\)bool Ok/\1bool Ok() const { return IsOk(); }\n\1bool IsOk/' >$file.tmp
                mv $file.tmp $file

                (( processed++ ))
            fi
        fi
    done
}


function SubstituteOk2
{
    for d in $(/bin/ls $1)
    do
        file=$1/$d

        if [[ -d $file ]]; then
            echo "Recursing in $file..."
            SubstituteOk2 $file
        elif [[ -f $file ]]; then

            grep "::Ok" $file >/dev/null
            if [[ $? = '0' ]]; then

                echo "Processing $file..."
                cat $file | sed 's/::Ok/::IsOk/g' > $file.tmp
                mv $file.tmp $file

                (( processed++ ))
            fi
        fi
    done
}



function SubstituteOk3
{
    for d in $(/bin/ls $1)
    do
        file=$1/$d

        if [[ -d $file ]]; then
            echo "Recursing in $file..."
            SubstituteOk3 $file
        elif [[ -f $file ]]; then

            grep "::Ok" $file >/dev/null
            if [[ $? = '0' ]]; then

                echo "Processing $file..."
                cat $file | sed 's/::Ok}\\label{\(.*\)ok}/::IsOk}\\label{\1isok}/g' > $file.tmp
                cat $file.tmp | sed 's/bool Ok/bool IsOk/g' > $file

                cat $file | sed 's/constfunc{bool}{Ok}/constfunc{bool}{IsOk}/g' > $file.tmp
                mv $file.tmp $file

                (( processed++ ))
            fi

            grep "helpref{\(.*\)[^s]Ok}{\(.*\)ok}" $file >/dev/null
            if [[ $? = '0' ]]; then

                echo "Processing $file..."
                cat $file | sed "s/helpref{\(.*\)[^s]Ok}{\(.*\)ok}/helpref{\1IsOk}{\2isok}/g" >$file.tmp
                mv $file.tmp $file

                (( processed++ ))
            fi
        fi
    done
}


SubstituteOk1 include/wx
SubstituteOk2 src
SubstituteOk3 docs/latex/wx

echo
echo Processed $processed files!
echo
 	  	 
