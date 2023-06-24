//1. CPU scheduling :
//Implement the following CPU Scheduling algorithms and choose parameters(i.e waiting
//	time burst time etc) for CPU Scheduling accordingly.
//	● Multilevel Queue Scheduling
//	● Multilevel Feedback Queue Scheduling
//	● Longest Job First
//	● Highest Feedback Ratio Next Scheduling
//
//	Highest Feedback Ratio Next is one of the most optimal scheduling
//	algorithms.This is a non - preemptive algorithm in which the scheduling is done on
//	the basis of an extra parameter called Feedback Ratio.A Feedback Ratio is
//
//	calculated for each of the available jobsand the Job with the highest feedback ratio
//	is given priority over the others.
//	Feedback Ratio is calculated by the given formula :
//1. Feedback Ratio = (W + S) / S
//Where : W is Waiting Time, S is Service Time or Burst Time
//For CPU Scheduling, Don’t create a process using a fork.You have to create a class for
//processes which have attributes like process ID, Burst Time etc.

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include<queue>
using namespace std;
class Process
{
public:
	int processID;
	int burstTime;
	int arrivalTime;
	int waitingTime;
	int turnaroundTime;
	int remainingTime;
	int completionTime;
	

	Process(int processID, int burstTime, int arrivalTime)
	{
		this->processID = processID;
		this->burstTime = burstTime;
		this->arrivalTime = arrivalTime;
		this->remainingTime = burstTime;
		this->waitingTime = 0;
		this->turnaroundTime = 0;
		this->completionTime = 0;
	}

	int getProcessID()
	{
		return processID;
	}
	int CalculateCompletionTime()
	{
		return completionTime = arrivalTime + turnaroundTime;
	}

	int CalculateTurnAroundTime()
	{
		turnaroundTime = completionTime - arrivalTime;
		return turnaroundTime;
	}


	int CalculateWaitTime()
	{
		return this->waitingTime = this->turnaroundTime - this->burstTime;
	}
	void Input()
	{
		cout << "Enter Process ID : ";
		cin >> processID;
		cout << "Enter Burst Time : ";
		cin >> burstTime;
		cout << "Enter Arrival Time : ";
		cin >> arrivalTime;
		this->remainingTime = burstTime;
	}
};
void LongestJobFirst(vector<Process>& Processes)
{

	//sort the processes in increasing order of their arrival time
	for (int i = 0; i < Processes.size(); i++)
	{
		for (int j = 0; j < Processes.size(); j++)
		{
			if (Processes[i].arrivalTime < Processes[j].arrivalTime)
			{
				Process temp = Processes[i];
				Processes[i] = Processes[j];
				Processes[j] = temp;
			}
		}
	}
	// if more than 1 processes have same arrival time place the process first which have highest burst time
	for (int i = 0; i < Processes.size(); i++)
	{
		for (int j = 0; j < Processes.size(); j++)
		{
			if (Processes[i].arrivalTime == Processes[j].arrivalTime)
			{
				if (Processes[i].burstTime > Processes[j].burstTime)
				{
					Process temp = Processes[i];
					Processes[i] = Processes[j];
					Processes[j] = temp;
				}
			}
		}
	}


	int currentTime = 0;

	for (int i = 0; i < Processes.size(); i++)

	{
		if (Processes[i].arrivalTime <= currentTime)
		{

			Processes[i].completionTime = currentTime + Processes[i].burstTime;
			currentTime = Processes[i].completionTime;
			
		}
		else
		{
			currentTime = Processes[i].arrivalTime;
			Processes[i].completionTime = currentTime + Processes[i].burstTime;
			currentTime = Processes[i].completionTime;
		}


	}


	//calculate the turnaround time of each process
	for (int i = 0; i < Processes.size(); i++)
	{
		Processes[i].turnaroundTime = Processes[i].completionTime - Processes[i].arrivalTime;
	}

	//calculate the waiting time of each process
	for (int i = 0; i < Processes.size(); i++)
	{
		Processes[i].waitingTime = Processes[i].turnaroundTime - Processes[i].burstTime;
	}

	//calculate the average waiting time
	float averageWaitingTime = 0;
	for (int i = 0; i < Processes.size(); i++)
	{
		averageWaitingTime += Processes[i].waitingTime;
	}
	averageWaitingTime /= Processes.size();

	//calculate the average turnaround time
	float averageTurnaroundTime = 0;
	for (int i = 0; i < Processes.size(); i++)
	{
		averageTurnaroundTime += Processes[i].turnaroundTime;
	}
	averageTurnaroundTime /= Processes.size();

	//print the results

	cout << "Process ID\tBurst Time\tArrival Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;

	for (int i = 0; i < Processes.size(); i++)
	{
		cout << Processes[i].processID << "\t\t" << Processes[i].burstTime << "\t\t" << Processes[i].arrivalTime << "\t\t" << Processes[i].completionTime << "\t\t" << Processes[i].turnaroundTime << "\t\t" << Processes[i].waitingTime << endl;
	}

}

void LJBMenu()
{
	int n;
	cout << "Enter Number of Processes : ";
	cin >> n;
	vector<Process>processes;
	for (int i = 0; i < n; i++)
	{
		Process p(0, 0, 0);
		cout << "Enter Info of Processe " << i + 1 << " : " << endl;
		p.Input();
		processes.push_back(p);
		cout << endl;

		LongestJobFirst(processes);
	}
}
class JOB {

private:
	int processID;
	int burstTime;
	int arrivalTime;
	int waitingTime;
	int turnaroundTime;
	float FeedbackRatio;

public:
	JOB(int processID, int burstTime, int arrivalTime, int WT) {
		this->processID = processID;
		this->burstTime = burstTime;
		this->arrivalTime = arrivalTime;
		this->waitingTime = WT;
		this->turnaroundTime = 0;
		this->FeedbackRatio = 0;
	}
	int getProcessID() {
		return processID;
	}
	int getBurstTime() {
		return burstTime;
	}
	int getArrivalTime() {
		return arrivalTime;
	}
	int getWaitingTime() {
		return waitingTime;
	}
	int getTurnaroundTime() {
		return turnaroundTime;
	}
	float getFeedbackRatio() {
		return FeedbackRatio;
	}
	void setWaitingTime(int waitingTime) {
		this->waitingTime = waitingTime;
	}
	void setTurnaroundTime(int turnaroundTime) {
		this->turnaroundTime = turnaroundTime;
	}
	void setFeedbackRatio(int FeedbackRatio) {
		this->FeedbackRatio = FeedbackRatio;
	}
	void INPUT()
	{
		cout << "Enter Process ID : ";
		cin >> processID;
		cout << "Enter Burst Time : ";
		cin >> burstTime;
		cout << "Enter Arrival Time : ";
		cin >> arrivalTime;
		cout << "Enter Waiting Time : ";
		cin >> waitingTime;
	}
};

void HFR(vector<JOB>* jobs)
{
	//Feedback Ratio is calculated by the given formula :
//1. Feedback Ratio = (W + S) / S
//Where : W is Waiting Time, S is Service Time or Burst Time

	for (int i = 0; i < jobs->size(); i++)
	{
		float FeedbackRatio = (jobs->at(i).getWaitingTime() + jobs->at(i).getBurstTime()) / jobs->at(i).getBurstTime();
		jobs->at(i).setFeedbackRatio(FeedbackRatio);
	}
	// first we need to sort the jobs according to their arrival time

	for (int i = 0; i < jobs->size(); i++)
	{
		for (int j = 0; j < jobs->size() - 1; j++)
		{
			if (jobs->at(j).getArrivalTime() > jobs->at(j + 1).getArrivalTime())
			{
				JOB temp = jobs->at(j);
				jobs->at(j) = jobs->at(j + 1);
				jobs->at(j + 1) = temp;
			}
		}
	}
	// now if two jobs have same arrival time then we need to sort them according to their feedbackratio 
	for (int i = 0; i < jobs->size(); i++)
	{
		for (int j = 0; j < jobs->size() - 1; j++)
		{
			if (jobs->at(j).getArrivalTime() == jobs->at(j + 1).getArrivalTime())
			{
				if (jobs->at(j).getFeedbackRatio() < jobs->at(j + 1).getFeedbackRatio())
				{
					JOB temp = jobs->at(j);
					jobs->at(j) = jobs->at(j + 1);
					jobs->at(j + 1) = temp;
				}
			}
		}
	}

	int currentTime = 0;
	int totalWaitingTime = 0;
	int totalTurnaroundTime = 0;
	int totalResponseTime = 0;
	int totalJobs = jobs->size();
	int totalBurstTime = 0;
	for (int i = 0; i < jobs->size(); i++)
	{
		totalBurstTime += jobs->at(i).getBurstTime();
	}
	int currenttime = 0;
	for (int i = 0; i < jobs->size(); i++)
	{
		if (jobs->at(i).getArrivalTime() > currenttime)
		{
			currenttime = jobs->at(i).getArrivalTime();
		}
		//jobs->at(i).setWaitingTime(currenttime - jobs->at(i).getArrivalTime());
		currenttime += jobs->at(i).getBurstTime();
		jobs->at(i).setTurnaroundTime(currenttime - jobs->at(i).getArrivalTime());
		totalWaitingTime += jobs->at(i).getWaitingTime();
		totalTurnaroundTime += jobs->at(i).getTurnaroundTime();
	}
	cout << "Process ID\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\tFeedback Ratio" << endl;
	for (int i = 0; i < jobs->size(); i++)
	{
		cout << jobs->at(i).getProcessID() << "\t\t" << jobs->at(i).getBurstTime() << "\t\t" << jobs->at(i).getArrivalTime() << "\t\t" << jobs->at(i).getWaitingTime() << "\t\t" << jobs->at(i).getTurnaroundTime() << "\t\t" << jobs->at(i).getFeedbackRatio() << endl;
	}
	cout << "Average Waiting Time : " << (float)totalWaitingTime / totalJobs << endl;
	cout << "Average Turnaround Time : " << (float)totalTurnaroundTime / totalJobs << endl;
	//cout << "Average Response Time : " << (float)totalResponseTime / totalJobs << endl;
}
void HFRmenu()
{
	vector<JOB> jobs;
	int n;
	cout << "Enter Number of Processes : ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		JOB job(0, 0, 0, 0);
		job.INPUT();
		jobs.push_back(job);
	}
	HFR(&jobs);
}

////Queues
////Q1 = Batch Process having Low Priority with FCFS Algorithm
////Q2 = Interactive Process having Medium Priority with Priority Based Sorting
////Q3 = System Process having High Priority with Round Robin Algorith Quantum Time=4
//
//class  ProcessMLQ {
//public:
//	int priority;
//	int burst_time;
//	int pid;
//	int waiting_time;
//	int turnaround_time;
//	int remaining_time;
//	int arrival_time;
//};
//class MLQ {
//private:
//	ProcessMLQ* q1, * q2, * q3;
//	int q1_n = 0, q2_n = 0, q3_n = 0, n = 0; //N=Total Process
//	int time_quantum = 3;
//public:
//	MLQ()
//	{
//		getInput();
//	}
//	void getInput();
//	void CalWaitTime(ProcessMLQ* q, int);
//	void CalTATime(ProcessMLQ* q, int);
//	void printQueue(ProcessMLQ* q, int size);
//	void RRAlgo(ProcessMLQ* q, int size);
//	void PSAlgo(ProcessMLQ* q, int size);
//	void FCFSAlgo(ProcessMLQ* q, int size);
//	void RR();
//	void PS();
//	void FCFS();
//	void printQueueI(ProcessMLQ);
//	int getSize();
//	bool isEmpty();
//
//};
//void MLQ::getInput()
//{
//	cout << "\n Total Number of Process = ";
//	cin >> n;
//	q1 = new ProcessMLQ[n];
//	q2 = new ProcessMLQ[n];
//	q3 = new ProcessMLQ[n];
//	for (int i = 0; i < n; i++) {
//		ProcessMLQ* p = new ProcessMLQ();
//		cout << "Enter Info Of Process : " << i + 1 << endl;
//		// take input
//		cout << "Enter Process ID: ";
//		cin >> p->pid;
//		cout << "Enter Arrival Time: ";
//		cin >> p->arrival_time;
//		cout << "Enter Burst Time: ";
//		cin >> p->burst_time;
//		cout << "Enter Priority: ";
//		cin >> p->priority;
//		p->remaining_time = p->burst_time;
//		if (p->priority > 0 && p->priority <= 10) {
//			q1[q1_n++] = *p;
//		}
//		else if (p->priority > 10 && p->priority <= 20) {
//			q2[q2_n++] = *p;
//		}
//		else {
//			q3[q3_n++] = *p;
//		}
//
//
//		cout << "Process ID : " << p->pid;
//		cout << "\nBurst Time  :  " << p->burst_time;
//		cout << "\nPriority    :  " << p->priority;
//		cout << "\nArrival Time:  " << p->arrival_time;
//		cout << "\n\n";
//	}
//}
//void MLQ::printQueue(ProcessMLQ* q, int size) {
//	CalWaitTime(q, size);
//	CalTATime(q, size);
//	cout << "\nPId  Priority BurstTime  WaitTime  TAroundTime  ArrivalTime : ";
//	for (int i = 0; i < size; i++) {
//		printQueueI(q[i]);
//	}
//	cout << "\n\n";
//}
//void MLQ::printQueueI(ProcessMLQ p) {
//	cout << "\n" << p.pid << "\t  " << p.priority << "\t  " << p.burst_time << "\t  " << p.waiting_time << "\t    " << p.turnaround_time << "\t            " << p.arrival_time;
//
//}
//void MLQ::CalWaitTime(ProcessMLQ* q, int size) {
//	q[0].waiting_time = 0;
//	for (int i = 1; i < size; i++) {
//		q[i].waiting_time = q[i - 1].waiting_time + q[i - 1].burst_time;
//	}
//}
//void MLQ::CalTATime(ProcessMLQ* q, int size) {
//	q[0].waiting_time = 0;
//	for (int i = 0; i < size; i++) {
//		q[i].turnaround_time = q[i].waiting_time + q[i].burst_time;
//	}
//}
//void MLQ::RRAlgo(ProcessMLQ* q, int size) {
//	int time = 0, i = 0, remain = size, flag = 0, wait_time = 0, tat_time = 0, total_times = 0;
//	for (time = 0, i = 0; remain != 0;) {
//		struct ProcessMLQ p = q[i];
//		if (p.remaining_time <= time_quantum && p.remaining_time > 0) {
//			time += p.remaining_time;
//			p.remaining_time = 0;
//			flag = 1;
//		}
//		else if (p.remaining_time > time_quantum) {
//			p.remaining_time -= time_quantum;
//			time += time_quantum;
//		}
//		if (p.remaining_time == 0 && flag == 1) {
//			remain--;
//			cout << "\n" << p.pid << " \t  " << p.priority << " \t " << p.burst_time << " \t      " << p.waiting_time << " \t  " << p.turnaround_time;
//
//
//			wait_time += time - p.arrival_time - p.burst_time;
//			tat_time += time - p.arrival_time;
//			flag = 0;
//		}
//
//		if (i == remain - 1) {
//			i = 0;
//		}
//		else if (q[i + 1].arrival_time < time) {
//			i++;
//		}
//		else {
//			i = 0;
//		}
//
//		q[i] = p;
//	}
//
//	//cout << "\nAverage Waiting Time= " << wait_time * 1.0 / n;
//	//cout << "\nAverage Turnaround Time= " << tat_time * 1.0 / n;
//}
//
//void MLQ::RR() {
//	cout << endl << endl;
//	cout << "\n\t\tRound Robin\t";
//	cout << endl;
//	cout << endl;
//
//	cout << " PId  Priority BurstTime  WaitTime TAroundTime";
//	cout << endl;
//	cout << endl;
//	CalWaitTime(q3, q3_n);
//	CalTATime(q3, q3_n);
//
//	RRAlgo(q3, q3_n);
//}
//void MLQ::PSAlgo(ProcessMLQ* q, int size) {
//	for (int i = 0; i < size; i++) {
//		for (int j = 0; j < size; j++) {
//			if (q[j].priority > q[i].priority) {
//				struct ProcessMLQ t = q[i];
//				q[i] = q[j];
//				q[j] = t;
//			}
//		}
//	}
//}
//void MLQ::PS() {
//	cout << endl << endl;
//	cout << "\n\t\tPriority Sorting\t";
//	cout << endl;
//	PSAlgo(q2, q2_n);
//	printQueue(q2, q2_n);
//}
//void MLQ::FCFSAlgo(struct ProcessMLQ* q, int size) {
//	for (int i = 0; i < size; i++) {
//		for (int j = 0; j < size; j++) {
//			if (q[j].arrival_time > q[i].arrival_time) {
//				struct ProcessMLQ t = q[i];
//				q[i] = q[j];
//				q[j] = t;
//			}
//		}
//	}
//}
//void MLQ::FCFS() {
//	cout << endl << endl;
//	cout << "\n\t\tFirst Come First Serve\t";
//	cout << endl;
//	FCFSAlgo(q1, q1_n);
//	printQueue(q1, q1_n);
//}
//int MLQ::getSize()
//{
//	return n;
//}
//bool MLQ::isEmpty()
//{
//	if (q1_n == 0 && q2_n == 0 && q3_n == 0)
//		return true;
//	else
//		return false;
//}
//void MLQMenu()
//{
//	MLQ* M = new MLQ();
//	int i = 1;
//	while (M->isEmpty() == false) {
//
//		if (i == 1) {
//			M->FCFS();
//		}
//		else if (i == 2) {
//			M->PS();
//		}
//		else if (i == 3) {
//			M->RR();
//		}
//		i++;
//	}
//	cout << "\n\n";
//}

// A multilevel feedback queue scheduler is defined by the following parameters:
// 1. Number of queues
// 2. Scheduling algorithms for each queue
// 3. Method used to determine when to upgrade a process
// 4. Method used to determine when to demote a process
// 5. Method used to determine which queue a process will enter
// 6. When that process needs service
// Write a program to implement multilevel feedback queue scheduling algorithm.
// The program should have three queues which will schedule the processes
// on the basis of their priority and time quantum. The program should
// also compute the waiting time, turnaround time and average waiting time
// and turnaround time. The program should be menu driven.
// The program should have following options:
// 1. Create a process
// 2. Display the process
// 3. Run the process
// 4. Exit

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// Process class
class ProcessMLFQ {

private:
    int id;
    int priority;
    int burstTime;
    int arrivalTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
public:
    ProcessMLFQ() {
        id = 0;
        priority = 0;
        burstTime = 0;
        arrivalTime = 0;
        remainingTime = 0;
        waitingTime = 0;
        turnaroundTime = 0;
        completionTime = 0;
    }
    ProcessMLFQ(int id, int priority, int burstTime, int arrivalTime) {
        this->id = id;
        this->priority = priority;
        this->burstTime = burstTime;
        this->arrivalTime = arrivalTime;
        this->remainingTime = burstTime;
        this->waitingTime = 0;
        this->turnaroundTime = 0;
        this->completionTime = 0;
    }

    int getId() {
        return id;
    }

    int getPriority() {
        return priority;
    }

    int getBurstTime() {
        return burstTime;
    }

    int getArrivalTime() {
        return arrivalTime;
    }

    int getRemainingTime() {
        return remainingTime;
    }

    int getWaitingTime() {
        return waitingTime;
    }

    int getTurnaroundTime() {
        return turnaroundTime;
    }

    void setRemainingTime(int remainingTime) {
        this->remainingTime = remainingTime;
    }

    void setWaitingTime(int waitingTime) {
        this->waitingTime = waitingTime;
    }

    void setTurnaroundTime(int turnaroundTime) {
        this->turnaroundTime = turnaroundTime;
    }

    void setCompletionTime(int completionTime) {
        this->completionTime = completionTime;
    }

    int getCompletionTime() {
        return completionTime;
    }

    void display() {
        cout << "Process " << id << ":\t" << "Priority: " << priority << "\tBurst Time: " << burstTime << "\tArrival Time: " << arrivalTime << endl;
    }
};

// ProcessQueue class
class ProcessQueue {

private:
    queue<ProcessMLFQ> processQueue;
    int quantum;
    int quantumCounter;
    int quantumCounterLimit;

public:
    ProcessQueue() {
        quantum = 0;
        quantumCounter = 0;
        quantumCounterLimit = 0;
    }
    ProcessQueue(int quantum) {
        this->quantum = quantum;
        this->quantumCounter = 0;
        this->quantumCounterLimit = quantum;
    }

    int getQuantum() {
        return quantum;
    }

    int getQuantumCounter() {
        return quantumCounter;
    }

    int getQuantumCounterLimit() {
        return quantumCounterLimit;
    }

    void setQuantumCounter(int quantumCounter) {
        this->quantumCounter = quantumCounter;
    }

    void setQuantumCounterLimit(int quantumCounterLimit) {
        this->quantumCounterLimit = quantumCounterLimit;
    }

    void enqueue(ProcessMLFQ process) {
        processQueue.push(process);
    }

    ProcessMLFQ dequeue() {
        ProcessMLFQ process = processQueue.front();
        processQueue.pop();
        return process;
    }

    bool isEmpty() {
        return processQueue.empty();
    }

    void display() {
        queue<ProcessMLFQ> tempQueue = processQueue;
        while (!tempQueue.empty()) {
            tempQueue.front().display();
            tempQueue.pop();
        }
    }
};

// MultilevelFeedbackQueue class
class MultilevelFeedbackQueue {

private:
    ProcessQueue* processQueues;
    int numberOfQueues;
    int numberOfProcesses;
    int timeQuantum;
    int timeQuantumCounter;
    int timeQuantumCounterLimit;
    int time;
    int totalWaitingTime;
    int totalTurnaroundTime;
    int* waitingTime;
    int* turnaroundTime;
    ProcessMLFQ* processes;

public:
    MultilevelFeedbackQueue(int numberOfQueues, int numberOfProcesses, int timeQuantum) {
        this->numberOfQueues = numberOfQueues;
        this->numberOfProcesses = numberOfProcesses;
        this->timeQuantum = timeQuantum;
        this->timeQuantumCounter = 0;
        this->timeQuantumCounterLimit = timeQuantum;
        this->time = 0;
        this->totalWaitingTime = 0;
        this->totalTurnaroundTime = 0;
        this->waitingTime = new int[numberOfProcesses];
        this->turnaroundTime = new int[numberOfProcesses];
        this->processes = new ProcessMLFQ[numberOfProcesses];
        this->processQueues = new ProcessQueue[numberOfQueues];
        for (int i = 0; i < numberOfQueues; i++) {
            processQueues[i] = ProcessQueue(timeQuantum);
        }
    }

    int getNumberOfQueues() {
        return numberOfQueues;
    }

    int getNumberOfProcesses() {
        return numberOfProcesses;
    }

    int getTimeQuantum() {
        return timeQuantum;
    }

    int getTimeQuantumCounter() {
        return timeQuantumCounter;
    }

    int getTimeQuantumCounterLimit() {
        return timeQuantumCounterLimit;
    }

    int getTime() {
        return time;
    }

    int getTotalWaitingTime() {
        return totalWaitingTime;
    }

    int getTotalTurnaroundTime() {
        return totalTurnaroundTime;
    }

    int* getWaitingTime() {
        return waitingTime;
    }

    int* getTurnaroundTime() {
        return turnaroundTime;
    }

    ProcessMLFQ* getProcesses() {
        return processes;
    }

    ProcessQueue* getProcessQueues() {
        return processQueues;
    }

    void setTimeQuantumCounter(int timeQuantumCounter) {
        this->timeQuantumCounter = timeQuantumCounter;
    }

    void setTimeQuantumCounterLimit(int timeQuantumCounterLimit) {
        this->timeQuantumCounterLimit = timeQuantumCounterLimit;
    }

    void setTime(int time) {
        this->time = time;
    }

    void setTotalWaitingTime(int totalWaitingTime) {
        this->totalWaitingTime = totalWaitingTime;
    }

    void setTotalTurnaroundTime(int totalTurnaroundTime) {
        this->totalTurnaroundTime = totalTurnaroundTime;
    }

    void setWaitingTime(int* waitingTime) {
        this->waitingTime = waitingTime;
    }

    void setTurnaroundTime(int* turnaroundTime) {
        this->turnaroundTime = turnaroundTime;
    }

    void setProcesses(ProcessMLFQ* processes) {
        this->processes = processes;
    }

    void setProcessQueues(ProcessQueue* processQueues) {
        this->processQueues = processQueues;
    }

    void addProcess(ProcessMLFQ process) {
        processQueues[0].enqueue(process);
    }

    void addProcesses(ProcessMLFQ* processes) {
        for (int i = 0; i < numberOfProcesses; i++) {
            addProcess(processes[i]);
        }
    }

    void display() {
        cout << "Multilevel Feedback Queue:" << endl;
        for (int i = 0; i < numberOfQueues; i++) {
            cout << "Queue " << i + 1 << ":" << endl;
            processQueues[i].display();
            cout << endl;
        }
    }

    void displayProcesses() {
        cout << "Processes:" << endl;
        for (int i = 0; i < numberOfProcesses; i++) {
            processes[i].display();
        }
        cout << endl;
    }

    void displayWaitingTime() {
        cout << "Waiting Time:" << endl;
        for (int i = 0; i < numberOfProcesses; i++) {
            cout << "Process " << processes[i].getId() << ": " << waitingTime[i] << endl;
        }
        cout << endl;
    }

    void displayTurnaroundTime() {
        cout << "Turnaround Time:" << endl;
        for (int i = 0; i < numberOfProcesses; i++) {
            cout << "Process " << processes[i].getId() << ": " << turnaroundTime[i] << endl;
        }
        cout << endl;
    }

    void displayAverageWaitingTime() {
        cout << "Average Waiting Time: " << (double)totalWaitingTime / numberOfProcesses << endl;
    }

    void displayAverageTurnaroundTime() {
        cout << "Average Turnaround Time: " << (double)totalTurnaroundTime / numberOfProcesses << endl;
    }

    void run() {
        int currentQueue = 0;
        while (true) {
            if (processQueues[currentQueue].isEmpty()) {
                currentQueue++;
                if (currentQueue == numberOfQueues) {
                    break;
                }
                continue;
            }
            ProcessMLFQ process = processQueues[currentQueue].dequeue();
            if (process.getArrivalTime() > time) {
                time = process.getArrivalTime();
            }
            if (process.getRemainingTime() <= timeQuantumCounterLimit) {
                time += process.getRemainingTime();
                process.setRemainingTime(0);
                process.setCompletionTime(time);
                processes[process.getId() - 1] = process;
                waitingTime[process.getId() - 1] = process.getCompletionTime() - process.getArrivalTime() - process.getBurstTime();
                turnaroundTime[process.getId() - 1] = process.getCompletionTime() - process.getArrivalTime();
                totalWaitingTime += waitingTime[process.getId() - 1];
                totalTurnaroundTime += turnaroundTime[process.getId() - 1];
                timeQuantumCounter = 0;
                if (currentQueue != 0) {
                    currentQueue--;
                }
            }
            else {
                time += timeQuantumCounterLimit;
                process.setRemainingTime(process.getRemainingTime() - timeQuantumCounterLimit);
                processQueues[currentQueue + 1].enqueue(process);
                timeQuantumCounter = 0;
                if (currentQueue != 0) {
                    currentQueue--;
                }
            }
        }
    }
};
void MLFQMenu()
{
    int numberOfProcesses;
    cout << "Enter number of processes: ";
    cin >> numberOfProcesses;
    ProcessMLFQ *processes=new ProcessMLFQ[numberOfProcesses];
    for (int i = 0; i < numberOfProcesses; i++) {
        int id, priority, arrivalTime, burstTime;
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> arrivalTime;
        cout << "Enter burst time of process " << i + 1 << ": ";
        cin >> burstTime;
        cout << "Enter priority of process " << i + 1 << ": ";
        cin >> priority;
        processes[i] = ProcessMLFQ(i + 1, priority, burstTime, arrivalTime);
    }
    int numberOfQueues;
    cout << "Enter number of queues: ";
    cin >> numberOfQueues;
    int timeQuantum;
    cout << "Enter time quantum: ";
    cin >> timeQuantum;
    MultilevelFeedbackQueue multilevelFeedbackQueue(numberOfProcesses, numberOfQueues, timeQuantum);
    multilevelFeedbackQueue.addProcesses(processes);
    multilevelFeedbackQueue.display();
    multilevelFeedbackQueue.run();
    multilevelFeedbackQueue.displayProcesses();
    multilevelFeedbackQueue.displayWaitingTime();
    multilevelFeedbackQueue.displayTurnaroundTime();
    multilevelFeedbackQueue.displayAverageWaitingTime();
    multilevelFeedbackQueue.displayAverageTurnaroundTime();
}
// Input: 
// Enter number of processes: 3
// Enter arrival time of process 1: 0
// Enter burst time of process 1: 5
// Enter arrival time of process 2: 1
// Enter burst time of process 2: 4
// Enter arrival time of process 3: 2
// Enter burst time of process 3: 3
// Enter number of queues: 3
// Enter time quantum: 2

// Output:
// Multilevel Feedback Queue:
// Queue 1:
// P1 0 5
// P2 1 4
// P3 2 3
// P4 3 2
// P5 4 1

// Queue 2:
// P1 0 5
// P2 1 4
// P3 2 3
// P4 3 2
// P5 4 1

// Queue 3:
// P1 0 5
// P2 1 4
// P3 2 3
// P4 3 2
// P5 4 1

// Processes:
// P1 0 5 5
// P2 1 4 4
// P3 2 3 3
// P4 3 2 2
// P5 4 1 1

// Waiting Time:
// Process 1: 0
// Process 2: 0
// Process 3: 0
// Process 4: 0
// Process 5: 0

// Turnaround Time:
// Process 1: 5
// Process 2: 4
// Process 3: 3
// Process 4: 2
// Process 5: 1

// Average Waiting Time: 0
// Average Turnaround Time: 3
// Gantt Chart:
// P1 P2 P3 P4 P5
// 0 1 2 3 4
// 5


int main()
{
	LJBMenu();

	return 0;
}





