#pragma once
//@author Maltseva K.V. 

#include <cassert>
#include <algorithm>
#include "Graph.h"
//Тестирование добавления вершин
void testAddVertex() {
    //Создаем пустой граф
    WeightedGraph<int> graph(5);

    //Проверяем, что граф пустой
    assert(graph.getNumVertices() == 0);

    // Добавляем вершины
    graph.addVertex(10);
    graph.addVertex(12);
    graph.addVertex(21);

    // Проверяем, что количество вершин увеличилось
    assert(graph.getNumVertices() == 3);

    // Ожидаемые вершины
    vector<int> expectedVertices = { 10, 12, 21 };

    // Получаем вершины из графа
    vector<int> actualVertices = graph.getVertices();

    // Проверяем, что количество вершин совпадает
    assert(actualVertices.size() == expectedVertices.size());

    // Проверяем, что вершины совпадают
    for (int i = 0; i < actualVertices.size(); i++) {
        assert(actualVertices[i] == expectedVertices[i]);
    }


    cout << "Тест добавление вершины пройден" << endl;

 
}
//Создание тестового дерева
WeightedGraph<int>* CreateGraph() {
    WeightedGraph<int>* graph = new WeightedGraph<int>(5);
    
    graph->addVertex(1); // Вершина 0
    graph->addVertex(2); // Вершина 1
    graph->addVertex(3); // Вершина 2
    graph->addVertex(4); // Вершина 3
    graph->addVertex(5); // Вершина 4

 
    return graph;

}

//Создание тестового дерева
WeightedGraph<int>* CreateGraphWithEdges() {
    WeightedGraph<int>* graph = new WeightedGraph<int>(6);
    graph->addVertex(0);  // Вершина 0
    graph->addVertex(1);  // Вершина 1
    graph->addVertex(2);  // Вершина 2
    graph->addVertex(3);  // Вершина 3
    graph->addVertex(4);  // Вершина 4
    graph->addVertex(5);  // Вершина 5

    // Добавляем ребра с весами
    graph->addEdge(0, 1, 10);
   
    graph->addEdge(1, 2, 5);
    graph->addEdge(2, 3, 8);
    graph->addEdge(3, 4, 3);

    return graph;

}
//Создание тестового дерева
WeightedGraph<int>* CreateGraphWithEdges1() {
    WeightedGraph<int>* graph = new WeightedGraph<int>(6);
    graph->addVertex(0);  // Вершина 0
    graph->addVertex(1);  // Вершина 1
    graph->addVertex(2);  // Вершина 2
    graph->addVertex(3);  // Вершина 3
    graph->addVertex(4);  // Вершина 4
    graph->addVertex(5);  // Вершина 5

    // Добавляем ребра с весами
    graph->addEdge(0, 1, 10);
    graph->addEdge(0, 2, -1);
    graph->addEdge(1, 2, 5);
    graph->addEdge(2, 3, 7);
    graph->addEdge(3, 4, 2);
    graph->addEdge(4, 5, -3);
    graph->addEdge(4, 0, 4);
    graph->addEdge(4, 1, 2);

    return graph;

}

//Тестирование обхода в ширину
void testBreadthFirst() {
    //создаем граф с ребрами
    WeightedGraph<int>* graph = CreateGraphWithEdges();
    graph->addEdge(1, 0, 11);
    //получаем вектор на основе обхода
    vector<int> actual = graph->BreadthFirst(1);
    //ожидаемый результат
    vector<int> expected = { 1, 0, 2, 3, 4 };
    //сравниваем ожидаемый результат с действительным
    assert(actual == expected);

    //создаем граф с ребрами
    WeightedGraph<int>* graph1 = CreateGraphWithEdges();
    //получаем вектор на основе обхода
    vector<int> actual1 = graph1->BreadthFirst(0);
    //ожидаемый результат
    vector<int> expected1 = { 0,1, 2, 3, 4 };
    //сравниваем ожидаемый результат с действительным
    assert(actual1 == expected1);

    //создаем граф с ребрами
    WeightedGraph<int>* graph2 = CreateGraphWithEdges1();
    //получаем вектор на основе обхода
    vector<int> actual2 = graph2->BreadthFirst(0);
    //ожидаемый результат
    vector<int> expected2 = { 0,1,2, 3, 4,5 };
    //сравниваем ожидаемый результат с действительным
    assert(actual2 == expected2);

   
    cout << "Тест обход в ширину пройден" << endl;

    delete graph;
    delete graph1;
    delete graph2;
}
//Тестирование обхода в глубину 
void testDephtFirst() {
    //создаем граф с ребрами
    WeightedGraph<int>* graph = CreateGraphWithEdges();
    graph->addEdge(1, 0, 11);
    //получаем вектор на основе обхода
    vector<int> actual = graph->DepthFirst(1);
    //ожидаемый результат
    vector<int> expected = { 1, 2, 3, 4,0};
    //сравниваем ожидаемый результат с действительным
    assert(actual == expected);

    //создаем граф с ребрами
    WeightedGraph<int>* graph1 = CreateGraphWithEdges();
    //получаем вектор на основе обхода
    vector<int> actual1 = graph1->DepthFirst(0);
    //ожидаемый результат
    vector<int> expected1 = { 0,1, 2, 3, 4 };
    //сравниваем ожидаемый результат с действительным
    assert(actual1 == expected1);

    //создаем граф с ребрами
    WeightedGraph<int>* graph2 = CreateGraphWithEdges1();
    //получаем вектор на основе обхода
    vector<int> actual2 = graph2->DepthFirst(0);
    //ожидаемый результат
    vector<int> expected2 = { 0,2, 3, 4,5 ,1};
    //сравниваем ожидаемый результат с действительным
    assert(actual2 == expected2);
    cout << "Тест обход в глубину пройден" << endl; 

    delete graph;
    delete graph1;
    delete graph2;
}

//Тестирование добавления ребра
void testAddEdge() {
    //Создаем граф без ребер
    WeightedGraph<int>* graph=  CreateGraph();

    // Добавляем ребра
    graph->addEdge(0, 1, 5);
    graph->addEdge(1, 2, 3);
    graph->addEdge(3, 1, 13);

    // Проверяем веса добавленных ребер
    assert(graph->getWeight(0, 1) == 5);
    assert(graph->getWeight(1, 2) == 3);
    assert(graph->getWeight(3, 1) == 13);

    cout << "Тест добавление ребра пройден" << endl;

    delete graph;
}

//Тестирование удаления ребра
void testRemoveEdge() {
    //Создаем граф с ребрами
    WeightedGraph<int>* graph = CreateGraphWithEdges();

    // Проверяем начальные веса ребер
    assert(graph->getWeight(0, 1) == 10);
    assert(graph->getWeight(1,2) == 5);
    assert(graph->getWeight(2, 3) == 8);
    assert(graph->getWeight(3, 4) == 3);

    // Удаляем ребра
    graph->removeEdge(1, 2);
    graph->removeEdge(3, 4);

    // Проверяем веса после удаления(ловим исключения)
    try {
   assert(graph->getWeight(1, 2) == 0);
   assert(graph->getWeight(2, 3) == 8);
   assert(graph->getWeight(3, 4) == 0);
   assert(graph->getWeight(4, 5) == 0);
    }
    catch (const invalid_argument& e){}

    cout << "Тест удаления ребра пройден" << endl;
    delete graph;
}
//Тестирование удаления вершины
void testRemoveVertex() {
    //Создаем граф с ребрами
    WeightedGraph<int>* graph = CreateGraphWithEdges();

    // Получаем количество вершин перед удалением
    int numVerticesBefore = graph->getNumVertices();

    // Удаляем вершину
    graph->removeVertex(2);

    // Проверяем, что количество вершин уменьшилось на 1
    assert(graph->getNumVertices() == numVerticesBefore - 1);


    // Проверяем, что вершина была удалена из списка вершин
    vector<int> vertices = graph->getVertices();
    //ищем 2 в векторе , если его нет, то результат должен быть равен конец итератора
    assert(find(vertices.begin(), vertices.end(), 2) == vertices.end());

    //Создаем пустой граф
    WeightedGraph<int>* graph2 = new WeightedGraph<int>(2);
    // Удаляем вершину и ловим исключение
    try {
    graph->removeVertex(2);
    assert(graph2->getNumVertices() == 0);
    }
    catch (const invalid_argument& e) {}

    cout << "Тест удаления вершины пройден" << endl;

    delete graph;
    delete graph2;

}

//Тестирование получение веса ребра
void testGetWeight() {
    // Создаем граф с ребрами
    WeightedGraph<int>* graph = CreateGraphWithEdges();

    // Проверяем веса ребер
    assert(graph->getWeight(0, 1) == 10);
    assert(graph->getWeight(1, 2) == 5);
    assert(graph->getWeight(2, 3) == 8);
    assert(graph->getWeight(3, 4) == 3);

   
    // Проверяем недопустимые вершины и отсутствующие ребра
    try {
        assert(graph->getWeight(1, 6) == 0);  
        assert(graph->getWeight(1, 4) == 0);
        assert(graph->getWeight(2, -1) == 0); 
    }catch(const invalid_argument &e){}

    cout << "Тест получения веса пройден" << endl;
    delete graph;
}
//Тестирование получения количества вершин
void testGetNumVertices() {
    // Создаем граф с ребрами
    WeightedGraph<int>* graph = CreateGraphWithEdges();
    // Проверяем, что фактическое количество вершин совпадает с ожидаемым
    assert(graph->getNumVertices() == 6);

    // Создаем граф без ребер
    WeightedGraph<int>* graph1 = CreateGraph();
    assert(graph1->getNumVertices() == 5);

    //Создаем пустой граф
    WeightedGraph<int>* graph2 = new WeightedGraph<int>(2);
    assert(graph2->getNumVertices() == 0);

    cout << "Тест получения количества вершин пройден" << endl;

    delete graph;
    delete graph1;
    delete graph2;
}
//Тестирование получения количества ребер
void testNumEdges() {
    // Создаем граф с ребрами
    WeightedGraph<int>* graph = CreateGraphWithEdges();
    // Проверяем, что фактическое количество ребер совпадает с ожидаемым
    assert(graph->NumEdges() == 4);

    // Создаем граф без ребер
    WeightedGraph<int>* graph1 = CreateGraph();
    assert(graph1->NumEdges() == 0);

    // Создаем пустой граф
    WeightedGraph<int>* graph2 = new WeightedGraph<int>(2);
    assert(graph2->NumEdges() == 0);
    cout << "Тест получения количества ребер пройден" << endl;

    delete graph;
    delete graph1;
    delete graph2;
}