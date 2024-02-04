#include "MeshGraph.h"
#include "BinaryHeap.h"

// For printing
#include <fstream>
#include <iostream>
#include <sstream>

MeshGraph::MeshGraph(const std::vector<Double3> &vertexPositions,
                     const std::vector<IdPair> &edges)
{
    // TODO:
    vertices.resize(vertexPositions.size());
    adjList.resize(vertexPositions.size());
    for (int a = 0; a < (int)vertexPositions.size(); a++)
    {
        Vertex middle;
        middle.id = a;
        middle.position3D.x = vertexPositions[a].x;
        middle.position3D.y = vertexPositions[a].y;
        middle.position3D.z = vertexPositions[a].z;
        vertices[a] = middle;
    }

    for (int a = 0; a < (int)edges.size(); a++)
    {
        int firstid = edges[a].vertexId0;
        int secondid = edges[a].vertexId1;
        // ilk id deki index gidip ikinciyi ekle, ikinci index gidip ilkini ekle
        adjList[firstid].push_back(&vertices[secondid]);
        adjList[secondid].push_back(&vertices[firstid]);
    }
}

void MeshGraph::dijkstra(std::vector<int> &previous_array, int starting_point) const
{
    std::vector<double> distances(vertices.size(), INFINITY);
    BinaryHeap storage;
    int store_id;
    double store_weight; // distance of that vertex
    distances[starting_point] = 0;

    for (int i = 0; i < vertices.size(); i++)
    {
        storage.Add(i, INFINITY);
    }
    storage.ChangePriority(starting_point, 0);
    while (storage.HeapSize() != 0)
    {
        storage.PopHeap(store_id, store_weight);
        // std::cout << "popped id: " << store_id << std::endl;
        for (std::list<Vertex *>::const_iterator mover = adjList[store_id].begin(); mover != adjList[store_id].end(); mover++)
        {
            int komsu_id = (*mover)->id;
            double komsu_current_distance = (*mover)->position3D.Distance(vertices[store_id].position3D, (*mover)->position3D);

            if ((distances[store_id] + komsu_current_distance) < distances[komsu_id])
            {
                previous_array[komsu_id] = store_id;
                distances[komsu_id] = (distances[store_id] + komsu_current_distance);
                storage.ChangePriority(komsu_id, distances[komsu_id]);
            }
        }
    }

    /*
    for(storage.Add(starting_point,0); storage.HeapSize() != 0 ;){
        storage.PopHeap(store_id,store_weight);
        for(std::list<Vertex*>::const_iterator mover = adjList[store_id].begin(); mover != adjList[store_id].end();mover++){
            int komsu_id = (*mover)->id;
            int komsu_current_distance = (*mover)->position3D.Distance(vertices[store_id].position3D,(*mover)->position3D);
            //elimizde güncel fark var şu an liste başı ile şu komşu arası

            if( (distances[store_id] + komsu_current_distance ) < distances[komsu_id]){
                //yeni bulduğum daha küçük
                previous_array[komsu_id] = store_id;
                distances[komsu_id] = (distances[store_id] + komsu_current_distance);
                storage.Add(komsu_id,distances[komsu_id]);
            }
        }
    }
    */
    return;
}

double MeshGraph::AverageDistanceBetweenVertices() const
{
    // TODO:
    double total_number = 0;
    double total_edge = 0;
    for (int a = 0; a < (int)adjList.size(); a++)
    {
        for (std::list<Vertex *>::const_iterator mover = adjList[a].begin(); mover != adjList[a].end(); mover++)
        {
            double k = (*mover)->position3D.Distance((*mover)->position3D, vertices[a].position3D);
            total_number += k;
            total_edge++;
        }
    }
    return total_number / total_edge;
}

double MeshGraph::AverageEdgePerVertex() const
{
    // TODO:
    double total_edge = 0;
    for (int a = 0; a < (int)adjList.size(); a++)
    {
        for (std::list<Vertex *>::const_iterator mover = adjList[a].begin(); mover != adjList[a].end(); mover++)
        {
            total_edge++;
        }
    }
    return total_edge / ((double)vertices.size()*2);
}

int MeshGraph::TotalVertexCount() const
{
    // TODO:
    return vertices.size();
}

int MeshGraph::TotalEdgeCount() const
{
    // TODO:
    double total_edge = 0;
    for (int a = 0; a < (int)adjList.size(); a++)
    {
        for (std::list<Vertex *>::const_iterator mover = adjList[a].begin(); mover != adjList[a].end(); mover++)
        {
            total_edge++;
        }
    }
    return total_edge / 2;
}

int MeshGraph::VertexEdgeCount(int vertexId) const
{
    // TODO:
    int total_edge = 0;
    if ((vertexId < 0) || (vertexId >= vertices.size()))
        return -1;
    for (std::list<Vertex *>::const_iterator mover = adjList[vertexId].begin(); mover != adjList[vertexId].end(); mover++)
    {
        total_edge++;
    }
    return total_edge;
}

void MeshGraph::ImmediateNeighbours(std::vector<int> &outVertexIds,
                                    int vertexId) const
{
    // TODO:
    // önce vertex id var mı, sonra varsa listedekiler vektöre
    int exist_flag;
    for (int a = 0; a < (int)vertices.size(); a++)
        if (vertexId == vertices[a].id)
            exist_flag = 1;
    if (exist_flag == 0)
        return;
    for (std::list<Vertex *>::const_iterator mover = adjList[vertexId].begin(); mover != adjList[vertexId].end(); mover++)
    {
        outVertexIds.push_back((*mover)->id);
    }
    return;
}

void MeshGraph::PaintInBetweenVertex(std::vector<Color> &outputColorAllVertex,
                                     int vertexIdFrom, int vertexIdTo,
                                     const Color &color) const
{
    int from_exist = 0;
    int to_exist = 0;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].id == vertexIdFrom)
            from_exist = 1;
        else if (vertices[i].id == vertexIdTo)
            to_exist = 1;
    }
    if ((to_exist == 0) || (from_exist == 0)){
        outputColorAllVertex.resize(0);
        return;
    }

    outputColorAllVertex.resize(vertices.size());
    for (int a = 0; a < (int)outputColorAllVertex.size(); a++)
    {
        outputColorAllVertex[a].r = 0;
        outputColorAllVertex[a].b = 0;
        outputColorAllVertex[a].g = 0;
    }
    // find shortest path and modify between

    // heap kullanılacak, distance modifiye edildiğinde parent[i] de modifiye edilecek.

    // en yakın önceki vertex'in id'si tutulacak.
    std::vector<int> previous(vertices.size(), -1);
    std::vector<int> a;
    int v = vertexIdTo;

    dijkstra(previous, vertexIdFrom);
    // sonra kontroller cart curt
    while (v != vertexIdFrom)
    {
        a.push_back(v);
        v = previous[v];
    }
    a.push_back(vertexIdFrom);
    for (int b = a.size() - 1; b >= 0; b--)
    {
        outputColorAllVertex[a[b]] = color;
        //    std::cout << "the unique id:" << a[b] << std::endl;
    }
    return;
}

void MeshGraph::PaintInRangeGeodesic(std::vector<Color> &outputColorAllVertex,
                                     int vertexId, const Color &color,
                                     int maxDepth, FilterType type,
                                     double alpha) const
{
    // TODO:
    int filter_apply;
    std::vector<double> distance(vertices.size(), 0);
    distance[vertexId] = 0;

    std::vector<int> visited;

    // for depth:
    int depth = 0;
    int time_left = 1;
    bool pending_depth = false;

    BinaryHeap queue_like;
    int number_pushed = 0; // special holder for no:of pushings (to apply strictly increasing)
    int popped_id;
    double popped_weight; // we wont use just not to get an error

    if (type == FILTER_BOX)
        filter_apply = 1;
    else
        filter_apply = 0;

    // vertexId legal mi bak!!

    // heap kullanıp queue gibi davrandırılacak ama depth'e dikkat
    queue_like.Add(vertices[vertexId].id, number_pushed);
    visited.push_back(vertexId); // implementasyondan dolayı explicit eklemeliyim.
    number_pushed++;

    while (queue_like.HeapSize() != 0)
    {

        queue_like.PopHeap(popped_id, popped_weight);
        time_left--;

        if (time_left == 0)
        {
            depth++;
            pending_depth = true;
        }
        if (depth == 2)
            break;

        std::list<Vertex *> tmp = adjList[popped_id];
        tmp.sort();
        // sorted list now.

        for (std::list<Vertex *>::const_iterator mover = tmp.begin(); mover != tmp.end(); mover++)
        {
            int tmp_id = (*mover)->id;
            int in_visited = 0;
            for (int b = 0; b < visited.size(); b++)
            {
                if (visited[b] == tmp_id)
                {
                    in_visited = 1;
                    break;
                }
            }
            if (in_visited == 1) // do not add, already passed that
                continue;
            distance[tmp_id] = distance[popped_id] + (*mover)->position3D.Distance(vertices[popped_id].position3D, vertices[tmp_id].position3D);
            // distance modifiye ettim
            queue_like.Add(tmp_id, number_pushed);
            number_pushed++;
            visited.push_back(tmp_id);
        }
        if (pending_depth == true)
        {
            time_left = queue_like.HeapSize();
            pending_depth == false;
        }
    }
    // elimde visitedler ve distance'lar var
    // her visited için distance'a göre boya

    Color ex;
    ex.b = 0;
    ex.g = 0;
    ex.r = 0;
    outputColorAllVertex.resize(vertices.size(), ex);
    if (filter_apply == 1)
    {
        for (int k = 0; k < visited.size(); k++)
        {
            int visited_id = visited[k];
            double x = distance[visited_id];
            double multiply = exp(-(x * x) / (alpha * alpha));
            outputColorAllVertex[visited_id].b = (unsigned char)((double)(color.b) * multiply);
            outputColorAllVertex[visited_id].r = (unsigned char)((double)(color.r) * multiply);
            outputColorAllVertex[visited_id].g = (unsigned char)((double)(color.g) * multiply);
        }
    }
    else
    {
        for (int k = 0; k < visited.size(); k++)
        {
            int visited_id = visited[k];
            if ((-alpha < distance[visited_id]) && (distance[visited_id] < alpha))
                outputColorAllVertex[visited_id] = color;
        }
    }
    return;
}

void MeshGraph::PaintInRangeEuclidian(std::vector<Color> &outputColorAllVertex,
                                      int vertexId, const Color &color,
                                      int maxDepth, FilterType type,
                                      double alpha) const
{
    // TODO:
}

void MeshGraph::WriteColorToFile(const std::vector<Color> &colors,
                                 const std::string &fileName)
{
    // IMPLEMENTED
    std::stringstream s;
    for (int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        int r = static_cast<int>(colors[i].r);
        int g = static_cast<int>(colors[i].g);
        int b = static_cast<int>(colors[i].b);

        s << r << ", " << g << ", " << b << "\n";
    }
    std::ofstream f(fileName.c_str());
    f << s.str();
}

void MeshGraph::PrintColorToStdOut(const std::vector<Color> &colors)
{
    // IMPLEMENTED
    for (int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        std::cout << static_cast<int>(colors[i].r) << ", "
                  << static_cast<int>(colors[i].g) << ", "
                  << static_cast<int>(colors[i].b) << "\n";
    }
}