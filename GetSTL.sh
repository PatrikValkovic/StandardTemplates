touch tmp.txt
rm STL.h

touch tmp.txt

echo '#ifndef __KowalSTL_H_' >> tmp.txt
echo '#define __KowalSTL_H_' >> tmp.txt

echo '#ifndef _STALIB_' >> tmp.txt
echo '#include <stdlib.h>' >> tmp.txt
echo '#include <iostream>' >> tmp.txt
echo '#include <string.h>' >> tmp.txt
echo '#endif' >> tmp.txt

g++ Templates.h -E -D _STALIB_ -Wall -Werror -pedantic -std=c++11 | grep -v '^#' | grep '.' >> tmp.txt

echo '#endif' >> tmp.txt

mv tmp.txt STL.h

echo '#include <assert.h>' > x.h
CompileToSource main.cpp
rm x.h

cd Debug
valgrind -q --leak-check=full ./program.exe
