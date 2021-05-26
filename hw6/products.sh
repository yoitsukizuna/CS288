#! /bin/bash
#set -x

fun(){
    local file1=$1
    local file2=$2
    local m=1 #for count repeat time
    if [[ -f "tagsoup-1.2.1.jar" ]]
       then
            echo "tagsoup exists"
    else
        wget http://maven.org/maven2/org/ccil/cowan/tagsoup/tagsoup/1.2.1/tagsoup-1.2.1.jar
    fi

    
    #download html and convert to xhtml
    while [ : ]
        do
        local n=0 #for rename html file
        wget -E  -i $file1
        wget -E -i $file2
        
        #rename and convert to xthml
        for f in *.html
            do
                mv "$f" "$n.html"
                name="$n.html"
                java -jar tagsoup-1.2.1.jar --files $name
                n=$(($n+1))
                rm $name
            done
        #parser:
        
        for d in *.xhtml
            do
                echo $d
                python3 parser.py $d $m
                rm $d
            done
        m=$(($m+1))
        echo "done!"
        #repeat every 6 hours
        sleep 6h     
        done
   
}

fun bestbuy.txt microcenter.txt