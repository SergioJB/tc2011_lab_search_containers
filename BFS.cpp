#include <iostream>
#include <string> // Gain access to std::string
#include <cstring>
#include <cstdlib>

#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <utility>

/*
	BFS -> frontier = queue
*/

using namespace std; // std:: is implied.

struct node{
	//initial = [[a], [b], [c]]; goal = [[a, b], [x], [x]];
	std::vector<stack <char> > state;

	struct node *parent;

	//0 = (0,1); 1 = (0,2); 2 = (1,0); 
	//3 = (1,2); 4 = (2,0); 5 = (2, 1);
	std::pair<int,int>  action; 

	int pathCost;	
};

int isGoal(struct node actual, vector<vector <char> > &goal)
{
	int i, j;
	int res = 1;

	for(i = 0; i < goal.size(); i++)
	{
		if(goal[i][0] != 'X')
		{
			for(j = 0; j < goal[i].size(); j++)
			{
				if(goal[i][j] != actual.state[i].top())
				{
					return 0;
				}
				actual.state[i].pop();
			}
		}
	}
	cout << "Goal" << endl;
	return res;
}

int expandNode(struct node **child, struct node *parent, pair<int,int> action, int limit)
{	
	char aux;

	cout << "expand node" << endl;
	//Only expand valid nodes
	if( !(parent->state[action.first].empty()) && (parent->state[action.second].size() < limit))
	{
		cout << "valid" << endl;		
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
	//resultState.pathCost = parent->pathCost + 1;
}

int main(int arg, char** argv)
{
	char box;
	int fin = 0;
	int i, j, maxHeight;

	vector<char>temp;

	stack<char>temp2;
	vector<vector <char> > goalState;
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
		temp2.push(box);
		root->state.push_back(temp2);
		temp2.pop();

		cin >> box; 
		temp2.push(box);
		root->state.push_back(temp2);
		temp2.pop();

		cin >> box; 
		temp2.push(box);
		root->state.push_back(temp2);
		temp2.pop();

		root->parent = NULL;
		root->pathCost = 0;
	}

	//Read to specify goal state
	cin >> box; 
	temp.push_back(box);
	goalState.push_back(temp);
	temp.clear();

	cin >> box; 
	temp.push_back(box);
	goalState.push_back(temp);
	temp.clear();

	cin >> box; 
	temp.push_back(box);
	goalState.push_back(temp);
	temp.clear();

	isGoal(*root, goalState);

	//Step 1: Initialize the frontier using the initial state
	frontier.push(root);
	cout << "Frontier size: " << frontier.size() << endl;

	//Step 2: Initialize the exprored set to be empty
	explored.clear();
	cout << "Explored size: " << explored.size() << endl;

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

		cout << actualNode->action.first << endl;
		cout << actualNode->action.second << endl;
		
		//Success if is the goal
		//fin = isGoal(actualNode, goalState);

		//Add the node to the explored set
		explored.insert(actualNode);

		//Expand the node 
		for(i = 0; i < 3; i++)
		{
			for(j = 0; j < 3; j++)
			{
				if(i != j)		
				{				
					action = make_pair(i, j); 					
					if(expandNode(&childNode, actualNode, action, maxHeight) == 1)
					{
						//Add the resulting nodes to frontier
						//Only if they are not in frontier or explored*/
						cout << "action: (" << action.first << "," << action.second << ")" << endl;
						
						it = explored.find(childNode);
						if(it == explored.end())		//FALTA VERIFICAR SI NO ESTA EN FRONTIER... pero COMO?
						{
							//Success if is the goal
							cout << "Goal?";
							fin = isGoal(*childNode, goalState);
							cout << fin << endl;
							if(fin == 1)
							{
								return 1;
							}

							frontier.push(childNode);
						}
						
					}
				}
			}
		}
	}while(frontier.size() > 0 && fin == 0);

	return 0;
}
