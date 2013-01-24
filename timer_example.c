#include <stdio.h>

#include "timers.h"

int main(){
	pTimer czas = newTimer();
	startTimer(czas);
	sleep(5);
	stopTimer(czas);
	printTimer(czas);
	freeTimer(czas);
}
