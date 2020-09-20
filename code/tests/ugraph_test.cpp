﻿///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Testing module for UGraph class.
///
/// © Sergey Shershakov 2020.
///
/// This code is for educational purposes of the course "Algorithms and Data 
/// Structures" provided by the School of Software Engineering of the Faculty 
/// of Computer Science at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///////////////////////////////////////////////////////////////////////////////


#include <gtest/gtest.h>

#include "ugraph/ugraph.hpp"


TEST(UGraph, simplest)
{
}


// Graph with integers as node ids.
typedef UGraph<int> IntGraph;

TEST(UGraph, simpleCreation)
{
    IntGraph g;
}

TEST(UGraph, edgeCreation)
{
    IntGraph::Edge e1;

    IntGraph::Edge e2 = {1, 2};
    EXPECT_EQ(1, e2.getS());
    EXPECT_EQ(2, e2.getD());

    IntGraph::Edge e3(3, 4);
    EXPECT_EQ(3, e3.getS());
    EXPECT_EQ(4, e3.getD());
}

TEST(UGraph, edgesEquivalence)
{

    IntGraph::Edge e1(1, 2);
    IntGraph::Edge e2(1, 2);
    IntGraph::Edge e3(2, 1);

    EXPECT_TRUE(e1 == e2);
    EXPECT_TRUE(e1 == e3);
}


// Tests an empty graph for its default properties.
TEST(UGraph, emptyGraphProps)
{
    IntGraph g;
    EXPECT_EQ(0, g.getVerticesNum());
    EXPECT_EQ(0, g.getEdgesNum());
}


// Tests an empty graph for its default properties.
TEST(UGraph, addEdge1)
{
    IntGraph g;
    EXPECT_EQ(0, g.getVerticesNum());
    EXPECT_EQ(0, g.getEdgesNum());

    EXPECT_FALSE(g.isVertexExists(1));
    EXPECT_FALSE(g.isVertexExists(3));


    g.addEdge(1, 2);
    EXPECT_EQ(2, g.getVerticesNum());
    EXPECT_EQ(1, g.getEdgesNum());

    EXPECT_TRUE(g.isVertexExists(1));
    EXPECT_FALSE(g.isVertexExists(3));


    g.addEdge(1, 3);
    EXPECT_EQ(3, g.getVerticesNum());
    EXPECT_EQ(2, g.getEdgesNum());

    EXPECT_TRUE(g.isVertexExists(1));
    EXPECT_TRUE(g.isVertexExists(3));
}

