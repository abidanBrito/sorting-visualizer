#include "quick_sort.hpp"

#include <algorithm>

auto QuickSort::step(std::vector<float>& elements) -> void
{
    if (is_done()) return;

    const size_t n { elements.size() };

    if (!started_)
    {
        pending_ranges_.push({ .start = 0, .end = n });
        started_ = true;
    }

    last_swapped_.clear();

    while (!partitioning_)
    {
        if (pending_ranges_.empty())
        {
            for (size_t k {}; k < n; k++)
                sorted_.insert(k);

            mark_done();
            return;
        }

        const Range range { pending_ranges_.top() };
        pending_ranges_.pop();

        if (range.end - range.start <= 1)
        {
            if (range.end > range.start) sorted_.insert(range.start);
            continue;
        }

        partition_start_ = range.start;
        partition_end_ = range.end;

        pivot_ = elements[partition_end_ - 1];
        boundary_ = partition_start_;
        cursor_ = partition_start_;
        partitioning_ = true;
    }

    // One step of the Lomuto partition
    if (cursor_ < partition_end_ - 1)
    {
        last_compared_ = { cursor_, partition_end_ - 1 };
        if (elements[cursor_] < pivot_)
        {
            if (boundary_ != cursor_)
            {
                std::swap(elements[boundary_], elements[cursor_]);
                last_swapped_ = { boundary_, cursor_ };
            }
            boundary_++;
        }
        cursor_++;
    }
    else
    {
        // Place the pivot at its final position
        last_compared_ = { boundary_, partition_end_ - 1 };
        if (boundary_ != partition_end_ - 1)
        {
            std::swap(elements[boundary_], elements[partition_end_ - 1]);
            last_swapped_ = { boundary_, partition_end_ - 1 };
        }
        sorted_.insert(boundary_);

        if (boundary_ > partition_start_)
            pending_ranges_.push({ .start = partition_start_, .end = boundary_ });

        if (boundary_ + 1 < partition_end_)
            pending_ranges_.push({ .start = boundary_ + 1, .end = partition_end_ });

        partitioning_ = false;
    }
}

auto QuickSort::reset() -> void
{
    reset_done();
    last_compared_.clear();
    last_swapped_.clear();
    sorted_.clear();

    partition_start_ = 0;
    partition_end_ = 0;

    boundary_ = 0;
    cursor_ = 0;
    pivot_ = 0.0f;

    started_ = false;
    partitioning_ = false;

    while (!pending_ranges_.empty())
        pending_ranges_.pop();
}

auto QuickSort::compared_indices() const -> std::set<size_t>
{
    if (is_done()) return {};
    return last_compared_;
}

auto QuickSort::swapped_indices() const -> std::set<size_t>
{
    return last_swapped_;
}

auto QuickSort::sorted_indices() const -> std::set<size_t>
{
    return sorted_;
}
