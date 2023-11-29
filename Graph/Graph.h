#pragma once
//@author Maltseva K.V. 

#include <iostream>
#include<vector>

using namespace std;

//���������� ��������������� ����
template <class T>
class WeightedGraph {
private:
    int maxVertices;//������������ ������ �����
    int numVertices; // ���������� ������ �����
    int* vertices; // ������ ������ �����
    int** adjacencyMatrix; // ������� ���������
public:
   
    // ����������� � ���������� (������������ ������ �����)
    WeightedGraph(int _maxVertices) {
        maxVertices = _maxVertices;
        numVertices = 0;

        // �������� ������ ��� ������� ������ � �������������� ��� ���������� 
        vertices = new int[maxVertices];
        for (int i = 0; i < maxVertices; i++) {
            vertices[i] =  i + 1;
        }

        // �������� ������ ��� ������� ��������� � �������������� ���������� 0,��� ��� ���������� ������� �����
        adjacencyMatrix = new int* [maxVertices];
        for (int i = 0; i < maxVertices; i++) {
            adjacencyMatrix[i] = new int[maxVertices];
            for (int j = 0; j < maxVertices; j++) {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }
    
    //���������� �������
    void addVertex(const char& vertex) {
        if (numVertices >= maxVertices) {
            // ��������� ������������ ������ �����, ���������� ��������� ������
            int newMaxVertices = maxVertices * 2;

            // ������� ����� ������� ��������� � ����������� ��������
            int** newAdjacencyMatrix = new int* [newMaxVertices];
            for (int i = 0; i < newMaxVertices; i++) {
                newAdjacencyMatrix[i] = new int[newMaxVertices];
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
        vertices[numVertices] = vertex;

        // ����������� ���������� ������
        numVertices++;
    }
    //���������� �����
    void addEdge(const T& source, const T& destination, int weight) {
        // ���������, ��� ������� ��������� � ���������� ��������
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            // ��������� ����� � ����� � ������� 
            adjacencyMatrix[source][destination] = weight;
            adjacencyMatrix[destination][source] = weight; 
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

            // ������� ������� �� ������ ������, ������� ������� �����
            for (int i = vertex; i < numVertices - 1; i++) {
                vertices[i] = vertices[i + 1];
            }

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
        cout << "<���������� ������> = " << getNumVertices()<<endl;
        cout << "������ ������ �����: "<<endl;
        for (int i = 0; i < numVertices; i++) {
            cout<<"�������"<<i<<"  "<< vertices[i] << endl;
        }
        cout << endl;

        cout << "<���������� �����> = " << NumEdges() << endl;
        for (int i = 0; i < numVertices; i++) {
             for (int j = i + 1; j < numVertices; j++) {   // for (int j = 0; j < numVertices; j++)
                if (adjacencyMatrix[i][j] != 0) {
                    cout << "����� " << i << "-" << j << "  ���: " << adjacencyMatrix[i][j] << endl;
                }
            }
        }
        cout << "������� ���������:" << endl;
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {

                cout << adjacencyMatrix[i][j] << " ";
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
            for (int j = i; j < numVertices; j++) { //  for (int j = 0; j < numVertices; j++)
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
    //��������� ������� ������ �����
    vector<int> getVertices() const {
        vector<int> vertexVector;
        for (int i = 0; i < numVertices; i++) {
            vertexVector.push_back(vertices[i]);
        }
        return vertexVector;
    }

   /* void DepthFirstSearch(int node) {
        bool* visitedVertices = new bool[numVertices];
        for (int i = 0; i < numVertices; i++)
        {
            visitedVertices[i] = false;
        }
        visitedVertices[node] = true;
        cout << node + 1 << endl;
        for (int i = 0; i < numVertices; i++) {
            if (adjacencyMatrix[node][i] && visitedVertices[i]) {
                DepthFirstSearch(i);
            }
        }
        delete[] visitedVertices;
    }*/

   
    //����������
    ~WeightedGraph() {
        // ����������� ������, ���������� ��� ������� ������
        delete[] vertices;

        // ����������� ������, ���������� ��� ������� ���������
        for (int i = 0; i < numVertices; i++) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }
};
