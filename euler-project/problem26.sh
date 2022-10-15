#!/bin/bash
declare -a ones=("one" "two" "three" "four" "five" "six" "seven" "eight" "nine")
declare -a ten_twenty=("ten" "eleven" "twelve" "thirteen" "fourteen" "fifteen" "sixteen" "seventeen" "eighteen" "nineteen")
declare -a tens=("twenty" "thirty" "forty" "fifty" "sixty" "seventy" "eighty" "ninety")

string=""
for i in {0..1}; do
	
	for j in {0..8}; do
		for k in {0..9}; do
			if [ k != "0" ]; then
				string="${ones[${k}]}${string}"
			fi
			string="${string}"
		done
		if [ j != "0" ]; then
			string="${tens[${j}]}${string}"
		fi
	done
	
	for j in ten_twenty; do
		string="${j}${string}"
	done

	if [ i != "0" ]; then
		string="${ones[${i}]}hundredand${string}"
	fi
done
echo $string
