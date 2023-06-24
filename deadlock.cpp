#include <iostream>
#include <string>

using namespace std;

// Function prototypes
void printMatrices(int, int, int[][10], int[][10], int[][10], int[]);
void printSafeSequence(int, int, int[]);
bool safetyAlgorithm(int, int, int[][10], int[][10], int[], int[]);
bool resourceRequestAlgorithm(int, int, int[][10], int[][10], int[], int[], int[]);
bool checkIfSafe(int, int, int[][10], int[][10], int[], bool[], int);

int main()
{
    int numProcesses, numResources;
    int available[10], maximum[10][10], allocation[10][10], need[10][10];
    int request[10];
    int safeSequence[10];
    bool safe = false;
    bool requestGranted = false;
    
    // Get number of processes and resources
    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    cout << "Enter the number of resources: ";
    cin >> numResources;
    
    // Get available resources
    cout << "Enter the available resources: ";
    for (int i = 0; i < numResources; i++)
    {
        cin >> available[i];
    }
    
    // Get maximum resources
    cout << "Enter the maximum resources: ";
    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numResources; j++)
        {
            cin >> maximum[i][j];
        }
    }
    
    // Get allocation resources
    cout << "Enter the allocation resources: ";
    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numResources; j++)
        {
            cin >> allocation[i][j];
        }
    }
    
    // Calculate need matrix
    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numResources; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
    
    // Print matrices
    printMatrices(numProcesses, numResources, maximum, allocation, need, available);
    
    // Run safety algorithm
    safe = safetyAlgorithm(numProcesses, numResources, maximum, allocation, available, safeSequence);
    
    // Print safe sequence
    if (safe)
    {
        printSafeSequence(numProcesses, numResources, safeSequence);
    }
    else
    {
        cout << "The system is not in a safe state." << endl;
    }
    
    // Get request
    cout << "Enter the process requesting resources: ";
    int process;
    cin >> process;
    cout << "Enter the request: ";
    for (int i = 0; i < numResources; i++)
    {
        cin >> request[i];
    }

    // Run resource request algorithm
    requestGranted = resourceRequestAlgorithm(numProcesses, numResources, maximum, allocation, available, request, safeSequence);

    // Print safe sequence
    if (requestGranted)
    {
        printSafeSequence(numProcesses, numResources, safeSequence);
    }
    else
    {
        cout << "The request cannot be granted." << endl;
    }

    return 0;
}

// Function to print matrices
void printMatrices(int numProcesses, int numResources, int maximum[][10], int allocation[][10], int need[][10], int available[])
{
    // Print maximum matrix
    cout << "Maximum Matrix" << endl;
    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numResources; j++)
        {
            cout << maximum[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    // Print allocation matrix
    cout << "Allocation Matrix" << endl;
    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numResources; j++)
        {
            cout << allocation[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    // Print need matrix
    cout << "Need Matrix" << endl;
    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numResources; j++)
        {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    // Print available matrix
    cout << "Available Matrix" << endl;
    for (int i = 0; i < numResources; i++)
    {
        cout << available[i] << " ";
    }
    cout << endl << endl;
}

// Function to print safe sequence
void printSafeSequence(int numProcesses, int numResources, int safeSequence[])
{
    cout << "Safe Sequence: ";
    for (int i = 0; i < numProcesses; i++)
    {
        cout << safeSequence[i] << " ";
    }
    cout << endl << endl;
}

// Function to run safety algorithm
bool safetyAlgorithm(int numProcesses, int numResources, int maximum[][10], int allocation[][10], int available[], int safeSequence[])
{
    int work[10];
    bool finish[10];
    int count = 0;
    
    // Initialize work and finish
    for (int i = 0; i < numResources; i++)
    {
        work[i] = available[i];
    }
    for (int i = 0; i < numProcesses; i++)
    {
        finish[i] = false;
    }
    
    // Loop until all processes are finished
    while (count < numProcesses)
    {
        bool found = false;
        
        // Loop through processes
        for (int i = 0; i < numProcesses; i++)
        {
            // Check if process is finished
            if (!finish[i])
            {
                // Check if process can be completed
                if (checkIfSafe(numProcesses, numResources, maximum, allocation, work, finish, i))
                {
                    // Add process to safe sequence
                    safeSequence[count] = i;
                    count++;
                    
                    // Update work
                    for (int j = 0; j < numResources; j++)
                    {
                        work[j] += allocation[i][j];
                    }
                    
                    // Update finish
                    finish[i] = true;
                    
                    // Set found to true
                    found = true;
                }
            }
        }
        
        // Check if no process was found
        if (!found)
        {
            return false;
        }
    }
    
    return true;
}

// Function to check if process can be completed
bool checkIfSafe(int numProcesses, int numResources, int maximum[][10], int allocation[][10], int work[], bool finish[], int process)
{
    // Loop through resources
    for (int i = 0; i < numResources; i++)
    {
        // Check if process can be completed
        if (maximum[process][i] - allocation[process][i] > work[i])
        {
            return false;
        }
    }
    
    return true;
}

// Function to run resource request algorithm
bool resourceRequestAlgorithm(int numProcesses, int numResources, int maximum[][10], int allocation[][10], int available[], int request[], int safeSequence[])
{
    int work[10];
    bool finish[10];
    int count = 0;
    
    // Initialize work and finish
    for (int i = 0; i < numResources; i++)
    {
        work[i] = available[i];
    }
    for (int i = 0; i < numProcesses; i++)
    {
        finish[i] = false;
    }
    
    // Loop until all processes are finished
    while (count < numProcesses)
    {
        bool found = false;
        
        // Loop through processes
        for (int i = 0; i < numProcesses; i++)
        {
            // Check if process is finished
            if (!finish[i])
            {
                // Check if process can be completed
                if (checkIfSafe(numProcesses, numResources, maximum, allocation, work, finish, i))
                {
                    // Add process to safe sequence
                    safeSequence[count] = i;
                    count++;
                    
                    // Update work
                    for (int j = 0; j < numResources; j++)
                    {
                        work[j] += allocation[i][j];
                    }
                    
                    // Update finish
                    finish[i] = true;
                    
                    // Set found to true
                    found = true;
                }
            }
        }
        
        // Check if no process was found
        if (!found)
        {
            return false;
        }
    }
    
    return true;
}

// Input:

// 5 3
// 3 3 2
// 7 5 3
// 3 2 2
// 9 0 2
// 2 2 2
// 4 3 3
// 0 1 0
// 2 0 0
// 3 0 2
// 2 1 1
// 0 0 2

// Output:

// Maximum Matrix
// 7 5 3
// 3 2 2
// 9 0 2
// 2 2 2
// 4 3 3

// Allocation Matrix
// 0 1 0
// 2 0 0
// 3 0 2
// 2 1 1
// 0 0 2

// Need Matrix
// 7 4 3
// 1 2 2
// 6 0 0
// 0 1 1
// 4 3 1

// Available Matrix
// 3 3 2

// Safe Sequence: 1 3 4 0 2

// Process 2 requests 2 0 2


