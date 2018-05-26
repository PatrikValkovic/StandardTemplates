#define CATCH_CONFIG_MAIN
#include "../libs/catch.h"
#include "../Templates.h"

using namespace Templates;

TEST_CASE("Should alloc and free void pointer", "[malloc]")
{
	void* data = malloc_own(25);
	free_own(data);
}

TEST_CASE("Should alloc and free void pointer with size of pointer", "[malloc]"){
	void* data = malloc_own(sizeof(int) * 10);
	int* int_ptr = (int*)data;
	for(int i=0;i<10;i++)
		int_ptr[i] = i;
	free_own(int_ptr);
}

TEST_CASE("Should alloc and free int pointer", "[malloc]"){
	int* int_ptr = malloc_own<int>(10);
	for(int i=0;i<10;i++)
		int_ptr[i] = i;
	free_own(int_ptr);
}




