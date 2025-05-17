#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

enum class Status : uint8_t { Declined = 0, Allocated = 1, Removed = 2 };

class Block {
private:
  bool is_free_;
  size_t start_;
  size_t end_;
  Block* prev_;
  Block* next_;

public:
  Block(Block* prev, Block* next, bool free, size_t start, size_t end)
      : is_free_(free), start_(start), end_(end), prev_(prev), next_(next) {
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

  void Remove() {
    if (prev_ != nullptr) {
      prev_->SetNext(next_);
    }
    if (next_ != nullptr) {
      next_->SetPrev(prev_);
    }
    prev_ = nullptr;
    next_ = nullptr;
  }

  size_t Size() const {
    return end_ - start_;
  }
};

class Heap {
private:
  size_t current_request_ = 0;
  std::vector<Status> request_status_;
  std::vector<std::unique_ptr<Block>> blocks_for_requests_;
  std::vector<std::unique_ptr<Block>> all_blocks_;
  std::vector<Block*> free_blocks_;

public:
  Heap(size_t n, size_t num_requests) {
    request_status_.resize(num_requests, Status::Declined);
    blocks_for_requests_.resize(num_requests);
    all_blocks_.push_back(std::make_unique<Block>(nullptr, nullptr, true, 0, n));
    free_blocks_.push_back(all_blocks_.back().get());
  }

  void Allocate(size_t request_size) {
    if (free_blocks_.empty()) {
      request_status_[current_request_++] = Status::Declined;
      std::cout << "-1\n";
      return;
    }

    auto max_it =
        std::max_element(free_blocks_.begin(), free_blocks_.end(), [](Block* a, Block* b) {
          return a->Size() < b->Size();
        });
    Block* max_block = *max_it;

    if (max_block->Size() < request_size) {
      request_status_[current_request_++] = Status::Declined;
      std::cout << "-1\n";
      return;
    }

    size_t allocated_start = max_block->GetStart();
    size_t allocated_end = allocated_start + request_size;

    blocks_for_requests_[current_request_] = std::make_unique<Block>(
        max_block->GetPrev(), max_block, false, allocated_start, allocated_end
    );
    request_status_[current_request_] = Status::Allocated;
    std::cout << allocated_start + 1 << '\n';
    current_request_++;

    max_block->SetStart(allocated_end);
    if (max_block->Size() == 0) {
      free_blocks_.erase(max_it);
      max_block->Remove();
    }
  }

  void Free(size_t request_index) {
    request_index--;

    if (request_index >= current_request_ || request_status_[request_index] != Status::Allocated) {
      request_status_.push_back(Status::Removed);
      current_request_++;
      return;
    }

    Block* block = blocks_for_requests_[request_index].get();
    block->SetFree(true);

    Block* prev_block = block->GetPrev();
    Block* next_block = block->GetNext();

    bool prev_free = (prev_block != nullptr) && prev_block->IsFree();
    bool next_free = (next_block != nullptr) && next_block->IsFree();

    if (prev_free) {
      auto prev_it = std::find(free_blocks_.begin(), free_blocks_.end(), prev_block);
      if (prev_it != free_blocks_.end()) {
        free_blocks_.erase(prev_it);
      }
    }

    if (next_free) {
      auto next_it = std::find(free_blocks_.begin(), free_blocks_.end(), next_block);
      if (next_it != free_blocks_.end()) {
        free_blocks_.erase(next_it);
      }
    }

    if (prev_free) {
      block->SetStart(prev_block->GetStart());
      prev_block->Remove();
    }

    if (next_free) {
      block->SetEnd(next_block->GetEnd());
      next_block->Remove();
    }

    free_blocks_.push_back(block);
    request_status_[current_request_++] = Status::Removed;
  }

  void Dispatch(int request) {
    if (request > 0) {
      Allocate(static_cast<size_t>(request));
    } else {
      Free(static_cast<size_t>(-request));
    }
  }
};

int main() {
  size_t heap_size = 0;
  size_t num_requests = 0;
  std::cin >> heap_size >> num_requests;

  Heap heap(heap_size, num_requests);

  int request = 0;
  for (size_t i = 0; i < num_requests; ++i) {
    std::cin >> request;
    heap.Dispatch(request);
  }

  return 0;
}
