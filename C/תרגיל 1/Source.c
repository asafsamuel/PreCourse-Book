#include <stdio.h>
#include "list.h"
#include "queue.h"

int main()
{
	/* list test */
	puts("*******************************");
	puts("List test:");
	listCreate();
	listAdd(10);
	listAdd(20);
	listAdd(15);

	printf("%f\n", listAvgValues());
	printf("%d\n", listSize());

	listRemove(listFirstNode());

	printf("%f\n", listAvgValues());
	printf("%d\n", listSize());

	listAdd(10);
	listRemove(nextNode(listFirstNode()));

	printf("%f\n", listAvgValues());
	printf("%d\n", listSize());

	listAdd(30);
	listRemove(prevNode(listLastNode()));

	printf("%f\n", listAvgValues());
	printf("%d\n", listSize());

	listRemoveAll();
	printf("%f\n", listAvgValues());
	printf("%d\n", listSize());
	puts("*******************************");

	/* queue test */
	puts("*******************************");
	puts("queue test:");
	queueCreate();

	queuePush(100);
	queuePush(200);
	queuePush(50);
	printf("%d\n", queueSize());

	printf("%d\n", queuePeek());
	printf("%d\n", queuePop());
	printf("%d\n", queueSize());

	printf("%d\n", queuePop());
	printf("%d\n", queueSize());

	queueClean();
	printf("%d\n", queueSize());
	puts("*******************************");
	return 0;
}