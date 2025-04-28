#include <iostream>
#include <vector>
#include <algorithm> // for sort()
#include <cmath>     // for abs()

using namespace std;

int main()
{
  int n, current_head, disk_size;
  string direction;

  cout << "Enter the number of requests: ";
  cin >> n;

  vector<int> requests(n);
  cout << "Enter the request queue (space-separated): ";
  for (int i = 0; i < n; i++)
  {
    cin >> requests[i];
  }

  cout << "Enter the current head position: ";
  cin >> current_head;

  cout << "Enter the disk size (maximum cylinder number): ";
  cin >> disk_size;

  cout << "Enter direction (up for higher values / down for lower values): ";
  cin >> direction;

  // Add current head to request list
  requests.push_back(current_head);

  // Sort the requests
  sort(requests.begin(), requests.end());

  int total_movement = 0;
  int head_index = -1;

  // Find the index of the current head
  for (int i = 0; i < requests.size(); i++)
  {
    if (requests[i] == current_head)
    {
      head_index = i;
      break;
    }
  }

  if (direction == "up")
  {
    // Move towards higher values first
    for (int i = head_index; i < requests.size() - 1; i++)
    {
      total_movement += abs(requests[i + 1] - requests[i]);
    }
    // Move from last request to end of disk
    total_movement += abs((disk_size - 1) - requests.back());
    // Jump from end to start (circular move)
    total_movement += abs((disk_size - 1) - 0);
    // Then move from start (0) to lowest pending request
    for (int i = 0; i < head_index; i++)
    {
      if (i == 0)
        total_movement += abs(requests[i] - 0);
      else
        total_movement += abs(requests[i] - requests[i - 1]);
    }
  }
  else if (direction == "down")
  {
    // Move towards lower values first
    for (int i = head_index; i > 0; i--)
    {
      total_movement += abs(requests[i] - requests[i - 1]);
    }
    // Move from lowest request to start (0)
    total_movement += abs(requests[0] - 0);
    // Jump from start (0) to end of disk
    total_movement += abs((disk_size - 1) - 0);
    // Then move from end to highest pending request
    for (int i = requests.size() - 1; i > head_index; i--)
    {
      if (i == requests.size() - 1)
        total_movement += abs((disk_size - 1) - requests[i]);
      else
        total_movement += abs(requests[i + 1] - requests[i]);
    }
  }
  else
  {
    cout << "Invalid direction entered!" << endl;
    return 1;
  }

  cout << "\nTotal head movement: " << total_movement << " cylinders" << endl;

  return 0;
}
