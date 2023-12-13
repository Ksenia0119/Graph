#pragma once
//@author Maltseva K.V. 

#include <iostream>
#include<vector>
#include<stack>
#include<queue>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;


//���������� ��������������� ����
template <class T>
class WeightedGraph {
private:
    int maxVertices;//������������ ������ �����
    int numVertices; // ���������� ������ �����
    //int* vertices; // ������ ������ ����� 

    vector<T> vertices;  // ������ ������ �����
    double** adjacencyMatrix; // ������� ���������
public:
   
    // ����������� � ���������� (������������ ������ �����)
    WeightedGraph(int _maxVertices) {
        maxVertices = _maxVertices;
        numVertices = 0;

        //// �������� ������ ��� ������� ������ � �������������� ��� ���������� 
        //vertices = new int[maxVertices];
        //for (int i = 0; i < maxVertices; i++) {
        //    vertices[i] =  i + 1;
        //}

        // �������� ������ ��� ������� ��������� � �������������� ���������� 0,��� ��� ���������� ������� �����
        adjacencyMatrix = new double* [maxVertices];
        for (int i = 0; i < maxVertices; i++) {
            adjacencyMatrix[i] = new double[maxVertices];
            for (int j = 0; j < maxVertices; j++) {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    // ����������� ����������� 
    WeightedGraph(const WeightedGraph& other) {
        maxVertices = other.maxVertices;
        numVertices = other.numVertices;

        // �������� �������
        vertices = other.vertices;

        // �������� ������ ��� ����� ������� ��������� � �������� ��������
        adjacencyMatrix = new double* [maxVertices];
        for (int i = 0; i < maxVertices; i++) {
            adjacencyMatrix[i] = new double[maxVertices];
            memcpy(adjacencyMatrix[i], other.adjacencyMatrix[i], maxVertices * sizeof(double));
        }
    }

    // �������� ������������ �����������
    WeightedGraph<T>& operator=(const WeightedGraph<T>& other) {
        //�������� ����������������
        if (this != &other) {
            // ����������� ������� �������� �������
            for (int i = 0; i < numVertices; i++) {
                delete[] adjacencyMatrix[i];
            }
            delete[] adjacencyMatrix;

            // �������� �������� �� ������� �������
            maxVertices = other.maxVertices;
            numVertices = other.numVertices;
            vertices = other.vertices;

            // �������� ������ ��� ����� ������� ��������� � �������� ��������
            adjacencyMatrix = new double* [maxVertices];
            for (int i = 0; i < maxVertices; i++) {
                adjacencyMatrix[i] = new double[maxVertices];
                memcpy(adjacencyMatrix[i], other.adjacencyMatrix[i], maxVertices * sizeof(double));
            }
        }
        return *this;
    }
    
    // ����������� �����������
    WeightedGraph(WeightedGraph&& other)
        : numVertices(other.numVertices), adjacencyMatrix(move(other.adjacencyMatrix))
    {
        other.numVertices = 0;
    }
    // �������� ������������ �����������
    WeightedGraph& operator=(WeightedGraph&& other) {
        //�������� ����������������
        if (this != &other) {
            numVertices = other.numVertices;
            adjacencyMatrix = move(other.adjacencyMatrix);
            
            other.numVertices = 0;
        }
        return *this;
    }
    //���������� �������
    void addVertex(const char& vertex) {
        if (numVertices >= maxVertices) {
            // ��������� ������������ ������ �����, ���������� ��������� ������
            int newMaxVertices = maxVertices * 2;

            // ������� ����� ������� ��������� � ����������� ��������
            double** newAdjacencyMatrix = new double* [newMaxVertices];
            for (int i = 0; i < newMaxVertices; i++) {
                newAdjacencyMatrix[i] = new double[newMaxVertices];
            }

            // �������� �������� �� ������ ������� ��������� � ����� 
            for (int i = 0; i < maxVertices; i++) {
                memcpy(newAdjacencyMatrix[i], adjacencyMatrix[i], maxVertices * sizeof(int));
            }

            // �������������� ����� �������� ��������� 0
            for (int i = maxVertices; i < newMaxVertices; i++) {
                memset(newAdjacencyMatrix[i], 0, newMaxVertices * sizeof(int));
            }

            // ����������� ������ ������ ������� ���������
            for (int i = 0; i < maxVertices; i++) {
                delete[] adjacencyMatrix[i];
            }
            delete[] adjacencyMatrix;

            // ��������� ��������� �� ����� ������� ��������� � ������������ ������
            adjacencyMatrix = newAdjacencyMatrix;
            maxVertices = newMaxVertices;
        }

        // ��������� ����� ������� � ������ ������
       // vertices[numVertices] = vertex;
        vertices.push_back(vertex);
        // ����������� ���������� ������
        numVertices++;
    }
    //���������� �����
    void addEdge(const T& source, const T& destination, double weight) {
        // ���������, ��� ������� ��������� � ���������� ��������
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            // ��������� ����� � ����� � ������� 
            adjacencyMatrix[source][destination] = weight;
           // adjacencyMatrix[destination][source] = weight; 
        }
        else {
           
            // ���������� ���������� 
            throw invalid_argument("����������� �������, ������ �������� �����");
        }
    }
    //�������� �����
    void removeEdge(const T& source, const T& destination) {
        // ���������, ��� ������� ��������� � ���������� ��������
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            // ������� ����� �� ������� ���������
            adjacencyMatrix[source][destination] = 0;
        }
        else {
           
             // ���������� ���������� 
            throw invalid_argument("������ ����� � ����� ���");
        }
    }
    //�������� �������
    void removeVertex(const T& vertex) {
        // ���������, ��� ������� ��������� � ���������� ��������
        if (vertex >= 0 && vertex < numVertices) {

            //// ������� ������� �� ������ ������, ������� ������� �����
            //for (int i = vertex; i < numVertices - 1; i++) {
            //    vertices[i] = vertices[i + 1];
            //}

             // ������� ������� �� ������� ������, ������� ������� �����
            vertices.erase(vertices.begin() + vertex);
            // ������� ������ � �������, ��������������� �������, �� ������� ���������
            //��������� �� ������� ����� �� ������� � ����� �� ������
            for (int i = vertex; i < numVertices - 1; i++) {
                for (int j = 0; j < numVertices; j++) {
                    adjacencyMatrix[i][j] = adjacencyMatrix[i + 1][j];
                }
            }
            for (int i = 0; i < numVertices; i++) {
                for (int j = vertex; j < numVertices - 1; j++) {
                    adjacencyMatrix[i][j] = adjacencyMatrix[i][j + 1];
                }
            }
            //��������� ���������� ������ � �����
            numVertices--;
        }
        //����� ���������� ����������
        else {
            throw invalid_argument("����� ������� � ����� ���");
        }
    }


    // ������ ������ � ����� 
    void printGraph() {
        cout << endl;
        cout << "<���������� ������> = " << getNumVertices()<<endl;
        cout << "������ ������ �����: "<<endl;
        for (int i = 0; i < numVertices; i++) {
            cout<<"�������"<<i<<"  "<< vertices[i] << endl;
        }
        cout << endl;

        cout << "<���������� �����> = " << NumEdges() << endl;
        for (int i = 0; i < numVertices; i++) {
           // for (int j = i + 1; j < numVertices; j++) 
                 for (int j = 0; j < numVertices; j++){
                if (adjacencyMatrix[i][j] != 0) {
                    cout << "����� " << i << "-" << j << "  ���: " << adjacencyMatrix[i][j] << endl;
                }
            }
        }
        cout << "������� ���������:" << endl;
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {

                cout << setw(3)<<adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

   
    //���������� ������ � �����
    int getNumVertices() const{
        return numVertices;
    }
    //���������� ����� � �����
    int NumEdges() {

        int countEdge = 0;
        for (int i = 0; i < numVertices; i++) {
            //for (int j = i; j < numVertices; j++) 
              for (int j = 0; j < numVertices; j++){
                if (adjacencyMatrix[i][j] != 0)
                    countEdge++;
            }
        }
        return countEdge;
       /* int countEdge = 0;
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (adjacencyMatrix[i][j] != 0 )
                    countEdge++;
            }
         
        }
        return countEdge;*/
    }
    //�������� ��� ����� ���������
    int getWeight(const T& source, const T& destination) {
        // ���������, ��� ������� ��������� � ���������� ��������
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            // ���������� ��� ����� �� ������� 
            return adjacencyMatrix[source][destination];
        }
        //����� ���������� ����������
        else {
           
            throw invalid_argument("����������� ������� ��� �����");
            //return -1;
        }
    }
    // ��������� ������� ������
    vector<T> getVertices() const {
        return vertices;
    }
    ////��������� ������� ������ �����
    //vector<int> getVertices() const {
    //    vector<int> vertexVector;
    //    for (int i = 0; i < numVertices; i++) {
    //        vertexVector.push_back(vertices[i]);
    //    }
    //    return vertexVector;
    //}
    //����� � �������
 
    //����� � ������� �� ������ �����
    vector<T> DepthFirst( const T& startNode) {
        //������ ��������� ���������� ������, ���������� ��� false,�.� �� ��������
        vector<bool> visitedVertices(numVertices, false);
        //���� ��� ������, ������� ����� ����������
         stack<int> nodeStack;
         //��������� � ���� ��������� �������
        nodeStack.push(startNode);
        //�������� � ���������� �������
        visitedVertices[startNode] = true;
        //������ ��� ������ ���������� ������
        vector<int> SaveVertices;
        //���� ���� �� ����
        while (!nodeStack.empty()) {
            //����������� ������� �����
            int currentNode = nodeStack.top();
            nodeStack.pop();
            //��������� 
            SaveVertices.push_back(currentNode);
            //cout << currentNode << " ";
            // ������������� ��� ������� �������
            for (int i = 0; i < numVertices; i++) {
                // ���� ���� ����� ����� ������� �������� � �������� i, � ������� i ��� �� ��������
                if (adjacencyMatrix[currentNode][i] && !visitedVertices[i]) {
                    //��������� ������� � ����
                    nodeStack.push(i);
                    //�������� ������� ��� ����������
                    visitedVertices[i] = true;
                }
            }
        }
        // ������� ��������� ������
        for (int i = 0; i < SaveVertices.size(); i++) {
            cout << SaveVertices[i] << " ";
        }
        cout << endl;
      
        //���������� ������ �� ������ ������
       
        return SaveVertices;
    }
    //����� � ������ �� ������ �������
    vector<T> BreadthFirst(const T& startNode) {
        //������ ��������� ���������� ������, ���������� ��� false,�.� �� ��������
        vector<bool> visitedVertices(numVertices, false);
        //���� ��� ������, ������� ����� ����������
        queue<int> nodeQueue;
        //��������� � ���� ��������� �������
        nodeQueue.push(startNode);
        //�������� � ���������� �������
        visitedVertices[startNode] = true;
        //������ ��� ������ ���������� ������
        vector<int> SaveVertices;
        //���� ������� �� �����
        while (!nodeQueue.empty()) {
            //����������� �������
            int currentNode = nodeQueue.front();
            nodeQueue.pop();
            //���������
            SaveVertices.push_back(currentNode);
            //cout << currentNode << " ";
            // ������������� ��� ������� �������
            for (int i = 0; i < numVertices; i++) {
                // ���� ���� ����� ����� ������� �������� � �������� i, � ������� i ��� �� ��������
                if (adjacencyMatrix[currentNode][i] && !visitedVertices[i]) {
                    //��������� ������� � �������
                    nodeQueue.push(i);
                    //�������� ������� ��� ����������
                    visitedVertices[i] = true;
                }
            }
        }
        // ������� ��������� ������
        for (int i = 0; i < SaveVertices.size(); i++) {
            cout << SaveVertices[i] << " ";
        }
        cout << endl;

        //���������� ������ �� ������ ������
        return  SaveVertices;
    }

    // ����� ������� ������� � ������� vertices �� ��������
    int findVertexIndex(const T& vertex) {
        //�������� �� �������
        for (int i = 0; i < numVertices; i++) {
            //���������� � ������ ���������
            if (vertices[i] == vertex) {
                //���������� ������ �������
                return i;
            }
        }
        //���������� -1 
        return -1; 
    }
    //�������� ��������
    //����� ����������� ���� �� ��������� ������� startNode �� ���� ��������� ������ � �����
    vector<T> dijkstrasAlgorithm(const T& startNode) {
        //����������� ��������� ��������: ���������� = "�������������", �������� = "�� ��������"//
        vector<int> distance(numVertices, numeric_limits<int>::max()); // ���������� �� ��������� ������� �� ���������
        vector<bool> visited(numVertices, false); // ���������� �������

        // ������� ������ ��������� �������,����� ��������� ������ ���� �� ���( � ����)
        int startIndex = findVertexIndex(startNode);
        if (startIndex == -1) {
            // ��������� ������� �� �������
            throw invalid_argument("������������ ������");
        }
        
        // ���������� �� ��������� ������� �� ��� ����� ����� 0
        distance[startIndex] = 0;
      
        //��������� ������ ���������� ��������, ���� ���� �������� � �� �������
        while (startIndex != -1) {
            // ��� �������� ������ ���������� ��������������� � �������� ����������
            for (int i = 0; i < numVertices; i++) {
                //�������� ��� ����� ����� ������� �������� � �������� i
                int weight = getWeight(startIndex,i);  
                //�������� �� ����������� ���������� ��������� ��������
               if(weight<0) throw invalid_argument("��������� ������������� ��� � �����");
                //���� ��� �� ����� 0 � ������� �� �������� � ����� ���� ����� ������� ������� ������ �������� ���������� �� ������� i
                if (weight != 0 && !visited[i] && (weight + distance[startIndex] < distance[i])) {
                  //���������� ����������� �� ����� ����� ����
                    distance[i] = weight + distance[startIndex];
                } 
                  
                
            }

            // �������� ������� ������� ��� "����������" � �������� ���������
            visited[startIndex] = true;
            startIndex = -1;
            int mindistance = numeric_limits<int>::max();
            for (int i = 0; i < numVertices; i++) {
                //����� ��������� ������������ �������
                if (!visited[i] && distance[i] < mindistance) {
                    //������������ ������� ����� ������� �������
                    startIndex = i;
                    //������� ����������� ���������� = ����������� �� ��������� �������
                    mindistance = distance[i];
                }
            }
        }

        // ������� ����������
        for (int i = 0; i < numVertices; i++) {
            cout << "���������� ���������� �� ������� " << startNode << " �� ������� "
                << vertices[i] << ": ";
            if (distance[i] == numeric_limits<int>::max()) {
                cout << "��� ����" << endl;
            }
            else {
                cout << distance[i] << endl;
            }
        }

        return distance;
    }
    //todo
    void bellmanFordAlgorithm(const T& startNode) {
        int startIndex = findVertexIndex(startNode);
        if (startIndex == -1) {
            std::cout << "������: ������� " << startNode << " �� �������" << std::endl;
            return;
        }

        vector<int> distance(numVertices, std::numeric_limits<int>::max());
        distance[startIndex] = 0;

        

      
        for (int i = 0; i < numVertices; i++) {
            std::cout << "���������� ���������� �� ������� " << startNode << " �� ������� "
                << vertices[i] << ": ";
            if (distance[i] == std::numeric_limits<int>::max()) {
                std::cout << "��� ����" << std::endl;
            }
            else {
                std::cout << distance[i] << std::endl;
            }
        }
    }

    //������ � ���� ������� GraphML
    void WriteToFile(const string& filename)
    { //����� ��� ������ � ����
        ofstream file(filename);
        //���� ���� �� ��������
        if (!file.is_open())
        {//���������� ����������
            throw "������ �������� �����";
        }
        //����� ���� ������� ������� ����������, ��� ������ � ����� ������ ����� ���...
        // ���������� ��������� XML
        file << R"(<?xml version="1.0" encoding="UTF-8"?>)" << '\n';
        file << R"(<graphml xmlns="http://graphml.graphdrawing.org/xmlns" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd">)" << '\n';

        // ���������� ����
        //���������������
        file << R"(<graph id="G" edgedefault="directed">)" << '\n';
        //��� ����� ���� -������� ��� ���� �������������
        file << R"(<key id="weight" for="edge" attr.name="weight" attr.type="double"/>)" << '\n';
        // �������� ������ ������
        vector<T> vertices = getVertices();

        // ���������� �������
        for (int i = 0; i < vertices.size(); i++)
        {
            file << R"(<node id="n)" << i << R"("/>)" << '\n';
        }
        // ���������� �����
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                if (adjacencyMatrix[i][j] != 0)
                {
                    file << R"(<edge source="n)" << i << R"(" target="n)" << j << R"(">)" << '\n';
                    file << R"(<data key="weight">)" << adjacencyMatrix[i][j] << R"(</data>)" << '\n';
                    file << R"(</edge>)" << '\n';
                }
            }
        }

        // ��������� ���� � ����
        file << R"(</graph>)" << '\n';
        file << R"(</graphml>)" << '\n';
        file.close();
    }

    
    ////����������
    ~WeightedGraph() {
        // ����������� ������, ���������� ��� ������� ������
      //  delete[] vertices;

        // ����������� ������, ���������� ��� ������� ���������
        for (int i = 0; i < numVertices; i++) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }


};
