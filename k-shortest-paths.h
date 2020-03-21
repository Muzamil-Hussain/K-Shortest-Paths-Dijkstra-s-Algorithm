/*
	Overview: Dijkstra's shortest path algorithm has been used to find the shortest path
				  and for second shortest path Yen's algorithm has been used in the assignment
				  which is also the modification of Dijkstra's algorithm. 
				  For Dijkstra set class has been used to keep track of the repeatation of
				  Nodes/vertices. Second, min heap has been used to get minimum out of all
				  vertices. Third, adjacency list is created from the GraphData.csv and the	
				  adjacency list is two-dimensional doubly link list, which saves memory 
				  as well as time and also saves time of shifting when removed from middle, as 
				  nodes can be deleted from middle too. The initial work, i.e. reading from file 
				  and making graph/adjacency list is done in the function named general().
				  Moreover, the user interface, the calculation of shortest path and second 
				  shortest path has been calculated in the class graph. Also, the final 
				  paths are stored in the three-dimensional linked list and looped out 
				  to find the second shortest of all at a time in Yen's algorithm.
				  Finally, the requirement of templatizing the code has been kept on the 
				  priority thourgh out the code.

*/

#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;
template<typename T, typename U>
class sNodeData;
template<typename T, typename U>
class pNodeData;


/*
Implementation of set.
It will be used in Dijkstra to prevent repeatation of vertices.
 */
template<class T>
class Set {
private:
	T *arr;
	int size;
	int currentPosition;
public:
	// default constructor
	Set<T>() {
		arr = NULL;
		size = 0;
		currentPosition = 0;
	}
	// parameterized constructor by the default size of 100
	Set<T>(int size = 100) {
		if (size == 0) {
			size = size + 1;
		}
		arr = new T[size];
		for (int i = 0; i < size; i++) {
			arr[i] = "\0";
		}
		this->size = size;
		currentPosition = 0;
	}
	// function to check whether the set is empty or not
	bool isEmpty() {
		if (currentPosition == 0) {
			return true;
		}
		return false;
	}
	/* function for adding the new item in the set.
	   The set in Dijkstra's algorithm is made size specfic 
	   and because of it, it never reaches the limit and 
	   it keeps the code safe from shifting the elements 
	   of set.
	*/
	void addItem(T item) {
		if (currentPosition == size) {

			T *tempArr = new T[size];
			for (int i = 0; i < size; i++) {
				tempArr[i] = arr[i];
			}
			delete[] arr;
			arr = new T[size * 2];
			for (int i = 0; i < size; i++) {
				arr[i] = tempArr[i];
			}
			delete[] tempArr;
			arr[currentPosition] = item;
			currentPosition++;
			size = size * 2;
		} else {
			arr[currentPosition] = item;
			currentPosition++;
		}
	}
	// function used in Dijkstra to get to know about the presence of the element in the set
	bool isAlreadyInSet(T item) {
		if (!isEmpty()) {
			for (int i = 0; i < currentPosition; i++) {
				if (arr[i] == item) {
					return true;
				}
			}
		}
		return false;
	}
	// returns current size of the set
	int getSize() const {
		return size;
	}

	int getCurrentPosition() const {
		return currentPosition;
	}
	void ascendingOrder() {
		for (int i = 0; i < currentPosition; i++) {
			for (int j = 0; j < currentPosition; j++) {
				if (arr[i] < arr[j]) {
					T temp;
					temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}
	}
	// function to print the set and has been used while testing
	void Print() {
		for (int i = 0; i < currentPosition; i++) {
			cout << arr[i] << " ";
		}
	}
};

/*
Implementation of min heap which has been used in Dijkstra's algorithm
to find shortest path.
*/

template<typename T, typename U>
class minHeap {
private:
	int heapSize;
	T *data;
	U *names;
	int currentSize;
public:
	//constructor
	minHeap(int capacity) {
		heapSize = capacity + 1;
		data = new T[capacity + 1];
		names = new U[capacity + 1];
		currentSize = 1;
	}
	// function to if the heap is empty or not
	bool isEmpty() {
		if (currentSize == 1)
			return true;
		return false;
	}
	// return parent 
	int getParent(int index) {
		return floor(static_cast<double>(index / 2));
	}
	// returns right child 
	int getRightChild(int index) {
		return (2 * index) + 1;
	}
	// returns left child
	int getLeftChild(int index) {
		return 2 * index;
	}
	// inserts key while following the rules of insertion if the min heap
	void insertKey(T key, U city) {
		data[currentSize] = key;
		names[currentSize] = city;
		currentSize++;

		int i = currentSize - 1;
		while (i != 1 && data[getParent(i)] > data[i]) {
			// swapping keys
			T tempData = data[i];
			data[i] = data[getParent(i)];
			data[getParent(i)] = tempData;

			//swapping names wrt to keys
			U tempName = names[i];
			names[i] = names[getParent(i)];
			names[getParent(i)] = tempName;

			i = getParent(i);
		}
	}
	// function to assist the main function used for deletion of min value
	void deleteMinInnerProcess(int minIndex) {

		int left = getLeftChild(minIndex);
		int right = getRightChild(minIndex);
		int smallestValue = minIndex;

		if (left < currentSize && data[left] < data[minIndex]) {
			smallestValue = left;
		}
		if (right < currentSize && data[right] < data[smallestValue]) {
			smallestValue = right;
		}
		if (smallestValue != minIndex) {
			T tempData = data[minIndex];
			data[minIndex] = data[smallestValue];
			data[smallestValue] = tempData;

			U tempName = names[minIndex];
			names[minIndex] = names[smallestValue];
			names[smallestValue] = tempName;

			deleteMinInnerProcess(smallestValue);
		}
	}
	// function to delete the min value
	U deleteMin(T &minValue) {
		if (currentSize != 1) {
			if (currentSize == 2) {
				currentSize--;
				minValue = data[1];
				return names[currentSize];
			} else {
				U storeReturnValue = names[1];
				minValue = data[1];
				currentSize--;
				data[1] = data[currentSize];
				names[1] = names[currentSize];
				deleteMinInnerProcess(1);
				return storeReturnValue;
			}
		} else
			cout << "\nHeap is empty!\n";
	}
	// return min value which will always be on the first index
	U getMin() {
		if (currentSize != 1) {
			return names[1];
		} else {
			cout << "Heap is Empty\n";
		}
	}
	// returns the distance of given city
	T getDistance(U cityName, int &cityIndex) {
		//searching for distance of given city
		for (int i = 1; i < currentSize; i++) {
			if (names[i].compare(cityName) == 0) {
				cityIndex = i;
				return data[i];
			}
		}
	}
	// sets the distance of given index
	void setDistance(int index, T distance) {
		data[index] = distance;
		while (index != 1 && data[getParent(index)] > data[index]) {

			T tempData = data[index];
			data[index] = data[getParent(index)];
			data[getParent(index)] = tempData;

			U tempName = names[index];
			names[index] = names[getParent(index)];
			names[getParent(index)] = tempName;

			index = getParent(index);
		}
	}
	// function for displaying min heap. Was used for testing
	void display() {
		for (int i = 1; i < currentSize; i++) {
			cout << data[i] << " " << names[i] << endl;
		}
	}
};

// Node for doubly link list
template<typename T>
class Node {
public:
	T data;
	Node<T> *Next;
	Node<T> *Prev;
	Node() {
		Next = NULL;
		Prev = NULL;
	}
};

// implementation of the doubly link list
template<class T>
class list {
private:
	Node<T> *Head;
	Node<T> *Tail;
	int size;
public:
	list() {
		Head = NULL;
		Tail = NULL;
		size = 1;
	}
	Node<T>* getHead() const {
		return Head;
	}
	Node<T>* getTail() const {
		return Tail;
	}
	bool isEmpty() {
		if (Head == NULL)
			return true;
		else
			return false;
	}
	// inserts the data item at specific index
	void insertAt(const T &newDataItem, int index) {
		Node<T> *newNode = new Node<T>;
		newNode->data = newDataItem;
		if (index > 1 && isEmpty())
			cout << "index out of range";
		else {
			Node<T> *currNode = Head;
			int currIndex = 2;
			while (currNode && index > currIndex) {
				currNode = currNode->Next;
				currIndex++;
			}
			if (index > currIndex - 1 && !currNode)
				cout << "index out of range";
			else {
				if (index == 1 && isEmpty()) {
					newNode->Next = NULL;
					newNode->Prev = NULL;
					Head = newNode;
					Tail = newNode;
				} else if (index == 1) {
					newNode->Next = currNode;
					Head = newNode;
					if (!currNode->Next)
						Tail = currNode;
				} else if (currNode->Next == NULL) {
					newNode->Next = currNode->Next;
					newNode->Prev = currNode;
					currNode->Next = newNode;
					currNode = currNode->Next;
					Tail = currNode;
				} else {
					newNode->Next = currNode->Next;
					currNode->Next = newNode;
					newNode->Next->Prev = newNode;
					newNode->Prev = currNode;
				}
				size++;
			}
		}
	}
	// removes data item from the specific index
	void removeAt(int index) {
		if (index <= 0)
			return;
		int currIdx = 1;
		Node<T>*current = Head;
		while (current->Next && index > currIdx) {
			current = current->Next;
			currIdx++;
		}
		if (index > currIdx) {
			cout << "index out of range" << endl;
			return;
		}
		if (current) {
			if (current->Prev && index == currIdx) {
				Node<T>*oldNode = current;
				oldNode->Prev->Next = oldNode->Next;
				if (oldNode->Next) {
					oldNode->Next->Prev = oldNode->Prev;
				}
				current = oldNode->Prev;
				if (!current->Next)
					Tail = current;
				delete oldNode;
			} else {
				if (current->Next) {
					Head = current->Next;
					Head->Prev = NULL;
					if (!Head->Next)
						Tail = current;
					delete current;
				} else {
					Head = NULL;
					Tail = NULL;
				}
			}
		}
		this->size--;
	}
	// removes data item from the end
	void remove() {
		Node<T>*current = Head;
		while (current->Next) {
			current = current->Next;
		}
		if (current) {
			if (current->Prev) {
				Node<T>*oldNode = current;
				oldNode->Prev->Next = oldNode->Next;
				current = oldNode->Prev;
				Tail = current;
				delete oldNode;
			} else {
				if (current->Next) {
					Head = current->Next;
					Head->Prev = NULL;
					delete current;
					Tail = Head;
				} else {
					Head = NULL;
					Tail = NULL;
				}
			}
		}
		size--;
	}
	// inserts data item at the end
	void insert(T newDataItem) {
		if (!Head) {
			Head = new Node<T>;
			Head->data = newDataItem;
			Head->Next = NULL;
			Head->Prev = NULL;
			Tail = Head;
			return;
		} else {
			Node<T>*current = Head;
			while (current->Next) {
				current = current->Next;
			}
			Node<T>*newNode = new Node<T>;
			newNode->data = newDataItem;
			newNode->Prev = current;
			newNode->Next = current->Next;
			newNode->Prev->Next = newNode;
			current = newNode;
			Tail = current;
		}
		size++;
	}
	// returns size 
	int getSize() {
		return size;
	}
	// displays link list
	void displayList() {
		if (!isEmpty()) {
			Node<T> *currNode = Head;
			while (currNode) {
				currNode->data.display();
				currNode = currNode->Next;
			}
		} else
			cout << "List is already Empty";
	}
};

/* following are the data nodes used to create various things throughtout the code*/

template<typename T, typename U>
class sNodeData {
public:
	T adjCityName;
	U adjCityDistance;

	sNodeData() {
		adjCityName = "";
		adjCityDistance = 0;
	}
	void insertSNodeData(T name, U distance) {
		adjCityName = name;
		adjCityDistance = distance;
	}
	void display() {
		cout << "|" << adjCityName << " ";
		cout << adjCityDistance << "|  ";
	}
};

template<typename T>
class singleCity {
public:
	T city;

	singleCity() {
		city = "";
	}
	void insertPathData(T city) {
		this->city = city;
	}
	void display() {
		cout << "|" << city << "|-->";
	}
};

template<typename T, typename U>
class Path {
public:
	list<T> pathCityToCity;
	U distanceCityToCity;
	Path() {
		distanceCityToCity = 0;
	}
	Path(list<U> pathCityToCitySourceData, U distanceCityToCity) {
		pathCityToCity = pathCityToCitySourceData;
		this->distanceCityToCity = distanceCityToCity;
	}
	void display() {
		pathCityToCity.displayList();
		cout << "Distance: [" << distanceCityToCity << "]" << endl;
	}
};

template<typename T, typename U>
class pNodeData {
public:
	T cityName;
	list<U> adjNodes;
	pNodeData() {
		cityName = "";
	}
	pNodeData(T name, list<U> adjNodesSourceData) {
		cityName = name;
		adjNodes = adjNodesSourceData;
	}
	void display() {
		cout << cityName << "--> ";
		adjNodes.displayList();
		cout << endl;
	}
};

template<typename T>
class shortestPathsNodes {
public:
	list<T> shortestPaths;
	shortestPathsNodes() {
	}
	shortestPathsNodes(list<T> shortestPathsSourceData) {
		shortestPaths = shortestPathsSourceData;
	}
	void display() {
		shortestPaths.displayList();
	}
};


// class which has adjacency list as a member variable and 
// handles user interface as well as the finding of shortest
// and second shortest paths.
template<typename T, typename U, typename V>
class graph {
public:
	list<V> adjacencyList;
	// function for inseting the node
	void insert(V primaryNode) {
		adjacencyList.insert(primaryNode);
	}
	void display() {
		adjacencyList.displayList();
	}
	// function adds the new city the adjacency list 
	void addNewCity(T newCity) {
		V newCityInTheAdjacencyList;
		newCityInTheAdjacencyList.cityName = newCity;
		adjacencyList.insert(newCityInTheAdjacencyList);
	}
	/* 
	 checks whether the city is already present in the graph or not
	 if No then it returns -1 and if yes then it returns its location
	 */
	int isCityAlreadyPresent(T newCityName) {
		int count = 1;
		Node<V> *currentNode = adjacencyList.getHead();
		if (!adjacencyList.isEmpty()) {
			while (currentNode) {
				if (currentNode->data.cityName == newCityName) {
					return count;
				}
				currentNode = currentNode->Next;
				count++;
			}
		} else {
			return -1;
		}
		return -1;
	}
	// function which checks that the edged city is already present or not
	int isEdgedCityAlreadyPresent(Node<V> *currentNode, T edgedCityName) {
		Node<sNodeData<T, U>> *adjNodesCurrentNode =
				currentNode->data.adjNodes.getHead();
		int count = 1;
		while (adjNodesCurrentNode) {
			if (adjNodesCurrentNode->data.adjCityName == edgedCityName) {
				return count;
			}
			adjNodesCurrentNode = adjNodesCurrentNode->Next;
			count++;
		}
		return -1;
	}
	// function which removes all the thinks in the adjacency list with the given city name
	void removeAllLinks(T cityName) {
		if (!adjacencyList.isEmpty()) {
			Node<V> *currentNode = adjacencyList.getHead();
			while (currentNode) {
				int count = 1;
				Node<sNodeData<T, U>> *innerCurrentNode =
						currentNode->data.adjNodes.getHead();
				while (innerCurrentNode) {
					if (innerCurrentNode->data.adjCityName == cityName) {
						currentNode->data.adjNodes.removeAt(count);
						break;
					}
					innerCurrentNode = innerCurrentNode->Next;
					count++;
				}
				currentNode = currentNode->Next;
			}
		}
	}
	// inserts the new edge
	void insertEdge(sNodeData<T, U> s, T cityName) {
		Node<V> *currentNode = adjacencyList.getHead();
		while (currentNode) {
			if (currentNode->data.cityName == cityName) {
				currentNode->data.adjNodes.insert(s);
			}
			currentNode = currentNode->Next;
		}
	}
	// removes the edge between two cities
	void removeEdge(T mainNodeName, T innerListNodeName) {
		Node<V> *currentNode = adjacencyList.getHead();
		while (currentNode) {
			if (currentNode->data.cityName == mainNodeName) {
				int isEdgedCityAlreadyPresentCheck = isEdgedCityAlreadyPresent(
						currentNode, innerListNodeName);

				if (isEdgedCityAlreadyPresentCheck == -1) {
					cout << "No such link with this city";
				} else {
					currentNode->data.adjNodes.removeAt(
							isEdgedCityAlreadyPresentCheck);
				}
			}
			currentNode = currentNode->Next;
		}
	}
	// returns graph size
	int getAdjacencyListSize() {

		int count = 0;
		Node<V> *currentNode = adjacencyList.getHead();
		while (currentNode) {
			count++;
			currentNode = currentNode->Next;
		}
		return count;
	}
	// recursive function which has been implemented to get the path from source to destination
	void printPath(T *parentArray, int destination, T *verticesArray,
			int verticesArraySize, int choice,
			Path<singleCity<T>, U> &singleCityPathAndDistance,
			singleCity<T> & storeSingleCity) {

		if (parentArray[destination] == "\0") {
			return;
		}
		int i = 0;
		for (; i < verticesArraySize; i++) {
			if (verticesArray[i] == parentArray[destination]) {
				destination = i;
				break;
			}

		}
		if (choice == 2) {
			storeSingleCity.insertPathData(verticesArray[destination]);
			singleCityPathAndDistance.pathCityToCity.insert(storeSingleCity);
		}
		printPath(parentArray, destination, verticesArray, verticesArraySize,
				choice, singleCityPathAndDistance, storeSingleCity);
		if (choice == 1 || choice == 3) {
			storeSingleCity.insertPathData(verticesArray[destination]);
			singleCityPathAndDistance.pathCityToCity.insert(storeSingleCity);
		}

	}
	// implementation of dijkstra's algorithm to find the shortest path
	list<Path<singleCity<T>, U>> runDijkstra(T nameOfCity, int choice,
			T sink) {

		int adjacencyListSize = getAdjacencyListSize();
		Set<T> s(adjacencyListSize);
		minHeap<U, T> m(adjacencyListSize);
		T *parentArray = new T[adjacencyListSize];
		T *verticesArray = new T[adjacencyListSize];
		U *updatedDistances = new U[adjacencyListSize];
		Node<V> *currentNode = adjacencyList.getHead();
		int i = 0;
		// inserting 0 as distance of the city from where to start in the min heap
		// and 2147483648 as infinity to all other cities 
		while (currentNode) {

			if (currentNode->data.cityName.compare(nameOfCity) == 0) {
				m.insertKey(0, currentNode->data.cityName);
				parentArray[i] = "\0";
				verticesArray[i] = currentNode->data.cityName;
			} else {
				m.insertKey(2147483648, currentNode->data.cityName);
				parentArray[i] = "\0";
				verticesArray[i] = currentNode->data.cityName;
			}

			currentNode = currentNode->Next;
			i++;
		}


		T vertex = "";
		// runs untill the min heap is not empty
		while (!m.isEmpty()) {

			vertex = m.getMin();
			// storing the vertex in the set if it is not already present
			if (!s.isAlreadyInSet(vertex))
				s.addItem(vertex);
			currentNode = adjacencyList.getHead();
			while (currentNode) {
				if (currentNode->data.cityName.compare(vertex) == 0) {
					Node<sNodeData<T, U>> *innerCurrentNode =
							currentNode->data.adjNodes.getHead();
					while (innerCurrentNode) {
						int vertexIndex;
						int neighbhorIndex;
						U vertexDistance = m.getDistance(vertex, vertexIndex);
						U neighbhorDistance = m.getDistance(
								innerCurrentNode->data.adjCityName,
								neighbhorIndex);
						// condition to check if the vertex is not already in the set
						// and vertecdistance from the min heap + its distance from adjacency list
						// if less than the distance of the neihbour of the vertex or not.
						// if yes, then replace the distance.
						if (!s.isAlreadyInSet(
								innerCurrentNode->data.adjCityName)
								&& (vertexDistance
										+ innerCurrentNode->data.adjCityDistance)
										< neighbhorDistance) {

							m.setDistance(neighbhorIndex,
									(vertexDistance
											+ innerCurrentNode->data.adjCityDistance));
							for (int j = 0; j < adjacencyListSize; j++) {
								if (verticesArray[j].compare(
										innerCurrentNode->data.adjCityName)
										== 0) {
									parentArray[j] = vertex;
									break;
								}
							}
						}
						innerCurrentNode = innerCurrentNode->Next;
					}
					break;
				}
				currentNode = currentNode->Next;
			}

			// getting minimum value and the city with min value and deleting from the min heap
			U storeMinValue;
			T storeMinCity = m.deleteMin(storeMinValue);

			// updating the distance of the mincity
			for (int i = 0; i < adjacencyListSize; i++) {
				if (verticesArray[i].compare(storeMinCity) == 0) {
					updatedDistances[i] = storeMinValue;
					break;
				}
			}
		}

		// two- dimensional link list to store all paths to return it later
		list<Path<singleCity<T>, U>> paths;

		// if choice is 1 or 2 then it stores the path from all the cities to specific city and vice versa
		if (choice == 1 || choice == 2) {
			for (int i = 0; i < adjacencyListSize; i++) {
				singleCity<T> storeSingleCity;
				Path<singleCity<T>, U> pathAndDistanceNode;
				if (verticesArray[i] != nameOfCity) {
					if (choice == 1) {
						printPath(parentArray, i, verticesArray,
								adjacencyListSize, choice, pathAndDistanceNode,
								storeSingleCity);
						if (updatedDistances[i] == 2147483648) {

							storeSingleCity.insertPathData(verticesArray[i]);
							pathAndDistanceNode.pathCityToCity.insert(
									storeSingleCity);
							pathAndDistanceNode.distanceCityToCity =
									updatedDistances[i];
							paths.insert(pathAndDistanceNode);
						} else {
							storeSingleCity.insertPathData(verticesArray[i]);
							pathAndDistanceNode.pathCityToCity.insert(
									storeSingleCity);
							pathAndDistanceNode.distanceCityToCity =
									updatedDistances[i];
							paths.insert(pathAndDistanceNode);
						}
					}
					if (choice == 2) {
						if (updatedDistances[i] == 2147483648) {
							storeSingleCity.insertPathData(verticesArray[i]);
							pathAndDistanceNode.pathCityToCity.insert(
									storeSingleCity);
							pathAndDistanceNode.distanceCityToCity =
									updatedDistances[i];
							paths.insert(pathAndDistanceNode);

						}

						else {
							storeSingleCity.insertPathData(verticesArray[i]);
							pathAndDistanceNode.pathCityToCity.insert(
									storeSingleCity);
						}
						printPath(parentArray, i, verticesArray,
								adjacencyListSize, choice, pathAndDistanceNode,
								storeSingleCity);
						if (updatedDistances[i] != 2147483648) {

							pathAndDistanceNode.distanceCityToCity =
									updatedDistances[i];
							paths.insert(pathAndDistanceNode);
						}
					}
				}
			}
			return paths;
		}
		// if choice is 3 which means it will store the path from one city to another 
		if (choice == 3) {

			for (int i = 0; i < adjacencyListSize; i++) {
				singleCity<T> storeSingleCity;
				Path<singleCity<T>, U> pathAndDistanceNode;
				if (verticesArray[i] == sink) {
					printPath(parentArray, i, verticesArray, adjacencyListSize,
							choice, pathAndDistanceNode, storeSingleCity);
					if (updatedDistances[i] == 2147483648) {

						storeSingleCity.insertPathData(verticesArray[i]);
						pathAndDistanceNode.pathCityToCity.insert(
								storeSingleCity);
						pathAndDistanceNode.distanceCityToCity =
								updatedDistances[i];
						paths.insert(pathAndDistanceNode);
					} else {

						storeSingleCity.insertPathData(verticesArray[i]);
						pathAndDistanceNode.pathCityToCity.insert(
								storeSingleCity);
						pathAndDistanceNode.distanceCityToCity =
								updatedDistances[i];
						paths.insert(pathAndDistanceNode);
					}
					break;
				}
			}
			// returning path list
			return paths;
		}
	}
	// returns the weight of the edge between two cities in the adjacency list
	int getDistance(T city1, T city2) {
		Node<V> *currentNode = adjacencyList.getHead();
		while (currentNode) {
			if (city1.compare(currentNode->data.cityName) == 0) {
				Node<sNodeData<T, U>> *innerCurrentNode =
						currentNode->data.adjNodes.getHead();
				while (innerCurrentNode) {
					if (innerCurrentNode->data.adjCityName.compare(city2)
							== 0) {
						return innerCurrentNode->data.adjCityDistance;
					}
					innerCurrentNode = innerCurrentNode->Next;
				}
			}
			currentNode = currentNode->Next;
		}
	}

	// Yen's algo implemented to get the second shortest path 
	// it first stores the shortest paths in the three-dimensional 
	// doubly linked list to also handle the distances from one city to many 
	// and looping through them to get the second shortest path of all 

	void runYen(T cityName, int choice, int k, string sink) {
		list<shortestPathsNodes<Path<singleCity<T>, U>>> kShortestPaths;
		shortestPathsNodes<Path<singleCity<T>,U>> firstShortestPath(runDijkstra(cityName,choice,sink));
		kShortestPaths.insert(firstShortestPath); // it will store the k shortest path and first path is already stored

		// temporary adjacency list is created which will be used later to store the original 
		// adjacency list to use it in the process. It also helps to get the original 
		// graph to be unaltered at the end of the process of finding the second shortest 
		// path.

		list <V> tempAdjacencyList;

		Node <shortestPathsNodes<Path<singleCity<T>,U>>> *OuterCurrentNode= kShortestPaths.getHead();
		Node <Path<singleCity<T>,U>> *InnerCurrentNode= OuterCurrentNode->data.shortestPaths.getHead();
		while (InnerCurrentNode)
		{
			if (InnerCurrentNode->data.distanceCityToCity!=2147483648)
			{
				sink = InnerCurrentNode->data.pathCityToCity.getTail()->data.city;

				list <Path<singleCity<T>,U>> alternativePaths;

				for (int i=0;i<=InnerCurrentNode->data.pathCityToCity.getSize()-2;i++)
				{
					Node <singleCity<T>> *currNode=InnerCurrentNode->data.pathCityToCity.getHead(); // to get spurNode A[0].node(i)
					list <singleCity<T>> rootPath;
					singleCity<T> currCity;

					int distance=0;
					string spurNode="";

					// storing the root path and spurNode
					for (int j=0;j<=i;j++)
					{
						currCity.city=currNode->data.city;
						rootPath.insert(currCity);
						if (j!=i)
						{
							distance+=getDistance(currNode->data.city,currNode->Next->data.city);
						}
						if (j==i)
						{
							spurNode=currNode->data.city;
						}
						currNode=currNode->Next;

					}

					bool flag=true;
					Node <singleCity<T>> *checkCityNode=InnerCurrentNode->data.pathCityToCity.getHead();
					Node <singleCity<T>> *rootPathNode = rootPath.getHead();

					// check whether the root path is the part of the shortest path founded
					while (rootPathNode)
					{
						if (rootPathNode->data.city!=checkCityNode->data.city)
						{
							flag=false;
							break;
						}

						checkCityNode=checkCityNode->Next;
						rootPathNode=rootPathNode->Next;
					}

					// if yes then remove the edge of spur node and next to it
					if (flag)
					{
						// copying original adjacency list in the temp adjacency list to 
						// use the original in the process and then getting it returned
						// to its original state.
						Node <V> *adjacencyListCopyNode= adjacencyList.getHead();
						while (adjacencyListCopyNode)
						{
							list <sNodeData<T,U>> copySNodeList;
							Node <sNodeData<T,U>> *copySNode=adjacencyListCopyNode->data.adjNodes.getHead();
							while (copySNode)
							{
								sNodeData <T,U> copySNodeData;
								copySNodeData.insertSNodeData(copySNode->data.adjCityName,copySNode->data.adjCityDistance);
								copySNodeList.insert(copySNodeData);
								copySNode=copySNode->Next;
							}
							pNodeData<T,sNodeData<T,U>> copyPNodeData;
							copyPNodeData.cityName=adjacencyListCopyNode->data.cityName;
							copyPNodeData.adjNodes=copySNodeList;
							tempAdjacencyList.insert(copyPNodeData);
							adjacencyListCopyNode=adjacencyListCopyNode->Next;
						}

						// removing edges of city1 with city2 and vice versa
						removeEdge(currNode->Prev->data.city,currNode->data.city);
						removeEdge(currNode->data.city,currNode->Prev->data.city);
					}

					// also remove the nodes of the root path except the spur Node from the adjacency list
					rootPathNode = rootPath.getHead();
					while (rootPathNode->data.city!=spurNode)
					{
						adjacencyList.removeAt(isCityAlreadyPresent(rootPathNode->data.city));
						removeAllLinks(rootPathNode->data.city);
						rootPathNode=rootPathNode->Next;
					}

					// running dijkstra to find the shortest path from spur node
					list <Path<singleCity<T>,U>> spurPath=runDijkstra(spurNode,3,sink);

					Node <singleCity<T>> *spurPathNode=spurPath.getHead()->data.pathCityToCity.getHead();
					singleCity<T> spurPathNodeData;
					spurPathNode=spurPathNode->Next;
					// combining the root path and spur path found by running dijkstra on it
					while (spurPathNode)
					{
						spurPathNodeData.insertPathData(spurPathNode->data.city);
						rootPath.insert(spurPathNodeData);
						spurPathNode=spurPathNode->Next;
					}

					Path<singleCity<T>,U> pathNode;
					// adding distances of root path and spur path to get the total distance
					pathNode.distanceCityToCity=spurPath.getHead()->data.distanceCityToCity+distance;
					pathNode.pathCityToCity=rootPath;
					alternativePaths.insert(pathNode);


					// deleting the original adjacency list 
					Node <V> *adjacencyListCopyNode= adjacencyList.getHead();
					while (adjacencyListCopyNode)
					{
						int size=adjacencyListCopyNode->data.adjNodes.getSize();
						Node <sNodeData<T,U>> *copySNode=adjacencyListCopyNode->data.adjNodes.getHead();
						while (size>0 && copySNode)
						{
							adjacencyListCopyNode->data.adjNodes.remove();
							size--;
						}
						adjacencyListCopyNode=adjacencyListCopyNode->Next;
					}

					while (!adjacencyList.isEmpty())
					{
						adjacencyList.remove();
					}

					// getting back to its original condition by assigning it the tempAdjacency list stored before 
					adjacencyListCopyNode= tempAdjacencyList.getHead();
					while (adjacencyListCopyNode)
					{
						list <sNodeData<T,U>> copySNodeList;
						Node <sNodeData<T,U>> *copySNode=adjacencyListCopyNode->data.adjNodes.getHead();
						while (copySNode)
						{
							sNodeData <T,U> copySNodeData;
							copySNodeData.insertSNodeData(copySNode->data.adjCityName,copySNode->data.adjCityDistance);
							copySNodeList.insert(copySNodeData);
							copySNode=copySNode->Next;
						}
						pNodeData<T,sNodeData<T,U>> copyPNodeData;
						copyPNodeData.cityName=adjacencyListCopyNode->data.cityName;
						copyPNodeData.adjNodes=copySNodeList;
						adjacencyList.insert(copyPNodeData);
						adjacencyListCopyNode=adjacencyListCopyNode->Next;
					}

					// deleting temp graph/adjacency list
					adjacencyListCopyNode= tempAdjacencyList.getHead();
					while (adjacencyListCopyNode)
					{
						int size=adjacencyListCopyNode->data.adjNodes.getSize();
						Node <sNodeData<T,U>> *copySNode=adjacencyListCopyNode->data.adjNodes.getHead();
						while (size>0 && copySNode)
						{
							adjacencyListCopyNode->data.adjNodes.remove();
							size--;
						}
						adjacencyListCopyNode=adjacencyListCopyNode->Next;
					}

					adjacencyListCopyNode= tempAdjacencyList.getHead();
					while (!tempAdjacencyList.isEmpty())
					{
						tempAdjacencyList.remove();
					}

				}

				// sorting all the spur paths to get shortest of all which will be second shortest path
				for(int i =0; i<alternativePaths.getSize() - 1; i++)
				{
					Node<Path<singleCity<T>,U>>* nodeForSorting = alternativePaths.getHead();
					for(int j = 0; j<alternativePaths.getSize() - i - 1; j++)
					{
						Node<Path<singleCity<T>,U>>* tempNode = new Node<Path<singleCity<T>,U>>;
						if(nodeForSorting->data.distanceCityToCity > nodeForSorting->Next->data.distanceCityToCity)
						{
							tempNode->data = nodeForSorting->data;
							nodeForSorting->data = nodeForSorting->Next->data;
							nodeForSorting->Next->data = tempNode->data;
						}
						nodeForSorting = nodeForSorting->Next;
					}

				}
				// displaying shortest and second shorest paths
				cout<<"Shortest Path: ";
				InnerCurrentNode->data.display();
				if (alternativePaths.getHead()->data.distanceCityToCity != 2147483648){
					cout<<"Second Shortest Path: ";
					alternativePaths.getHead()->data.display();
				}
				else
				cout<<"No Second Shortest Path of "<<alternativePaths.getHead()->data.pathCityToCity.getHead()->data.city<<" Exists With "<<sink<<endl;
				cout<<endl;
			}
			else
			{
				cout<<"No Shortest Path Exists With "<<InnerCurrentNode->data.pathCityToCity.getHead()->data.city<<endl<<endl;
			}

			InnerCurrentNode=InnerCurrentNode->Next;
		}
	}
	// function which handles the user interface and given input and calls respecive functions
	void performOperation() {
		int choice;
		cin>>choice;
		if (choice==0) {
			cout<<"______________________________________________________________________________________________________________________"<<endl;
			adjacencyList.displayList();
			cout<<"______________________________________________________________________________________________________________________"<<endl<<endl;
		}
		if (choice==1) {
			string newCity="";
			cout<<"Please input the name of the city you want to add\n";
			cin.ignore();
			getline(cin,newCity);
			if (isCityAlreadyPresent(newCity)==-1) {
				addNewCity(newCity);
				cout<<"New city added. Press 0 to see the updated graph."<<endl<<endl;
			}
			else {
				cout<<"This city is already present\n";
			}
		}
		if (choice==2) {
			string cityName="";
			cout<<"Please input the name of the city you want to remove\n";
			cin.ignore();
			getline(cin,cityName);
			if (isCityAlreadyPresent(cityName)==-1) {
				cout<<"The given city doesn't exist\n";
			}
			else {
				adjacencyList.removeAt(isCityAlreadyPresent(cityName));
				removeAllLinks(cityName);
				cout<<"City Deleted. Press 0 to see the updated graph."<<endl<<endl;
			}
		}
		if (choice==3) {
			string cityName="";
			cout<<"Please input the name of the city to which you want to add an edge of other city\n";
			cin.ignore();
			getline(cin,cityName);
			if (isCityAlreadyPresent(cityName)==-1) {
				cout<<"No such city exists";
			}
			else {

				T edgeCityName="";
				U edgeCityDistance;
				cout<<"Please Enter the name of the city which is to be edged with the entered city\n";
				getline(cin,edgeCityName);

				bool flag=false;
				Node <V> *currentNode=adjacencyList.getHead();
				while (currentNode)
				{
					if (cityName.compare(currentNode->data.cityName)==0){
						Node <sNodeData<T,U>> * innerCurrentNode = currentNode->data.adjNodes.getHead();
						while (innerCurrentNode)
						{
							if (edgeCityName.compare(innerCurrentNode->data.adjCityName)==0){
								flag=true;
								break;
							}
							innerCurrentNode=innerCurrentNode->Next;
						}
						break;
					}
					currentNode=currentNode->Next;
				}

				if (!flag){
					if (edgeCityName.compare(cityName)!=0){

						if (isCityAlreadyPresent(edgeCityName)==-1) {
							cout<<"\nCan't add an edge of the city which is not in the list\n";
						}
						else {
							cout<<"\nPlease Enter the distance\n";
							cin>>edgeCityDistance;
							while (edgeCityDistance<=0) {
								cout<<"\nPlease Enter appropriate distance\n";
								cin>>edgeCityDistance;
							}
							sNodeData<T,U> s;
							s.insertSNodeData(edgeCityName,edgeCityDistance);

							insertEdge(s,cityName);

							s.insertSNodeData(cityName,edgeCityDistance);
							insertEdge(s,edgeCityName);
							cout<<"Edge added. Press 0 to see the updated graph"<<endl<<endl;
						}
					}
					else{
						cout<<"Can't add the edge with the city itself! "<<endl;
					}
				}
				else
				{
					cout<<"Edge is already present!"<<endl;
				}
			}
		}
		if (choice==4) {
			string cityName="";
			cout<<"Please input the name of the city of which you want to remove an edge of other city\n";
			cin.ignore();
			getline(cin,cityName);
			if (isCityAlreadyPresent(cityName)==-1) {
				cout<<"No such city exists";
			}
			else {
				string edgeCityName="";
				cout<<"Please Enter the name of the other city\n";
				getline(cin,edgeCityName);

				removeEdge(cityName,edgeCityName);
				removeEdge(edgeCityName,cityName);
				cout<<"Edge removed. Press 0 to see the updated graph"<<endl<<endl;

			}
		}
		if (choice == 5) {
			string cityName="";
			cout<<"Please Enter the name of the city\n";
			cin.ignore();
			getline(cin,cityName);
			cout<<endl;
			if (isCityAlreadyPresent(cityName)==-1) {
				cout<<"Sorry, city doesn't exist\n";
			}
			else {
				runYen (cityName,1,2,"");
			}
		}
		if (choice ==6)
		{
			string cityName="";
			cout<<"Please Enter the name of the city\n";
			cin.ignore();
			getline(cin,cityName);
			cout<<endl;
			if (isCityAlreadyPresent(cityName)==-1) {
				cout<<"Sorry, city doesn't exist\n";
			}
			else {
				runYen (cityName,2,2,"");
			}
		}
		if (choice ==7)
		{
			string cityName="";
			cout<<"Please Enter the name of the city\n";
			cin.ignore();
			getline(cin,cityName);
			cout<<endl;
			if (isCityAlreadyPresent(cityName)==-1) {
				cout<<"Sorry, city doesn't exist\n";
			}
			else {

				string secondCityName="";
				cout<<"Please Enter the name of the second city\n";
				getline(cin,secondCityName);
				cout<<endl;

				if (isCityAlreadyPresent(secondCityName)==-1) {
					cout<<"Sorry, city doesn't exist\n";
				}
				else
				{
					runYen (cityName,3,2,secondCityName);
				}

			}
		}
	}
	// menu 
	void displayMenu() {
		cout<<"Please choose the operation you want to perform\n"<<
		"0) Show the graph \n"<<
		"1) Insert a city\n"<<
		"2) Remove a city\n"<<
		"3) Insert an edge in an existing city\n"<<
		"4) Remove an edge from an existing city\n"<<
		"5) Compute Shortest and Second Shortest Distance From a City to All Other Cities\n"<<
		"6) Compute Shortest and Second Shortest Distance from All Other Cities to Specific City\n"<<
		"7) Compute Shortest and Second Shortest distance between two cities\n"<<endl;
		performOperation();
	}
};

// function in which the data from the given file is read
// and graph/ adjacencylist is created.

template<typename T, typename U>
void general(string path) {
	graph<T, U, pNodeData<T, sNodeData<T, U>>> g;

	ifstream readFile (path);
	string line;
	if (readFile.is_open()) {
		getline(readFile, line);
	}
	line+='\0';

	int citiesCount=0;
	for (int i=0;line[i]!='\0';i++) {
		if (line[i]==',') {
			citiesCount++;
		}
	}
	T *cities=new T [citiesCount];
	int j=0;
	for (int i=1;i<line.length();i++) {
		while (line[i]!=',' && line[i]!='\0') {
			cities[j]+=line[i];
			i++;
		}
		j++;
	}

	int outerCondition=0;
	while (outerCondition<citiesCount) {
		getline(readFile,line);
		line+='\0';

		int pNodeDataStringCount=0;
		for (int i=0;line[i]!='\0';i++) {
			if (line[i]==',') {
				pNodeDataStringCount++;
			}
		}
		T *pNodeDataString= new T [pNodeDataStringCount+1];
		j=0;

		for (int i=0;i<line.length();i++) {
			while (line[i]!=',' && line[i]!='\0') {
				pNodeDataString[j]+=line[i];
				i++;
			}
			j++;
		}

		T cityName;
		list <sNodeData<T,U>> adjNodesSource;
		for (int i=0;i<pNodeDataStringCount+1;i++) {
			if (i==0) {
				cityName=pNodeDataString[i];
			}
			else {
				if (stoi(pNodeDataString[i])>0) {
					sNodeData <T,U> s1;
					s1.insertSNodeData(cities[i-1],stoi(pNodeDataString[i]));
					adjNodesSource.insert(s1);
				}
			}
		}

		pNodeData <T,sNodeData<T,U>> p(cityName,adjNodesSource);

		g.insert(p);

		outerCondition++;
	}

	while (true) {
		g.displayMenu();
	}
}