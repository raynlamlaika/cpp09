# C++ STL Containers: Choosing the Right Data Structure

## Introduction

When working with the C++ Standard Template Library (STL), you have many container choices, each representing a different data structure with unique performance characteristics and trade-offs.

Choosing the right container is often **more important than the implementation itself**. Even an optimal algorithm can become a bottleneck if it's paired with the wrong data structure.

In this article, we'll cover:

* Sequence Containers
* Ordered Associative Containers
* Unordered Associative Containers
* Container Adaptors
* Modern C++ Containers

For each category, we'll examine its internal implementation, time complexity, practical use cases, and real LeetCode examples to help you understand **when to use—and when to avoid—each container.**

---

# 1. Sequence Containers

Sequence containers store elements in a linear order.

## Complexity Comparison

| Container           | Underlying Structure    | Random Access | Insert Front | Insert Back | Insert Middle | Delete Front | Delete Back | Delete Middle | Search |
| ------------------- | ----------------------- | ------------- | ------------ | ----------- | ------------- | ------------ | ----------- | ------------- | ------ |
| `std::array`        | Fixed-size array        | O(1)          | N/A          | N/A         | N/A           | N/A          | N/A         | N/A           | O(n)   |
| `std::vector`       | Dynamic array           | O(1)          | O(n)         | O(1)*       | O(n)          | O(n)         | O(1)        | O(n)          | O(n)   |
| `std::deque`        | Segmented dynamic array | O(1)          | O(1)         | O(1)        | O(n)          | O(1)         | O(1)        | O(n)          | O(n)   |
| `std::list`         | Doubly linked list      | O(n)          | O(1)         | O(1)        | O(1)**        | O(1)         | O(1)        | O(1)**        | O(n)   |
| `std::forward_list` | Singly linked list      | O(n)          | O(1)         | O(n)        | O(1)**        | O(1)         | O(n)        | O(1)**        | O(n)   |

* Amortized constant time.

** Assuming an iterator to the insertion or deletion position is already available.

---

# Real-World Examples

Theory is useful, but seeing these containers solve actual problems makes their strengths much clearer.

---

## Example 1 — Linked Lists

**Problem:** LeetCode #61 — Rotate List

This problem manipulates node connections rather than array indices, making a linked list the natural choice.

### Optimized Solution

```cpp
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || k == 0)
            return head;

        ListNode* tail = head;
        int length = 1;

        while (tail->next) {
            tail = tail->next;
            length++;
        }

        tail->next = head;

        k %= length;
        int stepsToNewTail = length - k - 1;

        ListNode* newTail = head;
        while (stepsToNewTail--) {
            newTail = newTail->next;
        }

        ListNode* newHead = newTail->next;
        newTail->next = nullptr;

        return newHead;
    }
};
```

### Complexity Analysis

**Time Complexity:** **O(n)**

* One traversal to compute the length.
* One partial traversal to locate the new tail.

**Space Complexity:** **O(1)**

The rotation is performed entirely in place.

---

## Example 2 — Sliding Window Maximum

**Problem:** LeetCode #239 — Sliding Window Maximum

### A Naive Solution Using `std::vector`

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ans;

        for (int i = 0; i + k <= nums.size(); i++) {
            vector<int> subarr(nums.begin() + i,
                               nums.begin() + i + k);

            ans.push_back(*max_element(subarr.begin(), subarr.end()));
        }

        return ans;
    }
};
```

Although correct, this solution repeatedly scans each window to compute its maximum.

Since each of the **n − k + 1** windows requires an **O(k)** scan, the total complexity becomes:

**O(n × k)**

---

## Optimized Solution Using `std::deque`

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {

        vector<int> result;
        deque<int> dq;

        for (int i = 0; i < nums.size(); i++) {

            if (!dq.empty() && dq.front() < i - k + 1)
                dq.pop_front();

            while (!dq.empty() && nums[dq.back()] < nums[i])
                dq.pop_back();

            dq.push_back(i);

            if (i >= k - 1)
                result.push_back(nums[dq.front()]);
        }

        return result;
    }
};
```

### Why `std::deque`?

A `std::deque` supports constant-time insertion and removal at **both ends**:

* `push_front()`
* `push_back()`
* `pop_front()`
* `pop_back()`

The deque stores **indices** of useful elements while maintaining them in decreasing order.

Each element is inserted and removed **at most once**, making the overall algorithm:

* **Time Complexity:** O(n)
* **Space Complexity:** O(k)

---

# 2. Ordered Associative Containers

Ordered associative containers automatically keep elements sorted.

## Internal Implementation

Most implementations use **Red-Black Trees**, a type of self-balancing binary search tree.

As a result:

* Insertion: **O(log n)**
* Deletion: **O(log n)**
* Lookup: **O(log n)**

## Complexity Comparison

| Container       | Duplicate Keys | Ordered | Insert   | Delete   | Find     |
| --------------- | -------------- | ------- | -------- | -------- | -------- |
| `std::set`      | No             | Yes     | O(log n) | O(log n) | O(log n) |
| `std::multiset` | Yes            | Yes     | O(log n) | O(log n) | O(log n) |
| `std::map`      | Unique keys    | Yes     | O(log n) | O(log n) | O(log n) |
| `std::multimap` | Yes            | Yes     | O(log n) | O(log n) | O(log n) |

Use these containers whenever sorted traversal or ordered lookups are required.
## Probleme 49 leetcode
```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs)
    {
        vector<vector<string>> anw ; 
        if (strs.size() == 0)
            return anw;        

        
        unordered_map<string,  vector<int>> helper ;


        for (int i =  0 ; strs.size() > i ; i++)
        {
            // sort the string
            string h = strs[i];
            sort(h.begin(), h.end());
            helper[h].push_back(i);
        }
        // for (int i =  0 ; helper.size() > i ; i++)
        // {
        //     string h = strs[i];
        //     sort(h.begin(), h.end());
        //     vector<int>& i2 = helper[h];
        //     for (int  o : i2)
        //     {
        //         anw[i].push_back(strs[o]);
        //     }
        // }
        for (auto &entry : helper)
        {
            vector<string> group;

            for (int idx : entry.second)
            {
                group.push_back(strs[idx]);
            }

            anw.push_back(group);
        }
        return anw;
    }
};
```


## problem 414-easy
```cpp
class Solution {
public:
    int thirdMax(vector<int>& nums)
    {
        set<int>  holder;
        for (int i : nums)
        {
            auto [it, success] = holder.insert(i);
        }
        if (holder.size() >= 3)
        {
            auto it = holder.rbegin();
            std::advance(it, 2);
            return *it;
        }
        
        return *holder.rbegin();
    }
};
```
---

# 3. Unordered Associative Containers

If ordering isn't important, hash tables provide much faster average performance.

## Complexity Comparison

| Container                 | Duplicate Keys | Ordered | Insert | Delete | Find | Worst Case |
| ------------------------- | -------------- | ------- | ------ | ------ | ---- | ---------- |
| `std::unordered_set`      | No             | No      | O(1)   | O(1)   | O(1) | O(n)       |
| `std::unordered_multiset` | Yes            | No      | O(1)   | O(1)   | O(1) | O(n)       |
| `std::unordered_map`      | Unique keys    | No      | O(1)   | O(1)   | O(1) | O(n)       |
| `std::unordered_multimap` | Yes            | No      | O(1)   | O(1)   | O(1) | O(n)       |

Average performance is constant time, although excessive hash collisions can degrade operations to **O(n)**.

---

# 4. Container Adaptors

Container adaptors aren't new containers.

Instead, they provide specialized interfaces built on top of existing sequence containers.

| Adaptor               | Default Container | Push     | Pop      | Access |
| --------------------- | ----------------- | -------- | -------- | ------ |
| `std::stack`          | `deque`           | O(1)     | O(1)     | O(1)   |
| `std::queue`          | `deque`           | O(1)     | O(1)     | O(1)   |
| `std::priority_queue` | `vector` + heap   | O(log n) | O(log n) | O(1)   |

Choose an adaptor when you need a specific access pattern rather than a general-purpose container.

---

# 5. Modern C++ Containers

Recent C++ standards have introduced several new containers and container-like views designed for performance and safer abstractions.

| Container            | Standard | Description                                             |
| -------------------- | -------- | ------------------------------------------------------- |
| `std::span`          | C++20    | A lightweight, non-owning view over contiguous memory.  |
| `std::mdspan`        | C++23    | A multidimensional non-owning view.                     |
| `std::flat_map`      | C++23    | A sorted vector-based map optimized for cache locality. |
| `std::flat_set`      | C++23    | A sorted vector-based set.                              |
| `std::flat_multimap` | C++23    | A sorted vector-based multimap.                         |
| `std::flat_multiset` | C++23    | A sorted vector-based multiset.                         |

These additions focus on improving cache efficiency, reducing allocations, and providing safer interfaces.

---

# Final Thoughts

Big-O notation tells only part of the story.

The best container isn't always the one with the best asymptotic complexity—it's the one whose memory layout and access patterns match your workload.

Understanding trade-offs such as:

* Cache locality
* Memory fragmentation
* Allocation overhead
* Iterator stability
* Lookup speed
* Insertion cost

is what separates intermediate C++ programmers from experienced systems developers.

Keep this cheat sheet handy, experiment with the containers, and choose the one that fits your problem—not just your algorithm.

Happy coding!
