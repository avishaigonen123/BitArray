# include "BitArray.h"
#include "stdio.h"

int main() {
	BitArray *bitarray = new BitArray();
	for (int i = 0; i < 20; i++)
	{
		bitarray->SetAt(i, 0);
		printf("%d", bitarray->GetAt(i));
	}
	printf("\n");

	for (int i = 0; i < 10; i++)
	{
		bitarray->SetAt(i, 1);
		printf("%d", bitarray->GetAt(i));
	}
	printf("\n");
	//bitarray->SetAt(5, 1);
	bitarray->SetAt(5, 0);
	//bitarray->SetAt(16, 1);
	for (int i = 0; i < 34; i++)
	{
		printf("%d", bitarray->GetAt(i));
	}
	printf("\n");
	return 0;
}