#include <stdio.h>
#include "stack.h"

int main() {
	IntStack stack;

	if (stackInit(&stack) != 0)
		return -1;
	
	stackPush(&stack, 1);
	stackPush(&stack, 2);
	stackPush(&stack, 3);
	stackPrint(&stack);
	
	while (!stackIsEmpty(&stack))
		printf("%i\n", stackPop(&stack));

	printf("Empty: %d\n", stackIsEmpty(&stack));

	stackPop(&stack);
	
	stackRelease(&stack);
	return 0;
}


/* Erwartete Ausgabe:
3
2
1
<<Fehlermeldung, da IntStack leer>>
*/
