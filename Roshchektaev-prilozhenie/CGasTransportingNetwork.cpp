#pragma once
#include "CGasTransportingNetwork.h"
#include "Cpipe.h"
#include "CStation.h"
#include "Utils.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <queue>


void CGasTransportingNetwork::showConnection(const std::unordered_map<uint32_t, CPipe>& mP, const std::unordered_map<uint32_t, CStation>& mS)
{
    uint32_t flag = 0;
    if (mP.size() > 0 && mS.size() > 1)
    {
        for (auto& [i, p] : mP)
        {
            if (p.linked())
                p.showLink();
            flag += i;
        }
        if (flag==0)
            std::cout << "There are no pipes with connections!" << std::endl;
    }
    else
        std::cout << "There are no pipes or stations!" << std::endl;
}

void CGasTransportingNetwork::addConnection(std::unordered_map<uint32_t, CPipe>& mP, std::unordered_map<uint32_t, CStation>& mS)
{
    if ((mP.size() > 0) && (mS.size() > 1))
    {
        std::vector<uint32_t> result{};
        std::cout << "Enter pipe diameter to add connection: ";
        double_t pDiameter = getCorrectPipeDiameter();

        for (auto& [pID, p] : mP)
        {
            if (checkByDiameter(p, pDiameter) && !p.linked())
            {
                result.push_back(p.getPipeID());
            }
        }

        uint32_t pipeId;

        if (result.empty())
        {
            std::cout << "There are no avaiable pipes with this parameter\n";
            CPipe pipe;
            std::cin >> pipe;
            mP.insert({ pipe.getPipeID(), pipe });
           pipeId = mP[1].newPipeID;
        }
        
        if (!result.empty())
        {
          pipeId = result[0];
        }

        std::cout << "Enter station id OUT: " << std::endl;
        uint32_t out = SearchId(mS, getCorrect(out));
        std::cout << "Enter station id IN: " << std::endl;
        uint32_t in = SearchId(mS, getCorrect(in));

        if (mP[pipeId].inStationID == 0 && mP[pipeId].outStationID == 0 && out != -1 && in != -1 && out != in)
        {
            mP[pipeId].link(in, out);
            mS[in].createLink();
            mS[out].createLink();
        }
        else
        {
            std::cout << "Error! Pipe already connected!";
        }
    }
    else
    {
        std::cout << "Not enough pipes or stations to connect\n";
    }
}

void CGasTransportingNetwork::deleteConnection(std::unordered_map<uint32_t, CPipe>& mP, std::unordered_map<uint32_t, CStation>& mS)
{
    if (mP.size() > 0 && mS.size() > 1)
    {
        std::cout << "Enter pipe id: " << std::endl;
        uint32_t pipeId = SearchId(mP, getCorrect(pipeId));
        if (pipeId != -1 && mP[pipeId].linked())
        {
            mP[pipeId].clearLink();
            mS[mP[pipeId].inStationID].clearLink();
            mS[mP[pipeId].outStationID].clearLink();
            std::cout << "Pipe and stations are disconnected!\n";
        }
        else
            std::cout << "There are no pipes with this id or pipe isn't connected" << std::endl;
    }
    else
        std::cout << "There are no pipes or stations!" << std::endl;
}

std::unordered_map<uint32_t, uint32_t> CGasTransportingNetwork::createIndexOfVertices(const std::unordered_map<uint32_t, CPipe>& mP, std::unordered_map<uint32_t, CStation>& mS)
{
    std::set<uint32_t> vertices;
    for (const auto& [i, p] : mP)
        if (p.canBeUsed() && mS.count(p.inStationID) && mS.count(p.outStationID))
        {
            vertices.insert(p.outStationID);
            vertices.insert(p.inStationID);
        }

    std::unordered_map<uint32_t, uint32_t> verticesIndex;
    uint32_t i = 0;
    for (const uint32_t& v : vertices)
        verticesIndex.insert({ v, i++ });


    return verticesIndex;
}

std::unordered_map<uint32_t, uint32_t> CGasTransportingNetwork::createIndexOfVerticesReverse(const std::unordered_map<uint32_t, CPipe>& mP, std::unordered_map<uint32_t, CStation>& mS)
{
    std::set<uint32_t> vertices;
    for (const auto& [i, p] : mP)
        if (p.canBeUsed() && mS.count(p.inStationID) && mS.count(p.outStationID))
        {
            vertices.insert(p.outStationID);
            vertices.insert(p.inStationID);
        }
    std::unordered_map<uint32_t, uint32_t> verticesIndex;
    uint32_t i = 0;
    for (const uint32_t& v : vertices)
        verticesIndex.insert({ i++, v });

    return verticesIndex;
}

std::vector<std::vector<uint32_t>> CGasTransportingNetwork::createGraph(const std::unordered_map<uint32_t, CPipe>& mP, std::unordered_map<uint32_t, CStation>& mS)
{
    std::unordered_map<uint32_t, uint32_t> verticesIndex = createIndexOfVertices(mP, mS);
    std::vector<std::vector<uint32_t>> result;
    result.resize(verticesIndex.size());
    for (const auto& [i, p] : mP)
        if (p.canBeUsed())
            result[verticesIndex[p.outStationID]].push_back(verticesIndex[p.inStationID]);

    return result;
}

std::vector<std::vector<double>> CGasTransportingNetwork::createMatrixWeights(const std::unordered_map<uint32_t, CPipe>& mP, std::unordered_map<uint32_t, CStation>& mS)
{
    std::unordered_map<uint32_t, uint32_t> verticesIndex = createIndexOfVertices(mP, mS);
    std::vector<std::vector<double>> weights;
    weights.assign(verticesIndex.size(), {});
    for (uint32_t i = 0; i < verticesIndex.size(); ++i)
    {
        weights[i].assign(verticesIndex.size(), INT_MAX);
        weights[i][i] = 0;
    }
    for (const auto& [i, p] : mP)
        if (p.canBeUsed())
            weights[verticesIndex[p.outStationID]][verticesIndex[p.inStationID]] = p.length;
    
    return weights;
}

std::vector<std::vector<uint32_t>> CGasTransportingNetwork::createMatrixThroughput(const std::unordered_map<uint32_t, CPipe>& mP, std::unordered_map<uint32_t, CStation>& mS)
{
    std::unordered_map<uint32_t, uint32_t> verticesIndex = createIndexOfVertices(mP, mS);
    std::vector<std::vector<uint32_t>> throughput;
    throughput.assign(verticesIndex.size(), {});
    for (int i = 0; i < verticesIndex.size(); ++i)
        throughput[i].assign(verticesIndex.size(), 0);
    for (const auto& [i, p] : mP)
        if (p.canBeUsed())
            throughput[verticesIndex[p.outStationID]][verticesIndex[p.inStationID]] = p.getProductivity();
    
    return throughput;
}

void CGasTransportingNetwork::depthFirstSearch(uint32_t vertices, std::vector<char>& cl, std::vector<uint32_t>& p, uint32_t& cycleStart, const std::vector<std::vector<uint32_t>>& ribs, std::vector<uint32_t>& result)
{
    cl[vertices] = 1;
    for (size_t i = 0; i < ribs[vertices].size(); ++i)
    {
        uint32_t to = ribs[vertices][i];
        if (cl[to] == 0) {
            p[to] = vertices;
            depthFirstSearch(to, cl, p, cycleStart, ribs, result);
        }
        else if (cl[to] == 1)
        {
            cycleStart = to;
            return;
        }
    }

    result.push_back(vertices);
    cl[vertices] = 2;
}

void CGasTransportingNetwork::topologicalSort(const std::unordered_map<uint32_t, uint32_t>& verticesIndex)
{
    uint32_t n = ribs.size();
    std::vector<uint32_t> result;
    std::vector<char> cl;
    std::vector<uint32_t> p;
    uint32_t cycleStart;
    p.assign(n, -1);
    cl.assign(n, 0);
    cycleStart = -1;
    result.clear();
    for (int i = 0; i < n; ++i)
        if (cl[i] != 2)
            depthFirstSearch(i, cl, p, cycleStart, ribs, result);
    if (cycleStart == -1) {
        std::cout << "Cycle not found!" << std::endl;
        reverse(result.begin(), result.end());
        for (uint32_t i = 0; i < result.size(); i++) {
            std::cout << i + 1 << " Station: " << verticesIndex.at(result[i]) << std::endl;
        }
    }
    else
        std::cout << "Sorting is not avaiable, because of cycle " << std::endl;
}

void CGasTransportingNetwork::showTopologicalSort(const std::unordered_map<uint32_t, CPipe>& mP, std::unordered_map<uint32_t, CStation>& mS)
{
    ribs = createGraph(mP, mS);
    weightsMatrix = createMatrixWeights(mP, mS);
    throughputMatrix = createMatrixThroughput(mP, mS);
    std::unordered_map<uint32_t, uint32_t> verticesIndex = createIndexOfVertices(mP, mS);
    std::unordered_map<uint32_t, uint32_t> verticesIndexForOutput = createIndexOfVerticesReverse(mP, mS);
    topologicalSort(verticesIndexForOutput);
}

void CGasTransportingNetwork::maxStream(uint32_t start, uint32_t finish, const std::unordered_map<uint32_t, uint32_t>& verticesIndexForOutput)
{
    uint32_t n = throughputMatrix.size();
    std::vector<std::vector<uint32_t>> c = throughputMatrix;
    double_t maxFlow = 0;                                                       //Ќачальный максимальный поток
    while (true)
    {
        /* ѕоиск в ширину */
        std::vector <uint32_t> parent(n, -1);
        std::vector <bool> used(n, false);
        std::queue <int> q;

        used[start] = true;
        q.push(start);

        while (!q.empty())
        {
            uint32_t v = q.front();
            q.pop();
            for (int i = 0; i < n; i++)
            {
                if (!used[i] && c[v][i] > 0)
                {
                    parent[i] = v;
                    used[i] = true;
                    q.push(i);
                }
            }
        }
        if (!used[finish])                                                           //Ќе дошли до стока - поток уже максимальный
            break;
        uint32_t augFlow = INT_MAX;

        /* »щем ребро с минимальной пропускной способностью - оно насытитс€ */
        uint32_t ptr = finish;
        while (ptr != start)
        {
            augFlow = std::min(augFlow, c[parent[ptr]][ptr]);
            ptr = parent[ptr];
        }
        /* »змен€ем пропускные способности проход€ по пути */
        ptr = finish;
        while (ptr != start)
        {
            c[parent[ptr]][ptr] -= augFlow; 
            c[ptr][parent[ptr]] += augFlow;
            ptr = parent[ptr];
        }
        maxFlow += augFlow;
    }
    std::cout << "Max stream: " << maxFlow << std::endl;
}

void CGasTransportingNetwork::findMaxStream(const std::unordered_map<uint32_t, CPipe>& mP, std::unordered_map<uint32_t, CStation>& mS)
{
    ribs = createGraph(mP, mS);
    weightsMatrix = createMatrixWeights(mP, mS);
    throughputMatrix = createMatrixThroughput(mP, mS);
    std::unordered_map<uint32_t, uint32_t> verticesIndex = createIndexOfVertices(mP, mS);
    std::unordered_map<uint32_t, uint32_t> verticesIndexForOutput = createIndexOfVerticesReverse(mP, mS);
    
    uint32_t start;
    uint32_t finish;
    std::cout << "Enter start vertice (id station): " << std::endl;
    start = SearchId(mS, getCorrect(start));
    std::cout << "Enter finish vertice(id station) : " << std::endl;
    finish = SearchId(mS, getCorrect(finish));
    if (start == -1 || finish == -1 || start == finish) return;
    maxStream(verticesIndex[start], verticesIndex[finish], verticesIndexForOutput);
}

void CGasTransportingNetwork::findWay(uint32_t start, uint32_t finish, const std::unordered_map<uint32_t, uint32_t>& verticesIndexForOutput)
{
    std::vector<std::vector<double_t>> res = weightsMatrix;
    std::vector<std::vector<uint32_t>> next;                                                      // матрица дл€ восстановлени€ пути
    uint32_t n = res.size();
    next.resize(n);
    for (uint32_t i = 0; i < n; i++)
        for (uint32_t t = 0; t < n; t++)
            next[i].push_back(t);
    for (uint32_t k = 0; k < n; k++)
        for (uint32_t i = 0; i < n; i++)
            for (uint32_t j = 0; j < n; j++)
                if (res[i][j] > res[i][k] + res[k][j])
                {
                    res[i][j] = res[i][k] + res[k][j];
                    next[i][j] = next[i][k];
                }
    if (res[start][finish] == INT_MAX)
    {
        std::cout << "There is no way!" << std::endl;
        return;
    }
    std::cout << "Way from station " << verticesIndexForOutput.at(start) << " to station " << verticesIndexForOutput.at(finish) << " is " << res[start][finish] << std::endl << "Way: " << std::endl;
    uint32_t temp = start;
    while (temp != finish)
    {
        std::cout << verticesIndexForOutput.at(temp) << " -> ";
        temp = next[temp][finish];
    }
    std::cout << verticesIndexForOutput.at(finish) << std::endl;
}

void CGasTransportingNetwork::showFindWay(const std::unordered_map<uint32_t, CPipe>& mP, std::unordered_map<uint32_t, CStation>& mS)
{
    ribs = createGraph(mP, mS);
    weightsMatrix = createMatrixWeights(mP, mS);
    throughputMatrix = createMatrixThroughput(mP, mS);
    std::unordered_map<uint32_t, uint32_t> verticesIndex = createIndexOfVertices(mP, mS);
    std::unordered_map<uint32_t, uint32_t> verticesIndexForOutput = createIndexOfVerticesReverse(mP, mS);

    uint32_t start;
    uint32_t finish;
    std::cout << "Enter start vertice (id station): " << std::endl;
    start = SearchId(mS, getCorrect(start));
    std::cout << "Enter finish vertice(id station) : " << std::endl;
    finish = SearchId(mS, getCorrect(finish));
    if (start == -1 || finish == -1 || start == finish) return;
    findWay(verticesIndex[start], verticesIndex[finish], verticesIndexForOutput);
}




bool checkByDiameter(const CPipe& p, double parameter)
{
    return p.diameter == parameter;
}



