#pragma once
//@author Maltseva K.V. 

#include <iostream>
#include<vector>

using namespace std;

//взвешанный ориентированный граф
template <class T>
class WeightedGraph {
private:
    int maxVertices;//Максимальный размер графа
    int numVertices; // Количество вершин графа
    int* vertices; // Массив вершин графа
    int** adjacencyMatrix; // Матрица смежности
public:
   
    // Конструктор с параметром (максимальный размер графа)
    WeightedGraph(int _maxVertices) {
        maxVertices = _maxVertices;
        numVertices = 0;

        // Выделяем память для массива вершин и инициализируем его значениями 
        vertices = new int[maxVertices];
        for (int i = 0; i < maxVertices; i++) {
            vertices[i] =  i + 1;
        }

        // Выделяем память для матрицы смежности и инициализируем значениями 0,так как изначально матрица пуста
        adjacencyMatrix = new int* [maxVertices];
        for (int i = 0; i < maxVertices; i++) {
            adjacencyMatrix[i] = new int[maxVertices];
            for (int j = 0; j < maxVertices; j++) {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }
    
    //добавление вершины
    void addVertex(const char& vertex) {
        if (numVertices >= maxVertices) {
            // Достигнут максимальный размер графа, необходимо расширить память
            int newMaxVertices = maxVertices * 2;

            // Создаем новую матрицу смежности с увеличенным размером
            int** newAdjacencyMatrix = new int* [newMaxVertices];
            for (int i = 0; i < newMaxVertices; i++) {
                newAdjacencyMatrix[i] = new int[newMaxVertices];
            }

            // Копируем значения из старой матрицы смежности в новую 
            for (int i = 0; i < maxVertices; i++) {
                memcpy(newAdjacencyMatrix[i], adjacencyMatrix[i], maxVertices * sizeof(int));
            }

            // Инициализируем новые элементы значением 0
            for (int i = maxVertices; i < newMaxVertices; i++) {
                memset(newAdjacencyMatrix[i], 0, newMaxVertices * sizeof(int));
            }

            // Освобождаем память старой матрицы смежности
            for (int i = 0; i < maxVertices; i++) {
                delete[] adjacencyMatrix[i];
            }
            delete[] adjacencyMatrix;

            // Обновляем указатель на новую матрицу смежности и максимальный размер
            adjacencyMatrix = newAdjacencyMatrix;
            maxVertices = newMaxVertices;
        }

        // Добавляем новую вершину в массив вершин
        vertices[numVertices] = vertex;

        // Увеличиваем количество вершин
        numVertices++;
    }
    //добавление ребра
    void addEdge(const T& source, const T& destination, int weight) {
        // Проверяем, что вершины находятся в допустимых пределах
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            // Добавляем ребро с весом в матрицу 
            adjacencyMatrix[source][destination] = weight;
            adjacencyMatrix[destination][source] = weight; 
        }
        else {
           
            // генерируем исключение 
            throw invalid_argument("Отсутствуют вершины, нельзя добавить ребро");
        }
    }
    //удаление ребра
    void removeEdge(const T& source, const T& destination) {
        // Проверяем, что вершины находятся в допустимых пределах
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            // Удаляем ребро из матрицы смежности
            adjacencyMatrix[source][destination] = 0;
        }
        else {
           
             // генерируем исключение 
            throw invalid_argument("Такого ребра в графе нет");
        }
    }
    //удаление вершины
    void removeVertex(const T& vertex) {
        // Проверяем, что вершина находится в допустимых пределах
        if (vertex >= 0 && vertex < numVertices) {

            // Удаляем вершину из списка вершин, сдвигая вершину влево
            for (int i = vertex; i < numVertices - 1; i++) {
                vertices[i] = vertices[i + 1];
            }

            // Удаляем строку и столбец, соответствующие вершине, из матрицы смежности
            //сдвигаясь на позицию влево по столбцу и вверх по строке
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
            //уменьшаем количество вершин в графе
            numVertices--;
        }
        //иначе генерируем исключение
        else {
            throw invalid_argument("Такой вершины в графе нет");
        }
    }


    // печать данных о графе 
    void printGraph() {
        cout << "<Количество вершин> = " << getNumVertices()<<endl;
        cout << "Список вершин графа: "<<endl;
        for (int i = 0; i < numVertices; i++) {
            cout<<"Вершина"<<i<<"  "<< vertices[i] << endl;
        }
        cout << endl;

        cout << "<Количество ребер> = " << NumEdges() << endl;
        for (int i = 0; i < numVertices; i++) {
             for (int j = i + 1; j < numVertices; j++) {   // for (int j = 0; j < numVertices; j++)
                if (adjacencyMatrix[i][j] != 0) {
                    cout << "Ребро " << i << "-" << j << "  Вес: " << adjacencyMatrix[i][j] << endl;
                }
            }
        }
        cout << "Матрица смежности:" << endl;
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {

                cout << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

   
    //количество вершин в графе
    int getNumVertices() const{
        return numVertices;
    }
    //количество ребер в графе
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
    //получить вес между вершинами
    int getWeight(const T& source, const T& destination) {
        // Проверяем, что вершины находятся в допустимых пределах
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            // Возвращаем вес ребра из матрицы 
            return adjacencyMatrix[source][destination];
        }
        //иначе генерируем исключение
        else {
           
            throw invalid_argument("Отсутствуют вершины или ребро");
            //return -1;
        }
    }
    //Получение вектора вершин графа
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

   
    //деструктор
    ~WeightedGraph() {
        // Освобождаем память, выделенную для массива вершин
        delete[] vertices;

        // Освобождаем память, выделенную для матрицы смежности
        for (int i = 0; i < numVertices; i++) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }
};
