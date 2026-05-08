#include "selection_sort.hpp"

#include <algorithm>

auto SelectionSort::step(std::vector<float>& elements) -> void
{
    if (done_) return;

    auto begin { elements.begin() + static_cast<long>(right_marker_) };
    auto min_it { std::min_element(begin, elements.end()) };

    compared_ = { right_marker_, static_cast<size_t>(std::distance(elements.begin(), min_it)) };
    std::iter_swap(begin, min_it);

    right_marker_++;
    if (right_marker_ >= elements.size()) done_ = true;
}

auto SelectionSort::reset() -> void
{
    right_marker_ = 0;
    done_ = false;
}

auto SelectionSort::get_compared() const -> std::pair<size_t, size_t>
{
    return compared_;
}

auto SelectionSort::get_name() const -> std::string_view
{
    return "Selection Sort";
}

auto SelectionSort::is_done() const -> bool
{
    return done_;
}
