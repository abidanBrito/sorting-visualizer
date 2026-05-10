#include "bubble_sort.hpp"

#include <algorithm>

auto BubbleSort::step(std::vector<float>& elements) -> void
{
    if (is_done()) return;

    const size_t num_elements { elements.size() };
    last_compared_ = { cursor_, cursor_ + 1 };
    last_was_swap_ = false;

    if (elements[cursor_] > elements[cursor_ + 1])
    {
        std::swap(elements[cursor_], elements[cursor_ + 1]);
        last_was_swap_ = true;
    }
    cursor_++;

    if (cursor_ >= num_elements - 1 - sweep_count_)
    {
        cursor_ = 0;
        sweep_count_++;

        if (sweep_count_ >= num_elements - 1) mark_done();
    }
}

auto BubbleSort::reset() -> void
{
    reset_done();
    last_compared_.clear();
    last_was_swap_ = false;
    sweep_count_ = 0;
    cursor_ = 0;
}

auto BubbleSort::compared_indices() const -> std::set<size_t>
{
    if (is_done()) return {};
    return last_compared_;
}

auto BubbleSort::swapped_indices() const -> std::set<size_t>
{
    if (last_was_swap_) return last_compared_;
    return {};
}
