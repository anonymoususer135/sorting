#include <stdio.h>

#include "bitsStdCppPlus.hpp"

//Megan Jen


// C++ program to implement Shortest Remaining Time First

// Shortest Remaining Time First (SRTF)


//C++ Program for implementing

//Round Robin Algorithm



#include <iostream>



using namespace std;
#define MAX_PROCESSES 100


struct Process {

    char id;

    int burstTime;

    int arrivalTime;

    int priority;

};

int tq = 3;





void queueUpdation(int queue[],int timer,int arrival[],int n, int maxProccessIndex){

    int zeroIndex = 0;

    for(int i = 0; i < n; i++){

        if(queue[i] == 0){

            zeroIndex = i;

            break;

        }

    }

    queue[zeroIndex] = maxProccessIndex + 1;

}



void queueMaintainence(int queue[], int n){

    for(int i = 0; (i < n-1) && (queue[i+1] != 0) ; i++){

        int temp = queue[i];

        queue[i] = queue[i+1];

        queue[i+1] = temp;

    }

}



void checkNewArrival(int timer, int arrival[], int n, int maxProccessIndex,int queue[]){

    if(timer <= arrival[n-1]){

    bool newArrival = false;

    for(int j = (maxProccessIndex+1); j < n; j++){

            if(arrival[j] <= timer){

            if(maxProccessIndex < j){

                maxProccessIndex = j;

                newArrival = true;

            }

        }

    }

    //adds the incoming process to the ready queue

    //(if any arrives)

    if(newArrival)

        queueUpdation(queue,timer,arrival,n, maxProccessIndex);

    }

}
int processRRPrint(char ids[], int burstTimes[], int arrivalTimes[], int processSize, int previousArrivalTime, int remainingBurstTime[], int *t, int turn[], int wait[]) {
    int timer=*t;
    int n=processSize;
    for (int i=0;i<n;i++)
    {
        if (remainingBurstTime[i]==-1)
            continue;
        if (previousArrivalTime>=arrivalTimes[i]-1) {
            
            std::cout<< timer << " " << ids[i] << "     ";
            if (remainingBurstTime[i]>tq)
            {
                int remainingTime=remainingBurstTime[i]-tq;
                printf("Quantum expired – %d ms remaining\n",remainingTime);
                remainingBurstTime[i]=remainingTime;
                timer=timer+tq;
            }
            else
            {
                printf("Process terminated\n");
                timer=timer+remainingBurstTime[i];
                /*
                 The difference b/w Completion Time and Arrival Time is called Turnaround Time.
                 The time difference b/w Turnaround Time and Burst Time is called Waiting Time.
                 
                 */
                turn[i]=timer-arrivalTimes[i];
                wait[i]=turn[i]-burstTimes[i];
                remainingBurstTime[i]=-1; //if remainingBurstTime is -1, process terminated
                }
            previousArrivalTime=arrivalTimes[i];
        }
        else {
            int diff=arrivalTimes[i]-previousArrivalTime-1;
            int counter=0;
            //Need to run previous processes still having ms left
            for (int j=0;j<i;j++) {
                if (counter>=diff)
                    break;
                if (remainingBurstTime[j]==-1) //skip, that process is terminated
                    continue;
                std::cout<< timer << " " << ids[j] << "     ";
                if (remainingBurstTime[j]>tq)
                {
                    int remainingTime=remainingBurstTime[j]-tq;
                    printf("Quantum expired – %d ms remaining\n",remainingTime);
                    remainingBurstTime[j]=remainingTime;
                    timer=timer+tq;
                }
                else
                {
                    printf("Process terminated\n");
                    timer=timer+remainingBurstTime[j];
                    /*
                     The difference b/w Completion Time and Arrival Time is called Turnaround Time.
                     The time difference b/w Turnaround Time and Burst Time is called Waiting Time.
                     */
                    turn[j]=timer-arrivalTimes[j];
                    wait[j]=turn[j]-burstTimes[j];
                    
                    
                    remainingBurstTime[j]=-1; //if remainingBurstTime is -1, process terminated
                }
                counter++;
            }
            
            std::cout<< timer << " " << ids[i] << "     ";
            if (remainingBurstTime[i]>tq)
            {
                int remainingTime=remainingBurstTime[i]-tq;
                printf("Quantum expired – %d ms remaining\n",remainingTime);
                remainingBurstTime[i]=remainingTime;
                timer=timer+tq;
            }
            else
            {
                printf("Process terminated\n");
                timer=timer+remainingBurstTime[i];
                /*
                 The difference b/w Completion Time and Arrival Time is called Turnaround Time.
                 The time difference b/w Turnaround Time and Burst Time is called Waiting Time.
                 
                 */
                turn[i]=timer-arrivalTimes[i];
                wait[i]=turn[i]-burstTimes[i];
                remainingBurstTime[i]=-1; //if remainingBurstTime is -1, process terminated
                }
            previousArrivalTime=arrivalTimes[i];
          }
        }
    
    *t=timer;
    
    return 0;
}


//Driver Code

//int processRR(struct Process processes[], int burstTimes[], int arrivalTimes[]) {
int processRR(char ids[], int burstTimes[], int arrivalTimes[], int processSize) {
    
    std::cout << "RR Scheduling\n" << std::endl;

    int n = processSize, timer = 0, maxProccessIndex = 0;
    int previousArrivalTime;

    float avgWait = 0, avgTT = 0;

    //cout << "\nEnter the time quanta : ";


    //cout << "\nEnter the number of processes : ";

    //cin>>n;

    int wait[n], remainingBurstTime[n], turn[n], queue[n], temp_burst[n];

    int complete[n];

    //Initially, remainingBurstTime is BurstTimes, initialize remainingBurstTime with
    //BurstTimes
    
    for (int i=0;i<n;i++) {
        remainingBurstTime[i]=burstTimes[i];
        turn[i]=0;
        wait[i]=0;
    }
    
    processRRPrint(ids, burstTimes, arrivalTimes, n, previousArrivalTime, remainingBurstTime, &timer, turn, wait);

    bool allDone=false;
    while (!allDone) {
        //first check if all remainingBurstTime is -1, which means all done
        int counter=0;
        for (int i=0;i<n;i++) {
            if (remainingBurstTime[i]==-1)
                continue;
            else
                counter++;
        }
        if (counter==0) {
            allDone=true;
            std::cout<< timer << "       Complete"<<std::endl;
            continue;
        }
        processRRPrint(ids, burstTimes, arrivalTimes, n, previousArrivalTime, remainingBurstTime, &timer, turn, wait);
    }
    
  
    //Print Turnaround Time and Wait time stats
    
    std::cout << std::endl << std::endl;
    
    int tatTotal=0;
    int waitTotal=0;
    std::cout<<"Process ID" << "\t\t" <<"Turnaround Time" << "\t\t" << "Wait Time" <<std::endl;
    for (int i=0;i<n;i++) {
        std::cout << ids[i] << "\t\t\t\t\t" << turn[i] << "\t\t\t\t" << wait[i] << std::endl;
        tatTotal+=turn[i];
        waitTotal+=wait[i];
    }
    std::cout<<"Average\t\t\t\t" << tatTotal << "/" << n << "=" << (tatTotal*1.0)/n << "\t\t" << waitTotal << "/" << n << "=" << (waitTotal*1.0)/n << std::endl << std::endl;
    
    std:: cout << "RR Completed" << std::endl;
    return 0;
}

//The end of processRR()


// C++ program to implement Shortest Remaining Time First
// Shortest Remaining Time First (SRTF)


void findWaitingTime(char ids[],  int burstTimes[], int arrivalTimes[], int n,
                                int wt[])
{
    int rt[n];

    // Copy the burst time into rt[]
    for (int i = 0; i < n; i++)
        rt[i] = burstTimes[i];

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

    // Process until all processes gets
    // completed
    while (complete != n) {

        // Find process with minimum
        // remaining time among the
        // processes that arrives till the
        // current time`
        for (int j = 0; j < n; j++) {
            if ((arrivalTimes[j] <= t) &&
            (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }

        if (check == false) {
            t++;
            continue;
        }

        // Reduce remaining time by one
        rt[shortest]--;

        // Update minimum
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        // If a process gets completely
        // executed
        if (rt[shortest] == 0) {

            // Increment complete
            complete++;
            check = false;

            // Find finish time of current
            // process
            finish_time = t + 1;

            // Calculate waiting time
            wt[shortest] = finish_time -
                        burstTimes[shortest] -
                        arrivalTimes[shortest];

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        // Increment time
        t++;
    }
}

// Function to calculate turn around time
void findTurnAroundTime(char ids[],  int burstTimes[], int arrivalTimes[], int n,
                        int wt[], int tat[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = burstTimes[i] + wt[i];
}

// Function to calculate average time
void findavgTime(char ids[],  int burstTimes[], int arrivalTimes[], int processSize)
{
    int n=processSize;
    int wt[n], tat[n], total_wt = 0,
                    total_tat = 0;

    // Function to find waiting time of all
    // processes
    findWaitingTime(ids,  burstTimes, arrivalTimes, n, wt);

    // Function to find turn around time for
    // all processes
    findTurnAroundTime(ids,  burstTimes, arrivalTimes, n, wt, tat);

    // Display processes along with all
    // details
    cout << " Process ID\t\t"
        << "Turnaround Time\t\t"
        << "Waiting Time \t\t\n";

    // Calculate total waiting time and
    // total turnaround time
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << ids[i] << "\t\t"
            <<  "\t\t " << tat[i]
            << "\t\t\t\t\t " << wt[i] << endl;
    }
    
    cout << "Average" << "\t"
    <<  "\t " << total_tat << "/" << n << "=" << (float)total_tat / (float)n
    << "\t\t\t " << total_wt << "/" << n << "=" << (float)total_wt / (float)n << endl;

 }


// Driver code
int processSRTF(char ids[],  int burstTimes[], int arrivalTimes[], int processSize)
{
    std::cout << "\n\nProcess SRTF Scheduling" << std::endl;
    findavgTime(ids, burstTimes, arrivalTimes, processSize);
    std::cout << std:: endl << "SRTF Completed\n" << std::endl;
    return 0;
}



void findWaitingTimeFCFS(char ids[],  int burstTimes[], int arrivalTimes[],  int n,
                         int wt[])
{
    // waiting time for first process is 0
    wt[0] = 0;

    // calculating waiting time
    for (int i = 1; i < n ; i++ )
        wt[i] = burstTimes[i-1] + wt[i-1] ;
}

// Function to calculate turn around time
void findTurnAroundTimeFCFS( char ids[],  int burstTimes[], int arrivalTimes[], int n, int wt[], int tat[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < n ; i++)
        tat[i] = burstTimes[i] + wt[i];
}

//Function to calculate average time
void findavgTimeFCFS( char ids[], int burstTimes[], int arrivalTimes[], int n)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    //Function to find waiting time of all processes
    findWaitingTimeFCFS(ids,  burstTimes, arrivalTimes, n, wt);

    //Function to find turn around time for all processes
    findTurnAroundTimeFCFS(ids,  burstTimes, arrivalTimes, n, wt, tat);

    //Display processes along with all details
    cout << "Processes ID\t\t"
        << "Turnaround Time\t\t" << "Waiting Time" << std::endl;

    // Calculate total waiting time and total turn
    // around time
    for (int i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << ids[i]  <<"\t\t\t\t\t"
            << tat[i] <<"\t\t\t\t\t" << wt[i] <<endl;
    }

    cout << "Average" << "\t"
    <<  "\t\t\t " << total_tat << "/" << n << "=" << (float)total_tat / (float)n
    << "\t\t\t " << total_wt << "/" << n << "=" << (float)total_wt / (float)n << endl;

}

// Driver code
int processFCFS(char ids[],  int burstTimes[], int arrivalTimes[], int processSize)
{
    std::cout << "\n\nProcess FCFS Scheduling" << std::endl;
    int n = processSize;

    findavgTimeFCFS(ids,  burstTimes, arrivalTimes, n);
    std::cout << std:: endl << "FCFS Completed\n" << std::endl;
    return 0;
}

int main() {

    FILE *fp;

    char id;

    char filename[100];

    int burstTime, arrivalTime;

    struct Process processes[MAX_PROCESSES];

    int numProcesses = 0;

    scanf("%s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL) {

        printf("Error opening file.\n");

        return 1;

    }

    char *ids = (char*)malloc(MAX_PROCESSES * sizeof(char));

       int *burstTimes = (int*)malloc(MAX_PROCESSES * sizeof(int));

       int *arrivalTimes = (int*)malloc(MAX_PROCESSES * sizeof(int));

    
    Process processLine;
    std::vector<Process> processLines;
    

    std::cout << "Inputed Process Info: " << std:: endl;
       while (fscanf(fp, " %c %d %d", &id, &burstTime, &arrivalTime) == 3) {

           //printf("%c", "%d", "%d");

           ids[numProcesses] = id;

           burstTimes[numProcesses] = burstTime;

           arrivalTimes[numProcesses] = arrivalTime;
           
           processLine.id = id;
           processLine.burstTime = burstTime;
           processLine.arrivalTime = arrivalTime;
           
           processLines.push_back(processLine);

           numProcesses++;
           std::cout << id << " " << burstTime << " " << arrivalTime << std:: endl;

       }
    std::cout << std::endl << std::endl;
    
    sort( processLines.begin(), processLines.end(), [](auto const& a, auto const& b) {
            if( a.arrivalTime < b.arrivalTime ) return true;
            if( a.arrivalTime == b.arrivalTime ) return a.arrivalTime < b.arrivalTime;
            return false;
        } );
    
//    std:: cout << "after sort: " << std::endl;
//    for (auto i: processLines)
    std::fill_n(ids, processLines.size(), NULL);
    std::fill_n(burstTimes, processLines.size(), NULL);
    std::fill_n(arrivalTimes, processLines.size(), NULL);
    
    
    for (size_t i=0;i<processLines.size();i++)
    {
 //       std::cout << processLines.at(i).id << " " << processLines.at(i).burstTime << " " << processLines.at(i).arrivalTime <<  std::endl;
        ids[i]=processLines.at(i).id;
        burstTimes[i]=processLines.at(i).burstTime;
        arrivalTimes[i]=processLines.at(i).arrivalTime;
    }

    fclose(fp);

    processRR(ids,  burstTimes, arrivalTimes, processLines.size());

    processSRTF(ids,  burstTimes, arrivalTimes, processLines.size());

    processFCFS(ids,  burstTimes, arrivalTimes, processLines.size());

     
    
    free(ids);

    free(burstTimes);

    free(arrivalTimes);
    



    return 0;

}


