#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <list>
#include <utility>

/*
	BFS -> frontier = queue
*/

using namespace std; // std:: is implied.

struct node{
	//initial = [[a], [b], [c]]; goal = [[b, a], [x], [x]];   **bottom to top
	std::vector<stack <char> > state;

	struct node *parent;

	//0 = (0,1); 1 = (0,2); 2 = (1,0); 
	//3 = (1,2); 4 = (2,0); 5 = (2, 1);
	std::pair<int,int>  action;
};

int isGoal(vector<stack <char> > actual, vector<stack <char> > goal)
{
	int i, j;
	int res = 1;

	for(i = 0; i < goal.size(); i++)
	{
		if(actual[i].size() != goal[i].size())
		{			
			return 0;				
		}
		while( goal[i].size() > 0)
		{
			if(goal[i].top() != 'X')
			{			
				if(actual[i].top() != goal[i].top())
				{
					return 0;
				}

				actual[i].pop();
				goal[i].pop();
			}
			else
			{
				goal[i].pop();
			}
		}
	}
	return res;
}

int expandNode(struct node **child, struct node *parent, pair<int,int> action, int limit)
{	
	char aux;

	//Only expand valid nodes
	if( !(parent->state[action.first].empty()) && (parent->state[action.second].size() < limit))
	{		
		(*child) = new node;

		(*child)->parent = parent;
		(*child)->state = parent->state;
		(*child)->action = action;

		//Adding element to new continer
		aux = (*child)->state[action.first].top();
		(*child)->state[action.second].push( aux );

		//Removing element from origin container
		(*child)->state[action.first].pop();

		return 1;
	}
	return 0;

}

int main(int arg, char** argv)
{
	char box;
	int fin = 0;
	int i, j, maxHeight;

	stack<char>temp;
	vector<stack <char> > goalState;
	stack<pair <int, int> > solution;
	pair<int,int>  action;

	queue <struct node *> frontier;
	set <struct node *> explored;
	set<struct node *>::iterator it;
	
	struct node *root = new node;
	struct node *actualNode = new node;
	struct node *childNode = new node;

	cin >> maxHeight; 

	//Read to specify initial state
	if(root != NULL){
		cin >> box; 
		temp.push(box);
		cin >> box; 
		temp.push(box);
		root->state.push_back(temp);
		temp.pop();
		temp.pop();

		cin >> box; 
		temp.push(box);
		root->state.push_back(temp);
		temp.pop();

		cin >> box; 
		temp.push(box);
		root->state.push_back(temp);
		temp.pop();

		root->parent = NULL;
	}

	//Read to specify goal state
	cin >> box; 
	temp.push(box);
	cin >> box; 
	temp.push(box);
	goalState.push_back(temp);
	temp.pop();
	temp.pop();

	cin >> box; 
	temp.push(box);
	goalState.push_back(temp);
	temp.pop();

	cin >> box; 
	temp.push(box);
	goalState.push_back(temp);
	temp.pop();

	isGoal(root->state, goalState);

	//Step 1: Initialize the frontier using the initial state
	frontier.push(root);

	//Step 2: Initialize the exprored set to be empty
	explored.clear();
	do{
		//Failure if the frontier is empty
		if(frontier.empty())
		{
			cout << "Frontier empty" << endl;
			return -1;			
		}

		//Remove leaf node from frontier
		actualNode = frontier.front();
		frontier.pop();
		
		//Add the node to the explored set
		explored.insert(actualNode);

		//Expand the node 
		for(i = 0; i < goalState.size(); i++)
		{
			for(j = 0; j < goalState.size(); j++)
			{
				if(i != j)		
				{				
					action = make_pair(i, j); 					
					if(expandNode(&childNode, actualNode, action, maxHeight) == 1)
					{
						//Add the resulting nodes to frontier
						//Only if they are not in frontier or explored*/

						it = explored.find(childNode);
						if(it == explored.end())
						{
							//Success if is the goal
							fin = isGoal(childNode->state, goalState);
							
							if(fin == 1)
							{
								actualNode = childNode;
								while(actualNode->parent != NULL)
								{
									solution.push(actualNode->action);
									actualNode = actualNode->parent;
								}

								while(!(solution.empty()) )
								{
									cout << "(" << solution.top().first << "," << solution.top().second << ")  " << endl;
									solution.pop();
								}
								return 1;
							}
							frontier.push(childNode);
						}
					}
				}
			}
		}
	}while(frontier.size() > 0 && fin == 0);

	cout << "No solution found" << endl;

	return 0;
}
