#include <bits/stdc++.h>

#include <cstddef>
#include <cstdint>
#include <memory>

enum class Status : std::uint8_t { Declined = 0, Allocated = 1, Removed = 2 };
using BlockIndex = size_t;

class Block {
private:
  bool is_free_;
  size_t start_;
  size_t end_;
  BlockIndex index_;
  Block* prev_;
  Block* next_;

public:
  Block(Block* prev, Block* next, bool free, size_t start, size_t end, BlockIndex index)
      : is_free_(free), start_(start), end_(end), index_(index), prev_(prev), next_(next) {
    if (prev_ != nullptr) {
      prev_->SetNext(this);
    }
    if (next_ != nullptr) {
      next_->SetPrev(this);
    }
  }

  bool IsFree() const {
    return is_free_;
  }
  void SetFree(bool free) {
    is_free_ = free;
  }

  size_t GetStart() const {
    return start_;
  }
  void SetStart(size_t start) {
    start_ = start;
  }

  size_t GetEnd() const {
    return end_;
  }
  void SetEnd(size_t end) {
    end_ = end;
  }

  BlockIndex GetIndex() const {
    return index_;
  }
  void SetIndex(BlockIndex index) {
    index_ = index;
  }

  Block* GetPrev() const {
    return prev_;
  }
  void SetPrev(Block* prev) {
    prev_ = prev;
  }

  Block* GetNext() const {
    return next_;
  }
  void SetNext(Block* next) {
    next_ = next;
  }

  void Remove() const {
    if (prev_ != nullptr) {
      prev_->SetNext(next_);
    }
    if (next_ != nullptr) {
      next_->SetPrev(prev_);
    }
  }

  size_t Size() const {
    return end_ - start_;
  }
};

class Heap {
private:
  size_t current_request_{};
  size_t heap_size_{};
  std::vector<Status> request_status_;
  std::vector<std::unique_ptr<Block>> heap_;
  std::vector<std::unique_ptr<Block>> blocks_for_requests_;

public:
  Heap(size_t n, size_t num_requests) : heap_size_(1) {  // Initialize heap_size_ to 1
    request_status_.resize(num_requests);
    blocks_for_requests_.resize(num_requests);
    heap_.resize(num_requests);
    heap_[0] = std::make_unique<Block>(nullptr, nullptr, true, 0, n, 0);
  }

  void Allocate(size_t request_size) {
    if (heap_size_ == 0 || heap_[0]->Size() < request_size) {
      request_status_[current_request_++] = Status::Declined;
      std::cout << "-1" << '\n';
      return;
    }

    Block* root = heap_[0].get();

    request_status_[current_request_++] = Status::Allocated;
    blocks_for_requests_[current_request_ - 1] = std::make_unique<Block>(
        root->GetPrev(), root, false, root->GetStart(), root->GetStart() + request_size, SIZE_MAX
    );

    std::cout << root->GetStart() + 1 << '\n';

    root->SetStart(root->GetStart() + request_size);
    if (root->GetStart() < root->GetEnd()) {
      Heapify(root->GetIndex());
    } else {
      root->Remove();
      Pop();
      if (heap_size_ > 0) {
        heap_[heap_size_].reset();
      }
    }
  }

  void Free(size_t request_index) {
    request_index--;

    request_status_[current_request_++] = Status::Removed;

    if (request_status_[request_index] == Status::Declined) {
      return;
    }

    request_status_[request_index] = Status::Removed;

    auto& block_ptr = blocks_for_requests_[request_index];
    Block* block = block_ptr.get();
    Block* prev_block = block->GetPrev();
    Block* next_block = block->GetNext();

    if (((prev_block == nullptr) || !prev_block->IsFree()) &&
        ((next_block == nullptr) || !next_block->IsFree())) {
      block->SetFree(true);
      block->SetIndex(heap_size_);
      heap_[heap_size_] = std::move(block_ptr);
      Lift(heap_size_++);
      return;
    }
    if ((prev_block == nullptr) || !prev_block->IsFree()) {
      next_block->SetStart(block->GetStart());
      Lift(next_block->GetIndex());
      block->Remove();
      block_ptr.reset();
      return;
    }
    if ((next_block == nullptr) || !next_block->IsFree()) {
      prev_block->SetEnd(block->GetEnd());
      Lift(prev_block->GetIndex());
      block->Remove();
      block_ptr.reset();
      return;
    }

    prev_block->SetEnd(next_block->GetEnd());
    Lift(prev_block->GetIndex());  // Corrected from GetEnd() to GetIndex()

    block->Remove();
    block_ptr.reset();

    next_block->Remove();
    Remove(next_block->GetIndex());
    heap_[heap_size_].reset();
  }

  void Dispatch(int request) {
    if (request > 0) {
      Allocate(static_cast<size_t>(request));
    } else {
      Free(static_cast<size_t>(-request));
    }
  }

private:
  static BlockIndex GetParentIndex(BlockIndex index) {
    return (index - 1) / 2;
  }
  static BlockIndex GetLeftChildIndex(BlockIndex index) {
    return (2 * index) + 1;
  }
  static BlockIndex GetRightChildIndex(BlockIndex index) {
    return (2 * index) + 2;
  }

  void Swap(BlockIndex index1, BlockIndex index2) {
    std::swap(heap_[index1], heap_[index2]);
    heap_[index1]->SetIndex(index1);
    heap_[index2]->SetIndex(index2);
  }

  bool Better(BlockIndex index1, BlockIndex index2) const {
    return heap_[index1]->Size() > heap_[index2]->Size();
  }

  void Heapify(BlockIndex index) {
    while (true) {
      BlockIndex largest = index;
      BlockIndex left_child = GetLeftChildIndex(index);
      BlockIndex right_child = GetRightChildIndex(index);

      if ((left_child < heap_size_) && Better(left_child, largest)) {
        largest = left_child;
      }
      if ((right_child < heap_size_) && Better(right_child, largest)) {
        largest = right_child;
      }
      if (index == largest) {
        return;
      }

      Swap(index, largest);
      index = largest;
    }
  }

  void Pop() {
    if (heap_size_ == 0) {
      return;
    }
    heap_size_--;
    if (heap_size_ > 0) {
      Swap(0, heap_size_);
      Heapify(0);
    }
  }

  void Lift(BlockIndex index) {
    while (index != 0 && Better(index, GetParentIndex(index))) {
      BlockIndex parent = GetParentIndex(index);
      Swap(index, parent);
      index = parent;
    }
  }

  void Remove(BlockIndex index) {
    if (index >= heap_size_) {
      return;
    }
    Swap(index, heap_size_ - 1);
    heap_size_--;
    if (index < heap_size_) {
      Lift(index);
      Heapify(index);
    }
  }
};

int main() {
  size_t heap_size = 0;
  size_t number_of_mem_operations = 0;
  std::cin >> heap_size >> number_of_mem_operations;

  Heap heap(heap_size, number_of_mem_operations);

  int request = 0;
  for (size_t i = 0; i < number_of_mem_operations; i++) {
    std::cin >> request;
    heap.Dispatch(request);
  }

  return 0;
}
