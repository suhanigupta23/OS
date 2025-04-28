#include <iostream>
#include <vector>
#include <cmath> // for abs()

using namespace std;

int main()
{
  int n, current_head;
  cout << "Enter the number of requests: ";
  cin >> n;

  vector<int> request_queue(n);

  cout << "Enter the request queue (space-separated): ";
  for (int i = 0; i < n; i++)
  {
    cin >> request_queue[i];
  }

  cout << "Enter the current head position: ";
  cin >> current_head;

  int total_movement = 0;
  int position = current_head;

  // Process requests in order
  for (int i = 0; i < n; i++)
  {
    total_movement += abs(request_queue[i] - position);
    position = request_queue[i];
  }

  cout << "\nTotal head movement: " << total_movement << " cylinders" << endl;

  return 0;
}
