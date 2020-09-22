////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief      Contains implementations of some algorithms for undirected graph.
/// \author     Sergey Shershakov
/// \version    0.1.0
/// \date       21.09.2020
/// \copyright  © Sergey Shershakov 2020.
///             This code is for educational purposes of the course "Algorithms
///             and Data Structures" provided by the Faculty of Computer Science
///             at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///
////////////////////////////////////////////////////////////////////////////////


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
