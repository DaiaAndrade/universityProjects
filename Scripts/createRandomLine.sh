#!/bin/bash
#	Primeiro argumento: numero de linhas
lines=$1
#	Segundo argumento: string a ser inserida no arquivo
stringSearched=$2
size=${#stringSearched}
for (( i = 0; i < $lines; i++ )); do
	stringsize=$((1+RANDOM%132))
	num=$((stringsize + size))
	# se o tamanho da nossa string mais o tamanho da string a ser gerada for menor que 132
	if [[ "$num" -lt 132 ]]; then
		# TALVEZ, tem 1/5 de chance de inserir nossa string
		maybe=$((RANDOM%5+1))
		if [[ "$maybe" -eq 2 ]]; then
			stringline=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w $stringsize - $size | head -n 1)$stringSearched
		else
			stringline=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w $stringsize - $size | head -n 1)
		fi
	else
		stringline=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w $stringsize - $size | head -n 1)
	fi
	echo "$stringline"
done
