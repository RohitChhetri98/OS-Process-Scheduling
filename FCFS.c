// FCFS PROCESS SCHEDULING
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

// FUNCTION TO SORT PROCESSES BY PROCESS NUMBER
void sortProcessesByProcessNumber(process *p, int nop){	
	int i, j;
	process temp;
	for(i=0; i<nop; i++){
		for(j=i+1; j<nop; j++){
			if(p[i].pno > p[j].pno){
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
}
// END OF PROCESS NUMBER Sort FUNCTION

// FUNCTION: FCFS(processes, numberOfProcesses)
void FCFS(process *p, int nop){
	int i, currentTime=0, timeStamps[1000], k=0;
	float atat=0.0, awt=0.0;
	printf("\n GANTT Chart:");
	printf("\n_________________________________________________________________________________________________________\n|");
	for(i=0; i<nop; i++){
		currentTime += p[i].bt;
		printf("  P%d  |", p[i].pno);
		p[i].ct = currentTime;
		p[i].tat = p[i].ct - p[i].at;
		p[i].wt = p[i].tat - p[i].bt;
		atat += p[i].tat;
		awt += p[i].wt;
	}
	atat = atat/nop; // average turn around time
	awt = awt/nop; // average waiting time
	printf("\n---------------------------------------------------------------------------------------------------------\n0");
	for(i=1; i<k; i++){
		printf("\t%d", timeStamps[i]);
	}
	
	sortProcessesByProcessNumber(p, nop);
	
	PrintResult(p, nop, atat, awt);
}
// END OF FCFS() FUNCTION

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
	printf("\n\t\t ***  Scheduling ***\n");
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
		// p[i].rt = p[i].bt;
	}
	// END OF INPUTS
	
	sortProcessesByArrivalTime(p, nop);
	
	FCFS(p, nop);
	
	return 0;
}

