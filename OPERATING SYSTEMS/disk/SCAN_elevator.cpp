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

  cout << "Enter the maximum disk size (for example 199): ";
  cin >> disk_size;

  cout << "Enter direction (up for higher values / down for lower values): ";
  cin >> direction;

  // Add current head to the request queue
  requests.push_back(current_head);

  // Sort all requests
  sort(requests.begin(), requests.end());

  int total_movement = 0;
  int head_index = -1;

  // Find the index of current head
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
    // Then move to the highest end
    total_movement += (disk_size - requests.back());
    // Reverse direction: move from highest end to the lowest pending request
    total_movement += (disk_size - requests[0]);
  }
  else if (direction == "down")
  {
    // Move towards lower values first
    for (int i = head_index; i > 0; i--)
    {
      total_movement += abs(requests[i] - requests[i - 1]);
    }
    // Then move to the start (0)
    total_movement += requests[0];
    // Reverse direction: move from start to the highest pending request
    total_movement += requests.back();
  }
  else
  {
    cout << "Invalid direction entered!" << endl;
    return 1;
  }

  cout << "\nTotal head movement: " << total_movement << " cylinders" << endl;

  return 0;
}
