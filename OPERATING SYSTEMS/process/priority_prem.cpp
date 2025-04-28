#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Process
{
  int id;
  int arrivaltime;
  int bursttime;
  int priority;
  int waitingtime;
  int turnaroundtime;
  int remainingtime;
  int completiontime;
  int responsetime;
};

void calculatetimes(vector<Process> &processes, int n)
{
  int completed = 0;
  int curtime = 0;
  vector<bool> iscompleted(n, false);
  vector<bool> isstarted(n, false);
  while (completed != n)
  {
    int maxpriority = INT_MAX;
    int min_index = -1;
    for (int i = 0; i < n; i++)
    {
      if (!iscompleted[i] && processes[i].arrivaltime <= curtime)
      {
        if (processes[i].priority <maxpriority || (processes[i].priority == maxpriority && processes[i].arrivaltime < processes[min_index].arrivaltime))
        {
          maxpriority = processes[i].priority;
          min_index = i;
        }
      }
    }
    if (min_index == -1)
    {
      curtime++;
    }
    else
    {
      if (!isstarted[min_index]) // ✅ Set Response Time when process starts for the first time
      {
        processes[min_index].responsetime = curtime - processes[min_index].arrivaltime;
        isstarted[min_index] = true;
      }
      processes[min_index].remainingtime--;
      curtime++;
      if (processes[min_index].remainingtime == 0)
      {
        processes[min_index].completiontime = curtime;
        processes[min_index].turnaroundtime = processes[min_index].completiontime - processes[min_index].arrivaltime;
        processes[min_index].waitingtime = processes[min_index].turnaroundtime - processes[min_index].bursttime;
        iscompleted[min_index] = true;
        completed++;
      }
    }
  }
}
int main()
{
  int n;
  cout << "enter the number of processes" << endl;
  cin >> n;
  vector<Process> processes(n);
  for (int i = 0; i < n; i++)
  {
    processes[i].id = i + 1;
    cout << "enter the arrival time,burst time and priority of" << i + 1 << endl;
    cin >> processes[i].arrivaltime >> processes[i].bursttime >> processes[i].priority;
    processes[i].remainingtime = processes[i].bursttime;
  }
  calculatetimes(processes, n);

  cout << "\nProcess\tAT\tBT\tP\tCT\tTAT\tWT\tRT\n";
  for (const auto &p : processes)
  {
    cout << p.id << "\t" << p.arrivaltime << "\t" << p.bursttime << "\t" << p.priority << "\t"
         << p.completiontime << "\t" << p.turnaroundtime << "\t" << p.waitingtime << "\t" << p.responsetime << endl;
  }
  int total_turnaround = 0;
  int total_waiting = 0;
  for (const auto &p : processes)
  {
    total_turnaround += p.turnaroundtime;
    total_waiting += p.waitingtime;
  }
  double avg_turnaround = total_turnaround / n;
  double avg_waiting = total_waiting / n;
  cout << "avg turnaround is:" << avg_turnaround << endl;
  cout << "avg waiting time is:" << avg_waiting << endl;

  return 0;
}