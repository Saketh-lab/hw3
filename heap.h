#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <cstddef>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   *
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  *
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   *
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   *
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   *
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /**
   * @brief Returns true if the heap is empty
   *
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   *
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> hv_;   // the heap itself, level order
  int kidss_;               // m (children per node)
  PComparator bttr_;     // bttr_(a,b) true => a goes above b

  void bUp(size_t pos);
  void sD(size_t pos);
};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
  : hv_(), kidss_(m < 2 ? 2 : m), bttr_(c)
{
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::bUp(size_t pos)
{
  while (pos > 0) {
    size_t par = (pos - 1) / kidss_;
    if (bttr_(hv_[pos], hv_[par])) {
      T tmp = hv_[pos];
      hv_[pos] = hv_[par];
      hv_[par] = tmp;
      pos = par;
    }
    else {
      break;
    }
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::sD(size_t pos)
{
  size_t n = hv_.size();
  while (true) {
    size_t first = pos * kidss_ + 1;
    if (first >= n) break;            // no children, we're a leaf

    // find the best child
    size_t best = first;
    for (int k = 1; k < kidss_; k++) {
      size_t c = first + k;
      if (c >= n) break;
      if (bttr_(hv_[c], hv_[best])) best = c;
    }

    if (bttr_(hv_[best], hv_[pos])) {
      T tmp = hv_[pos];
      hv_[pos] = hv_[best];
      hv_[best] = tmp;
      pos = best;
    }
    else {
      break;
    }
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  hv_.push_back(item);
  bUp(hv_.size() - 1);
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty()  const
{
  return hv_.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return hv_.size();
}

// parttt where i have to calll empt 
template <typename T, typename PComparator>
T const &   Heap<T,PComparator>::top() const
{

  if(empty()){
    throw   std::underflow_error("Heap is empty (top)");
  }
  
  return hv_[0];
}



template <typename  T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std:: underflow_error("Heap is empty (pop)");
  }
  hv_[0] = hv_.back();
  hv_.pop_back();
  if (!hv_.empty()) {
    sD(0);
  }
}

#endif