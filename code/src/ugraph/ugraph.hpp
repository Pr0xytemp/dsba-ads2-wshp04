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
template <typename Vertex>
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
        Edge() : _s(Vertex()), _d(Vertex()) { }

        Edge(Vertex s, Vertex d)
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
        Vertex getS() const { return _s; }
        Vertex getD() const { return _d; }

    protected:
        /// Relatively speaking, source and destination nodes.
        Vertex _s, _d;

    }; // struct Edge

    /// Set of vertices.
    typedef std::set<Vertex> VerticesSet;

    /// Iterator type for vertices.
    typedef typename VerticesSet::iterator VertexIter;

    /// Pair of vertex iterators.
    typedef std::pair<VertexIter, VertexIter> VertexIterPair;

    // TODO: there need to define const iterator types.

    // Edge Iterators must be defined customly!


    /// \brief Adjacency list datatype, for storing adjacent vertices.
    ///
    /// Consists of exactly twice more elements than the number of edges in a
    /// graph (think of why).
    typedef std::multimap<Vertex, Vertex> AdjList;
    typedef typename AdjList::iterator AdjListIter;
    typedef typename AdjList::const_iterator AdjListCIter;


    /// \brief Custom definition of Edge Iterators.
    ///
    /// Iterator is an any object that behaves like an iterator. So, we need
    /// to implement all necessary features specific to the forward iterator.
    ///
    /// This class iterates a given range of edges in a multimap, considering
    /// only non-repeating edges.
    class EdgeIter {
    public:
        // Typically expected types
//        typedef Edge                        value_type;
//        typedef Edge&                       reference;
//        typedef Edge*                       pointer;
        typedef typename AdjListCIter::value_type  value_type;
        typedef typename AdjListCIter::reference   reference;
        typedef typename AdjListCIter::pointer     pointer;


        typedef std::forward_iterator_tag   iterator_category;
        typedef long                        difference_type;

        typedef EdgeIter Self;              ///< For convenience.
    public:
        // Minimum set of expected operations
        EdgeIter(AdjListCIter cur, AdjListCIter end)
            : _cur(cur), _end(end)
        {
            goUntilNextValid();
        }

        /// Prefix verion of ++: iterates first until the end.
        Self operator++(int junk)
        {
            ++_cur;
            goUntilNextValid();

            return *this;
        }

        // Postfix version of ++: creates a copy of this.
        Self operator++()
        {
            Self curCopy = *this;

            ++_cur;
            goUntilNextValid();

            return curCopy;
        }

        // this works perfectly and  could be cool, but breaks a bit general
        // (expected!) logic of iterators
        //Edge operator*() { return Edge(_cur->first, _cur->second); }

        reference operator*() { return *_cur; }
        pointer operator->() { return _cur; }

        bool operator==(const Self& rhv)
        {
            return (_cur == rhv._cur) && (_end == rhv._end);
        }

        bool operator!=(const Self& rhv)
        {
            return !(*this == rhv);
        }

    protected:
        /// Iterates the underlying mmap until finds a valid pair or reaches
        /// the end.
        void goUntilNextValid()
        {
            bool duplicate = false;             // indicates duplicates existance
            while (_cur != _end)
            {
                // self-loop case
                if(_cur->first == _cur->second)
                {
                    if(duplicate)
                    {
                        duplicate = false;
                        return;                 // valid second instance of s SL
                    }
                    duplicate = true;
                    ++_cur;
                    continue;
                }

                // “normal” case
                if(_cur->first < _cur->second)
                    return;                     // valid first part of edge

                // “collinear” case
                // _cur->first > _cur->second
                ++_cur;
                continue;
            }

            return;                             // endge empty
        }

    protected:
        AdjListCIter _cur;                   ///< Current iterator in the mmap.
        AdjListCIter _end;                   ///< End iterator in the mmap.
    }; // class EdgeIter



    /// Pair of edge iterators.
    typedef std::pair<EdgeIter, EdgeIter> EdgeIterPair;





public:
    // Graph structure modifying methods.

    /// Adds into this graph a new vertex \a v and returns it by value.
    Vertex addVertex(Vertex v)
    {
        _vertices.insert(v);
        return v;
    }

    /// \brief Adds into this graph a new edge made of two vertices.
    /// \return An object of type Edge with normalized positions of vertices.
    ///
    /// If a correponding edge {s, d} or equivalent {d, s} has been added earlier,
    /// do nothing else as just return an edge object.
    Edge addEdge(Vertex s, Vertex d)
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
    bool isEdgeExists(Vertex s, Vertex d) const
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

    bool isVertexExists(Vertex v) const
    {
        return (_vertices.find(v) != _vertices.end());
    }



public:
    // setters/getters
    size_t getVerticesNum() const { return _vertices.size(); }
    size_t getEdgesNum() const { return _edges.size() / 2; }


    /// Provides a collection of vertices as a semirange (pair of iterators).
    VertexIterPair getVertices() const
    {
        return {_vertices.begin(), _vertices.end()};
    }

    EdgeIterPair getEdges() const
    {
        EdgeIter beg(_edges.begin(), _edges.end());
        EdgeIter end(_edges.end(), _edges.end());

        return {beg, end};
    }


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
