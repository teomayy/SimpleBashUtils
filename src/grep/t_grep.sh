#!/bin/bash

DIFF_RES=""
COUNTER_SUCCESS=0
COUNTER_FAIL=0

./s21_grep n test.txt > s21_grep.txt
grep n test.txt > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
  then
    (( COUNTER_SUCCESS++ ))
      echo "nan - OK"
  else
    echo "$TEST1" >> log.txt
      (( COUNTER_FAIL++ ))
fi
rm s21_grep.txt grep.txt

./s21_grep -e "for" test.txt > s21_grep.txt
grep -e "for" test.txt > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
  then
    (( COUNTER_SUCCESS++ ))
      echo "e - OK"
  else
    echo "$TEST1" >> log.txt
      (( COUNTER_FAIL++ ))
fi
rm s21_grep.txt grep.txt

./s21_grep -i n test.txt > s21_grep.txt
grep -i n test.txt > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
  then
    (( COUNTER_SUCCESS++ ))
      echo "i - OK"
  else
    echo "$TEST1" >> log.txt
      (( COUNTER_FAIL++ ))
fi
rm s21_grep.txt grep.txt

./s21_grep -v n test.txt > s21_grep.txt
grep -v n test.txt > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
  then
    (( COUNTER_SUCCESS++ ))
      echo "v - OK"
  else
    echo "$TEST1" >> log.txt
      (( COUNTER_FAIL++ ))
fi
rm s21_grep.txt grep.txt

./s21_grep -c n test.txt > s21_grep.txt
grep -c n test.txt > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
  then
    (( COUNTER_SUCCESS++ ))
      echo "c - OK"
  else
    echo "$TEST1" >> log.txt
      (( COUNTER_FAIL++ ))
fi
rm s21_grep.txt grep.txt

./s21_grep -l n test.txt test.txt test.txt > s21_grep.txt
grep -l n test.txt test.txt test.txt > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
  then
    (( COUNTER_SUCCESS++ ))
      echo "l - OK"
  else
    echo "$TEST1" >> log.txt
      (( COUNTER_FAIL++ ))
fi
rm s21_grep.txt grep.txt

./s21_grep -n n test.txt > s21_grep.txt
grep -n n test.txt > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
  then
    (( COUNTER_SUCCESS++ ))
      echo "n - OK"
  else
    echo "$TEST1" >> log.txt
      (( COUNTER_FAIL++ ))
fi
rm s21_grep.txt grep.txt

./s21_grep -h n test.txt s21_grep.c > s21_grep.txt
grep -h n test.txt s21_grep.c > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
  then
    (( COUNTER_SUCCESS++ ))
      echo "h - OK"
  else
    echo "$TEST1" >> log.txt
      (( COUNTER_FAIL++ ))
fi
rm s21_grep.txt grep.txt

./s21_grep -n test.txt s21_grep.c > s21_grep.txt
grep -n test.txt s21_grep.c > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
  then
    (( COUNTER_SUCCESS++ ))
      echo "f - OK"
  else
    echo "$TEST1" >> log.txt
      (( COUNTER_FAIL++ ))
fi
rm s21_grep.txt grep.txt

./s21_grep -s n tes.txt s21_gre.c > s21_grep.txt
grep -s n tes.txt s21_gre.c > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
  then
    (( COUNTER_SUCCESS++ ))
      echo "s - OK"
  else
    echo "$TEST1" >> log.txt
      (( COUNTER_FAIL++ ))
fi
rm s21_grep.txt grep.txt

./s21_grep -o n test.txt > s21_grep.txt
grep -o n test.txt > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
  then
    (( COUNTER_SUCCESS++ ))
      echo "o - OK"
  else
    echo "$TEST1" >> log.txt
      (( COUNTER_FAIL++ ))
fi
rm s21_grep.txt grep.txt


echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"