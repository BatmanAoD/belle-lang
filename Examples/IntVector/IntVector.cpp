// The example C++ implementation of IntVector; this is what IntVector.class
// could "compile" into

#include <iterator>

class IntVector
{
  class Node
  {
      // Note that since in C++, the declaration order determines the
      // initialization order, the order here is different from the "##data"
      // section. Note that this will eventually cause a problem when Belle
      // supports multiple constructors with different member-initialization
      // orders.
      int[] data_segment_;
      int size_;
      Node* next_;

    public:
      Node() :
        data_segment_{new int[64]},
        size_{0},
        next_{nullptr}
      {}

      ~Node()
      {
        delete next_;
        delete[] data_segment_;
      }

      Node(const Node& rhs)
        data_segment_{new int[64]},
        size_{rhs.size_}
      {
        // This should be paralellizable.
        std::copy(std::begin(rhs.data_segment_),
                  std::end(rhs.data_segment_),
                  std::begin(data_segment_));
        if (rhs.next_ != nullptr)
        {
          next_{new Node(rhs.next_)};
        }
      }

      Node(Node&& rhs) :
        data_segment_{rhs.data_segment_},
        size_{rhs.size_},
        next_{rhs.next_}
      {
        rhs.data_segment_ = nullptr;
        rhs.next_ = nullptr;
      }

      //TODO add assignment operators: copy-and-swap and move

      // ...I don't actually know what the "standard" behavior here is. Copying
      // seems sane.
      int operator[](int i) const
      {
        return data_segment_[i];
      }

      // This could (/should?) return a pointer instead.
      int& operator[](int i)
      {
        return data_segment_[i];
      }

      Node* next()
      {
        return next_;
      }

      const Node* next() const
      {
        return next_;
      }

      void append(int n)
      {
        self[size_] = n;
        ++size;
      }

      void init_next()
      {
        next = new Node;
      }

      bool isFull() const
      {
        return size == 64;
      }
  }

    Node* head_;
    int first_;
    int last_;
    int size_;

  public:
    IntVector() :
      head{new Node},
      first_{-1},
      last_{0},
      size_{0}
    {}

    ~IntVector()
    {
      delete Node;
    }
    
    //TODO copy & move constructors & assignment operators

    // Does this even work?
    const int operator[](int i) const
    {
      return const_cast<IntVector>(*this)[i];
    }

    int& operator[](int i)
    {
      int tmp{i - start_};
      int seg_no{tmp / 64};
      int index{tmp % 64};
      Node* containing_seg{head_};
      while (0 < seg_no--)
      {
        containing_seg = containing_seg.next();
      }
      return (*containing_seg)[i];
    }

    void append(int n)
    {
      Node* last_seg{head_};
      while (! last_seg.isFull())
      {
        if (last_seg.next() == nullptr) last_seg.init_next();
        last_seg = last_seg.next();
      }
      last_seg.append(n);
    }
}
