// ROUND ROBIN SCHEDULING - DONE
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

// FUNCTION: RoundRobin(processes, numberOfProcesses, timeQuantum)
void RoundRobin(process *p, int nop, int timeQuantum){
	int i, completed, currentTime, timeFactor, pno, timeStamps[1000], k;
	float atat=0.0, awt=0.0;
	printf("\n GANTT Chart:");
	printf("\n_________________________________________________________________________________________________________\n|");
	for(i=0, completed=0, currentTime=0, atat=0, awt=0, k=0; completed!=nop; i++){
		pno = i % nop;
		if(p[pno].rt==0) continue;
		timeFactor = (p[pno].rt < timeQuantum) ? p[pno].rt : timeQuantum;
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
	for(i=0; i<k; i++){
		printf("\t%d", timeStamps[i]);
	}
	
	PrintResult(p, nop, atat, awt);
}
// END OF RoundRobin FUNCTION

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
	int nop, tq, i;
	// END OF DECLARATIONS
	
	// INPUTS
	printf("\n\t\t *** Round Robin Scheduling ***\n");
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
	printf("\n Enter Time Slice: ");
	scanf("%d", &tq);
	// END OF INPUTS
	
	sortProcessesByArrivalTime(p, nop);
	
	RoundRobin(p, nop, tq);
	
	return 0;
}
