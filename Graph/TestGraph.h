#pragma once
//@author Maltseva K.V. 

#include <cassert>
#include <algorithm>
#include "Graph.h"
//������������ ���������� ������
void testAddVertex() {
    //������� ������ ����
    WeightedGraph<int> graph(5);

    //���������, ��� ���� ������
    assert(graph.getNumVertices() == 0);

    // ��������� �������
    graph.addVertex(10);
    graph.addVertex(12);
    graph.addVertex(21);

    // ���������, ��� ���������� ������ �����������
    assert(graph.getNumVertices() == 3);

    // ��������� �������
    vector<int> expectedVertices = { 10, 12, 21 };

    // �������� ������� �� �����
    vector<int> actualVertices = graph.getVertices();

    // ���������, ��� ���������� ������ ���������
    assert(actualVertices.size() == expectedVertices.size());

    // ���������, ��� ������� ���������
    for (int i = 0; i < actualVertices.size(); i++) {
        assert(actualVertices[i] == expectedVertices[i]);
    }


    cout << "���� ���������� ������� �������" << endl;

 
}
//�������� ��������� ������
WeightedGraph<int>* CreateGraph() {
    WeightedGraph<int>* graph = new WeightedGraph<int>(5);
    
    graph->addVertex(1); // ������� 0
    graph->addVertex(2); // ������� 1
    graph->addVertex(3); // ������� 2
    graph->addVertex(4); // ������� 3
    graph->addVertex(5); // ������� 4

 
    return graph;

}

//�������� ��������� ������
WeightedGraph<int>* CreateGraphWithEdges() {
    WeightedGraph<int>* graph = new WeightedGraph<int>(6);
    graph->addVertex(0);  // ������� 0
    graph->addVertex(1);  // ������� 1
    graph->addVertex(2);  // ������� 2
    graph->addVertex(3);  // ������� 3
    graph->addVertex(4);  // ������� 4
    graph->addVertex(5);  // ������� 5

    // ��������� ����� � ������
    graph->addEdge(0, 1, 10);
    graph->addEdge(1, 2, 5);
    graph->addEdge(2, 3, 8);
    graph->addEdge(3, 4, 3);

    return graph;

}

//������������ ���������� �����
void testAddEdge() {
    //������� ���� ��� �����
    WeightedGraph<int>* graph=  CreateGraph();

    // ��������� �����
    graph->addEdge(0, 1, 5);
    graph->addEdge(1, 2, 3);
    graph->addEdge(3, 1, 13);

    // ��������� ���� ����������� �����
    assert(graph->getWeight(0, 1) == 5);
    assert(graph->getWeight(1, 2) == 3);
    assert(graph->getWeight(3, 1) == 13);

    cout << "���� ���������� ����� �������" << endl;

    delete graph;
}

//������������ �������� �����
void testRemoveEdge() {
    //������� ���� � �������
    WeightedGraph<int>* graph = CreateGraphWithEdges();

    // ��������� ��������� ���� �����
    assert(graph->getWeight(0, 1) == 10);
    assert(graph->getWeight(1,2) == 5);
    assert(graph->getWeight(2, 3) == 8);
    assert(graph->getWeight(3, 4) == 3);

    // ������� �����
    graph->removeEdge(1, 2);
    graph->removeEdge(3, 4);

    // ��������� ���� ����� ��������(����� ����������)
    try {
   assert(graph->getWeight(1, 2) == 0);
   assert(graph->getWeight(2, 3) == 8);
   assert(graph->getWeight(3, 4) == 0);
   assert(graph->getWeight(4, 5) == 0);
    }
    catch (const invalid_argument& e){}

    cout << "���� �������� ����� �������" << endl;
    delete graph;
}
//������������ �������� �������
void testRemoveVertex() {
    //������� ���� � �������
    WeightedGraph<int>* graph = CreateGraphWithEdges();

    // �������� ���������� ������ ����� ���������
    int numVerticesBefore = graph->getNumVertices();

    // ������� �������
    graph->removeVertex(2);

    // ���������, ��� ���������� ������ ����������� �� 1
    assert(graph->getNumVertices() == numVerticesBefore - 1);


    // ���������, ��� ������� ���� ������� �� ������ ������
    vector<int> vertices = graph->getVertices();
    //���� 2 � ������� , ���� ��� ���, �� ��������� ������ ���� ����� ����� ���������
    assert(find(vertices.begin(), vertices.end(), 2) == vertices.end());

    //������� ������ ����
    WeightedGraph<int>* graph2 = new WeightedGraph<int>(2);
    // ������� ������� � ����� ����������
    try {
    graph->removeVertex(2);
    assert(graph2->getNumVertices() == 0);
    }
    catch (const invalid_argument& e) {}

    cout << "���� �������� ������� �������" << endl;

    delete graph;
    delete graph2;

}

//������������ ��������� ���� �����
void testGetWeight() {
    // ������� ���� � �������
    WeightedGraph<int>* graph = CreateGraphWithEdges();

    // ��������� ���� �����
    assert(graph->getWeight(0, 1) == 10);
    assert(graph->getWeight(1, 2) == 5);
    assert(graph->getWeight(2, 3) == 8);
    assert(graph->getWeight(3, 4) == 3);

   
    // ��������� ������������ ������� � ������������� �����
    try {
        assert(graph->getWeight(1, 6) == 0);  
        assert(graph->getWeight(1, 4) == 0);
        assert(graph->getWeight(2, -1) == 0); 
    }catch(const invalid_argument &e){}

    cout << "���� ��������� ���� �������" << endl;
    delete graph;
}
//������������ ��������� ���������� ������
void testGetNumVertices() {
    // ������� ���� � �������
    WeightedGraph<int>* graph = CreateGraphWithEdges();
    // ���������, ��� ����������� ���������� ������ ��������� � ���������
    assert(graph->getNumVertices() == 6);

    // ������� ���� ��� �����
    WeightedGraph<int>* graph1 = CreateGraph();
    assert(graph1->getNumVertices() == 5);

    //������� ������ ����
    WeightedGraph<int>* graph2 = new WeightedGraph<int>(2);
    assert(graph2->getNumVertices() == 0);

    cout << "���� ��������� ���������� ������ �������" << endl;

    delete graph;
    delete graph1;
    delete graph2;
}
//������������ ��������� ���������� �����
void testNumEdges() {
    // ������� ���� � �������
    WeightedGraph<int>* graph = CreateGraphWithEdges();
    // ���������, ��� ����������� ���������� ����� ��������� � ���������
    assert(graph->NumEdges() == 4);

    // ������� ���� ��� �����
    WeightedGraph<int>* graph1 = CreateGraph();
    assert(graph1->NumEdges() == 0);

    // ������� ������ ����
    WeightedGraph<int>* graph2 = new WeightedGraph<int>(2);
    assert(graph2->NumEdges() == 0);
    cout << "���� ��������� ���������� ����� �������" << endl;

    delete graph;
    delete graph1;
    delete graph2;
}