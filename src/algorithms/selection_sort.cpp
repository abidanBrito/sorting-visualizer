#include "selection_sort.hpp"

#include <algorithm>

auto SelectionSort::step(std::vector<float>& elements) -> void
{
    if (is_done()) return;

    auto begin { elements.begin() + static_cast<long>(right_marker_) };
    auto min_it { std::min_element(begin, elements.end()) };

    last_min_idx_ = static_cast<size_t>(std::distance(elements.begin(), min_it));
    last_compared_ = { right_marker_, last_min_idx_ };
    last_was_swap_ = false;

    if (last_min_idx_ != right_marker_)
    {
        std::iter_swap(begin, min_it);
        last_was_swap_ = true;
    }

    right_marker_++;
    if (right_marker_ >= elements.size()) mark_done();
}

auto SelectionSort::reset() -> void
{
    reset_done();
    last_compared_.clear();
    last_was_swap_ = false;
    right_marker_ = 0;
}

auto SelectionSort::compared_indices() const -> std::set<size_t>
{
    if (is_done()) return {};
    return last_compared_;
}

auto SelectionSort::swapped_indices() const -> std::set<size_t>
{
    if (last_was_swap_) return { last_min_idx_ };
    return {};
}
