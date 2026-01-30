// SHORTEST REMAINING TIME FIRST (SRTF) - PREEMPTIVE SJF SCHEDULING - DONE
#include<stdio.h>
#include<stdlib.h>

// PROCESS STRUCTURE
typedef struct processes{
	int pno, at, bt, rt, ct, tat, wt;
}process;

// FUNCTION TO SORT PROCESSES BY ARRIVAL TIMES
void sortProcessesByArrivalTime(process *p, int nop){	
	int i, j;
	process temp;
	for(i=0; i<nop; i++){
		for(j=i+1; j<nop; j++){
			if(p[i].at > p[j].at){
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
}
// END OF Arrival Time Sort FUNCTION

// FUNCTION TO FIND NEXT SHORTEST JOB PROCESS NUMBER 
int shortestJobNext(process *p, int nop, int currentTime){
	int i, pno=1, minRT=1000;
	for(i=0; i<nop; i++){
		if(p[i].rt==0 || p[i].at>currentTime) continue;
		if(p[i].rt < minRT){
			minRT = p[i].rt;
			pno = p[i].pno;
		}
	}
	return pno;
}
// END OF FUNCTION TO FIND NEXT SHORTEST JOB PROCESS NUMBER

// FUNCTION TO FIND MINIMUM OF TWO VALUES
int min(int a, int b){
	return (a < b) ? a : b;
}
// END OF FUNCTION TO FIND MINIMUM OF TWO VALUES


// FUNCTION TO SEARCH PROCESS INDEX BY PROCESS NUMBER
int search(process *p, int nop, int pno){
	int i;
	for(i=0; i<nop; i++){
		if(p[i].pno==pno){
			return i;
		}
	}
	return -1;
}
// END OF FUNCTION TO SEARCH PROCESS INDEX BY PROCESS NUMBER

// FUNCTION: SRTF(processes, numberOfProcesses)
void SRTF(process *p, int nop){
	int i, pno, currentTime=0, completed=0, timeFactor, timeStamps[1000], k=0, visited=1;
	float atat=0.0, awt=0.0;
	printf("\n GANTT Chart:");
	printf("\n_________________________________________________________________________________________________________\n|");
	while(completed != nop)
	{
		pno = search(p, nop, shortestJobNext(p, nop, currentTime));
		timeFactor = (visited < nop) ? (min(p[pno].rt, abs(currentTime - p[visited++].at))) : p[pno].rt;
		currentTime += timeFactor;
		p[pno].rt -= timeFactor;
		
		printf(" P%d \t|", p[pno].pno);
		timeStamps[k++] = currentTime;
			
		if(p[pno].rt == 0){
			completed++;
			p[pno].ct = currentTime;
			p[pno].tat = p[pno].ct - p[pno].at;
			p[pno].wt = p[pno].tat - p[pno].bt;
			atat += p[pno].tat;
			awt += p[pno].wt;
		}
	}
	atat = atat/nop; // average turn around time
	awt = awt/nop; // average waiting time
	printf("\n---------------------------------------------------------------------------------------------------------\n0");
	for(i=1; i<k; i++){
		printf("\t%d", timeStamps[i]);
	}
	
	PrintResult(p, nop, atat, awt);
}
// END OF SRTF() FUNCTION

// FUNCTION TO PRINT FINAL RESULT
void PrintResult(process *p, int nop, float ATAT, float AWT){
	int i;
	printf("\n\n_________________________________________________________");
	printf("\n     Process \t| AT \t| BT \t| CT \t| TAT \t| WT \t|");
	printf("\n---------------------------------------------------------");
	for(i=0; i<nop; i++){
		printf("\n\tP%d \t| %d \t| %d \t| %d \t| %d \t| %d \t|", p[i].pno, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
	}
	printf("\n---------------------------------------------------------");
	printf("\n Average Turn Around Time: %.2f", ATAT);
	printf("\n Average Waiting Time: %.2f", AWT);
}
// END OF FUNCTION TO PRINT FINAL RESULT

int main(){
	// DECLARATIONS
	process *p;
	int nop, i;
	// END OF DECLARATIONS
	
	// INPUTS
	printf("\n\t\t *** SRTF Scheduling ***\n");
	printf("\n Enter number of processes: ");
	scanf("%d", &nop);
	p = (process *) malloc (sizeof(process)*nop);
	for(i=0; i<nop; i++){
		printf("\n Process P%d", i+1);
		p[i].pno = i+1;
		printf("\n Enter arrival time: ");
		scanf("%d", &p[i].at);
		printf("\n Enter burst time: ");
		scanf("%d", &p[i].bt);
		p[i].rt = p[i].bt;
	}
	// END OF INPUTS
	
	sortProcessesByArrivalTime(p, nop);
	
	SRTF(p, nop);
	
	return 0;
}
