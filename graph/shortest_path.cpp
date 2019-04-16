
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

template <typename T>
class Node
{
private:
	vector<int> connections;
public:
	T data;
	Node(T data)
	{
		this->data = data;
	}
	void addConnection(int index)
	{
		connections.push_back(index);
	}
	int getSize()
	{
		return connections.size();
	}
	int &operator[] (int);
};

template <typename T>
int &Node<T>::operator[](int index)
{
	if (index >= this->connections.size())
	{
		cout << "Array index out of bound, exiting" << endl;
		exit(0);
	}
	return this->connections[index];
}

template <typename T>
class NodeGraph
{
private:
	vector<bool> isVisited;
	vector<Node<T>> arr;
public:
	void insertData(T data)
	{
		Node<T> n(data);
		arr.push_back(n);
		isVisited.push_back(false);
	}
	T &operator[] (int);
	void setVisited(int);
	void addEdge(int, int);
	void display();
	int getDistance(int, int);
};
template <typename T>
T &NodeGraph<T>::operator[](int i)
{
	return this->arr[i];
}
template <typename T>
void NodeGraph<T>::setVisited(int i)
{
	if (i >= this->isVisited.size())
		cout << "Array Index out of bond for visiting" << endl;
	this->isVisited[i] = true;
}

template <typename T>
void NodeGraph<T>::addEdge(int from, int to)
{
	this->arr[from].addConnection(to);
	this->arr[to].addConnection(from);
}

template <typename T>
void NodeGraph<T>::display()
{
	for (int i = 0; i < this->arr.size(); i++) {
		cout << (i+1) << " ";
		string ans = (string)this->arr[i].data;
		cout << ans << " ";
		for (int j = 0; j < this->arr[i].getSize(); j++)
		{
			cout << (this->arr[i][j] +1) << " ";
		}
		cout << endl;
	}
}

template <typename T>
int NodeGraph<T>::getDistance(int from, int to)
{
	int size = this->arr.size();
	for (int i = 0; i < size; i++)
		this->isVisited[i] = false;
	int que = 1;
	int distance = 0;
	queue<int> indexes[2];
	int qn = 0, fn = 1;
	indexes[qn].push(from);
	this->isVisited[from] = true;
	while (!indexes[0].empty() || !indexes[1].empty())
	{
		int index = indexes[qn].front();
		indexes[qn].pop();
		for (int i = 0; i < this->arr[index].getSize(); i++)
			if (!this->isVisited[arr[index][i]])
			{
				indexes[fn].push(this->arr[index][i]);
				this->isVisited[this->arr[index][i]] = true;
				if (this->arr[index][i] == to)
					return distance + 1;
			}
		if (indexes[qn].empty())
		{
			int temp = qn;
			qn = fn;
			fn = temp;
			distance++;
		}
	}
	return -1;
}

int main()
{
    NodeGraph<string> graph;

	int edges, nodes;
	cin >> edges; // Enter no of edges
	cin >> nodes; // Enter no of nodes
	for (int i = 0; i < nodes; i++)
		graph.insertData("sam" + to_string(i+1)); // generate random data (string) data type example given here could be any other datatype
	for (int i = 0; i < edges; i++)
	{
		int temp1, temp2;
		cin >> temp1 >> temp2;
		graph.addEdge(temp1 - 1, temp2 - 1); //converting input to index and adding an edge between them
	}
	graph.display(); // Display data in the graph
	int queries;
	cin >> queries; // Number of queries for distance
	for (int i = 0; i < queries; i++)
	{
		int from, to;
		cin >> from >> to;
		cout << graph.getDistance(from - 1, to - 1);
	}
	cin >> edges;
}
