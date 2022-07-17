#!/usr/bin/awk -f 
{
    if ( NR == 1 ){ 
        $4 = NUM
    } 
    print $0 > "script.js"
}
