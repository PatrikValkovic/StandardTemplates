#!/bin/sh
g++ -E -D _STALIB_ Templates.h | grep . | grep -v "^#" > temp.h
touch templates.h
rm templates.h
touch templates.h
echo "#include <cstring>" >> templates.h
echo "#include <iostream>" >> templates.h
echo "#include <exception>" >> templates.h
cat temp.h >> templates.h
rm temp.h