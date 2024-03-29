﻿//@author Maltseva K.V. 

#include <iostream>
#include "Graph.h"
#include"TestGraph.h"
#include <fstream>

int main() {

    setlocale(LC_ALL, "rus");
    try {
    // Создаем граф
    WeightedGraph<int> graph(10);
    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2); 
    graph.addVertex(3);
    // Добавляем ребра с весами
    graph.addEdge(0, 1, 2);
    graph.addEdge(1, 0, 6);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 3, 3.6);

    graph.addVertex(4);
    graph.addEdge(4, 4, 9.7);
    cout << "Результат обхода в глубину:" << endl;
    graph.DepthFirst(0);
    cout << "Обход графа в ширину:" << endl;
    graph.BreadthFirst(0);
    graph.printGraph();
    graph.WriteToFile("graph.graphml");
    // Удаляем ребро между вершинами 
   // graph.removeEdge(0, 4);
 //   graph.removeVertex(2);
 //   graph.printGraph();
    int startNode = 1;
    
   graph.dijkstrasAlgorithm(startNode);
  // graph.bellmanFordAlgorithm(0);
    graph.printGraph();
    }
    catch (const invalid_argument& e) {
        // Обработка исключения
        cout << "Ошибка: " << e.what() << endl;
    }



    cout << "Тесты" << endl;
    testAddVertex();
    testAddEdge();
    testRemoveEdge();
    testGetWeight();
    testRemoveVertex();
    testGetNumVertices();
    testNumEdges();
    testBreadthFirst();
    testDephtFirst();
    testDijkstrasAlgorithm();
    testCopyConstructor();
    testCopyOperator();
    testMoveConstructor();
    //testMoveOperator();
    

    return 0;
}
