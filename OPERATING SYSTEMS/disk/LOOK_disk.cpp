#include <iostream>
#include <vector>
#include <algorithm> // for sort()
#include <cmath>     // for abs()

using namespace std;

int main()
{
  int n, current_head;
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

  cout << "Enter direction (up for higher values / down for lower values): ";
  cin >> direction;

  // Add current head to the request list
  requests.push_back(current_head);

  // Sort the requests
  sort(requests.begin(), requests.end());

  int total_movement = 0;
  int head_index = -1;

  // Find the index of the current head in the sorted array
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
    // After reaching the highest request, move to the lowest pending one
    for (int i = head_index - 1; i >= 0; i--)
    {
      if (i == head_index - 1)
        total_movement += abs(requests.back() - requests[i]);
      else
        total_movement += abs(requests[i + 1] - requests[i]);
    }
  }
  else if (direction == "down")
  {
    // Move towards lower values first
    for (int i = head_index; i > 0; i--)
    {
      total_movement += abs(requests[i] - requests[i - 1]);
    }
    // After reaching the lowest request, move to the highest pending one
    for (int i = head_index + 1; i < requests.size(); i++)
    {
      if (i == head_index + 1)
        total_movement += abs(requests[0] - requests[i]);
      else
        total_movement += abs(requests[i] - requests[i - 1]);
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
