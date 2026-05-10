#include "bubble_sort.hpp"

#include <algorithm>

auto BubbleSort::step(std::vector<float>& elements) -> void
{
    if (done_) return;

    const size_t num_elements { elements.size() };
    compared_ = { cursor_, cursor_ + 1 };

    if (elements[cursor_] > elements[cursor_ + 1])
    {
        std::swap(elements[cursor_], elements[cursor_ + 1]);
    }
    cursor_++;

    if (cursor_ >= num_elements - 1 - sweep_count_)
    {
        cursor_ = 0;
        sweep_count_++;

        if (sweep_count_ >= num_elements - 1) done_ = true;
    }
}

auto BubbleSort::reset() -> void
{
    cursor_ = 0;
    sweep_count_ = 0;
    done_ = false;
    compared_ = { 0, 0 };
}

auto BubbleSort::get_compared() const -> std::pair<size_t, size_t>
{
    return compared_;
}

auto BubbleSort::get_name() const -> std::string_view
{
    return "Bubble Sort";
}

auto BubbleSort::is_done() const -> bool
{
    return done_;
}
