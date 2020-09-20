/*! \file udgraph.hpp
 *  Contains declarations of the types for undirected graphs.
 */

#ifndef UDGRAPH_HPP
#define UDGRAPH_HPP


#include <set>
#include <map>
//#include <vector>
//#include <cstddef> // size_t
//#include <iostream>


/*! ****************************************************************************
 *  \brief The UGraph class represents a undirected graph.
 *
 *  \tparam TVertex represents a type for vertices. Will be used as a node ID by
 *  copy, so choose it cleverly. Must be comparable.
 ******************************************************************************/
template <typename TVertex>
class UGraph {
public:
    // type definitions

    /// \brief Custom datatype for representing Edge of a graph as an unordered pair
    /// of nodes.
    ///
    /// Stores vertices normalized, which means that “smaller” vertex is always
    /// stored as _s, ad “bigger” as _d.
    class Edge {
    public:
        // constructors and all
        Edge() : _s(TVertex()), _d(TVertex()) { }

        Edge(TVertex s, TVertex d)
        {
            // we always put “smaller” node as “source”
            if(s < d)
            {
                _s = s;
                _d = d;
            }
            else
            {
                _s = d;
                _d = s;
            }
        }

    public:
        // Comparison operator
        bool operator==(const Edge& other) const
        {
            // {a, b} == {a, b} OR
            // {a, b} == {b, a}

            return (_s == other._s && _d == other._d);
                  // || (s == other.d && d == other.s);
        }

    public:
        // setter/getters
        TVertex getS() const { return _s; }
        TVertex getD() const { return _d; }

    protected:
        /// Relatively speaking, source and destination nodes.
        TVertex _s, _d;

    }; // struct Edge

    /// Set of vertices.
    typedef std::set<TVertex> VerticesSet;

    /// \brief Adjacency list datatype, for storing adjacent vertices.
    ///
    /// Consists of exactly twice more elements than the number of edges in a
    /// graph (think of why).
    typedef std::multimap<TVertex, TVertex> AdjList;


public:
    // Graph structure modifying methods.

    /// Adds into this graph a new vertex \a v and returns it by value.
    TVertex addVertex(TVertex v)
    {
        _vertices.insert(v);
        return v;
    }

    /// \brief Adds into this graph a new edge made of two vertices.
    /// \return An object of type Edge with normalized positions of vertices.
    ///
    /// If a correponding edge {s, d} or equivalent {d, s} has been added earlier,
    /// do nothing else as just return an edge object.
    Edge addEdge(TVertex s, TVertex d)
    {
        if(!isEdgeExists(s, d))      // need to add
        {
            // add two collinear edges
            _edges.insert({s, d});
            _edges.insert({d, s});

            // add edges vertices too
            _vertices.insert(s);
            _vertices.insert(d);
        }
        Edge e(s, d);

        return e;
    }

    /// Method determines whether an edge {s, d} exists in this graph.
    ///
    /// \return true if the edge exists, false otherwise.
    ///
    /// Graph guarantees that is a vertex {a, b} exists then its counterpart
    /// {b, a} exists too.
    bool isEdgeExists(TVertex s, TVertex d) const
    {
        auto itlow = _edges.lower_bound(s);
        auto itup = _edges.upper_bound(s);
        for (auto it = itlow; it != itup; ++it)
        {
            if(it->second == d)
                return true;
        }

        return false;
    }

    bool isVertexExists(TVertex v) const
    {
        return (_vertices.find(v) != _vertices.end());
    }



public:
    // setters/getters
    size_t getVerticesNum() const { return _vertices.size(); }
    size_t getEdgesNum() const { return _edges.size() / 2; }


protected:
    VerticesSet _vertices;      ///< Set of vertices.
    AdjList _edges;             ///< Adjacency list for representing edges.
}; // class UGraph
















//class Matrix {
//public:
//    typedef std::vector<double> MatrixVector;
//    typedef MatrixVector RowVector;
//    typedef MatrixVector ColVector;
//    typedef std::vector<RowVector> VectorOfRows;
//    typedef std::pair<size_t, size_t> SizePair;



//public:

//    // When we do not define any constructorsin a class, then
//    // the compiler creates the default one for us.
//    // Since we add any other type of constructors, the default
//    // constructor is not available anymore.
//    Matrix() { }


//    /// The initializing constuctor.
//    Matrix(size_t m, size_t n, double def = 42);


//    /// Resizes the current matrix up to m*n cells.
//    /// \a def is a defualt value for each newly added cell.
//    void resize(size_t m, size_t n, double def = 0);

//    /// Overloaded version of the resize() method dispatching the packed size.
//    /// We define the body of the method right here, which makes it inline.
//    /*inline*/ void resize(const SizePair& sz, double def = 0)
//    {
//        /*this->*/resize(sz.first, sz.second, def);
//    }

//    // TODO: repair this method!
//    /// Returns the size of the matrix object.
//    SizePair getSize();


//    /// \returns an i-th row of the matrix
//    RowVector& getRow(size_t i);

//    // TODO: add const overload for the method getRow()


//    /// Creates an independant vector of size \a n and fills it in be \a def values.
//    static MatrixVector createVector(size_t n, double def);

//    // TODO: repair this method!
//    /// \returns an individual i-tj, j-th element of the matrix.
//    double getEl(size_t i, size_t j);

//    /// sets the i-th, j-th element of a matrix to the given value \a val
//    void setEl(size_t i, size_t j, double val);


//    // TODO: implement the following operator:
//    /// another approach for overloading the operator==
//    /// the lhv operand is now passed by used the this pointer
//    bool operator == (const Matrix& rhv) const;

//    // TODO: implement the following operator:
//    /// multiplies the matrix to a scalar
//    Matrix& operator *= (double rhv) ;

//    // TODO: implement the following operator:
//    /// return a matrix which is formed by multiplication of the
//    /// intital matrix to a scalar
//    Matrix operator * (double rhv) const;

//private:
//    VectorOfRows _matrix;           ///< Internal storage.

//}; // class Matrix


//// TODO: implement the following operator:
///// Declaration of the output operator for printing pairs.
//std::ostream& operator <<(std::ostream& s, const Matrix::SizePair& pr);

//// TODO: implement the following operator:
///// output a matrix to the given stream \a s
//std::ostream& operator<<(std::ostream& s, const Matrix& m);

//// TODO: implement the following operator:
///// output a single vector to the given stream \a s
//std::ostream& operator<<(std::ostream& s, const Matrix::MatrixVector& v);

////// / compares two matrices
////bool operator==(const Matrix& lhv, const Matrix& rhv);

//// TODO: implement the following operator:
//bool operator!=(const Matrix& lhv, const Matrix& rhv);



#endif // UDGRAPH_HPP
