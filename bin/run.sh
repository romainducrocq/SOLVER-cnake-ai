#!/bin/sh

args=""
for ARG in $( echo "${@}" | sed 's/ / /g' );
do 
    args="${args} ${ARG}"; 
done

cd app/
./exec${args}
