// ask the tie breaking condition
// equal ke case mai kya kre
#include <iostream>
#include <vector>
#include <cmath>   // for abs()
#include <climits> // for INT_MAX

using namespace std;

// Function to find the index of the nearest request (with tie-breaking)
int findNearestRequest(vector<int> &requests, vector<bool> &visited, int current_head)
{
  int min_distance = INT_MAX;
  int index = -1;
  for (int i = 0; i < requests.size(); i++)
  {
    if (!visited[i])
    {
      int distance = abs(current_head - requests[i]);
      if (distance < min_distance)
      {
        min_distance = distance;
        index = i;
      }
      else if (distance == min_distance)
      {
        // Tie-breaker: pick the smaller track number
        if (requests[i] < requests[index])
        {
          index = i;
        }
      }
    }
  }
  return index;
}

int main()
{
  int n, current_head;
  cout << "Enter the number of requests: ";
  cin >> n;

  vector<int> requests(n);
  vector<bool> visited(n, false); // To track served requests

  cout << "Enter the request queue (space-separated): ";
  for (int i = 0; i < n; i++)
  {
    cin >> requests[i];
  }

  cout << "Enter the current head position: ";
  cin >> current_head;

  int total_movement = 0;
  int position = current_head;

  for (int i = 0; i < n; i++)
  {
    int nearest = findNearestRequest(requests, visited, position);
    total_movement += abs(position - requests[nearest]);
    position = requests[nearest];
    visited[nearest] = true;
  }

  cout << "\nTotal head movement: " << total_movement << " cylinders" << endl;

  return 0;
}
