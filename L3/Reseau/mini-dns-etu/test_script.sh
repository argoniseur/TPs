#!/bin/bash

# ---------------------------------------
# TEST SCRIPT for Res3 mini-dns project
# ---------------------------------------

ko='\e[00;31m';
wipe='\e[00m';
ok='\e[01;32m';

BASE=.
TMP=./tmp
TEST=./tests
RET=

rm -rf $TMP
mkdir $TMP

function test_authoritative_server {

    printf "\n*** Testing authoritative server (.univ-tlse3.fr) ***\n"

    for i in `ls $TEST/ref/authoritative`
    do
        dig $i @127.0.0.1 -p 12700 +short > $TMP/dig_result.txt
        diff $TEST/ref/authoritative/$i $TMP/dig_result.txt  &>/dev/null
        RET=$?

        [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
        [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return
    done
}

function test_resolver {

    printf "\n*** Testing resolver ***\n"

    for i in `ls $TEST/ref/resolver`
    do
        ./dns_client -s 8.8.8.8 $i > $TMP/dig_result.txt
        # ./dns_client -s 141.115.4.41 $i > $TMP/dig_result.txt
        diff $TEST/ref/resolver/$i $TMP/dig_result.txt  &>/dev/null
        RET=$?

        [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
        [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return
    done
}

function test_tld_server {

    printf "\n*** Testing TLD server ***\n"

    for i in `ls $TEST/ref/tld`
    do
        dig +noall +authority +additional $i @127.0.0.1 -p 1270 > $TMP/dig_result.txt
        diff $TEST/ref/tld/$i $TMP/dig_result.txt  &>/dev/null
        RET=$?

        [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
        [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return
    done
}

function test_root {

    printf "\n*** Testing ROOT server ***\n"

    for i in `ls $TEST/ref/root`
    do
        dig +noall +authority +additional $i @127.0.0.1 -p 8888 > $TMP/dig_result.txt
        diff $TEST/ref/root/$i $TMP/dig_result.txt  &>/dev/null
        RET=$?

        [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
        [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return
    done
}

function test_local_server {

    printf "\n*** Testing LOCAL DNS server ***\n"

    for i in `ls $TEST/ref/full`
    do
        dig $i @127.0.0.1 -p 5300 +short > $TMP/dig_result.txt
        diff $TEST/ref/full/$i $TMP/dig_result.txt  &>/dev/null
        RET=$?

        [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
        [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return
    done
}

function test {

    test_$1
    [ $RET -eq 0 ] && printf "%-12s [${ok}OK${wipe}]\n" "$1"
    [ $RET -ne 0 ] && printf "%-12s [${ko}KO${wipe}]\n" "$1"
}


# ============================================================
#                 Calling test functions
# (comment or uncomment according to what you want to test)
# ============================================================

test authoritative_server;
test resolver;
test tld_server;
test root;
test local_server;

# for TCP tests, run your TCP servers (dns_server_v2 and dns_server_local_v2)
# and execute only "test local_server"

exit 0
