#include <iostream>
#include <set>
#include <map>
#include <memory>
#include <list>
#include <Eigen/Dense>
#include "problem81.h"

typedef std::string Node;
template<class WeightT>
struct Graph {
	struct Edge {
		Edge(const std::string& node, WeightT weight = 0)
			: mOutNode(node)
			, mWeight(weight)
		{}
		Node mOutNode;
		WeightT mWeight;
		bool operator<(const Edge& other) const { return mOutNode < other.mOutNode; }
	};
	void connectFromToNodes(const Node& fromNode, const Node& toNode, WeightT weight = 0)
	{
		if ( mConnectivityList.contains(fromNode) )
		{
			auto& edgeMap = mConnectivityList.at(fromNode);
			if(edgeMap.contains({toNode}))
				edgeMap.erase(toNode);
			
			edgeMap.insert({toNode, weight});
				
		}
		else
			mConnectivityList.insert(std::make_pair(fromNode, std::set<Edge>({Edge{toNode, weight}})));
	}
	
	void disconnectFromToNodes(const Node& fromNode, const Node& toNode)
	{
		if ( mConnectivityList.contains(fromNode) )
		{
			std::set<Edge>& edgeMap = mConnectivityList.at(fromNode);
			auto it = std::remove_if(edgeMap.begin(), 
									 edgeMap.end(), 
									 [&toNode](const Edge& val){ return val.outNode == toNode; });
			
		}
	}
	const std::set<Edge>& edgesFrom(const Node& node) const
	{
		if(mConnectivityList.contains(node))
			return mConnectivityList.at(node);
		
		static const std::set<Edge> empty;
		return empty;
	}

	std::map<Node, std::set<Edge>> mConnectivityList;
	
};

namespace std
{
template<class T, class P, class WeightT>
std::basic_ostream<T, P>& operator<<(std::basic_ostream<T, P>& stream, const Graph<WeightT>& graph)
{
	for(const auto& connections : graph.mConnectivityList)
	{
		stream << connections.first << std::endl << "\t";
		stream.flush();
		for(const auto& edge : connections.second)
		{
			stream << "[" << edge.mOutNode << " : " << edge.mWeight << "]";
			stream.flush();
		}
		stream << std::endl;
	}
	return stream;
}

}

enum Direction {
	Left,
	Right,
	Top,
	Bottom
};

template<class T>
Graph<T> matrixToGraph(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& matr,
					std::set<Direction> directions)
{
	Graph<T> graph;
	for(int i = 0; i < matr.rows(); i++)
		for(int j = 0; j < matr.cols(); j++)
		{
			for(auto dir : directions)
			{
				int ro = 0, co = 0;
				switch(dir)
				{
				case Left: co = -1; break;
				case Right: co = 1; break;
				case Top: ro = -1; break;
				case Bottom: ro = 1; break;
				default: assert(0 && "failure");
				}
				if(i + ro < 0 ||
						i + ro >= matr.rows() ||
						j + co < 0 ||
						j + co >= matr.cols())
					continue;

				graph.connectFromToNodes(std::to_string(i) + "," + std::to_string(j),
										 std::to_string(i + ro) + "," + std::to_string(j + co),
										 matr(i + ro, j + co));
			}
		}
	return graph;
}

template<class T>
T findMinPath(const Node& startNode, const Node& endNode, const Graph<T>& graph)
{
	std::set<Node> traverseNodesSet{startNode};
	std::map<Node, T> nodePathMinSums {std::make_pair(startNode, 0)};
	while( !traverseNodesSet.empty() )
	{
		const auto& node = *traverseNodesSet.begin();
		assert(nodePathMinSums.contains(node));
		const auto& edges = graph.edgesFrom(node);
		for(const auto& c : edges)
		{
			if(!nodePathMinSums.contains(c.mOutNode) || 
					(nodePathMinSums.at(node) + c.mWeight) < nodePathMinSums.at(c.mOutNode))
			{
				nodePathMinSums[c.mOutNode] = nodePathMinSums.at(node) + c.mWeight;
				traverseNodesSet.insert(c.mOutNode);
			}
		}
		traverseNodesSet.erase(node);
	}
	
	if(!nodePathMinSums.contains(endNode))
	{
		std::cout << "No path from " << startNode << " to " << endNode << std::endl;
		return T(0);
	}
	else
		return nodePathMinSums.at(endNode);
} 
int main(int ac, char** av)
{
	auto matr = readoffMatrix(av[1]);
	auto newGraph = matrixToGraph(matr, {Direction::Bottom, Direction::Right, Direction::Top});
	
	for(int i = 0; i < matr.rows(); i++)
	{
		newGraph.connectFromToNodes("begin", std::to_string(i) + ",0", matr(i, 0));
		newGraph.connectFromToNodes(std::to_string(i) + "," + std::to_string(matr.cols() - 1), "end", 0);
	}
	std::cout << matr << std::endl;
	std::cout << newGraph << std::endl;
	std::cout << "min path: " << findMinPath<int>("begin", "end", newGraph);

}


