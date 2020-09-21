/*! \file ugraph_algos.hpp
 *  Contains implementations of some algorithms for undirected graph.
 */

#ifndef UGRAPH_ALGOS_HPP
#define UGRAPH_ALGOS_HPP

#include <set>

#include "lbl_ugraph.hpp"


/// Finds a MST for the given graph \a g using Prim's algorithm.
template<typename Vertex, typename EdgeLbl>
std::set<typename EdgeLblUGraph<Vertex, EdgeLbl>::Edge>
    findMSTPrim(const EdgeLblUGraph<Vertex, EdgeLbl>& g)
{
    // TODO:
}

/// Finds a MST for the given graph \a g using Kruskal's algorithm.
template<typename Vertex, typename EdgeLbl>
std::set<typename EdgeLblUGraph<Vertex, EdgeLbl>::Edge>
    findMSTKruskal(const EdgeLblUGraph<Vertex, EdgeLbl>& g)
{
    // TODO:
}





#endif // UGRAPH_ALGOS_HPP
